#if 1
#include <iostream>
#include "iutest.hpp"
#include "wrapper.h"

class PlayAudioTest : public iutest::Test
{
public:
    PlayAudio pa;

protected:
    // virtual void SetUp(){}
    // virtual void TearDown(){}
};

IUTEST_F(PlayAudioTest, Nowait)
{
    auto wavfile = "file_example_WAV_1MG.wav";
    pa.PlayAsync(wavfile);
}

IUTEST_F(PlayAudioTest, Async_3sec)
{
    auto wavfile = "file_example_WAV_1MG.wav";
    pa.PlayAsync(wavfile);
    for (int i = 0; i < 3; i++)
    {
        std::cout << i << "秒経過" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

IUTEST_F(PlayAudioTest, Async_10sec)
{
    auto wavfile = "file_example_WAV_1MG.wav";
    pa.PlayAsync(wavfile);
    for (int i = 0; i < 10; i++)
    {
        std::cout << i << "秒経過" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
#endif
