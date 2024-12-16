#include "AudioManager.h"

// 构造函数，初始化背景音乐播放器和播放列表
AudioManager::AudioManager(QObject *parent) : QObject(parent) {
    backgroundMusicPlayer = new QMediaPlayer(this);  // 初始化背景音乐播放器
    playlist = new QMediaPlaylist(this);  // 初始化播放列表
    backgroundMusicPlayer->setPlaylist(playlist);  // 将播放列表绑定到播放器
    playlist->setPlaybackMode(QMediaPlaylist::Loop);  // 设置播放列表为循环模式
}

// 播放背景音乐
void AudioManager::playBackgroundMusic(const QString &filePath) {
    playlist->clear();  // 清空播放列表
    playlist->addMedia(QUrl::fromLocalFile(filePath));  // 将本地音乐文件路径添加到播放列表
    backgroundMusicPlayer->play();  // 开始播放背景音乐
}

// 停止背景音乐
void AudioManager::stopBackgroundMusic() {
    backgroundMusicPlayer->stop();  // 停止播放
}

// 播放指定音效
void AudioManager::playSoundEffect(const QString &effectName) {
    if (soundEffects.contains(effectName)) {  // 检查是否加载了指定名称的音效
        soundEffects[effectName]->play();  // 播放音效
    }
}

// 加载音效文件并与名称关联
void AudioManager::loadSoundEffect(const QString &effectName, const QString &filePath) {
    if (!soundEffects.contains(effectName)) {  // 如果音效名称未被加载
        QMediaPlayer *effectPlayer = new QMediaPlayer(this);  // 创建新的音效播放器
        effectPlayer->setMedia(QUrl::fromLocalFile(filePath));  // 绑定音效文件
        soundEffects.insert(effectName, effectPlayer);  // 将名称和播放器映射存储到 QMap 中
    }
}

// 设置背景音乐和音效的音量
void AudioManager::setVolume(int volume) {
    backgroundMusicPlayer->setVolume(volume);  // 设置背景音乐音量
    // 遍历所有音效播放器，设置它们的音量
    for (auto effectPlayer : soundEffects) {
        effectPlayer->setVolume(volume);
    }
}
