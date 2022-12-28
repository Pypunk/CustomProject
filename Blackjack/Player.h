#pragma once
class Player
{
public:
	Player();
	~Player();

	void Draw(Point2f& position) const;
	void AddCard();
	int GetPoints() const;
private:
	class Deck* m_pDeck;
	Point2f m_CenterPosition;
	int m_Value;
};

