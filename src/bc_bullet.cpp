#include <bc/bullet.hpp>

bool bc_bullet::main(Context *ctx, std::vector<std::string> args) {
    std::string out = "";
    for (std::string arg : args) {
        if (out != "") {
            out += " ";
        }
        out += arg;
    }
    ctx->bullet(out);
    return true;
}
