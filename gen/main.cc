#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <streambuf>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <ctemplate/template.h>
#include <yaml-cpp/yaml.h>

#include "string_util.hh"

namespace fs = boost::filesystem;

/** Config for generating the site, read in from config.yaml */
struct Config {
    std::vector<std::string> files_to_template;
    std::map<std::string, std::string> template_variables;

    std::string versus_file;
    std::string versus_folder;
    std::map<std::string, std::string> versus;

    static Config parse(fs::path);
};

Config Config::parse(fs::path config_path) {
    auto yaml_conf = YAML::LoadFile(config_path.string());
    auto conf = Config {
        .files_to_template = yaml_conf["files"].as<std::vector<std::string>>(),
        .template_variables = {},
        .versus_file   = yaml_conf["versus_file"].as<std::string>(),
        .versus_folder = yaml_conf["versus_folder"].as<std::string>(),
        .versus = {},
    };
    auto vs = yaml_conf["variables"];
    if (vs.IsDefined() && vs.IsMap()) {
        for (auto it = vs.begin(); it != vs.end(); ++it) {
            conf.template_variables[it->first.as<std::string>()] = it->second.as<std::string>();;
        }
    }
    auto env = std::getenv("ENV");
    if (env != nullptr && std::string(env) == "production") {
        vs = yaml_conf["production"]["variables"];
        for (auto it = vs.begin(); it != vs.end(); ++it) {
            conf.template_variables[it->first.as<std::string>()] = it->second.as<std::string>();;
        }
    }
    auto versus = yaml_conf["versus"];
    if (versus.IsDefined() && versus.IsSequence()) {
        for (size_t i = 0; i < versus.size(); i++) {
            conf.versus[versus[i]["name"].as<std::string>()] = versus[i]["folder"].as<std::string>();
        }
    }
    return conf;
}

/** File representing a page (one that uses an include template) */
struct PageFile {
    std::string layout;
    std::string title;
    std::string body;

    static PageFile parse(fs::path);
};

PageFile PageFile::parse(fs::path file) {
    auto infile = std::ifstream(file.string());
    std::string yaml_input = "";
    std::string line;
    std::stringstream body;
    bool start = false;
    while (std::getline(infile, line)) {
        if (start) {
            yaml_input += line + "\n";
        }
        if (line.find("---") != std::string::npos && line.substr(0, 3) == "---") {
            start = !start;
            continue;
        }
        if (!start) {
            body << line << "\n";
        }
    }
    auto yaml = YAML::Load(yaml_input);
    auto pf = PageFile {
        .layout = yaml["layout"].as<std::string>(),
        .title  = "",
        .body   = body.str(),
    };
    if (yaml["title"]) pf.title = yaml["title"].as<std::string>();
    return pf;
}

