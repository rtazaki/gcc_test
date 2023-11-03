#include <filesystem>
#include <fstream>
#include <thread>
#include <iostream>
#include <pulse/simple.h>

void play_audio(const std::string wavfile, pa_simple *pa)
{
    auto filesize = std::filesystem::file_size(wavfile);
    char buf[filesize];
    std::ifstream fin(wavfile, std::ios::binary);
    fin.read(buf, filesize);
    fin.close();
    std::puts("before pa_simple_write");
    pa_simple_write(pa, buf, filesize, nullptr);
    std::puts("after pa_simple_write");
}

int main()
{
    const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 44100,
        .channels = 2};
    auto pa = pa_simple_new(
        nullptr, "pulseaudio_hoge", PA_STREAM_PLAYBACK,
        nullptr, "play", &ss, nullptr, nullptr, nullptr);

    auto wavfile = "file_example_WAV_1MG.wav";
    auto t1 = std::thread(play_audio, wavfile, pa);
    t1.detach();

    // 再生時間よりも待ちが短いと、pa_simple_drainで待つ。
    // 待ちが長くても問題なく終了する。(例: 10秒とか)
    for (int i = 0; i < 3; i++)
    {
        std::cout << i << "秒経過" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::puts("最後まで待ってから閉じる。");
    pa_simple_drain(pa, nullptr);
    pa_simple_free(pa);
    std::puts("main終端");
    return 0;
}
