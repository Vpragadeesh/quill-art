#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/file.h>
#endif

class FileHandler {
private:
    std::string filename;
    std::fstream file;

#ifdef _WIN32
    HANDLE hFile;
#else
    int fd;
#endif

public:
    FileHandler(const std::string& filename, std::ios::openmode mode) : filename(filename) {
#ifdef _WIN32
        DWORD access = 0;
        if (mode & std::ios::in) access |= GENERIC_READ;
        if (mode & std::ios::out) access |= GENERIC_WRITE;

        hFile = CreateFileA(filename.c_str(), access, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("Failed to open file exclusively.");
        }
#else
        int flags = 0;
        if (mode & std::ios::in) flags |= O_RDONLY;
        if (mode & std::ios::out) flags |= O_RDWR;
        if (mode & std::ios::app) flags |= O_APPEND;
        if (mode & std::ios::trunc) flags |= O_TRUNC;

        fd = open(filename.c_str(), flags, 0666);
        if (fd == -1) {
            throw std::runtime_error("Failed to open file.");
        }

        if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
            close(fd);
            throw std::runtime_error("File is already locked by another process.");
        }
#endif
        file.open(filename, mode);
        if (!file.is_open()) {
#ifdef _WIN32
            CloseHandle(hFile);
#else
            close(fd);
#endif
            throw std::runtime_error("Failed to open file stream.");
        }
    }

    std::fstream& stream() {
        return file;
    }

    ~FileHandler() {
        file.close();
#ifdef _WIN32
        if (hFile != INVALID_HANDLE_VALUE) {
            CloseHandle(hFile);
        }
#else
        if (fd != -1) {
            flock(fd, LOCK_UN);
            close(fd);
        }
#endif
    }
};

// int main() {
//     try {
//         FileHandler file("test.txt", std::ios::in | std::ios::out | std::ios::app);
//         file.stream() << "Hello, World!\n";
//         std::cout << "File locked and written successfully.\n";
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << '\n';
//     }
//     return 0;
// }
