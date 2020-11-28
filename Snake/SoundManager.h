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
	const QStringList m_mainBackgroundMusicList =
	{
		"qrc:/MainWindow/resource/music/Bumbling-Burglars_Looping.mp3",
		//"qrc:/MainWindow/resource/music/The-Hard-Luck-Gang.mp3",
		//"qrc:/MainWindow/resource/music/Trancyvania.mp3"
	};
};