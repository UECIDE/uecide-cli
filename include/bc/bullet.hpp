#ifndef _BUILTIN_COMMAND_BULLET_HPP
#define _BUILTIN_COMMAND_BULLET_HPP

#include <BuiltinCommand.hpp>

class bc_bullet : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
