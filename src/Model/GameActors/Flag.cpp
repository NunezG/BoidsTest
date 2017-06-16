#include "Model\GameActors\flag.h"
#include "Model\GameActors\GameObject.h"

CFlag::CFlag(ETeam team, CGameObject* owner, CFlagStand* friendlyStand) :
	CGameObject(owner->getPosition(), team)
	, m_friendlyStand(friendlyStand)
{
	m_currentOwner = owner;
}


CGameObject* CFlag::getOwner() const
{
	return m_currentOwner;
}

bool CFlag::pointRule()
{
	if ((getOwner()->getPosition() - m_friendlyStand->getPosition()).length() < 50)
		return true;

	return false;
}