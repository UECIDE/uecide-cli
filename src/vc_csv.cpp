#include <fstream>
#include <algorithm>
#include <sstream>

#include <Varcmd.hpp>
#include <File.hpp>
#include <Trim.hpp>

std::string vc_csv::main(Context *ctx, std::vector<std::string> args) {
    if (args.size() != 3) {
        return "SYNTAX_ERROR";
    }

    File f(args[0]);

    if (!f.exists()) {
        ctx->error("File " + args[0] + " not found");
        return "FILE_NOT_FOUND";
    }

    int colno = std::stoi(args[2], nullptr, 0);

    std::ifstream file(f.getAbsolutePath());
    if (file.is_open()) {
        std::string out = "KEY_NOT_FOUND";
        while (!file.eof()) {
            std::string in; 
            std::getline(file, in, '\n');
            trim(in);

            if (in.length() == 0) continue;
            if (in[0] == ';') continue;
            if (in[0] == '#') continue;

            std::vector<std::string> cols;
            std::istringstream iss(in);
            std::string col;
            while (std::getline(iss, col, ',')) {
                cols.push_back(col);
            }   


            if (cols[0] == args[1]) {
                out = cols[colno];
                break;
            }
        }
        file.close();
        return out;
    }
    return "FILE_OPEN_ERROR";
}

std::string vc_csv::usage() {
    return "${csv:file,col0,col}";
}
