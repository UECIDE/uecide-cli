#include <vc/basename.hpp>

#include <Varcmd.hpp>
#include <File.hpp>

std::string vc_basename::main(Context *ctx, std::vector<std::string> args) {

    if (args.size() == 1) {
        File f(args[0]);
        return f.getName();
    }

    if (args.size() == 2) {
        File f(args[0]);
        std::string name = f.getName();
        int epos = name.rfind(".");
        if (epos != std::string::npos) {
            std::string fn = name.substr(0, epos);
            std::string fnext = name.substr(epos + 1);
            if (fnext == args[1]) {
                name = fn;
            }
        }
        return name;
    }

    return "SYNTAX_ERROR";
}

std::string vc_basename::usage() {
    return "${basename:filename[,ext]}";
}
