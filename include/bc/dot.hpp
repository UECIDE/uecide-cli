#ifndef _BUILTIN_COMMAND_DOT_HPP
#define _BUILTIN_COMMAND_DOT_HPP

#include <BuiltinCommand.hpp>

class bc_dot : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
