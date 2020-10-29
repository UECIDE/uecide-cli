#include <sstream>
#include <Varcmd.hpp>
#include <File.hpp>

std::string vc_onefile::main(Context *ctx, std::vector<std::string> args) {

    for (std::string filename : args) {
        File f(filename);
        if (f.exists()) {
            return f.getAbsolutePath();
        }
    }

    return "FILE_NOT_FOUND";
}

std::string vc_onefile::usage() {
    return "${onefile:file1[,file2[...]]";
}
