#pragma once

#include <QObject>

class SoundManager : public QObject
{
	Q_OBJECT

public:
	SoundManager(QObject *parent);
	~SoundManager();
};
