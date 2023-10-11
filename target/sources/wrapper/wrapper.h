#pragma once

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>

inline void DebugFileWrite(const std::string &filename, const std::string &src)
{
    auto fs = std::filesystem::path("unittest/obj") / filename;
    fs += "*.txt";
    auto ofs = std::ofstream(fs);
    ofs << src;
}

inline void DebugFileWrite(const std::string &filename, const wchar_t *src)
{
    auto fs = std::filesystem::path("unittest/obj") / filename;
    fs += "*.txt";
    auto ofs = std::ofstream(fs);
    auto size = std::wcstombs(nullptr, src, 0) + 1;
    char dst[size];
    std::wcstombs(dst, src, size);
    ofs << dst;
}

inline std::string wcstombs(const wchar_t *src)
{
    auto size = std::wcstombs(nullptr, src, 0) + 1;
    char dst[size];
    std::wcstombs(dst, src, size);
    return dst;
}

inline std::wstring mbstowcs(const char *src)
{
    auto size = std::mbstowcs(nullptr, src, 0) + 1;
    wchar_t dst[size];
    std::mbstowcs(dst, src, size);
    return dst;
}

inline FILE *CreateFile(const wchar_t *lpfilePath)
{
    auto filepath = wcstombs(lpfilePath);
    return std::fopen(filepath.c_str(), "r");
}

inline void CloseFile(FILE *fp)
{
    std::fclose(fp);
}