#ifndef _BUILTIN_COMMAND_BULLET2_HPP
#define _BUILTIN_COMMAND_BULLET2_HPP

#include <BuiltinCommand.hpp>

class bc_bullet2 : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
