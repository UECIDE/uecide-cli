#ifndef _VC_CHAR_HPP
#define _VC_CHAR_HPP

#include <Varcmd.hpp>

class vc_char : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
