#pragma once
class TextureManager;
class Machine;
class Character
{
public:
	Character(const Window& window);
	void Update(float elapsedSec, Machine* pMachine);
	void Draw() const;
	int& GetCurrency();
private:
	bool m_TargetSet;
	bool m_IsMoving;
	Rectf m_Shape;
	Point2f m_StartPos;
	Point2f m_Target;
	int m_Currency;
};

