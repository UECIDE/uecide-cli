#include <bc/bullet2.hpp>

bool bc_bullet2::main(Context *ctx, std::vector<std::string> args) {
    std::string out = "";
    for (std::string arg : args) {
        if (out != "") {
            out += " ";
        }
        out += arg;
    }
    ctx->bullet2(out);
    return true;
}
