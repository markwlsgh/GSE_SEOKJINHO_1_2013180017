#pragma once
class Object
{
	float x;
	float y;
	float z;
	float size;
	float r;
	float g;
	float b;
	float a;
	float movingSpeed;
public:
	Object();
	~Object();

	float GetPositionX() { return x; }
	float GetPositionY() { return y; }
	float GetPositionZ() { return z; }
	float GetSize() { return size; }
	float GetColorRed() { return r; }
	float GetColorGreen() { return g; }
	float GetColorBlue() { return b; }
	float GetColorAlpha() { return a; }
	float GetMovingSpeed() { return movingSpeed; }

	void SetPositionX(float val) {  x = val; }
	void SetPositionY(float val) {  y = val; }
	void SetPositionZ(float val) {  z = val; }
	void SetSize(float val) { size = val; }
	void SetColorRed(float val) { r = val; }
	void SetColorGreen(float val) { g = val; }
	void SetColorBlue(float val) { b = val; }
	void SetColorAlpha(float val) { a = val; }
	void SetMovingSpeed(float val) { movingSpeed = val; }
};

