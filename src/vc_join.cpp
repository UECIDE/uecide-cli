#include <sstream>

#include <Varcmd.hpp>
#include <File.hpp>

static inline bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

std::string vc_join::main(Context *ctx, std::vector<std::string> args) {
    if (args.size() != 2) {
        return "SYNTAX_ERROR";
    }

    std::string &list = args[0];
    std::string &joiner = args[1];

    if (joiner == "::") {
        return "INFINITE_RECURSION";
    }

    while (replace(list, "::", joiner));
    return list;

}

std::string vc_join::usage() {
    return "${find:item[::item[...]],joiner}";
}
