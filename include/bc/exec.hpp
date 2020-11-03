#ifndef _BUILTIN_COMMAND_EXEC_HPP
#define _BUILTIN_COMMAND_EXEC_HPP

#include <BuiltinCommand.hpp>

class bc_exec : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
