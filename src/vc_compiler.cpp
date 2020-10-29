#include <Varcmd.hpp>
#include <File.hpp>

std::string vc_compiler::main(Context *ctx, std::vector<std::string> args) {
    if (args[0] == "root") {
        return ctx->getBoard().getFolder().getAbsolutePath();
    }
    return ctx->getBoard().get(args[0]);
}

std::string vc_compiler::usage() {
    return "${compiler:key}";
}
