#include <boost/filesystem.hpp>
#include <cstdlib>
#include <ctemplate/template.h>
#include <fstream>
#include <iostream>
#include <map>
#include <streambuf>
#include <sstream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

#include "string_util.hh"

namespace fs = boost::filesystem;

/** Config for generating the site, read in from config.yaml */
struct Config {
    std::vector<std::string> files_to_template;
    std::map<std::string, std::string> template_variables;

    static Config parse(fs::path);
};

Config Config::parse(fs::path config_path) {
    auto yaml_conf = YAML::LoadFile(config_path.string());
    auto conf = Config {
        .files_to_template = yaml_conf["files"].as<std::vector<std::string>>(),
        .template_variables = {},
    };
    YAML::Node vs = yaml_conf["variables"];
    if (vs.IsDefined() && vs.IsMap()) {
        for (auto it = vs.begin(); it != vs.end(); ++it) {
            conf.template_variables[it->first.as<std::string>()] = it->second.as<std::string>();;
        }
    }
    return conf;
}

/** File representing a page */
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
    return PageFile {
        .layout = yaml["layout"].as<std::string>(),
        .title  = yaml["title"].as<std::string>(),
        .body   = body.str(),
    };
}

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

    // Read includes into our template dictionary object
    for (auto const &dir_entry: fs::recursive_directory_iterator(site_dir / "includes")) {
        if (fs::is_regular_file(dir_entry)) {
            auto filename = std::string(dir_entry.path().filename().c_str());
            auto template_name = filename.substr(0, filename.find(".tpl.html"));

            std::ifstream t(dir_entry.path().c_str());
            std::string file_str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

            template_dict.SetValue("includes__" + template_name, file_str);
        }
    }

    // Read layout files into a map
    for (auto const &dir_entry: fs::recursive_directory_iterator(site_dir / "layouts")) {
        if (fs::is_regular_file(dir_entry)) {
            auto filename = dir_entry.path().filename().string();
            std::string template_name = filename.substr(0, filename.find(".tpl.html"));

            std::ifstream t(dir_entry.path().string());
            std::string file_str((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());

            layouts[template_name] = file_str;
        }
    }

    // Iterate over template files
    for (auto const &f: config.files_to_template) {
        auto file = site_dir / f;
        auto header = PageFile::parse(file);

        if (layouts.find(header.layout) == layouts.end()) {
            std::cerr << "Can not render to layout '" << header.layout << "' as it does not exist\n";
            return 1;
        }
        // render the page
        std::cout << "Rendering page: " << f << "\n";
        ctemplate::StringToTemplateCache("template_file", layouts[header.layout], ctemplate::DO_NOT_STRIP);
        template_dict.SetValue("content", header.body);
        template_dict.SetValue("title", header.title);
        std::string rendered_template;
        ctemplate::ExpandTemplate("template_file", ctemplate::DO_NOT_STRIP, &template_dict, &rendered_template);

        // second pass to set dynamic data within includes
        ctemplate::StringToTemplateCache("temp", rendered_template, ctemplate::DO_NOT_STRIP);
        rendered_template.clear();
        ctemplate::ExpandTemplate("temp", ctemplate::DO_NOT_STRIP, &template_dict, &rendered_template);
        ctemplate::mutable_default_template_cache()->ClearCache();

        // write out rendered page to disk
        std::ofstream rendered_file;
        rendered_file.open((build_dir / str_replace(f, ".tpl.html", ".html")).string());
        rendered_file << rendered_template;
        rendered_file.close();
    }
    // TODO: "layouts" folder, add meta-parser (YAML) to top of the other pages
    // std::string output;
    // ctemplate::ExpandTemplate((site_dir / "index.tpl.html").c_str(), ctemplate::DO_NOT_STRIP, &template_dict, &output);
    // std::ofstream index_out((build_dir / "index.html").c_str());
    // index_out << output;
    // index_out.close();
    return 0;
}