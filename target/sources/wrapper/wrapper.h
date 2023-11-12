#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/mman.h>

#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002

#define INVALID_HANDLE_VALUE reinterpret_cast<std::fstream *>(-1)

template <typename _CharT>
class basic_filebuf_Mfile : public std::basic_filebuf<_CharT>
{
public:
    using std::basic_filebuf<_CharT>::_M_file;
};

class HANDLE
{
public:
    HANDLE() {}
    HANDLE(std::fstream *)
    {
        m_fstream = INVALID_HANDLE_VALUE;
    }

    HANDLE(std::string filepath, std::ios_base::openmode mode, long sharedMode)
    {
        m_fstream = new std::fstream(filepath, mode);
        m_shared = 0;
        if (sharedMode | FILE_SHARE_READ == FILE_SHARE_READ)
            m_shared |= PROT_READ;
        if (sharedMode | FILE_SHARE_WRITE == FILE_SHARE_WRITE)
            m_shared |= PROT_WRITE;
        m_size = std::filesystem::file_size(filepath);
    }

    operator int() const
    {
        if (m_fstream == INVALID_HANDLE_VALUE)
            return -1;
        std::fstream *fin = dynamic_cast<std::fstream *>(m_fstream);
        if (!fin->is_open())
            return -1;
        auto x = reinterpret_cast<
            basic_filebuf_Mfile<std::fstream::char_type> *>(fin->rdbuf());
        return x->_M_file.fd();
    }

    long GetSize()
    {
        return m_size;
    }

    int GetSizeH()
    {
        return m_sizeHL[1];
    }

    int GetSizeL()
    {
        return m_sizeHL[0];
    }

private:
    std::fstream *m_fstream;
    long m_shared;
    union
    {
        unsigned long m_size;
        unsigned int m_sizeHL[2];
    };
};
#define GENERIC_READ (0x80000000L)
#define GENERIC_WRITE (0x40000000L)

#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4

inline auto CreateFile(
    char *lpFileName, long accessMode, long sharedMode, void *,
    unsigned int createMode, void *, void *)
{
    auto mode = std::ios_base::openmode();
    if (accessMode | GENERIC_READ == GENERIC_READ)
        mode |= std::ios_base::in;
    if (accessMode | GENERIC_WRITE == GENERIC_WRITE)
        mode |= std::ios_base::out;
    if (createMode == CREATE_ALWAYS)
        mode |= std::ios_base::trunc;
    auto filepath = std::string(lpFileName);
    auto ec = std::error_code();
    if (createMode == OPEN_EXISTING && !std::filesystem::exists(filepath, ec))
        return HANDLE(INVALID_HANDLE_VALUE);
    return HANDLE(filepath, mode, sharedMode);
}

inline auto CreateFileMapping(
    HANDLE hFile, void *, int type, int sizeH, int sizeL, wchar_t *)
{
    // auto filepath = "mmap_read.txt";
    // std::fstream f(filepath, std::ios::in | std::ios::out);
    // auto filesize = std::filesystem::file_size(filepath);
    // //
    // auto pagesize = sysconf(_SC_PAGESIZE);
    // auto mmapsize = (filesize / pagesize + 1) * pagesize;
    // auto fd = GetFd(f);
    return 0;
}
