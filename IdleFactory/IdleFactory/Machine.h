#pragma once
class CircularTimer;
class Machine
{
public:
	Machine(const Point2f& position, float size, int time, int price);
	~Machine();
	void Update(float elapsedSec);
	void Draw() const;
	bool IsHitByWorker(const Rectf& rect);
	bool IsMachineFull() const;
	Rectf GetShape() const;
	void SetActive(const Point2f& mousePos, int& price);
	void UpgradeMachine(const Point2f& mousePos, int& price);
private:
	bool m_IsActive;
	int m_AmountToCollect;
	int m_Price;
	Rectf m_Shape;
	Rectf m_UpgradeButton;
	CircularTimer* m_pTimer;
};

