#include "pch.h"
#include "Health.h"

Health::Health(int amount)
	:m_HealthAmount{amount}
{
}

int Health::GetHealth()
{
	return m_HealthAmount;
}

void Health::TakeDamage(int amount)
{
	m_HealthAmount -= amount;
}

std::string Health::ToString()
{
	return std::to_string(m_HealthAmount);
}
