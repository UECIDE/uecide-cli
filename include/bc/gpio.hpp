#ifndef _BUILTIN_COMMAND_GPIO_HPP
#define _BUILTIN_COMMAND_GPIO_HPP

#include <BuiltinCommand.hpp>

class bc_gpio : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
