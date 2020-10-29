#ifndef _VC_EXEC_HPP
#define _VC_EXEC_HPP

#include <Varcmd.hpp>

class vc_exec : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
