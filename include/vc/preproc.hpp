#ifndef _VC_PREPROC_HPP
#define _VC_PREPROC_HPP

#include <Varcmd.hpp>

class vc_preproc : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
