#ifndef _VC_COMPILER_HPP
#define _VC_COMPILER_HPP

#include <Varcmd.hpp>

class vc_compiler : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
