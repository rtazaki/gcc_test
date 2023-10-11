#if 0
#include "iutest.hpp"
#include "wrapper.h"

IUTEST(DebugFileTest, char)
{
    auto src = std::string("hoge");
    DebugFileWrite("char", src);
    IUTEST_ASSERT_STREQ("hoge", src);
}

IUTEST(DebugFileTest, char2)
{
    auto src = std::string("ほげ");
    DebugFileWrite("char2", src);
    IUTEST_ASSERT_STREQ("ほげ", src);
}

IUTEST(DebugFileTest, wchar_t)
{
    auto src = L"mohe";
    DebugFileWrite("wchar_t", src);
    IUTEST_ASSERT_STREQ(L"mohe", src);
}

IUTEST(DebugFileTest, wchar_t2)
{
    auto src = L"もへ";
    DebugFileWrite("wchar_t2", src);
    IUTEST_ASSERT_STREQ(L"もへ", src);
}

#endif
