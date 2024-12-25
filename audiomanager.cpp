#include "audiomanager.h"

AudioManager::AudioManager(QObject *parent) : QObject(parent), currentBackgroundMusic(nullptr) {}

void AudioManager::loadBackgroundMusic(const QString &name, const QString &filePath) {
    if (backgroundMusicMap.contains(name)) {
        delete backgroundMusicMap[name];
    }
    QSoundEffect *music = new QSoundEffect(this);
    music->setSource(QUrl(filePath.startsWith("qrc:/") ? filePath : QUrl::fromLocalFile(filePath)));
    music->setLoopCount(QSoundEffect::Infinite); // 无限循环
    music->setVolume(0.5); // 设置音量
    backgroundMusicMap[name] = music;
}

void AudioManager::loadSoundEffect(const QString &name, const QString &filePath) {
    if (soundEffects.contains(name)) {
        delete soundEffects[name];
    }
    QSoundEffect *effect = new QSoundEffect(this);
    effect->setSource(QUrl(filePath.startsWith("qrc:/") ? filePath : QUrl::fromLocalFile(filePath)));
    effect->setVolume(1.0); // 设置音量
    soundEffects[name] = effect;
}

void AudioManager::playBackgroundMusic(const QString &name) {
    if (backgroundMusicMap.contains(name)) {
        if (currentBackgroundMusic) {
            currentBackgroundMusic->stop();
        }
        currentBackgroundMusic = backgroundMusicMap[name];
        if (currentBackgroundMusic && currentBackgroundMusic->status() == QSoundEffect::Ready) {
            currentBackgroundMusic->play();
        }
    }
}

void AudioManager::stopBackgroundMusic() {
    if (currentBackgroundMusic) {
        currentBackgroundMusic->stop();
    }
}

void AudioManager::playSoundEffect(const QString &name) {
    if (soundEffects.contains(name) && soundEffects[name]->status() == QSoundEffect::Ready) {
        soundEffects[name]->play();
    }
}
