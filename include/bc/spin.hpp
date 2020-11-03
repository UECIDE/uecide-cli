#ifndef _BUILTIN_COMMAND_SPIN_HPP
#define _BUILTIN_COMMAND_SPIN_HPP

#include <BuiltinCommand.hpp>

class bc_spin : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
