#ifndef _BOARD_HPP
#define _BOARD_HPP

#include <string>
#include <map>

#include <UObject.hpp>
#include <Core.hpp>
#include <Compiler.hpp>
#include <Programmer.hpp>

class Board : public UObject {

    private:
        static std::map<std::string, Board> _boards;

    public:
        Board();
        Board(File f);
        int getType();
        std::string getGroup();
        Core &getCore();
        Compiler &getCompiler();
        Programmer &getProgrammer();
        
        static Board &findByName(std::string name);
        static void addBoard(Board board);
        static void dumpBoardList();
};

extern Board noBoard;

#endif
