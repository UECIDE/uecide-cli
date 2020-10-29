#ifndef _VC_EXISTS_HPP
#define _VC_EXISTS_HPP

#include <Varcmd.hpp>

class vc_exists : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
