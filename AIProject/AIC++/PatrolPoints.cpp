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

void PatrolPoints::RemovePoint(const Point2f& position, int& counter)
{
	const float distance{ 50.f };
	if (m_Points.size() > 1)
	{
		for (int i{}; i < m_Points.size(); ++i)
		{
			if (utils::GetDistance(position, m_Points[i]) < distance)
			{
				m_Points[i] = m_Points.back();
				m_Points.pop_back();
				counter = static_cast<int>(m_Points.size() - 1);
				break;
			}
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

std::vector<Point2f> PatrolPoints::GetPoints()
{
	return m_Points;
}
