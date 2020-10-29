#include <Board.hpp>
#include <Preferences.hpp>
#include <iostream>

std::map<std::string, Board> Board::_boards;
Board noBoard;

Board::Board() : UObject() {
}

Board::Board(File f) : UObject(f) {
    loadObject();
}

int Board::getType() {
    return UObject::BOARD;
}

std::string Board::getGroup() {
    return get("group", "Other");
}

Core &Board::getCore() {
    std::string key = "board." + getName() + ".core";
    std::string core = Preferences.get(key, get("core"));
    Core &selectedCore = Core::findByName(core);
    return selectedCore;
}

Compiler &Board::getCompiler() {
    std::string key = "board." + getName() + ".compiler";
    if (Preferences.keyExists(key)) {
        return Compiler::findByName(Preferences.get(key));
    }
    return getCore().getCompiler();
}

Programmer &Board::getProgrammer() {
    std::string key = "board." + getName() + ".programmer";
    if (Preferences.keyExists(key)) {
        return Programmer::findByName(Preferences.get(key));
    }
    return getCore().getProgrammer();
}

Board &Board::findByName(std::string name) {
    auto search = _boards.find(name);
    if (search == _boards.end()) {
        return noBoard;
    }   
    return search->second;
}

void Board::addBoard(Board board) {
    std::string name = board.getName();
    _boards[name] = board;
}

void Board::dumpBoardList() {
    for (auto b : _boards) {
        std::cout << b.second.getName() << " - " << b.second.getDescription() << std::endl;
    }
}
