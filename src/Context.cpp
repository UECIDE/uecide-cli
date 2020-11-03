#include <map>
#include <iostream>
#include <sstream>

#include <Context.hpp>
#include <Varcmd.hpp>

std::map<std::string, Varcmd *(*)()> varcmdList;
template<typename T> Varcmd * createInstance() { return new T; }

static std::vector<std::string> makeArgList(std::string args) {
    std::vector<std::string> out;
    std::istringstream iss(args);
    std::string item;
    while (std::getline(iss, item, ',')) {
        out.push_back(item);
    }
    return out;
}

Context::Context() {
    varcmdList["basename"] = &createInstance<vc_basename>;
    varcmdList["board"] = &createInstance<vc_board>;
    varcmdList["char"] = &createInstance<vc_char>;
    varcmdList["compiler"] = &createInstance<vc_compiler>;
    varcmdList["core"] = &createInstance<vc_core>;
    varcmdList["csv"] = &createInstance<vc_csv>;
    varcmdList["env"] = &createInstance<vc_env>;
    varcmdList["exec"] = &createInstance<vc_exec>;
    varcmdList["exists"] = &createInstance<vc_exists>;
    varcmdList["files"] = &createInstance<vc_files>;
    varcmdList["find"] = &createInstance<vc_find>;
    varcmdList["foreach"] = &createInstance<vc_foreach>;
    varcmdList["if"] = &createInstance<vc_if>;
    varcmdList["join"] = &createInstance<vc_join>;
    varcmdList["lc"] = &createInstance<vc_lc>;
    varcmdList["math"] = &createInstance<vc_math>;
    varcmdList["onefile"] = &createInstance<vc_onefile>;
    varcmdList["preproc"] = &createInstance<vc_preproc>;
    varcmdList["programmer"] = &createInstance<vc_programmer>;
    varcmdList["random"] = &createInstance<vc_random>;

    _settings = &_liveSettings;
}

void Context::setProgrammer(Programmer &programmer) {
    _programmer = &programmer;
}

void Context::setBoard(Board &board) {
    _board = &board;
}

void Context::setCore(Core &core) {
    _core = &core;
}

void Context::setCompiler(Compiler &compiler) {
    _compiler = &compiler;
}

Programmer &Context::getProgrammer() {  
    return *_programmer;
}

Board &Context::getBoard() {
    return *_board;
}

Core &Context::getCore() {
    return *_core;
}

Compiler &Context::getCompiler() {
    return *_compiler;
}

void Context::set(std::string key, std::string val) {
    _settings->set(key, val);
}

std::string Context::get(std::string key) {
    return _settings->get(key);
}

PropertyFile Context::getMerged() {
    PropertyFile pf;
    if (_programmer != &noProgrammer) pf.mergeData(_programmer->getProperties().getProperties());
    if (_compiler != &noCompiler) pf.mergeData(_compiler->getProperties().getProperties());
    if (_core != &noCore) pf.mergeData(_core->getProperties().getProperties());
    if (_board != &noBoard) pf.mergeData(_board->getProperties().getProperties());
    pf.mergeData(*_settings);
    return pf;
}

std::string Context::getMerged(std::string key) {
    PropertyFile pf;
    if (_programmer != &noProgrammer) pf.mergeData(_programmer->getProperties().getProperties());
    if (_compiler != &noCompiler) pf.mergeData(_compiler->getProperties().getProperties());
    if (_core != &noCore) pf.mergeData(_core->getProperties().getProperties());
    if (_board != &noBoard) pf.mergeData(_board->getProperties().getProperties());
    pf.mergeData(*_settings);
    return pf.get(key);
}

void Context::error(std::string m) {
    std::cout << m << std::endl;
}

void Context::warning(std::string m) {
    std::cout << m << std::endl;
}

void Context::message(std::string m) {
    std::cout << m << std::endl;
}

void Context::link(std::string m) {
    std::cout << m << std::endl;
}

void Context::command(std::string m) {
    std::cout << m << std::endl;
}

void Context::bullet(std::string m) {
    std::cout << "* " << m << std::endl;
}

void Context::bullet2(std::string m) {
    std::cout << "  * " << m << std::endl;
}

void Context::bullet3(std::string m) {
    std::cout << "    * " << m << std::endl;
}

void Context::heading(std::string m) {
    std::cout << m << std::endl;
    std::cout << std::string(m.length(), '=') << std::endl;
    std::cout << std::endl;
}

bool Context::executeKey(std::string key) {
    PropertyFile props = getMerged();
    key = props.getPlatformSpecificKey(key);

    if (props.keyExists(key + ".0")) {
        return executeUScript(key);
    }

    if (props.keyExists(key)) {
        return executeCommand(parseString(props.get(key)), parseString(props.get(key + ".environment")));
    }

    return false;
}

bool Context::executeUScript(std::string key) {
    return false;
}

bool Context::executeCommand(std::string command, std::string env) {
    return false;
}

std::string Context::parseString(std::string str) {
    PropertyFile props = getMerged();
    props.dump();
    int openpos = str.rfind("${");
    int closepos = str.find("}", openpos);

    while ((openpos != std::string::npos) && (closepos != std::string::npos)) {
        std::string left = str.substr(0, openpos);
        std::string mid = str.substr(openpos + 2, closepos - openpos - 2);
        std::string right = str.substr(closepos + 1);

        int colon = mid.find(":");
        if (colon != std::string::npos) {
            std::string command = mid.substr(0, colon);
            std::string param = mid.substr(colon + 1);

            mid = runFunctionVariable(command, param);

        } else {
            if (props.keyExists(mid)) {
                mid = props.get(mid);
            } else {
                mid = "KEY_NOT_FOUND";
            }
        }
        str = left + mid + right;
        openpos = str.rfind("${");
        closepos = str.find("}", openpos);
    }
    return str;
}

std::string Context::runFunctionVariable(std::string command, std::string param) {
    if (varcmdList.find(command) == varcmdList.end()) {
        error("Command " + command + " not found");
        return "COMMAND_NOT_FOUND";
    }
    std::vector<std::string> args = makeArgList(param);
    Varcmd *vc = varcmdList[command]();
    std::string ret = vc->main(this, args);
    if (ret == "SYNTAX_ERROR") {
        error(vc->usage());
    }
    delete vc;
    return ret;
}

void Context::snapshot() {
    _backupSettings.clear();
    _backupSettings.mergeData(_liveSettings);
    _settings = &_backupSettings;
}

void Context::restore() {
    _settings = &_liveSettings;
}

