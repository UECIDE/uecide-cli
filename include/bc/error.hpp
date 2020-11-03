#ifndef _BUILTIN_COMMAND_ERROR_HPP
#define _BUILTIN_COMMAND_ERROR_HPP

#include <BuiltinCommand.hpp>

class bc_error : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
