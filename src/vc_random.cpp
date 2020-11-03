#include <Varcmd.hpp>

std::string vc_random::main(Context *ctx, std::vector<std::string> args) {
    if (args.size() != 2) {
        return "SYNTAX_ERROR";
    }
    int low = std::stoi(args[0]);
    int high = std::stoi(args[1]);

    int diff = high - low;
    int r = (rand() % diff) + low;
    return std::to_string(r);
}

std::string vc_random::usage() {
    return "${random:low,high}";
}
