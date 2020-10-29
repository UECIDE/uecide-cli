#include <Varcmd.hpp>

std::string vc_compiler::main(Context *ctx, std::vector<std::string> args) {
    Compiler compiler;
    std::string key;

    if (args.size() == 1) {
        compiler = ctx->getCompiler();
        key = args[0];
    } else {
        compiler = Compiler::findByName(args[0]);
        if (compiler == noCompiler) {
            return "OBJECT_NOT_FOUND";
        }
        key = args[1];
    }

    if (args[0] == "root") {
        return compiler.getFolder().getAbsolutePath();
    }
    return compiler.getProperties().getPlatformSpecific(key);

}

std::string vc_compiler::usage() {
    return "${compiler:key}";
}
