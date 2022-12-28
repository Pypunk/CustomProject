#include "pch.h"
#include "Player.h"
#include "Deck.h"
#include <iostream>

Player::Player()
	:m_pDeck{ new Deck{} }
	, m_Value{}
{
	m_pDeck->ShuffleDeck();
}

Player::~Player()
{
	delete m_pDeck;
}

void Player::Draw(Point2f& position) const
{
	m_pDeck->Draw(position);
}

void Player::AddCard()
{
	m_pDeck->AddCardInHand();
	m_Value = m_pDeck->GetTotalValue();
}

int Player::GetPoints() const
{
	return m_Value;
}
