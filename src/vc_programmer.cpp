#include <Varcmd.hpp>

std::string vc_programmer::main(Context *ctx, std::vector<std::string> args) {

    Programmer programmer;
    std::string key;

    if (args.size() == 1) {
        programmer = ctx->getProgrammer();
        key = args[0];
    } else {
        programmer = Programmer::findByName(args[0]);
       if (programmer == noProgrammer) {
             return "OBJECT_NOT_FOUND";
        }
        key = args[1];
    }

    if (args[0] == "root") {
        return programmer.getFolder().getAbsolutePath();
    }
    return programmer.getProperties().getPlatformSpecific(key);
}

std::string vc_programmer::usage() {
    return "${programmer:key}";
}
