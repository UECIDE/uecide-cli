#include <Varcmd.hpp>
#include <File.hpp>
#include <stdlib.h>

std::string vc_exec::main(Context *ctx, std::vector<std::string> args) {

    if (ctx->executeKey(args[0])) {
        return "true";
    } else {
        return "false";
    }
}

std::string vc_exec::usage() {
    return "${exec:key}";
}
