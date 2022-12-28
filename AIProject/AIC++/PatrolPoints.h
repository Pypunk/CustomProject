#pragma once
class PatrolPoints
{
public:
	PatrolPoints();

	void DrawDebug() const;
	void AddPoint(const Point2f& position);
	void RemovePoint(const Point2f& position);
	Point2f& operator[](int index);

	size_t size() const;
	bool isEmpty() const;
private:
	std::vector<Point2f> m_Points;
};

