#include "iutest.hpp"
#include "wrapper.h"

class CreateFileTest : public iutest::Test
{
protected:
    virtual void SetUp()
    {
        std::filesystem::copy_file("mmap_read.txt", "unittest/obj/mmap_read.txt");
    }
    virtual void TearDown()
    {
        std::filesystem::remove("unittest/obj/mmap_read.txt");
    }
};

IUTEST_F(CreateFileTest, GENERIC_READ_OPEN_EXISTING)
{
    auto filepath = "unittest/obj/mmap_read.txt";
    auto hFile = CreateFile(
        (char *)filepath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, nullptr, nullptr);
    IUTEST_ASSERT_NE(-1, hFile);
    IUTEST_ASSERT_EQ(4, hFile.GetSize());
    IUTEST_ASSERT_EQ(0, hFile.GetSizeH());
    IUTEST_ASSERT_EQ(4, hFile.GetSizeL());
}

IUTEST_F(CreateFileTest, GENERIC_READ_OPEN_EXISTING_notfound)
{
    auto filepath = "unittest/obj/mmap_read____.txt";
    auto hFile = CreateFile(
        (char *)filepath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, nullptr, nullptr);
    IUTEST_ASSERT_EQ(-1, hFile);
}

IUTEST_F(CreateFileTest, accessModeなし)
{
    auto filepath = "unittest/obj/mmap_read.txt";
    auto hFile = CreateFile(
        (char *)filepath, 0, 0, nullptr, OPEN_EXISTING, nullptr, nullptr);
    IUTEST_ASSERT_NE(-1, hFile);
}

IUTEST_F(CreateFileTest, GENERIC_WRITE_OPEN_EXISTING)
{
    auto filepath = "unittest/obj/mmap_read.txt";
    auto hFile = CreateFile(
        (char *)filepath, GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, nullptr, nullptr);
    IUTEST_ASSERT_NE(-1, hFile);
}

IUTEST_F(CreateFileTest, GENERIC_WRITE_OPEN_EXISTING_notfound)
{
    auto filepath = "unittest/obj/mmap_read____.txt";
    auto hFile = CreateFile(
        (char *)filepath, GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, nullptr, nullptr);
    IUTEST_ASSERT_EQ(-1, hFile);
}