std::string read_file(const fs::path &p) {
    std::ifstream t(p.string());
    return std::string((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
}
std::pair<std::string, size_t> read_file_lines(const fs::path &p) {
    std::ifstream t(p.string());
    return std::pair<std::string, size_t> {
        read_file(p),
        std::count(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>(), '\n'),
    };
}
std::string file_ext_to_prism_language(const fs::path &p) {
    auto file = p.filename().string();
    auto n = file.rfind('.');
    if (n != std::string::npos) {
        auto ext = file.substr(n + 1, file.length());
        if (ext == "cc") return "cpp";
        if (ext == "js") return "javascript";
        if (ext == "go") return "go";
        if (ext == "rb") return "ruby";
        if (ext == "scala") return "scala";
    }
    return "none";
}

/** Expand a string as a template */
std::string expand_string(std::string const &expand, ctemplate::TemplateDictionary const &dict)
{
    std::string out;
    ctemplate::StringToTemplateCache("__temp__expand_string", expand, ctemplate::DO_NOT_STRIP);
    ctemplate::ExpandTemplate("__temp__expand_string", ctemplate::DO_NOT_STRIP, &dict, &out);
    ctemplate::mutable_default_template_cache()->Delete("__temp__expand_string");
    return out;
}

/** Most of the magic happens here... enjoy */
int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "[Error]: Must specify a site directory\n";
        return 1;
    }
    auto site_dir = fs::path(std::string(argv[1]));
    auto build_dir = (site_dir / ".." / "build" / "site");

    auto config = Config::parse(site_dir / "config.yaml");

    ctemplate::TemplateDictionary template_dict("template_dict");
    for (auto const &pair: config.template_variables) {
        template_dict.SetValue(pair.first, pair.second);
    }
    std::map<std::string, std::string> layouts;

    // Read includes into our template dictionary AND template cache (depending on how they get used)
    for (auto const &dir_entry: fs::recursive_directory_iterator(site_dir / "includes")) {
        if (fs::is_regular_file(dir_entry)) {
            auto filename = std::string(dir_entry.path().filename().c_str());
            auto template_name = filename.substr(0, filename.find(".tpl.html"));

            auto file_str = read_file(dir_entry.path());
            template_dict.SetValue("includes__" + template_name, file_str);
            ctemplate::StringToTemplateCache("includes_" + template_name, file_str, ctemplate::DO_NOT_STRIP);
        }
    }

    // Read layout files into a map
    for (auto const &dir_entry: fs::recursive_directory_iterator(site_dir / "layouts")) {
        if (fs::is_regular_file(dir_entry)) {
            auto filename = dir_entry.path().filename().string();
            std::string template_name = filename.substr(0, filename.find(".tpl.html"));
            layouts[template_name] = read_file(dir_entry.path());
        }
    }

    // lambda for rendering files (used for simple files and versus files)
    auto render_file_with_layout = [&](std::string const &f) -> std::string {
        auto file = site_dir / f;
        auto header = PageFile::parse(file);

        if (layouts.find(header.layout) == layouts.end()) {
            std::cerr << "Can not render to layout '" << header.layout << "' as it does not exist\n";
            std::exit(1);
        }
        // render the page
        template_dict.SetValue("content", header.body);
        template_dict.SetValue("title", header.title);
        std::string rendered_template = expand_string(layouts[header.layout], template_dict);

        // second pass to set dynamic data within includes
        return expand_string(rendered_template, template_dict);
    };

    // Render all of the "versus" files
    std::map<std::string, std::map<std::string, std::string>> versus_links;
    for (auto const &pair: config.versus) {
        std::cout << "Generating " << pair.first << " versus\n";
        auto base_folder = site_dir / ".." / config.versus_folder / pair.second;
        for (auto const &dir_entry: fs::recursive_directory_iterator(base_folder)) {
            if (dir_entry.path().filename().string() == "versus.yaml") {
                ctemplate::TemplateDictionary dict("template_dict");
                auto vs_conf = YAML::LoadFile(dir_entry.path().string());
                std::cout << "\tAdding versus: " << vs_conf["name"].as<std::string>() << "\n";

                dict.SetValue("name", vs_conf["versus_lang"].as<std::string>());
                auto render_code_file = [&](std::string &&key) -> std::string {
                    std::string out;
                    for (size_t i = 0; i < vs_conf[key].size(); i++) {
                        ctemplate::TemplateDictionary block_dict("template_dict");
                        auto file_path = dir_entry.path().parent_path() / vs_conf[key][i].as<std::string>();
                        auto file = str_replace_all(
                            str_replace_all(read_file(file_path), "<", "&lt;"),
                            ">",
                            "&gt;");
                        block_dict.SetValue("code", file);
                        block_dict.SetValue("prism_language", file_ext_to_prism_language(file_path));
                        if (vs_conf[key].size() > 1) block_dict.SetValue("file_name", file_path.filename().string());
                        ctemplate::ExpandTemplate("includes_versus_block", ctemplate::DO_NOT_STRIP, &block_dict, &out);
                    }
                    return out;
                };
                dict.SetValue("cpp_code", render_code_file("cpp"));
                dict.SetValue("other_code", render_code_file("other"));
                dict.SetValue("versus_name", vs_conf["name"].as<std::string>());
                dict.SetValue("code_description", expand_string(
                    read_file((dir_entry.path().parent_path() / "description.html").string()),
                    template_dict));

                std::string rendered;
                ctemplate::ExpandTemplate("includes_versus", ctemplate::DO_NOT_STRIP, &dict, &rendered);
                template_dict.SetValue("versus_content", rendered);

                std::ofstream versus_file;
                versus_file.open((build_dir / "versus" / vs_conf["filename"].as<std::string>()).string());
                versus_file << render_file_with_layout(config.versus_file);
                versus_file.close();

                versus_links[pair.first][vs_conf["name"].as<std::string>()] = "versus/" + vs_conf["filename"].as<std::string>();
            }
        }
    }

    // Render versus links for main page (dynamically built from previous section)
    std::string groups;
    for (auto const &group: versus_links) {
        ctemplate::TemplateDictionary group_dict("groups");
        std::string links;
        for (auto const &link: group.second) {
            ctemplate::TemplateDictionary link_dict("links");
            link_dict.SetValue("name", link.first);
            link_dict.SetValue("link", link.second);
            ctemplate::ExpandTemplate("includes_versus_link_group_link", ctemplate::DO_NOT_STRIP, &link_dict, &links);
        }
        group_dict.SetValue("group_name", group.first);
        group_dict.SetValue("links", links);
        ctemplate::ExpandTemplate("includes_versus_link_group", ctemplate::DO_NOT_STRIP, &group_dict, &groups);
    }
    template_dict.SetValue("versus_link_groups", groups);

    // Render all of the basic files
    for (auto const &f: config.files_to_template) {
        // write out rendered page to disk
        std::ofstream rendered_file;
        rendered_file.open((build_dir / str_replace(f, ".tpl.html", ".html")).string());
        rendered_file << render_file_with_layout(f);
        rendered_file.close();
    }
    return 0;
}