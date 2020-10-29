#include <iostream>
#include <sstream>
#include <vector>

#include <File.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <utime.h>

#if defined(__linux__)
#include <linux/limits.h>
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windef.h>
#include <windows.h>
#include <fileapi.h>
#elif defined(__APPLE__)
#include <sys/syslimits.h>
#else
#error Your OS is not supported
#endif

File::File() {
    _path.clear();
    _root = "";
}

File::File(std::string p) {
    loadPath(p);
}

File::File(File root, std::string p) {
    loadPath(root.getAbsolutePath() + "/" + p);
}

File::File(std::string root, std::string p) {
    loadPath(root + "/" + p);
}

File & File::operator = (const std::string &s) {
    loadPath(s);
    return *this;
}

bool File::operator == (const std::string &b) {
    return toString() == b;
}

std::string File::getAbsolutePath() {

    if (_root != "") { // A root means it's already absolute
        return toString();
    }
    
    char cwd[PATH_MAX + 1];
    char *c = getcwd(cwd, PATH_MAX);
    std::string out = cwd;
    out += "/";
    out += toString();
    return out;
}

File File::getParentFile() {
    std::string p = getParent();
    File fp(p);
    return fp;
}

bool File::isDirectory() {
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();
    if (access(fn, F_OK) != 0) {
        return false;
    }

#if defined(__linux__) || defined(__APPLE__)
    struct stat s;
    if (lstat(fn, &s) != 0) {
        return false;
    }
    return ((s.st_mode & S_IFMT) == S_IFDIR);

#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    DWORD stat = GetFileAttributesA(fn);
    return ((stat & FILE_ATTRIBUTE_DIRECTORY) != 0);
#else
#error Your OS is not supported
#endif

}

bool File::isFile() {
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();
    if (access(fn, F_OK) != 0) {
        return false;
    }

#if defined(__linux__) || defined(__APPLE__)
    struct stat s;
    if (lstat(fn, &s) != 0) {
        return false;
    }

     return ((s.st_mode & S_IFMT) == S_IFREG);

#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    DWORD stat = GetFileAttributesA(fn);
    return ((stat & (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_DEVICE)) == 0);
#else
#error Your OS is not supported
#endif
}

bool File::exists() {
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();
    return (access(fn, F_OK) == 0);
}

bool File::canRead() {
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();
    return (access(fn, R_OK) == 0);
}

bool File::canWrite() {
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();
    return (access(fn, W_OK) == 0);
}

bool File::canExecute() {
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();
    return (access(fn, X_OK) == 0);
}

bool File::mkdir() {
    File parent = getParentFile();
    if (!parent.canWrite()) return false;
    std::string s = getAbsolutePath();
    const char *fn = s.c_str();
#if defined(__linux__) || defined(__APPLE__)
    return (::mkdir(fn, 0755) == 0);
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    return (::mkdir(fn) == 0);
#else
#error Your OS is not supported
#endif
}

bool File::mkdirs() {
    std::string currentPath = _root;
    bool first = true;
    for (std::string p : _path) {


        if (first) {
            first = false;
        } else {
            currentPath += "/";
        }

        currentPath += p;

        File f(currentPath);    
        if (!f.exists()) {
            if (!f.mkdir()) {
                return false;
            }
        }
    }
    return true;
}

int File::compareTo(File &f) {
    return getAbsolutePath().compare(f.getAbsolutePath());
}

bool File::createNewFile() {
    if (exists()) return false;
    File pf = getParentFile();
    if (!pf.canWrite()) return false;
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();
    int fd = open(fn, O_CREAT | O_TRUNC, 0644);
    if (!fd) return false;
    close(fd);
    return true;
}

File File::createTempFile(std::string &prefix, std::string &suffix) {

#if defined(__linux__) || defined(__APPLE__)

    char tmpl[prefix.length() + suffix.length() + 8];

    strcpy(tmpl, prefix.c_str());
    strcat(tmpl, "-XXXXXX");
    strcat(tmpl, suffix.c_str());

    int fd = mkstemps(tmpl, suffix.length());
    char filename[PATH_MAX + 1];
    memset(filename, 0, PATH_MAX + 1);
    char proc[PATH_MAX + 1];
    snprintf(proc, PATH_MAX, "/proc/self/fd/%d", fd);
    if (readlink(proc, filename, PATH_MAX) == -1) {
        std::cout << "Couldn't get temp filename" << std::endl;
    }
    std::string tempfile = filename;

    std::cout << "Temporary filename: " << filename << std::endl;

    File f(tempfile);
    return f;
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
/* TODO: Make a temporary file */
    File f("...");
    return f;
#else
#error Your OS is not supported
#endif
}

