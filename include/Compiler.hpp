#ifndef _COMPILER_HPP
#define _COMPILER_HPP

#include <string>
#include <map>

#include <UObject.hpp>

class Compiler : public UObject {

    private:
        static std::map<std::string, Compiler> _compilers;
    

    public:
        Compiler();
        Compiler(File f);
        int getType();

        static Compiler &findByName(std::string name);
        static void addCompiler(Compiler compiler);
        static void dumpCompilerList();
};

extern Compiler noCompiler;

#endif
