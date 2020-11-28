#pragma once

#include <QObject>
#include <qstring.h>

class QMediaPlayer;
class QMediaPlaylist;

class SoundManager : public QObject
{
	Q_OBJECT

public:
	SoundManager(QObject *parent);
	~SoundManager();

	void playBackgroundMusic();

private:
	QMediaPlayer* m_mediaPlayer;
	QMediaPlaylist *m_mainBackgroundPlayList;
	const QString m_mainBackgroundMusic = "qrc:/MainWindow/resource/music/Bumbling-Burglars_Looping.mp3";
};
