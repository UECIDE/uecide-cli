#ifndef _BUILTIN_COMMAND_WRITE_HPP
#define _BUILTIN_COMMAND_WRITE_HPP

#include <BuiltinCommand.hpp>

class bc_write : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
