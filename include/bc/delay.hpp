#ifndef _BUILTIN_COMMAND_DELAY_HPP
#define _BUILTIN_COMMAND_DELAY_HPP

#include <BuiltinCommand.hpp>

class bc_delay : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
