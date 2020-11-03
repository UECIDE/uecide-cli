#ifndef _BUILTIN_COMMAND_SCP_HPP
#define _BUILTIN_COMMAND_SCP_HPP

#include <BuiltinCommand.hpp>

class bc_scp : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
