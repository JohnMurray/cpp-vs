#include <boost/filesystem.hpp>
#include <cstdlib>
#include <ctemplate/template.h>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

namespace fs = boost::filesystem;

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "[Error]: Must specify a site directory\n";
        return 1;
    }
    auto site_dir = fs::path(std::string(argv[1]));
    auto build_dir = (site_dir / ".." / "build" / "site");

    ctemplate::TemplateDictionary template_dict("template_dict");

    // Read includes into our template dictionary object
    for (auto const &dir_entry: fs::recursive_directory_iterator(site_dir / "includes")) {
        if (fs::is_regular_file(dir_entry)) {
            auto filename = std::string(dir_entry.path().filename().c_str());
            auto template_name = filename.substr(0, filename.find(".tpl.html"));

            std::ifstream t(dir_entry.path().c_str());
            std::string file_str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

            template_dict.SetValue(template_name, file_str);
        }
    }

    std::string output;
    ctemplate::ExpandTemplate((site_dir / "index.tpl.html").c_str(), ctemplate::DO_NOT_STRIP, &template_dict, &output);
    std::ofstream index_out((build_dir / "index.html").c_str());
    index_out << output;
    index_out.close();
    return 0;
}