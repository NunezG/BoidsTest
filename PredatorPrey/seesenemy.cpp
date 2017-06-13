////////////////////////////////////////////////////////////////////////////////
// file: seesenemy.cpp
// author: Radim Rehurek
// last update: 25.09.04
//
// sees enemy event
//////////////////////////////////////////////////////////////////////////////////

#include "agent.h"
#include "seesenemy.h"
#include "game.h"
#include "GameObjects\ObjectManager.h"

SeesEnemy::SeesEnemy() {
    m_name      = "SeesEnemy";
    m_owner     = NULL;
}

void SeesEnemy::init   ( CAgent * owner ) {
    m_owner = dynamic_cast<CAgent *> (owner);
}

bool SeesEnemy::update () {
	CAgent *nmy = findNearestVisibleEnemy();
	if (nmy != NULL) {
		m_owner->setEnemy(nmy);
		return true;
	}
	return false;
}

CAgent * SeesEnemy::findNearestVisibleEnemy() {
	CAgent *bestAgent = NULL;
	float bestDist = 1E10;
	for (std::list <CAgent *>::iterator agent = CObjectManager::m_agents.begin(); agent != CObjectManager::m_agents.end(); agent++) {
		if ((*agent)->GetTeam() != m_owner->GetTeam() && (*agent)->m_active && *agent != m_owner) {
			float dist = m_owner->distanceTo(*agent);
			if (dist < bestDist && m_owner->canSee(*agent)) {
				bestAgent = *agent;
				bestDist = dist;
			}
		}
	}
	return bestAgent;
}


CAgent * SeesEnemy::getOwner () {
    return m_owner;
}

const char * SeesEnemy::getName() {
    return m_name.c_str();
}
