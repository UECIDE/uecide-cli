#ifndef _VC_PROGRAMMER_HPP
#define _VC_PROGRAMMER_HPP

#include <Varcmd.hpp>

class vc_programmer : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
