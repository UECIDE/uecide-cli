#ifndef _CORE_HPP
#define _CORE_HPP

#include <string>
#include <map>

#include <UObject.hpp>
#include <Compiler.hpp>
#include <Programmer.hpp>

class Core : public UObject {

    private:
        static std::map<std::string, Core> _cores;
    

    public:
        Core();
        Core(File f);
        int getType();
        Compiler &getCompiler();
        Programmer &getProgrammer();

        static Core &findByName(std::string name);
        static void addCore(Core core);
        static void dumpCoreList();
};

extern Core noCore;

#endif
