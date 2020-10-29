#ifndef _VC_FILES_HPP
#define _VC_FILES_HPP

#include <Varcmd.hpp>

class vc_files : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
