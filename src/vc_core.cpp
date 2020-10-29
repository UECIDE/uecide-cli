#include <Varcmd.hpp>
#include <File.hpp>

std::string vc_core::main(Context *ctx, std::vector<std::string> args) {

    Core core;
    std::string key;

    if (args.size() == 1) {
        core = ctx->getCore();
        key = args[0];
    } else {
        core = Core::findByName(args[0]);
        if (core == noCore) {
            return "OBJECT_NOT_FOUND";
        }
        key = args[1];
    }

    if (args[0] == "root") {
        return core.getFolder().getAbsolutePath();
    }
    return core.getProperties().getPlatformSpecific(key);
}

std::string vc_core::usage() {
    return "${core:key}";
}
