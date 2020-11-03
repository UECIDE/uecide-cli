#ifndef _BUILTIN_COMMAND_WARNING_HPP
#define _BUILTIN_COMMAND_WARNING_HPP

#include <BuiltinCommand.hpp>

class bc_warning : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
