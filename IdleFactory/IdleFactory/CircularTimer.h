#pragma once
class TextureManager;
class CircularTimer
{
public:
	CircularTimer(const Point2f& position,int seconds, float size);
	~CircularTimer();
	CircularTimer(const CircularTimer& other);
	CircularTimer(CircularTimer&& other) noexcept;
	CircularTimer& operator=(const CircularTimer& other);
	CircularTimer& operator=(CircularTimer&& other) noexcept;
	
	void Update(float elapsedSec);
	void Draw() const;
	void Reset();
	bool HasTimerRunOut() const;
	void UpdateMaxSeconds(int seconds);
	int GetMaxSeconds() const;
private:
	Point2f m_Position;
	float m_Angle;
	int m_Seconds;
	float m_Interval;
	float m_SecondsText;
	float m_Size;
	Circlef m_Circle;
};

