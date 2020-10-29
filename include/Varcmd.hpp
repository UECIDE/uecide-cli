#ifndef _VARCMD_HPP
#define _VARCMD_HPP

#include <string>
#include <vector>
#include <Context.hpp>

class Varcmd {
    public:
        virtual std::string main(Context *ctx, std::vector<std::string> args) = 0;
        virtual std::string usage() = 0;
};

#include <vc/basename.hpp>
#include <vc/board.hpp>
#include <vc/char.hpp>
#include <vc/compiler.hpp>
#include <vc/core.hpp>
#include <vc/csv.hpp>
#include <vc/env.hpp>
#include <vc/exec.hpp>
#include <vc/exists.hpp>
#include <vc/files.hpp>
#include <vc/find.hpp>
#include <vc/foreach.hpp>
#include <vc/if.hpp>
#include <vc/join.hpp>
#include <vc/lc.hpp>
#include <vc/math.hpp>
#include <vc/onefile.hpp>

#endif
