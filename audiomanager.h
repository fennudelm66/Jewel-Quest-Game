#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QSoundEffect>
#include <QMap>
#include <QDebug>

class AudioManager : public QObject {
    Q_OBJECT

public:
    explicit AudioManager(QObject *parent = nullptr);

    // 加载音频文件
    void loadBackgroundMusic(const QString &name, const QString &filePath);
    void loadSoundEffect(const QString &name, const QString &filePath);

    // 播放控制
    void playBackgroundMusic(const QString &name);
    void stopBackgroundMusic();
    void playSoundEffect(const QString &name);

    // 音效设置
    void setGlobalVolume(float volume);  // 设置全局音量
    void setSoundEnabled(bool enabled);  // 启用或禁用音效
    bool isSoundEnabled() const;         // 获取音效是否启用
    float getGlobalVolume() const;       // 获取当前音量

private:
    QMap<QString, QSoundEffect *> backgroundMusicMap; // 多段背景音乐
    QSoundEffect *currentBackgroundMusic;            // 当前播放的背景音乐
    QMap<QString, QSoundEffect *> soundEffects;      // 音效集合
    bool soundEnabled;                               // 音效是否开启
    float globalVolume;                              // 全局音量
};

#endif // AUDIOMANAGER_H
