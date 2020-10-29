#ifndef _PROPERTY_FILE_HPP
#define _PROPERTY_FILE_HPP

#include <map>
#include <string>
#include <vector>

#include <File.hpp>

#define OS_FULL_NAME "linux_amd64"
#define OS_NAME "linux"

class PropertyFile {

    private:
        std::map<std::string, std::string> defaultProperties;
        std::map<std::string, std::string> properties;

        File userFile;

        bool doPlatformOverride = false;

        void loadProperties(std::map<std::string, std::string> *props, File *f);

    public:
        PropertyFile();
        PropertyFile(File user);
        PropertyFile(File user, File defaults);

        void loadProperties(File f);

        void mergeData(std::map<std::string, std::string> &data);
        void mergeData(std::string prefix, std::map<std::string, std::string> &data);
        void mergeData(PropertyFile &pf);
        void mergeData(std::string prefix, PropertyFile &pf);

        void save(File f);
        void save();

        std::map<std::string, std::string> &getProperties();

        std::string getPlatformSpecific(std::string key);
        std::string getPlatformSpecificKey(std::string key);

        bool keyExists(std::string key);
        std::string get(std::string key);
        std::string get(std::string key, std::string def);
        std::vector<std::string> getArray(std::string key);
        std::string getDefault(std::string key);

        void set(std::string key, std::string val);
        void unset(std::string key);
        void removeAll(std::string key);

        bool getBoolean(std::string key);
        bool getBoolean(std::string key, bool def);
        void setBoolean(std::string key, bool val);

        int getInteger(std::string key);
        int getInteger(std::string key, int def);
        void setInteger(std::string key, int val);

        long getLong(std::string key);
        long getLong(std::string key, long def);
        void setLong(std::string key, long val);

        float getFloat(std::string key);
        float getFloat(std::string key, float def);
        void setFloat(std::string key, float val);

        PropertyFile getChildren(std::string path);

        std::vector<std::string> childKeys();
        std::vector<std::string> childKeysOf(std::string path);

        void dump();
            
};

#endif
