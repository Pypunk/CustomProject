#pragma once
class Health
{
public:
	Health(int amount);
	int GetHealth();
	void TakeDamage(int amount);
	std::string ToString();
private:
	int m_HealthAmount;
};

