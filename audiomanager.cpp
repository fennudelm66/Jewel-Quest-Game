#include "audiomanager.h"

AudioManager::AudioManager(QObject *parent) : QObject(parent), currentBackgroundMusic(nullptr), soundEnabled(true), globalVolume(1.0f) {}

// 加载背景音乐
void AudioManager::loadBackgroundMusic(const QString &name, const QString &filePath) {
    if (backgroundMusicMap.contains(name)) {
        delete backgroundMusicMap[name];
    }
    QSoundEffect *music = new QSoundEffect(this);
    music->setSource(QUrl(filePath.startsWith("qrc:/") ? filePath : QUrl::fromLocalFile(filePath)));
    music->setLoopCount(QSoundEffect::Infinite);
    music->setVolume(globalVolume);
    backgroundMusicMap[name] = music;
}

// 加载音效
void AudioManager::loadSoundEffect(const QString &name, const QString &filePath) {
    if (soundEffects.contains(name)) {
        delete soundEffects[name];
    }
    QSoundEffect *effect = new QSoundEffect(this);
    effect->setSource(QUrl(filePath.startsWith("qrc:/") ? filePath : QUrl::fromLocalFile(filePath)));
    effect->setVolume(globalVolume);
    soundEffects[name] = effect;
}

// 播放背景音乐
void AudioManager::playBackgroundMusic(const QString &name) {
    if (backgroundMusicMap.contains(name)) {
        if (currentBackgroundMusic) {
            currentBackgroundMusic->stop();
        }
        currentBackgroundMusic = backgroundMusicMap[name];
        if (soundEnabled && currentBackgroundMusic) {
            currentBackgroundMusic->play();
        }
    }
}

// 停止播放当前背景音乐
void AudioManager::stopBackgroundMusic() {
    if (currentBackgroundMusic) {
        currentBackgroundMusic->stop();
    }
}

// 播放音效
void AudioManager::playSoundEffect(const QString &name) {
    if (soundEffects.contains(name) && soundEffects[name]->status() == QSoundEffect::Ready) {
        if (soundEnabled) {
            soundEffects[name]->play();
        }
    }
}

// 设置全局音量
void AudioManager::setGlobalVolume(float volume) {
    globalVolume = volume;
    if (currentBackgroundMusic) {
        currentBackgroundMusic->setVolume(volume);
    }
    for (auto effect : soundEffects) {
        effect->setVolume(volume);
    }
}

// 启用或禁用音效
void AudioManager::setSoundEnabled(bool enabled) {
    soundEnabled = enabled;
    if (!enabled && currentBackgroundMusic) {
        currentBackgroundMusic->stop();
    } else if (enabled && currentBackgroundMusic) {
        currentBackgroundMusic->play();
    }
}

// 获取当前音量
float AudioManager::getGlobalVolume() const {
    return globalVolume;
}

// 检查音效是否启用
bool AudioManager::isSoundEnabled() const {
    return soundEnabled;
}
