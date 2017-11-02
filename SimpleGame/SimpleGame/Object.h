#pragma once
class Object
{
	float m_x;
	float m_y;
	float m_z;
	float m_size;
	float m_color[4];		// 0 r 1 b 2 g 3 a
	
	//speed Vector
	float m_speedVx;
	float m_speedVy;
	float m_speedVz;

	// is colision ?
	bool m_isColision;

	// Life
	float m_life;
	float m_lifeTime;

public:
	Object(int x, int y);
	~Object();

	// Get Functions
	float GetPositionX() { return m_x; }
	float GetPositionY() { return m_y; }
	float GetPositionZ() { return m_z; }
	float GetSize() { return m_size ;	}
	float GetColorRed() { return m_color[0]; }
	float GetColorGreen() { return m_color[1]; }
	float GetColorBlue() { return m_color[2]; }
	float GetColorAlpha() { return m_color[3]; }
	bool GetIsColision() { return m_isColision; }
	float GetHalfSize() { return m_size *0.5f; }

	// Set Functions
	void SetPositionX(float val) {  m_x = val; }
	void SetPositionY(float val) {  m_y = val; }
	void SetPositionZ(float val) {  m_z = val; }
	void SetSize(float val) { m_size = val; }
	void SetColor(float red, float green, float blue, float alpha) {
		m_color[0] = red;
		m_color[1] = blue;
		m_color[2] = green;
		m_color[3] = alpha;
	}
	void SetSpeedVector(float valX, float valY, float valZ) {
		m_speedVx = valX; m_speedVy = valY; m_speedVz = valZ;}
	void SetIsColision(bool a) { m_isColision = a; }

	// Update()
	void Update(float elapsedTime );

};