bool File::deleteFile() {
    if (!canWrite()) return false;
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();
    
    return unlink(fn) == 0;
}

bool File::equals(File &f) {
    std::string me = getAbsolutePath();
    std::string them = f.getAbsolutePath();
    return me == them;
}

File File::getAbsoluteFile() {
    std::string abPath = getAbsolutePath();
    File f(abPath);
    return f;
}

std::string File::getCanonicalPath() {
    if (!exists()) {
        return toString();
    }

    std::vector<std::string> compressed;
    for (std::string part : _path) {
        if (part == ".") continue; // Skip /./
        if (part == "..") { // Go up a level on /../
            if (compressed.size() > 0)
                compressed.pop_back();
            continue;
        }
        compressed.push_back(part);
    }

    std::string out = _root;
    bool first = true;
    for (std::string item : compressed) {
        if (first) {
            first = false;
        } else {
            out += "/";
        }
        out += item;
    }
    return out;
}

File File::getCanonicalFile() {
    std::string f = getCanonicalPath();
    File fil(f);
    return fil;
}

std::string File::getName() {
    return _path.back();
}

std::string File::getParent() {
    std::string lastEntry = _path.back();
    _path.pop_back();
    std::string pn = getPath();
    _path.push_back(lastEntry);
    return pn;
}

std::string File::getPath() {
    return toString();
}

bool File::isAbsolute() {
    return _root != "";
}

bool File::isHidden() {
    std::string fn = getName();
#if defined(__linux__) || defined(__APPLE__)
    return fn[0] == '.';
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    DWORD stat = GetFileAttributesA(fn.c_str());
    return ((stat & FILE_ATTRIBUTE_HIDDEN) != 0);
#else
#error Your OS is not supported
#endif
}

time_t File::lastModified() {
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();
    if (access(fn, F_OK) != 0) {
        return 0;
    }

#if defined(__linux__) || defined(__APPLE__)
    struct stat s;
    if (lstat(fn, &s) != 0) {
        return 0;
    }

#if defined(__linux__)
    return s.st_mtim.tv_sec;
#else
    return s.st_mtime;
#endif
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    HANDLE hFile = CreateFile(fn, GENERIC_READ, 
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile==INVALID_HANDLE_VALUE)
        return 0;

    FILETIME creation;
    FILETIME access;
    FILETIME modification;

    if (!GetFileTime(hFile, &creation, &access, &modification)) {
        CloseHandle(hFile);
        return false;
    }
    CloseHandle(hFile);
    uint64_t cns = (((uint64_t)modification.dwHighDateTime << 32) | modification.dwLowDateTime);
    uint64_t secs = cns / 10000000;
    uint64_t epoch = secs - 11644469925;
    return epoch;
#else
#error Your OS is not supported
#endif
}

size_t File::length() {
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();
    if (access(fn, F_OK) != 0) {
        return 0;
    }

#if defined(__linux__) || defined(__APPLE__)
    struct stat s;
    if (lstat(fn, &s) != 0) {
        return 0;
    }

    return s.st_size;

#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    HANDLE hFile = CreateFile(fn, GENERIC_READ, 
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile==INVALID_HANDLE_VALUE)
        return 0;

    LARGE_INTEGER size;
    if (!GetFileSizeEx(hFile, &size))
    {
        CloseHandle(hFile);
        return 0;
    }

    CloseHandle(hFile);
    return size.QuadPart;
#else
#error Your OS is not supported
#endif
}

std::vector<std::string> File::list() {
    std::vector<std::string> files;
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();

    if (!isDirectory()) return files;

    DIR *dir = opendir(fn);
    struct dirent *d;
    while ((d = readdir(dir)) != NULL) {
        std::string n = d->d_name;
        files.push_back(n);
    }
    closedir(dir);
    return files;
}

std::vector<File> File::listFiles() {
    std::vector<std::string> files = list();
    std::vector<File> fileList;

    for (std::string s : files) {
        File f(*this, s);
        fileList.push_back(f);
    }
    return fileList;
}

bool File::renameTo(File &dest) {
    std::string dname = dest.getAbsolutePath();
    return rename(getAbsolutePath().c_str(), dname.c_str()) == 0;
}

bool File::setExecutable(bool ex) {
    return setExecutable(ex, false);
}

