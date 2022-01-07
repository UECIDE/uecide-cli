#include <unistd.h>
#include <bc/delay.hpp>

bool bc_delay::main(Context *ctx, std::vector<std::string> args) {

    if (args.size() != 1) return false;

    unsigned long ms = strtoul(args[0].c_str(), NULL, 10);

    usleep(ms * 1000);

    return true;
}
