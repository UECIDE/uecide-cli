#ifndef _BUILTIN_COMMAND_COUT_HPP
#define _BUILTIN_COMMAND_COUT_HPP

#include <BuiltinCommand.hpp>

class bc_cout : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
