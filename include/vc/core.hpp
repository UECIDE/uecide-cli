#ifndef _VC_CORE_HPP
#define _VC_CORE_HPP

#include <Varcmd.hpp>

class vc_core : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
