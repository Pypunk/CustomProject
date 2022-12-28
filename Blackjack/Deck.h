#pragma once
class Deck
{
public:
	Deck();
	~Deck();
	
	void Draw(Point2f& position) const;

	void ShuffleDeck();
	void Swap(int idx1, int idx2);
	void AddCardInHand();
	int GetTotalValue() const;
private:
	struct Card
	{
		Card(int value, class Texture* texture);

		int value;
		Texture* texture;
	};
	std::vector<Card> m_Cards;
	int m_AmountOfCardsInHand;
};

