#include <filesystem>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/mman.h>

template <typename _CharT>
class basic_filebuf_Mfile : public std::basic_filebuf<_CharT>
{
public:
    using std::basic_filebuf<_CharT>::_M_file;
};

int GetFd(std::ios &f)
{
    if (std::fstream *fin = dynamic_cast<std::fstream *>(&f))
    {
        if (!fin->is_open())
            return -1;
        auto x = (basic_filebuf_Mfile<std::fstream::char_type> *)fin->rdbuf();
        return x->_M_file.fd();
    }
    return -1;
}

int main()
{
    auto filepath = "mmap_read.txt";
    std::fstream f(filepath, std::ios::in | std::ios::out);
    auto filesize = std::filesystem::file_size(filepath);
    std::cout << "filesize: " << filesize << std::endl;
    auto pagesize = sysconf(_SC_PAGESIZE);
    std::cout << "pagesize: " << pagesize << std::endl;
    auto mmapsize = (filesize / pagesize + 1) * pagesize;
    std::cout << "mmapsize: " << mmapsize << std::endl;
    auto fd = GetFd(f);
    std::cout << "fd: " << fd << std::endl;
    auto mm =
        static_cast<unsigned char *>(
            mmap(nullptr, mmapsize, PROT_READ, MAP_SHARED, fd, 0));
    for (auto i = (unsigned long)0; i < mmapsize; i++)
    {
        std::cout << std::hex << mm[i] << std::endl;
        if (mm[i] == 0)
            break;
    }
    munmap(mm, mmapsize);
    return 0;
}
