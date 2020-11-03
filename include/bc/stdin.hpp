#ifndef _BUILTIN_COMMAND_STDIN_HPP
#define _BUILTIN_COMMAND_STDIN_HPP

#include <BuiltinCommand.hpp>

class bc_stdin : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
