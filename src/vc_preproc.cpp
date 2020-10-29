#include <sstream>
#include <fstream>
#include <streambuf>
#include <Varcmd.hpp>
#include <File.hpp>

std::string vc_preproc::main(Context *ctx, std::vector<std::string> args) {

    File f(args[0]);

    if (!f.exists()) {
        return "FILE_NOT_FOUND";
    }

    ctx->snapshot();

    bool skip = true;
    for (std::string kv : args) {
        if (skip) {
            skip = false;
            continue;
        }

        std::istringstream iss(kv);
        std::string k;
        std::string v;
        std::getline(iss, k, '=');
        std::getline(iss, v, '=');
        ctx->set(k, v);
    }

    std::ifstream file(f.getAbsolutePath());

    std::string str((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());

    file.close();
    str = ctx->parseString(str);
    ctx->restore();


    File tfile = File::createTempFile("vc-preproc", "txt");
    std::ofstream tempfile(tfile.getAbsolutePath());
    tempfile << str;
    tempfile.close();
    return tfile.getAbsolutePath();
}

std::string vc_preproc::usage() {
    return "${preproc:file1[,key=val[,key=val]]}";
}
