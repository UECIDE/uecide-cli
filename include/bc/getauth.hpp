#ifndef _BUILTIN_COMMAND_GETAUTH_HPP
#define _BUILTIN_COMMAND_GETAUTH_HPP

#include <BuiltinCommand.hpp>

class bc_getauth : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
