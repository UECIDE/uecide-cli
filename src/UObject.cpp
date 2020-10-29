#include <UObject.hpp>
#include <iostream>

UObject::UObject() {
    _valid = false;
}

UObject::UObject(File root) {
    _valid = false;
    _folder = root;
}

bool UObject::operator == (UObject &o) {
    return ((o.getName() == getName()) && (o.getType() == getType()));
}

bool UObject::operator != (UObject &o) {
    return ((o.getName() != getName()) || (o.getType() != getType()));
}

bool UObject::loadObject() {
    if (_folder.exists() && _folder.isDirectory()) {

        std::string filename = "";

        switch (getType()) {
            case BOARD:
                filename = "board.txt";
                break;
            case CORE:
                filename = "core.txt";
                break;
            case COMPILER:
                filename = "compiler.txt";
                break;
            case PROGRAMMER:
                filename = "programmer.txt";
                break;
            case TOOL:
                filename = "tool.txt";
                break;
            default:
                return false;
        }

        File f(_folder, filename);
        _properties.loadProperties(f);
        if (_properties.keyExists("name")) _valid = true;
        return _valid;
    }
    return false;
}

File UObject::getFolder() {
    return _folder;
}

File UObject::getLibrariesFolder() {
    std::string libs = _properties.get("libraries", "libraries");;
    File f(_folder, libs);
    return f;
}

File UObject::getExamplesFolder() {
    std::string exa = _properties.get("examples", "examples");;
    File f(_folder, exa);
    return f;
}

std::string UObject::getName() {
    std::string n = _properties.get("name");
    return n;
}

bool UObject::isValid() {
    return _valid;
}

std::string UObject::get(std::string key) {
    return _properties.get(key);
}

std::string UObject::get(std::string key, std::string def) {
    return _properties.get(key, def);
}

void UObject::set(std::string key, std::string val) {
    _properties.set(key, val);
}

void UObject::unset(std::string key) {
    _properties.unset(key);
}

std::string UObject::getFamily() {
    return _properties.get("family", "all");
}

std::vector<std::string> UObject::getFamilies() {
    return _properties.getArray("family");
}

bool UObject::inFamily(std::string fam) {
    std::vector<std::string> fams = _properties.getArray("family");
    for (std::string s : fams) {
        if (s == fam) return true;
    }
    return false;
}

PropertyFile UObject::getProperties() {
    return _properties;
}

std::string UObject::getDescription() {
    return _properties.get("description", "Unkown UECIDE Object");
}

bool UObject::worksWith(UObject &c) {
    std::vector<std::string> myFamilies = _properties.getArray("family");
    if (myFamilies.size() == 0) {
        myFamilies.push_back("all");
    }

    std::vector<std::string> otherFamilies = c.getFamilies();
    if (otherFamilies.size() == 0) {
        otherFamilies.push_back("all");
    }

    for (std::string mine : myFamilies) {
        for (std::string theirs : otherFamilies) {
            if (mine == theirs) return true;
        }
    }
    
    return false;
}

std::string UObject::toString() {
    return getDescription();
}
