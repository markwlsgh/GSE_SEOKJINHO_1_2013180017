#pragma once
class Object
{
	float m_x;
	float m_y;
	float m_z;
	float m_size;
	float m_r;
	float m_g;
	float m_b;
	float m_a;
	
	//speed Vector
	float m_speedVx;
	float m_speedVy;
	float m_speedVz;
public:
	Object(int x, int y);
	~Object();

	// Get Functions
	float GetPositionX() { return m_x; }
	float GetPositionY() { return m_y; }
	float GetPositionZ() { return m_z; }
	float GetSize() { return m_size;	}
	float GetColorRed() { return m_r; }
	float GetColorGreen() { return m_g; }
	float GetColorBlue() { return m_b; }
	float GetColorAlpha() { return m_a; }

	// Set Functions
	void SetPositionX(float val) {  m_x = val; }
	void SetPositionY(float val) {  m_y = val; }
	void SetPositionZ(float val) {  m_z = val; }
	void SetSize(float val) { m_size = val; }
	void SetColorRed(float val) { m_r = val; }
	void SetColorGreen(float val) { m_g = val; }
	void SetColorBlue(float val) { m_b = val; }
	void SetColorAlpha(float val) { m_a = val; }
	void SetSpeedVector(float valX, float valY, float valZ) {
		m_speedVx = valX; m_speedVy = valY; m_speedVz = valZ;}

	// Update()
	void Update(float elapsedTime );
	// Colide
	bool isColide(Object& a, Object& b);
};

