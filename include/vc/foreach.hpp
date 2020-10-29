#ifndef _VC_FOREACH_HPP
#define _VC_FOREACH_HPP

#include <Varcmd.hpp>

class vc_foreach : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
