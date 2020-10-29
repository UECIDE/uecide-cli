#ifndef _FILE_HPP
#define _FILE_HPP

#include <memory>
#include <vector>
#include <string>

class File {
    private:
        std::vector<std::string> _path;
        std::string _root;

        std::string sanitizePath(std::string path);
        void loadPath(std::string path);

    public:

        char pathSeparatorChar = '/';
        std::string pathSeparator = "/";

        File();
        File(std::string p);
        File(std::string root, std::string p);
        File(File root, std::string p);

        File & operator = (const std::string &s);
        bool operator == (const std::string &b);

        bool canExecute();
        bool canRead();
        bool canWrite();
        int  compareTo(File &f);
        bool createNewFile();
        static File createTempFile(std::string &prefix, std::string &suffix);
//        static File createTempFile(std::string &prefix, std::string &suffix, File &where);
        bool deleteFile();
//        void deleteOnExit();
        bool equals(File &f);
        bool exists();
        File getAbsoluteFile();
        std::string getAbsolutePath();
        File getCanonicalFile();
        std::string getCanonicalPath();
//        size_t getFreeSpace();
        std::string getName();
        std::string getParent();
        File getParentFile();
        std::string getPath();
//        size_t getTotalSpace();
//        size_t getUsableSpace();
//        int hashCode();
        bool isAbsolute();
        bool isDirectory();
        bool isFile();
        bool isHidden();
        time_t lastModified();
        size_t length();
        std::vector<std::string> list();
//        std::vector<std::string> list(FilenameFilter filter);
        std::vector<File> listFiles();
//        std::vector<File> listFiles(FileFilter filter);
//        std::vector<File> listFiles(FilenameFilter filter);
//        std::vector<File> listRoots();
        bool mkdir();
        bool mkdirs();
        bool renameTo(File &dest);
        bool setExecutable(bool ex);
        bool setExecutable(bool ex, bool ownerOnly);
        bool setLastModified(time_t t);
        bool setReadable(bool ex);
        bool setReadable(bool ex, bool ownerOnly);
        bool setReadOnly();
        bool setWritable(bool ex);
        bool setWritable(bool ex, bool ownerOnly);
//        Path toPath();
        std::string toString();
//        URI toURI();
//        URL toURL();

};

#endif
