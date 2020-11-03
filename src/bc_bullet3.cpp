#include <bc/bullet3.hpp>

bool bc_bullet3::main(Context *ctx, std::vector<std::string> args) {
    std::string out = "";
    for (std::string arg : args) {
        if (out != "") {
            out += " ";
        }
        out += arg;
    }
    ctx->bullet3(out);
    return true;
}
