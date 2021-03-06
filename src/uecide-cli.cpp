#include <iostream>
#include <string>
#include <sstream>

#include <getopt.h>

#include <File.hpp>
#include <PropertyFile.hpp>
#include <Board.hpp>
#include <Core.hpp>
#include <Compiler.hpp>
#include <Programmer.hpp>
#include <Preferences.hpp>
#include <Context.hpp>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <shlobj.h>
#endif

PropertyFile Preferences;

int debug = 0;

#define OPT_BOARD               0x1001
#define OPT_DATADIR             0x1002

static struct option long_options[] = {
    {"debug",		    no_argument,       &debug, 1},
    {"board",           required_argument, NULL,    OPT_BOARD},
    {"datadir",         required_argument, NULL,    OPT_DATADIR},
    {0, 0, 0, 0},
};

class Config {
    private:
        File datadir;
        std::string board;

    public:
        Config(int argc, char **argv) {
            int optind = 0;
            while (int opt = getopt_long(argc, argv, "", long_options, &optind) >= 0) {
                std::cout << "Option: " << opt << " at index " << optind << std::endl;

                if (opt != 1) {
                    std::cout << "Bad option " << opt << std::endl;
                    continue;
                }

                if (opt == 1) {
                    if (long_options[optind].flag != 0) {
                        std::cout << "Doing nothing for flag option" << std::endl;
                        continue;
                    }

                    switch (long_options[optind].val) {
                        case OPT_BOARD:
                            board = optarg;
                            break;
                    
                        case OPT_DATADIR:
                            datadir = optarg;
                            break;
                    }
                }
            }

            printf("Debug level: %d\n", debug);

            if (datadir == "") {
#if defined(__linux__)
                std::string t = getenv("HOME");
                t += "/.uecide";
                datadir = t;
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
                TCHAR path[MAX_PATH] = { 0 };
                SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path);
                std::stringstream ss;
                ss << path << "/UECIDE";
                datadir = ss.str();
#elif defined(__APPLE__)
                std::string t = getenv("HOME");
                t += "/Library/UECIDE";
                datadir = t;
#else
#error Your OS is not supported
#endif
            }

            File prefs(datadir, "preferences.txt");
            Preferences.loadProperties(prefs);
        }

        File getDataDirectory() {
            return datadir;
        }

        std::string getBoardName() {
            return board;
        }
};

Config *config;

// Traverse a file tree in depth-last mode looking for any board.txt files
void findThings(File &dir) {
    std::vector<File> files = dir.listFiles();
    for (File &file : files) {
        if (file.getName()[0] == '.') continue;
        if (!file.isDirectory()) {
            if (file.getName() == "board.txt") {
                Board b(dir);
                if (b.isValid()) {
                    Board::addBoard(b);
                }
                return;
            }
            if (file.getName() == "core.txt") {
                Core c(dir);
                if (c.isValid()) {
                    Core::addCore(c);
                }
                return;
            }
            if (file.getName() == "compiler.txt") {
                Compiler c(dir);
                if (c.isValid()) {
                    Compiler::addCompiler(c);
                }
                return;
            }
            if (file.getName() == "programmer.txt") {
                Programmer p(dir);
                if (p.isValid()) {
                    Programmer::addProgrammer(p);
                }
                return;
            }
        }
    }
    for (File &file : files) {
        if (file.getName()[0] == '.') continue;
        if (file.isDirectory()) {
            findThings(file);
        }
    }
}

int main(int argc, char **argv) {

    config = new Config(argc, argv);
    File dd = config->getDataDirectory();
    std::cout << "Data dir: " << dd.getAbsolutePath() << std::endl;

    File boardsDir(dd, "boards");
    File coresDir(dd, "cores");
    File compilersDir(dd, "compilers");
    File programmersDir(dd, "programmers");

    findThings(boardsDir);
    findThings(coresDir);
    findThings(compilersDir);
    findThings(programmersDir);

    Board &b = Board::findByName(Preferences.get("board"));
    Core &c = b.getCore();
    Compiler &compiler = b.getCompiler();
    Programmer &prog = b.getProgrammer();

    Context ctx;
    ctx.setBoard(b);
    ctx.setCore(c);
    ctx.setCompiler(compiler);
    ctx.setProgrammer(prog);
    

    std::cout << "Selected board: " << b.getDescription() << std::endl;
    std::cout << "Selected core: " << c.getDescription() << std::endl;
    std::cout << "Selected compiler: " << compiler.getDescription() << std::endl;
    std::cout << "Selected programmer: " << prog.getDescription() << std::endl;

    std::cout << ctx.parseString("this string ${basename:/path/to/some/smelly-file.foo,foo} is parsed") << std::endl;

    return 0;
}
