#include <sstream>

#include <Varcmd.hpp>
#include <File.hpp>
#include <Trim.hpp>

std::string vc_find::main(Context *ctx, std::vector<std::string> args) {
    if (args.size() != 2) {
        return "SYNTAX_ERROR";
    }

    std::string &filename = args[0];
    std::string &dirlist = args[1];

    int end = dirlist.find("::");
    int start = 0;
    while (end != std::string::npos) {
        std::string dir = dirlist.substr(start, end - start);
        trim(dir);
        File f(dir, filename);
        if (f.exists()) {
            return f.getAbsolutePath();
        }
        start = end + 2;
        end = dirlist.find("::");
    }
    std::string dir = dirlist.substr(start);
    trim(dir);
    File f(dir);
    if (f.exists()) {
        return f.getAbsolutePath();
    }

    return "FILE_NOT_FOUND";
}

std::string vc_find::usage() {
    return "${find:filename,dir[::dir[::dir[...]]]}";
}
