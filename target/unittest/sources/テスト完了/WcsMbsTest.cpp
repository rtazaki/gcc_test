#if 0
#include "iutest.hpp"
#include "wrapper.h"

IUTEST(WcsMbsTest, wcstombs)
{
    const wchar_t src[260] = L"あいうえお";
    auto dest = wcstombs(src);
    IUTEST_ASSERT_STREQ("あいうえお", dest);
}

IUTEST(WcsMbsTest, mbstowcs)
{
    const char src[260] = "かきくけこ";
    auto dest = mbstowcs(src);
    IUTEST_ASSERT_STREQ(L"かきくけこ", dest);
}
#endif
