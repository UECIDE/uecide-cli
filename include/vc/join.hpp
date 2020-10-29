#ifndef _VC_JOIN_HPP
#define _VC_JOIN_HPP

#include <Varcmd.hpp>

class vc_join : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
