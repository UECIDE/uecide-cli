#include <map>
#include <iostream>
#include <sstream>

#include <pstream.h>

#include <Context.hpp>
#include <Varcmd.hpp>
#include <BuiltinCommand.hpp>

std::ostringstream buffer;
bool buffered = false;

std::map<std::string, Varcmd *(*)()> varcmdList;
template<typename T> Varcmd * createVarcmd() { return new T; }

std::map<std::string, BuiltinCommand *(*)()> builtinList;
template<typename T> BuiltinCommand * createBuiltinCommand() { return new T; }

static std::vector<std::string> splitString(std::string in, std::string delim) {
    std::vector<std::string> out;
    size_t pos = in.find(delim);
    while (pos != std::string::npos) {
        std::string left = in.substr(0, pos);
        out.push_back(left);
        std::string right = in.substr(pos + delim.length(), in.length());
        pos = right.find(delim);
    }
    return out;
}

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
    varcmdList["basename"] = &createVarcmd<vc_basename>;
    varcmdList["board"] = &createVarcmd<vc_board>;
    varcmdList["char"] = &createVarcmd<vc_char>;
    varcmdList["compiler"] = &createVarcmd<vc_compiler>;
    varcmdList["core"] = &createVarcmd<vc_core>;
    varcmdList["csv"] = &createVarcmd<vc_csv>;
    varcmdList["env"] = &createVarcmd<vc_env>;
    varcmdList["exec"] = &createVarcmd<vc_exec>;
    varcmdList["exists"] = &createVarcmd<vc_exists>;
    varcmdList["files"] = &createVarcmd<vc_files>;
    varcmdList["find"] = &createVarcmd<vc_find>;
    varcmdList["foreach"] = &createVarcmd<vc_foreach>;
    varcmdList["if"] = &createVarcmd<vc_if>;
    varcmdList["join"] = &createVarcmd<vc_join>;
    varcmdList["lc"] = &createVarcmd<vc_lc>;
    varcmdList["math"] = &createVarcmd<vc_math>;
    varcmdList["onefile"] = &createVarcmd<vc_onefile>;
    varcmdList["preproc"] = &createVarcmd<vc_preproc>;
    varcmdList["programmer"] = &createVarcmd<vc_programmer>;
    varcmdList["random"] = &createVarcmd<vc_random>;

    builtinList["__builtin_append"] = &createBuiltinCommand<bc_append>;
    builtinList["__builtin_bullet"] = &createBuiltinCommand<bc_bullet>;
    builtinList["__builtin_bullet2"] = &createBuiltinCommand<bc_bullet2>;
    builtinList["__builtin_bullet3"] = &createBuiltinCommand<bc_bullet3>;
    builtinList["__builtin_cout"] = &createBuiltinCommand<bc_cout>;
    builtinList["__builtin_cp"] = &createBuiltinCommand<bc_cp>;
    builtinList["__builtin_delay"] = &createBuiltinCommand<bc_delay>;
    builtinList["__builtin_dot"] = &createBuiltinCommand<bc_dot>;
    builtinList["__builtin_echo"] = &createBuiltinCommand<bc_cout>;

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
        return executeCommand(parseString(props.get(key)), parseString(props.get(key + ".environment")), false);
    }

    return false;
}

bool Context::executeUScript(std::string key) {
    return false;
}

bool Context::executeCommand(std::string command, std::string env, bool silent = false) {
    if (command.find("__builtin_") == 0) {
        return runBuiltinCommand(command, silent);
    } else {
        return runSystemCommand(command, env, silent);
    }
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

bool Context::runBuiltinCommand(std::string command, bool silent) {
    std::vector<std::string> args = splitString(command, "::");

    std::string cmdname = args[0];
    args.erase(args.begin());

    if (builtinList.find(cmdname) == builtinList.end()) {
        error("Command " + cmdname + " not found");
        return false;
    }
    BuiltinCommand *bc = builtinList[command]();
    bool ret = bc->main(this, args);
    delete bc;
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

void Context::startBuffer() {
    buffer.str("");
    buffered = true;
}

std::string Context::endBuffer() {
    buffered = false;
    return buffer.str();
}
    
bool Context::runSystemCommand(std::string command, std::string env, bool silent = false) {
    std::vector<std::string> args = splitString(command, "::");

    redi::ipstream in(args[0], args);

    return false;
}
