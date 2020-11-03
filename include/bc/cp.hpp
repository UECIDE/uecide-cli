#ifndef _BUILTIN_COMMAND_CP_HPP
#define _BUILTIN_COMMAND_CP_HPP

#include <BuiltinCommand.hpp>

class bc_cp : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
