#ifndef _BUILTIN_COMMAND_PORT_HPP
#define _BUILTIN_COMMAND_PORT_HPP

#include <BuiltinCommand.hpp>

class bc_port : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
