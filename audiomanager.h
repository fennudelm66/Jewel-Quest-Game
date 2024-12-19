#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include<QObject>
#include<QMediaPlayer>
#include<QMap>


class AudioManager : public QObject
{
    Q_OBJECT

public:
    explicit AudioManager(QObject *parent = nullptr);

    void playBackgroundMusic(const QString &filePath);
    void stopBackgroundMusic();
    void playSoundEffect(const QString &effectName);
    void loadSoundEffect(const QString &effectName, const QString &filePath);
    void setVolume(int volume);

private:
    QMediaPlayer *backgroundMusicPlayer;
    QMediaPlayer *playlist;
    QMap<QString,QMediaPlayer*> soundEffects;
};

#endif // AUDIOMANAGER_H
