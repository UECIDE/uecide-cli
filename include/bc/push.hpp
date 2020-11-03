#ifndef _BUILTIN_COMMAND_PUSH_HPP
#define _BUILTIN_COMMAND_PUSH_HPP

#include <BuiltinCommand.hpp>

class bc_push : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
