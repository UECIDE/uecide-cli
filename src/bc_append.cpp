#include <fstream>

#include <File.hpp>
#include <bc/append.hpp>

bool bc_append::main(Context *ctx, std::vector<std::string> args) {
    File f(args[0]);

    std::ofstream file(f.getAbsolutePath());
    if (file.is_open()) {
        for (int i = 1; i < args.size(); i++) {
            file << args[i] << std::endl;
        }
        file.close();
        return true;
    }

    ctx->error("Unable to open " + f.getAbsolutePath());
    
    return false;
}
