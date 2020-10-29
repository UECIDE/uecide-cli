#include <sstream>

#include <Varcmd.hpp>
#include <File.hpp>
#include <Trim.hpp>

static inline bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

std::string vc_if::main(Context *ctx, std::vector<std::string> args) {
    if (args.size() != 3) {
        return "SYNTAX_ERROR";
    }

    std::string &condition = args[0];
    std::string &t = args[1];
    std::string &f = args[2];

    std::istringstream iss(condition);
    std::string a;
    std::string b;
    
    if (!std::getline(iss, a, '=')) return "SYNTAX_ERROR";
    if (!std::getline(iss, b, '=')) return "SYNTAX_ERROR";

    if (a == b) return t;
    return f;
}

std::string vc_if::usage() {
    return "${if:a=b,true,false}";
}
