#define MA_NO_DECODING
#define MA_NO_ENCODING

#include <thread>
#include <chrono>
#include <stdio.h>
#include "miniaudio.h"

// 后台运行
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_waveform* pWave;


    pWave = (ma_waveform*)pDevice->pUserData;

    ma_waveform_read_pcm_frames(pWave, pOutput, frameCount, NULL);

    (void)pInput;   /* Unused. */
}

int main(int argc, char** argv)
{
    ma_device_config deviceConfig;
    ma_device device;
    ma_waveform Wave;
    ma_waveform_config WaveConfig;

    ma_result result;
    ma_context context;
    ma_device_info* pPlaybackDeviceInfos;
    ma_uint32 playbackDeviceCount;

    if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS) {
        printf("Failed to initialize context.\n");
        return -2;
    }

    result = ma_context_get_devices(&context, &pPlaybackDeviceInfos, &playbackDeviceCount, NULL, NULL);
    if (result != MA_SUCCESS) {
        printf("Failed to retrieve device information.\n");
        return -3;
    }

    // 初始化设备配置
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = ma_format_u8;
    deviceConfig.playback.channels = 2;
    deviceConfig.sampleRate = 0;
    deviceConfig.dataCallback = data_callback;
    deviceConfig.pUserData = &Wave;

	// 选择扬声器
    printf("Playback Devices\n");
    for (int iDevice = 0; iDevice < playbackDeviceCount; ++iDevice) {
        ma_device_info iter = pPlaybackDeviceInfos[iDevice];
        printf("    %d: %s\n", iDevice, iter.name);
        if (strstr(iter.name, "扬声器") || strstr(iter.name, "speaker"))
        {
            deviceConfig.playback.pDeviceID = &iter.id;
            break;
        }
    }

    if (ma_device_init(&context, &deviceConfig, &device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        return -3;
    }

    //无声音频
    WaveConfig = ma_waveform_config_init(
        device.playback.format, 
        device.playback.channels, 
        device.sampleRate, 
        ma_waveform_type_square, 
        0, 0);

    ma_waveform_init(&WaveConfig, &Wave);

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&device);
        return -4;
    }

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::hours(1));
    }

    ma_device_uninit(&device);
	ma_context_uninit(&context);

    return 0;
}