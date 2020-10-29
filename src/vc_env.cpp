#include <Varcmd.hpp>
#include <File.hpp>
#include <stdlib.h>

std::string vc_env::main(Context *ctx, std::vector<std::string> args) {
    char *val = getenv(args[0].c_str());
    std::string envval = val;
    return envval;
}

std::string vc_env::usage() {
    return "${env:key}";
}
