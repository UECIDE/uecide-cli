#ifndef _BUILTIN_COMMAND_FOREACH_HPP
#define _BUILTIN_COMMAND_FOREACH_HPP

#include <BuiltinCommand.hpp>

class bc_foreach : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
