#ifndef _VC_RANDOM_HPP
#define _VC_RANDOM_HPP

#include <Varcmd.hpp>

class vc_random : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
