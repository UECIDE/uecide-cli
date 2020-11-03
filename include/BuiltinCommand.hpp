#ifndef _BUILTIN_COMMAND_HPP
#define _BUILTIN_COMMAND_HPP

#include <string>
#include <vector>
#include <Context.hpp>

class BuiltinCommand {
    public:
        virtual bool main(Context *ctx, std::vector<std::string> args) = 0;
};

#include <bc/append.hpp>
#include <bc/bullet2.hpp>
#include <bc/bullet3.hpp>
#include <bc/bullet.hpp>
#include <bc/cout.hpp>
#include <bc/cp.hpp>
#include <bc/delay.hpp>
#include <bc/dot.hpp>
#include <bc/echo.hpp>
#include <bc/end_buffer.hpp>
#include <bc/error.hpp>
#include <bc/exec.hpp>
#include <bc/foreach.hpp>
#include <bc/getauth.hpp>
#include <bc/gpio.hpp>
#include <bc/lock_port.hpp>
#include <bc/merge_hex.hpp>
#include <bc/port.hpp>
#include <bc/push.hpp>
#include <bc/scp.hpp>
#include <bc/set.hpp>
#include <bc/spin.hpp>
#include <bc/ssh.hpp>
#include <bc/start_buffer.hpp>
#include <bc/stdin.hpp>
#include <bc/unlock_port.hpp>
#include <bc/warning.hpp>
#include <bc/write.hpp>

#endif
