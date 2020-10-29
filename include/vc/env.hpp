#ifndef _VC_ENV_HPP
#define _VC_ENV_HPP

#include <Varcmd.hpp>

class vc_env : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
