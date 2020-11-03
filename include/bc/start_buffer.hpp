#ifndef _BUILTIN_COMMAND_START_BUFFER_HPP
#define _BUILTIN_COMMAND_START_BUFFER_HPP

#include <BuiltinCommand.hpp>

class bc_start_buffer : public BuiltinCommand {
    public:
        bool main(Context *ctx, std::vector<std::string> args);
};

#endif
