#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <bc/cp.hpp>

bool bc_cp::main(Context *ctx, std::vector<std::string> args) {

    if (args.size() != 2) return false;

    std::string from = args[0];
    std::string to = args[1];

    if (access(from.c_str(), R_OK) != 0) return false;
    if (access(to.c_str(), W_OK) != 0) return false;

    int fdin = open(from.c_str(), O_RDONLY);
    int fdout = open(to.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fdin < 0) return false;
    if (fdout < 0) return false;

    uint8_t buf[1024];

    int n = 0;

    while ((n = read(fdin, buf, 1024)) > 0) {
        if (write(fdout, buf, n) <= 0) {
            close(fdin);
            close(fdout);
            return false;
        }
    }
    close(fdin);
    close(fdout);

    return true;
}
