#ifndef _BUILTIN_COMMAND_ECHO_HPP
#define _BUILTIN_COMMAND_ECHO_HPP

#include <BuiltinCommand.hpp>

class bc_echo : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
