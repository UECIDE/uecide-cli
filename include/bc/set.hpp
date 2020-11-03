#ifndef _BUILTIN_COMMAND_SET_HPP
#define _BUILTIN_COMMAND_SET_HPP

#include <BuiltinCommand.hpp>

class bc_set : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
