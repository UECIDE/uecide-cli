#include <Programmer.hpp>
#include <iostream>

Programmer noProgrammer;

std::map<std::string, Programmer> Programmer::_programmers;

Programmer::Programmer() : UObject() {
}

Programmer::Programmer(File f) : UObject(f) {
    loadObject();
}

Programmer &Programmer::findByName(std::string name) {
    auto search = _programmers.find(name);
    if (search == _programmers.end()) {
        return noProgrammer;
    }
    return search->second;
}

void Programmer::addProgrammer(Programmer programmer) {
    std::string name = programmer.getName();
    _programmers[name] = programmer;
}

int Programmer::getType() {
    return UObject::PROGRAMMER;
}

void Programmer::dumpProgrammerList() {
    for (auto c : _programmers) {
        std::cout << c.second.getName() << " - " << c.second.getDescription() << std::endl;
    }
}
