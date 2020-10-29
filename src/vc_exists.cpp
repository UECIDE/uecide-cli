#include <Varcmd.hpp>
#include <File.hpp>

std::string vc_exists::main(Context *ctx, std::vector<std::string> args) {
    File f(args[0]);
    if (f.exists()) {
        return "YES";
    } else {
        return "NO";
    }
}

std::string vc_exists::usage() {
    return "${exists:file}";
}
