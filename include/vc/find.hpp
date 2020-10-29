#ifndef _VC_FIND_HPP
#define _VC_FIND_HPP

#include <Varcmd.hpp>

class vc_find : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
