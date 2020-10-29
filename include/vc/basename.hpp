#ifndef _VC_BASENAME_HPP
#define _VC_BASENAME_HPP

#include <Varcmd.hpp>

class vc_basename : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
