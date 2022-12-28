#include "pch.h"
#include "Deck.h"
#include "Texture.h"
#include <iostream>
#include <algorithm>

Deck::Deck()
	:m_AmountOfCardsInHand{2}
{
	const int types{ 4 };
	const int amount{ 13 };
	std::string path{ "Resources/" };
	for (int i{}; i < types; ++i)
	{
		for (int j{}; j < amount; j++)
		{
			path += std::to_string(i + 1);
			if (j < 9)
			{
				path += "0" + std::to_string(j + 1) + ".png";
			}
			else
			{
				path += std::to_string(j + 1) + ".png";
			}
			m_Cards.push_back(Card{ j + 1,new Texture{path} });
			std::cout << path << std::endl;
			path = "Resources/";
		}
	}
}

Deck::~Deck()
{
	for (const Card i : m_Cards)
	{
		delete i.texture;
	}
}

void Deck::Draw(Point2f& position) const
{
	float totalWidth{ m_Cards[0].texture->GetWidth() * m_AmountOfCardsInHand };
	Point2f pos{ position.x - totalWidth / 2.f ,position.y - m_Cards[0].texture->GetHeight() / 3.f};
	utils::SetColor(Color4f{ 0,0,0,1 });
	utils::DrawRect(Rectf{ pos,totalWidth,m_Cards[0].texture->GetHeight() });
	for (int i{}; i < m_AmountOfCardsInHand; ++i)
	{
		m_Cards[i].texture->Draw(pos);
		pos.x += m_Cards[i].texture->GetWidth();
	}
}

void Deck::ShuffleDeck()
{
	for (int i{}; i < m_Cards.size(); ++i)
	{
		int idx1{ utils::GetRand(0, 52) };
		int idx2{ utils::GetRand(0, 52) };
		if (idx1 == idx2)
		{
			idx2 = utils::GetRand(0, 52);
		}
		Swap(idx1, idx2);
	}
}

void Deck::Swap(int idx1, int idx2)
{
	Card temp{ m_Cards[idx1] };
	m_Cards[idx1] = m_Cards.back();
	m_Cards.back() = temp;
}

void Deck::AddCardInHand()
{
	m_AmountOfCardsInHand++;
}

int Deck::GetTotalValue() const
{
	int value{};
	for (int i{}; i < m_AmountOfCardsInHand; ++i)
	{
		value += m_Cards[i].value;
	}
	return value;
}

Deck::Card::Card(int value, Texture* texture)
	:value{value}
	,texture{texture}
{
}
