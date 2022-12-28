#include "pch.h"
#include "PatrolPoints.h"
#include <vector>

PatrolPoints::PatrolPoints()
	:m_Points{}
{
}

void PatrolPoints::DrawDebug() const
{
	if (!m_Points.empty())
	{
		utils::DrawPolygon(m_Points);
	}
}

void PatrolPoints::AddPoint(const Point2f& position)
{
	m_Points.push_back(position);
}

void PatrolPoints::RemovePoint(const Point2f& position)
{
	for (int i{}; i < m_Points.size(); ++i)
	{
		if (utils::GetDistance(position, m_Points[i]) < 50.f)
		{
			const Point2f temp{ m_Points[i] };
			m_Points[i] = m_Points.back();
			m_Points.back() = temp;
			m_Points.pop_back();
		}
	}
}

Point2f& PatrolPoints::operator[](int index)
{
	return m_Points[index];
}

size_t PatrolPoints::size() const
{
	return m_Points.size();
}

bool PatrolPoints::isEmpty() const
{
	return m_Points.empty();
}
