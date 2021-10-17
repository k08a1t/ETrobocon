//S)

//E)

#ifndef COMMUNICATION_SOUND_H
#define COMMUNICATION_SOUND_H

//S)
#include "Clock.h"
using namespace ev3api;
//E)

class Sound
{
	//S)
	
	//E)

private:

	bool m_soundcheckbox;

	int m_tone;

	Clock* m_pClock;

public:

	Sound(Clock* pClock);

	void beat();

	void instructBeat();

	~Sound();

	//S)
	
	//E)
};

//S)

//E)

#endif	// COMMUNICATION_SOUND_H

//S)

//E)
