#pragma once
#include <vector>
#include "Vector2f.h"

namespace utils
{
	const float g_Pi{ 3.1415926535f };

#pragma region OpenGLDrawFunctionality

	void SetColor( const Color4f& color );
	
	void DrawPoint( float x, float y, float pointSize = 1.0f );
	void DrawPoint( const Point2f& p, float pointSize = 1.0f );
	void DrawPoints( Point2f *pVertices, int nrVertices, float pointSize = 1.0f );

	void DrawLine( float x1, float y1, float x2, float y2, float lineWidth = 1.0f );
	void DrawLine( const Point2f& p1, const Point2f& p2, float lineWidth = 1.0f );

	void DrawRect(float left, float bottom, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Point2f& bottomLeft, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Rectf& rect, float lineWidth = 1.0f);
	void FillRect(float left, float bottom, float width, float height);
	void FillRect(const Point2f& bottomLeft, float width, float height);
	void FillRect(const Rectf& rect);

	void DrawVector(const Point2f& startPoint, const Vector2f& vector);

	void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const Point2f& center, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const Ellipsef& ellipse , float lineWidth = 1.0f );
	void DrawCircle(const Point2f& center, float rad, float lineWidth = 1.f);
	void DrawCircle(const Circlef& circle, float lineWidth = 1.f);
	void FillEllipse( float centerX, float centerY, float radX, float radY );
	void FillEllipse(const Ellipsef& ellipse );
	void FillEllipse(const Point2f& center, float radX, float radY);
	void FillCircle(const Point2f& center, float rad);
	void FillCircle(const Circlef& circle);

	void DrawArc( float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f );
	void DrawArc( const Point2f& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f );
	void FillArc( float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle );
	void FillArc( const Point2f& center, float radX, float radY, float fromAngle, float tillAngle );

	void DrawPolygon( const std::vector<Point2f>& vertices, bool closed = true, float lineWidth = 1.0f );
	void DrawPolygon( const Point2f* pVertices, size_t nrVertices, bool closed = true, float lineWidth = 1.0f );
	void FillPolygon( const std::vector<Point2f>& vertices);
	void FillPolygon( const Point2f* pVertices, size_t nrVertices);
#pragma endregion OpenGLDrawFunctionality

#pragma region CollisionFunctionality
	struct HitInfo
	{
		float lambda;
		Point2f intersectPoint;
		Vector2f normal;
	};
	float GetDistance(const Point2f& point1, const Point2f& point2);
	float GetDistance(float p1x, float p1y, float p2x, float p2y);
	Point2f GetMiddle(const Point2f& pointA, const Point2f& pointB);
	Point2f GetMiddle(float p1x, float p1y, float p2x, float p2y);

	bool IsPointInRect(const Point2f& p, const Rectf& r);
	bool IsPointInCircle(const Point2f& p, const Circlef& c);
	bool IsPointInPolygon( const Point2f& p, const std::vector<Point2f>& vertices );
	bool IsPointInPolygon( const Point2f& p, const Point2f* vertices, size_t nrVertices );

	bool IsOverlapping( const Point2f& a, const Point2f& b, const Circlef& c );
	bool IsOverlapping( const Point2f& a, const Point2f& b, const Rectf& r );

	bool IsOverlapping(const Rectf & r1, const Rectf & r2);
	bool IsOverlapping( const Rectf& r, const Circlef& c );
	bool IsOverlapping( const Circlef& c1, const Circlef& c2 );
	bool IsOverlapping( const std::vector<Point2f>& vertices, const Circlef& c );
	bool IsOverlapping( const Point2f* vertices, size_t nrVertices, const Circlef& c );
	bool Raycast( const Point2f* vertices, const size_t nrVertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo );
	bool Raycast( const std::vector<Point2f>& vertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo );
	bool Raycast(const Rectf& rect, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo);

	bool IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon = 1e-6);
	float DistPointLineSegment(const Point2f& p, const Point2f& a, const Point2f& b);
	bool IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b);
	bool IntersectRectLine(const Rectf& r, const Point2f& p1, const Point2f& p2, float& intersectMin, float& intersectMax);

#pragma endregion CollisionFunctionality

#pragma region OwnFunctions
	int GetRand(int min, int max);
	float GetRand(float min, float max);
	float ConvertToRadians(float degrees);
	float ConvertToDegrees(float radians);
	Point2f CreateCoordinatesFromRads(float radius, float radians, const Point2f& offset = {});
	int GetIndex(int rowIdx, int colIdx, int nrCols);
	int GetRowIndex(int index, int nrCols);
	int GetColIndex(int index, int nrCols);
	void DrawArrow(const Point2f& from, const Point2f& to, float arrowSize);
#pragma endregion OwnFunctions
}