#include <Compiler.hpp>
#include <iostream>

Compiler noCompiler;

std::map<std::string, Compiler> Compiler::_compilers;

Compiler::Compiler() : UObject() {
}

Compiler::Compiler(File f) : UObject(f) {
    loadObject();
}

Compiler &Compiler::findByName(std::string name) {
    auto search = _compilers.find(name);
    if (search == _compilers.end()) {
        return noCompiler;
    }
    return search->second;
}

void Compiler::addCompiler(Compiler compiler) {
    std::string name = compiler.getName();
    _compilers[name] = compiler;
}

int Compiler::getType() {
    return UObject::COMPILER;
}

void Compiler::dumpCompilerList() {
    for (auto c : _compilers) {
        std::cout << c.second.getName() << " - " << c.second.getDescription() << std::endl;
    }
}
