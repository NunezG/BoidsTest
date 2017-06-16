#ifndef FLAGSTAND_H
#define FLAGSTAND_H

#include "Model/GameObjects/GameActors/GameObject.h"

class CFlag;


class CFlagStand : public CGameObject
{
public:

	CFlagStand(Vector2d position, ETeam team);

	CFlagStand() : CGameObject(Vector2d(0,0), ETeam::antelopesTeam)
	{


	}

	EObjectType objectType() const
	{
		return EObjectType::Stand;
	}
private:


	float m_fApparitionRadius;

	CFlag* ownedFlag;
};

#endif
