#ifndef _VC_CSV_HPP
#define _VC_CSV_HPP

#include <Varcmd.hpp>

class vc_csv : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
