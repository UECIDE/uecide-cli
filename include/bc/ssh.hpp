#ifndef _BUILTIN_COMMAND_SSH_HPP
#define _BUILTIN_COMMAND_SSH_HPP

#include <BuiltinCommand.hpp>

class bc_ssh : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
