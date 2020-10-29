#ifndef _U_OBJECT_HPP
#define _U_OBJECT_HPP

#include <string>

#include <PropertyFile.hpp>
#include <File.hpp>

class UObject {
    private:
        PropertyFile _properties;
        File _folder;
        bool _valid;

    public: 

        static const int BOARD = 1;
        static const int CORE = 2;
        static const int COMPILER = 3;
        static const int PROGRAMMER = 4;
        static const int TOOL = 5;

        UObject();
        UObject(File root);
        
        bool loadObject();

        bool operator == (UObject &o);
        bool operator != (UObject &o);


        File getLibrariesFolder();
        File getExamplesFolder();
        std::string getName();
        File getFolder();
        bool isValid();
        std::string get(std::string key);
        std::string get(std::string key, std::string def);
        void set(std::string key, std::string value);
        void unset(std::string key);
        std::string getFamily();
        std::vector<std::string> getFamilies();
        bool inFamily(std::string family);
        PropertyFile getProperties();
        std::string getDescription();
        bool worksWith(UObject &c);
        std::string toString();

        virtual int getType() = 0;
};

#endif
