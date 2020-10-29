#ifndef _VC_IF_HPP
#define _VC_IF_HPP

#include <Varcmd.hpp>

class vc_if : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
