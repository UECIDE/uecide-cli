#ifndef _VC_MATH_HPP
#define _VC_MATH_HPP

#include <Varcmd.hpp>

class vc_math : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
