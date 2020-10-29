#include <Varcmd.hpp>
#include <File.hpp>

std::string vc_char::main(Context *ctx, std::vector<std::string> args) {
    int val = std::stoi(args[0], nullptr, 0);
    std::string out = "0";
    out[0] = char(val);
    return out;
}

std::string vc_char::usage() {
    return "${char:num}";
}
