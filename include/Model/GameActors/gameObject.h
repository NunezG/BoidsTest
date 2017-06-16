
#ifndef GAMEOBJECR_H
#define GAMEOBJECR_H


#include <cmath>

template <class T> inline T aminmax(T low, T val, T high) {
	if (val < low)
		return low;
	if (val > high)
		return high;
	return val;
}

struct Vector2d {
public:
	float m_x;
	float m_y;
	Vector2d(float x = 0, float y = 0) : m_x(x), m_y(y) {}
	Vector2d(const Vector2d &v) { m_x = v.m_x; m_y = v.m_y; }
	void scale(float factor) { m_x *= factor; m_y *= factor; }
	void stretchTo(float len) { float length = this->length(); if (length > 0) this->scale(len / length); }
	void normalize() { this->stretchTo(1.0f); }
	void truncate(float len) { float length = this->length(); if (length > len) this->stretchTo(len); }
	void clamp(const Vector2d &p1, const Vector2d &p2) { m_x = aminmax(p1.m_x, m_x, p2.m_x); m_y = aminmax(p1.m_y, m_y, p2.m_y); }

	float sqrLength() const { return m_x * m_x + m_y * m_y; }
	float length() const { return sqrtf(m_x * m_x + m_y * m_y); }
	Vector2d operator+(const Vector2d &v2) const { return Vector2d(m_x + v2.m_x, m_y + v2.m_y); }
	Vector2d operator-() const { return Vector2d(-m_x, -m_y); }
	Vector2d operator-(const Vector2d &v2) const { return (*this) + (-v2); }
	Vector2d operator*(float f) const { return Vector2d(m_x * f, m_y * f); }
};


enum EObjectType 
{
	Flag,
	Agent,
	Stand
};

enum ETeam
{
	lionsTeam,
	antelopesTeam
};


class CGameObject 
{
protected:
	Vector2d m_position;

public:
	
	CGameObject(Vector2d position, ETeam team) :
		m_eObjectTeam(team)
	, m_position(position)
	{
		
	}
	CGameObject(){}
	Vector2d getPosition() const { return m_position; }
	float getPosX() const { return m_position.m_x; }
	float getPosY() const { return m_position.m_y; }

	// static routines
	static float agentDistance(const CGameObject *agent1, const CGameObject *agent2) { return (agent1->getPosition() - agent2->getPosition()).length(); }
	static float sqrAgentDistance(const CGameObject *agent1, const CGameObject *agent2) { return (agent1->getPosition() - agent2->getPosition()).sqrLength(); }
	float distanceTo(const CGameObject *other) const { return agentDistance(this, other); }
	float sqrDistanceTo(const CGameObject *other) const { return sqrAgentDistance(this, other); }
	
	virtual EObjectType objectType() const = 0;

	void SetTeam(ETeam team) { m_eObjectTeam = team; }
	ETeam GetTeam() const { return m_eObjectTeam; }

	bool IsOfTeam(ETeam team) const { return m_eObjectTeam == team; }

protected:

	float m_fCollisionRadius;

	ETeam m_eObjectTeam;


};


#endif
