#ifndef _VC_BOARD_HPP
#define _VC_BOARD_HPP

#include <Varcmd.hpp>

class vc_board : public Varcmd {
    public:
        std::string main(Context *ctx, std::vector<std::string> args);
        std::string usage();
};

#endif
