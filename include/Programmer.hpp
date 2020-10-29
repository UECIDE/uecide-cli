#ifndef _PROGRAMMER_HPP
#define _PROGRAMMER_HPP

#include <string>
#include <map>

#include <UObject.hpp>

class Programmer : public UObject {

    private:
        static std::map<std::string, Programmer> _programmers;
    

    public:
        Programmer();
        Programmer(File f);
        int getType();

        static Programmer &findByName(std::string name);
        static void addProgrammer(Programmer programmer);
        static void dumpProgrammerList();
};

extern Programmer noProgrammer;

#endif
