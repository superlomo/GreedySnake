#include "SoundManager.h"
#include <QtMultimedia/qmediaplayer.h>
#include <QtMultimedia/qmediaplaylist.h>
#include <qurl.h>

SoundManager::SoundManager(QObject *parent)
	: QObject(parent)
{
	m_mediaPlayer = new QMediaPlayer(this);
}

SoundManager::~SoundManager()
{
}

void SoundManager::playBackgroundMusic()
{
	m_mainBackgroundPlayList = new QMediaPlaylist(this);
	for (auto& musicName : m_mainBackgroundMusicList)
	{
		m_mainBackgroundPlayList->addMedia(QUrl(musicName));
	}
	m_mainBackgroundPlayList->setPlaybackMode(QMediaPlaylist::Random);
	m_mediaPlayer->setPlaylist(m_mainBackgroundPlayList);
	m_mediaPlayer->setVolume(50);
	m_mediaPlayer->play();
}
