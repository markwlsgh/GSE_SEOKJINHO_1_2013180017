#pragma once
class Object
{

	float m_x;
	float m_y;
	float m_z;
	float m_size;
	float m_color[4];		// 0 r 1 b 2 g 3 a

	//speed Vector
	float m_moveDir[3]; // x,y,z
	float m_speed;

	// is colision ?
	bool m_isColision;

	// Life
	float m_life;
	float m_lifeTime;
	int m_type;

	float m_coolTime;
	bool m_isShoot;

	float m_lastBullet;
	float m_lastArrow;

	int m_parentID;
public:
	Object(float x, float y, int type);
	~Object();

	// Get Functions
	float GetPositionX() { return m_x; }
	float GetPositionY() { return m_y; }
	float GetPositionZ() { return m_z; }
	float GetSize() { return m_size; }
	float GetColorRed() { return m_color[0]; }
	float GetColorGreen() { return m_color[1]; }
	float GetColorBlue() { return m_color[2]; }
	float GetColorAlpha() { return m_color[3]; }
	bool GetIsColision() { return m_isColision; }
	float GetHalfSize() { return m_size *0.5f; }
	float GetCoolTime() { return m_coolTime; }

	float GetLife() { return m_life; }
	float GetLifeTime() { return m_lifeTime; }
	bool GetIsShoot() { return m_isShoot; }
	
	int GetType() { return m_type; }
	float GetLastBullet() { return m_lastBullet; }
	float GetLastArrow() { return m_lastArrow; }
	int GetParentID() { return m_parentID;  }

	// Set Functions
	void SetPosition(float x, float y, float z) { m_x = x; m_y = y; m_z = z; }
	void SetPositionX(float val) {  m_x = val; }
	void SetPositionY(float val) {  m_y = val; }
	void SetPositionZ(float val) {  m_z = val; }
	void SetSize(float val) { m_size = val; }
	void SetColor(float red, float green, float blue, float alpha) {
		m_color[0] = red;
		m_color[1] = green;
		m_color[2] = blue;
		m_color[3] = alpha;
	}
	void SetObjectType(int type) { m_type = type; }
	void SetMoveDirVector(float valX, float valY, float valZ) {
		m_moveDir[0] = valX; m_moveDir[1] = valY; m_moveDir[2] = valZ;}
	void SetIsColision(bool a) { m_isColision = a; }
	void SetLife(float val) { m_life = val; }
	void SetSpeed(float val) { m_speed = val; }
	void SetCoolTime(float val) { m_coolTime = val; }
	void SetIsShoot(bool a) { m_isShoot = a; }
	void SetDamage(float amount) { m_life -= amount; }

	void SetLastBullet(float val) { m_lastBullet = val; }
	void SetLastArrow(float val) { m_lastArrow = val; }

	void SetParentID(int val) { m_parentID = val; }


	// Update()
	void Update(float elapsedTime );

};

