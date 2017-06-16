

#ifndef _characterbrainlib_h_
#define _characterbrainlib_h_

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
#endif
