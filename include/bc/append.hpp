#ifndef _BUILTIN_COMMAND_APPEND_HPP
#define _BUILTIN_COMMAND_APPEND_HPP

#include <BuiltinCommand.hpp>

class bc_append : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
