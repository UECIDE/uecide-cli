#include <Core.hpp>
#include <iostream>
#include <Preferences.hpp>

Core noCore;

std::map<std::string, Core> Core::_cores;

Core::Core() : UObject() {
}

Core::Core(File f) : UObject(f) {
    loadObject();
}

Core &Core::findByName(std::string name) {
    auto search = _cores.find(name);
    if (search == _cores.end()) {
        return noCore;
    }
    return search->second;
}

void Core::addCore(Core core) {
    std::string name = core.getName();
    _cores[name] = core;
}

int Core::getType() {
    return UObject::CORE;
}

void Core::dumpCoreList() {
    for (auto c : _cores) {
        std::cout << c.second.getName() << " - " << c.second.getDescription() << std::endl;
    }
}

Compiler &Core::getCompiler() {
    Compiler &selectedCompiler = Compiler::findByName(get("compiler"));
    return selectedCompiler;
}

Programmer &Core::getProgrammer() {
    Programmer &selectedProgrammer = Programmer::findByName(get("programmer"));
    return selectedProgrammer;
}
