#include <bc/cout.hpp>

bool bc_cout::main(Context *ctx, std::vector<std::string> args) {
    std::string out = "";
    for (std::string arg : args) {
        out += arg;
    }
    ctx->message(out);
    return true;
}
