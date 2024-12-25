
#include <QObject>
#include <QSoundEffect>
#include <QMap>

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

private:
    QMap<QString, QSoundEffect *> backgroundMusicMap; // 多段背景音乐
    QSoundEffect *currentBackgroundMusic; // 当前播放的背景音乐
    QMap<QString, QSoundEffect *> soundEffects; // 音效集合
};
