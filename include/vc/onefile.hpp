#ifndef _VC_ONEFILE_HPP
#define _VC_ONEFILE_HPP

#include <Varcmd.hpp>

class vc_onefile : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
