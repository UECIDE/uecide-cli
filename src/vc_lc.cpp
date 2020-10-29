#include <sstream>

#include <Varcmd.hpp>
#include <File.hpp>

std::string vc_lc::main(Context *ctx, std::vector<std::string> args) {
    std::string &text = args[0];

    for (int i = 0; i < text.length(); i++) {
        if ((text[i] >= 'A') && (text[i] <= 'Z')) {
            text[i] += ('a' - 'A');
        }
    }
    return text;
}

std::string vc_lc::usage() {
    return "${if:a=b,true,false}";
}
