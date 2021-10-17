//S)

//E)

#ifndef COMMUNICATION_COMMUNICATION_H
#define COMMUNICATION_COMMUNICATION_H

//S)
#include "Sound.h"
//E)

class Communication
{
	//S)
	
	//E)

private:

	Sound* m_pSound;

public:

	Communication(Sound* pSound);

	void update();

	void setSound();

	~Communication();

	//S)
	
	//E)
};

//S)

//E)

#endif	// COMMUNICATION_COMMUNICATION_H

//S)

//E)
