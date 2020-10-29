#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

#include <PropertyFile.hpp>
#include <Trim.hpp>

PropertyFile::PropertyFile() {
}

PropertyFile::PropertyFile(File user) {
    userFile = user;
    loadProperties(&properties, &userFile);
}

PropertyFile::PropertyFile(File user, File defaults) {
    userFile = user;
    loadProperties(&defaultProperties, &defaults);
    loadProperties(&properties, &userFile);
}

void PropertyFile::loadProperties(std::map<std::string, std::string> *props, File *f) {
    if (!f->canRead()) return;

    std::ifstream file(f->getAbsolutePath());
    if (file.is_open()) {
        while (!file.eof()) {
            std::string in;
            std::getline(file, in, '\n');
            trim(in);

            if (in.length() == 0) continue;
            if (in[0] == ';') continue;
            if (in[0] == '#') continue;

            int eq = in.find("=");

            if (eq == std::string::npos) continue;

            std::string key = in.substr(0, eq);
            std::string val = in.substr(eq + 1);

            trim(key);
            trim(val);

            (*props)[key] = val;
        }
        file.close();
    }

}

void PropertyFile::dump() {
    for (auto const& x : properties) {
        std::cout << x.first  // string (key)
                  << '=' 
                  << x.second // string's value 
                  << std::endl ;
    }
}

void PropertyFile::mergeData(std::map<std::string, std::string> &data) {
    for (auto const& x : data) {
        std::cout << "Merging " << x.first << "=" << x.second << std::endl;
        properties[x.first] = x.second;
    }
}


void PropertyFile::mergeData(std::string prefix, std::map<std::string, std::string> &data) {
    for (auto const& x : data) {
        properties[prefix + "." + x.first] = x.second;
    }
}

void PropertyFile::mergeData(PropertyFile &pf) {
    std::map<std::string, std::string> data = pf.getProperties();
    mergeData(data);
}

void PropertyFile::mergeData(std::string prefix, PropertyFile &pf) {
    std::map<std::string, std::string> data = pf.getProperties();
    mergeData(prefix, data);
}

void PropertyFile::save(File f) {
    userFile = f;
    save();
}

void PropertyFile::save() {
    std::ofstream file(userFile.getAbsolutePath());
    if (file.is_open()) {
        for (auto const& x : properties) {
            file << x.first  // string (key)
                 << '=' 
                 << x.second // string's value 
                 << std::endl ;
        }
        file.close();
    }
}

std::map<std::string, std::string> &PropertyFile::getProperties() {
    return properties;
}

std::string PropertyFile::getPlatformSpecific(std::string key) {
    
    std::string pskey = key + "." + OS_FULL_NAME;
    if (keyExists(pskey)) {
        return get(pskey);
    }

    pskey = key + "." + OS_NAME;
    if (keyExists(pskey)) {
        return get(pskey);
    }

    return get(key);
}

std::string PropertyFile::getPlatformSpecificKey(std::string key) {
    std::string pskey = key + "." + OS_FULL_NAME;
    if (keyExists(pskey)) {
        return pskey;
    }

    pskey = key + "." + OS_NAME;
    if (keyExists(pskey)) {
        return pskey;
    }

    return key;
}

bool PropertyFile::keyExists(std::string s) {
    auto search = properties.find(s);
    if (search != properties.end()) return true;

    search = defaultProperties.find(s);
    if (search != defaultProperties.end()) return true;
    
    return false;
}

std::string PropertyFile::get(std::string s) {
    auto search = properties.find(s);
    if (search != properties.end()) return search->second;

    search = defaultProperties.find(s);
    if (search != defaultProperties.end()) return search->second;

    return "";
}

std::vector<std::string> PropertyFile::getArray(std::string key) {
    std::vector<std::string> out;

    size_t pos_start = 0, pos_end;
    std::string token;
    std::string s = get(key);

    while ((pos_end = s.find("::", pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + 2;
        trim(token);
        if (token.length() > 0) {
            out.push_back(token);
        }
    }

    if (pos_start < s.length()) {
        out.push_back(s.substr(pos_start));
    }
    return out;
}
    
std::string PropertyFile::get(std::string key, std::string def) {
    if (!keyExists(key)) return def;
    return get(key);
}

std::string PropertyFile::getDefault(std::string key) {
    return defaultProperties[key];
}

void PropertyFile::set(std::string key, std::string val) {
    properties[key] = val;
}

void PropertyFile::unset(std::string key) {
    auto search = properties.find(key);
    
    if (search != properties.end()) {
        properties.erase(search);
    }
}

void PropertyFile::removeAll(std::string key) {
    unset(key);
    std::string sk = key + ".";
    int sklen = sk.length();
    for (auto const& x : properties) {
        if (x.first.substr(0, sklen) == sk) {
            properties.erase(x.first);
        }
    }
}

bool PropertyFile::getBoolean(std::string key) {
    return getBoolean(key, false);
}

bool PropertyFile::getBoolean(std::string key, bool def) {
    std::string val = get(key);

    if (!keyExists(key)) return def;

    if (val == "true") return true;
    if (val == "yes") return true;
    if (val == "on") return true;
    if (val == "y") return true;
    if (val == "1") return true;
    return false;
}

void PropertyFile::setBoolean(std::string key, bool val) {
    properties[key] = val ? "true" : "false";
}

int PropertyFile::getInteger(std::string key) {
    return getInteger(key, 0);
}

int PropertyFile::getInteger(std::string key, int def) {
    if (!keyExists(key)) return def;
    std::string val = get(key);
    return std::stoi(val);
}

void PropertyFile::setInteger(std::string key, int val) {
    set(key, std::to_string(val));
}

long PropertyFile::getLong(std::string key) {
    return getLong(key, 0);
}

long PropertyFile::getLong(std::string key, long def) {
    if (!keyExists(key)) return def;
    std::string val = get(key);
    return std::stol(val);
}

void PropertyFile::setLong(std::string key, long val) {
    set(key, std::to_string(val));
}

float PropertyFile::getFloat(std::string key) {
    return getFloat(key, 0);
}

float PropertyFile::getFloat(std::string key, float def) {
    if (!keyExists(key)) return def;
    std::string val = get(key);
    return std::stof(val);
}

void PropertyFile::setFloat(std::string key, float val) {
    set(key, std::to_string(val));
}

PropertyFile PropertyFile::getChildren(std::string path) {
    if (path[path.length() - 1] != '.') {
        path += ".";
    }

    int plen = path.length();

    PropertyFile pf;

    for (auto const& x : properties) {
        if (x.first.substr(0, plen) == path) {
            std::string k = x.first.substr(plen + 1);
            pf.set(k, x.second);
        }
    }

    return pf;
}

std::vector<std::string> PropertyFile::childKeys() {
    std::vector<std::string> out;
    for (auto const& x : properties) {
        std::string key = x.first;
        int pos = key.find(".");
        if (pos != std::string::npos) {
            key = key.substr(0, pos);
        }

        if (std::find(out.begin(), out.end(), key) == out.end()) {
            out.push_back(key);
        }
    }

    return out;
    
}

std::vector<std::string> PropertyFile::childKeysOf(std::string path) {
    PropertyFile pf = getChildren(path);
    return pf.childKeys();
}

void PropertyFile::loadProperties(File f) {
    loadProperties(&properties, &f);
}
