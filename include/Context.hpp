#ifndef _CONTEXT_HPP
#define _CONTEXT_HPP

#include <string>

#include <Programmer.hpp>
#include <Board.hpp>
#include <Core.hpp>
#include <Compiler.hpp>

class Context {

    private:

        Programmer *_programmer = &noProgrammer;
        Board *_board = &noBoard;
        Core *_core = &noCore;
        Compiler *_compiler = &noCompiler;

        PropertyFile *_settings;
        PropertyFile _liveSettings;
        PropertyFile _backupSettings;

    public:

        Context();
        
        void setProgrammer(Programmer &programmer);
        void setBoard(Board &board);
        void setCore(Core &core);
        void setCompiler(Compiler &compiler);

        Programmer &getProgrammer();
        Board &getBoard();
        Core &getCore();
        Compiler &getCompiler();

        void set(std::string key, std::string val);
        std::string get(std::string key);

        PropertyFile getMerged();
        std::string getMerged(std::string key);

        void error(std::string m);
        void warning(std::string m);
        void message(std::string m);
        void link(std::string m);
        void command(std::string m);
        void bullet(std::string m);
        void bullet2(std::string m);
        void bullet3(std::string m);
        void heading(std::string m);

        bool executeKey(std::string key);
        bool executeUScript(std::string key);
        bool executeCommand(std::string command, std::string env);

        std::string parseString(std::string str);

        std::string runFunctionVariable(std::string command, std::string arg);
        bool runBuiltinCommand(std::string command, std::string arg);

        void snapshot();
        void restore();
};

#endif
