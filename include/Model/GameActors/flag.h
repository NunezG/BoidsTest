#ifndef FLAG_H
#define FLAG_H

#include "Model\GameActors\GameObject.h"
#include "Model\GameActors\flagStand.h"

class CAgent;
class CFlagStand;

enum EFlagState
{
	flriendlyStand,
	enemyStand,
	friendlyAgent,
	enemyAgent
};

class CFlag : public CGameObject
{
public:

	CFlag(ETeam team, CGameObject* owner, CFlagStand* friendlyStand);

	EObjectType objectType() const {	return EObjectType::Flag; }

	CGameObject* getOwner() const;

	void setOwner(CGameObject* owner){ m_currentOwner = owner; }

	bool pointRule();

	EFlagState getState() const { return m_currentState; }

private:

	CFlagStand* m_friendlyStand;

	EFlagState m_currentState;

	CGameObject* m_currentOwner;



};

#endif
