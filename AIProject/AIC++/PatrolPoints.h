#pragma once
class PatrolPoints
{
public:
	PatrolPoints();

	void DrawDebug() const;
	void AddPoint(const Point2f& position);
	void RemovePoint(const Point2f& position, int& counter);
	Point2f& operator[](int index);

	size_t size() const;
	bool isEmpty() const;
	std::vector<Point2f> GetPoints();
private:
	std::vector<Point2f> m_Points;
};

