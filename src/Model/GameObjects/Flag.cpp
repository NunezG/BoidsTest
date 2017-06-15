#include "Model\GameObjects\Flag.h"
#include "Model\GameObjects\GameActors\GameObject.h"

CFlag::CFlag(ETeam team, CGameObject* owner) : CTeamObject(team)
{
	m_currentOwner = owner;
//	owner->ReceiveFlag(this);

}


CGameObject* CFlag::getOwner() const
{
	return m_currentOwner;
}