bool File::setExecutable(bool ex, bool ownerOnly) {
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();

#if defined(__linux__) || defined(__APPLE__)
    struct stat s;
    if (lstat(fn, &s) != 0) {
        return false;
    }

    int mode = s.st_mode & 07777;
    if (ownerOnly) {
        if (ex) {
            mode |= 0400;
        } else {
            mode &= ~0400;
        }
    } else {
        if (ex) {
            mode |= 0444;
        } else {
            mode &= ~0444;
        }
    }

    return chmod(fn, mode) == 0;
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    // Windows doesn't seem to have the concept of executable...
    return true;
#else
#error Your OS is not supported
#endif
}

bool File::setLastModified(time_t t) {
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();
#if defined(__linux__) || defined(__APPLE__)
    struct stat s;
    if (lstat(fn, &s) != 0) {
        return false;
    }

    struct utimbuf times;
#if defined(__linux__)
    times.actime = s.st_atim.tv_sec;
#else
    times.actime = s.st_atime;
#endif
    times.modtime = t;
    return utime(fn, &times) == 0;
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    HANDLE hFile = CreateFile(fn, GENERIC_READ, 
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile==INVALID_HANDLE_VALUE)
        return 0;

    FILETIME modification;

    uint64_t cns = (t + 11644469925UL) * 10000000UL;
    modification.dwHighDateTime = cns >> 32;
    modification.dwLowDateTime = cns & 0xFFFFFFFF;

    bool res = GetFileTime(hFile, NULL, NULL, &modification);
    CloseHandle(hFile);
    return res;
#else
#error Your OS is not supported
#endif
}

bool File::setReadable(bool ex) {
    return setReadable(ex, false);
}

bool File::setReadable(bool ex, bool ownerOnly) {
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();

#if defined(__linux__) || defined(__APPLE__)
    struct stat s;
    if (lstat(fn, &s) != 0) {
        return false;
    }

    int mode = s.st_mode & 07777;
    if (ownerOnly) {
        if (ex) {
            mode |= 0100;
        } else {
            mode &= ~0100;
        }
    } else {
        if (ex) {
            mode |= 0111;
        } else {
            mode &= ~0111;
        }
    }

    return chmod(fn, mode) == 0;
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    // Is this a thing in Windows?
    return true;
#else
#error Your OS is not supported
#endif
}

bool File::setReadOnly() {
    if (!setReadable(true)) return false;
    if (!setExecutable(false)) return false;
    if (!setWritable(false)) return false;
    return true;
}

bool File::setWritable(bool ex) {
    return setWritable(ex, false);
}

bool File::setWritable(bool ex, bool ownerOnly) {
    std::string p = getAbsolutePath();
    const char *fn = p.c_str();

#if defined(__linux__) || defined(__APPLE__)
    struct stat s;
    if (lstat(fn, &s) != 0) {
        return false;
    }

    int mode = s.st_mode & 07777;
    if (ownerOnly) {
        if (ex) {
            mode |= 0200;
        } else {
            mode &= ~0200;
        }
    } else {
        if (ex) {
            mode |= 0222;
        } else {
            mode &= ~0222;
        }
    }

    return chmod(fn, mode) == 0;
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    DWORD attr = GetFileAttributesA(fn);
    attr &= ~FILE_ATTRIBUTE_READONLY;
    return SetFileAttributes(fn, attr);
#else
#error Your OS is not supported
#endif
}

std::string File::toString() {
    std::string out = _root;
    bool first = true;
    for (std::string item : _path) {
        if (first) {
            first = false;
        } else {
            out += "/";
        }
        out += item;
    }
    return out;
}

std::string File::sanitizePath(std::string path) {
    for (int i = 0; i < path.length(); i++) {
#if defined(__linux__) || defined(__APPLE__)
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        if (path[i] == '\\') path[i] = '/';
#endif
    }
    return path;
}

void File::loadPath(std::string path) {
    path = sanitizePath(path);
    _path.clear();
    _root = "";
#if defined(__linux__) || defined(__APPLE__)
    if (path[0] == '/') {
        _root = "/";
        path = path.substr(1);
    }
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    if ((path.length() > 2) && (path[1] == ':')) {
        _root = path.substr(0, 3);
        path = path.substr(3);
    }
#else
#error Your OS is not supported
#endif

    std::istringstream iss(path);
    std::string item;
    while (std::getline(iss, item, '/')) {
        _path.push_back(item);
    }
}
