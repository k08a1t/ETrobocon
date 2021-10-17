//S)

#include "Communication.h"

#include "Sound.h"
//E)

Communication::Communication(Sound* pSound)
//S)
 : m_pSound(pSound)
//E)
{
	//S)
	
	
	//E)
}

void Communication::update()
{
	//S)
		
	m_pSound -> beat();
	//E)
}

void Communication::setSound()
{
	//S)
		
	m_pSound -> instructBeat();
	//E)
}

Communication::~Communication()
{
	//S)
	
	
	//E)
}

//S)

//E)
