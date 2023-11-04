#pragma once
#include <filesystem>
#include <fstream>
#include <mutex>
#include <pulse/simple.h>
#include <thread>

/// @attention 中断とか真面目にやるなら、pulse/simpleを使ってはいけない。

/// @note 分割せずにそのままバッファを突っ込む。
/// @attention 超巨大ファイルの再生とかはしない。
void play_audio(const std::string wavfile, pa_simple *pa, std::mutex *mtx)
{
    std::puts("play_audio");
    auto filesize = std::filesystem::file_size(wavfile);
    char buf[filesize];
    std::ifstream fin(wavfile, std::ios::binary);
    fin.read(buf, filesize);
    fin.close();
    std::puts("play_audio: unlock()");
    mtx->unlock();
    std::puts("before pa_simple_write");
    pa_simple_write(pa, buf, filesize, nullptr);
    std::puts("after pa_simple_write");
}

class PlayAudio
{
public:
    /// @brief リソース生成
    PlayAudio()
    {
        std::puts("PlayAudio");
        const pa_sample_spec ss = {
            .format = PA_SAMPLE_S16LE,
            .rate = 44100,
            .channels = 2};
        m_pa = pa_simple_new(
            nullptr, "pulseaudio_hoge", PA_STREAM_PLAYBACK,
            nullptr, "play", &ss, nullptr, nullptr, nullptr);
        std::puts("PlayAudio end");
    }

    /// @brief 非同期再生
    /// @param wavfile 再生するファイル
    /// @param pa PulseAudio Simple API接続情報
    /// @brief 数秒程度のwavfileを想定し、待たずに即応答する。
    /// @attention ファイル再生中かどうかは気にしない。
    void PlayAsync(const std::string &wavfile)
    {
        std::puts("PlayAsync");
        m_mtx = new std::mutex();
        std::puts("PlayAsync: lock()");
        m_mtx->lock();
        auto t1 = std::thread(play_audio, wavfile, m_pa, m_mtx);
        t1.detach();
        std::puts("PlayAsync end");
    }

    /// @brief 解放待ち
    /// @param pa PulseAudio Simple API接続情報
    /// @note 再生中にプログラム停止されるとシステムに優しくないので最後まで待つ。
    /// @attention 非同期再生コール後、1ms(pa_simple_writeされた後?)程度後であれば、
    /// 再生終了を待つため、安全。
    ~PlayAudio()
    {
        std::puts("~PlayAudio");
        std::puts("~PlayAudio: lock()");
        m_mtx->lock();
        pa_simple_drain(m_pa, nullptr);
        pa_simple_free(m_pa);
        delete m_mtx;
        std::puts("~PlayAudio end");
    }

private:
    pa_simple *m_pa;
    std::mutex *m_mtx;
};
