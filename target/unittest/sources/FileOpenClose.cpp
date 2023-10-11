#if 1
#include "iutest.hpp"
#include "wrapper.h"

IUTEST(FileOpenClose, Open_Close)
{
    auto file = L"unittest/sources/main.cpp";
    auto fp = CreateFile(file);
    IUTEST_ASSERT_NOTNULL(fp);
    CloseFile(fp);
    IUTEST_ASSERT_NOTNULL(fp);
}
#endif
