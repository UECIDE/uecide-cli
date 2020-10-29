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

std::string vc_foreach::main(Context *ctx, std::vector<std::string> args) {
    if (args.size() != 2) {
        return "SYNTAX_ERROR";
    }

    std::string &format = args[0];
    std::string &list = args[1];

    int end = list.find("::");
    int start = 0;
    bool first = true;
    std::string out;
    while (end != std::string::npos) {
        std::string item = list.substr(start, end - start);

        std::string formatted = format;
        replace(formatted, "%0", item);

        if (first) {
            first = false;
        } else {
            out += "::";
        }

        out += formatted;

        start = end + 2;
        end = list.find("::");
    }
    std::string item = list.substr(start);
    std::string formatted = format;
    replace(formatted, "%0", item);

    if (first) {
        first = false;
    } else {
        out += "::";
    }

    return out;
}

std::string vc_foreach::usage() {
    return "${find:filename,dir[::dir[::dir[...]]]}";
}
