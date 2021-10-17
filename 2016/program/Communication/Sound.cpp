//S)
#include "Sound.h"

#include "Clock.h"
using namespace ev3api;
//E)

Sound::Sound(Clock* pClock)
//S)
 : m_pClock(pClock)
//E)
{
	//S)
	m_soundcheckbox = false;
	m_tone = 1;	
	//E)
}

void Sound::beat()
{
	//S)
	if(m_soundcheckbox == true){
		m_soundcheckbox = false;
		switch(m_tone){
		case 1:
			ev3_speaker_play_tone(NOTE_A6, 100);
			break;
		case 2:
			ev3_speaker_play_tone(NOTE_B6, 100);
			break;
		case 3:
			ev3_speaker_play_tone(NOTE_C6, 100);
			break;
		case 4:
			ev3_speaker_play_tone(NOTE_D6, 100);
			break;
		case 5:
			ev3_speaker_play_tone(NOTE_E6, 100);
			break;
		case 6:
			ev3_speaker_play_tone(NOTE_F6, 100);
			break;
		}
		m_pClock->wait(100);
		m_tone++;
		if(m_tone>=7){
			m_tone = 1;
		}
	}	
	//E)
}

void Sound::instructBeat()
{
	//S)
	m_soundcheckbox = true;	
	//E)
}

Sound::~Sound()
{
	//S)
	
	//E)
}

//S)

//E)
