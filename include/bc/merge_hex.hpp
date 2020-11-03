#ifndef _BUILTIN_COMMAND_MERGE_HEX_HPP
#define _BUILTIN_COMMAND_MERGE_HEX_HPP

#include <BuiltinCommand.hpp>

class bc_merge_hex : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
