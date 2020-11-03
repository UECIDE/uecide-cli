#ifndef _BUILTIN_COMMAND_BULLET3_HPP
#define _BUILTIN_COMMAND_BULLET3_HPP

#include <BuiltinCommand.hpp>

class bc_bullet3 : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
