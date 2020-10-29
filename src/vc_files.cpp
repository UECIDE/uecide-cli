#include <sstream>

#include <Varcmd.hpp>
#include <File.hpp>

std::string vc_files::main(Context *ctx, std::vector<std::string> args) {
    File f(args[0]);
    if (!f.exists()) {
        return "FILE_NOT_FOUND";
    } 

    if (!f.isDirectory()) {
        return "NOT_DIRECTORY";
    }

    std::vector<File> files = f.listFiles();
    std::stringstream ss;
    bool first = true;
    std::string ext = "";
    if (args.size() == 2) {
        ext = args[1];
    }

    for (File file : files) {

        if (file.isHidden()) continue;

        if (ext != "") {
            std::string filename = file.getName();
            if (filename.length() < ext.length()) continue; // Too short to have the extension
            int epos = filename.rfind(".");
            if (epos == std::string::npos) continue; // No extension
            std::string fex = filename.substr(epos + 1);
            if (fex != ext) continue;
        }

        if (first) {
            first = false;
        } else {
            ss << ",";
        }
        ss << file.getAbsolutePath();
    }
    return ss.str();
}

std::string vc_files::usage() {
    return "${files:dir[,ext]}";
}
