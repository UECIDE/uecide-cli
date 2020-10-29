#ifndef _VC_LC_HPP
#define _VC_LC_HPP

#include <Varcmd.hpp>

class vc_lc : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
