#pragma once
#include <string>
#include <vector>

struct Window
{
	explicit Window( const std::string& title = "Title", float width = 320.0f, 
		float height = 180.0f, bool isVSyncOn = true );

	std::string title;
	float width;
	float height;
	bool isVSyncOn;
};

struct Point2f
{
	Point2f( );
	explicit Point2f( float x, float y );


	float x;
	float y;
};

struct Point3f
{
	Point3f();
	explicit Point3f(float x, float y, float z);

	float x;
	float y;
	float z;
};

struct Rectf
{
	Rectf( );
	explicit Rectf( float left, float bottom, float width, float height );
	explicit Rectf(Point2f bottomLeft, float width, float height);
	
	float left;
	float bottom;
	float width;
	float height;

	void Log() const;
	void SetBottomLeft(const Point2f& point);
	Point2f GetBottomLeft(float offsetX = 0, float offsetY = 0) const;
	Point2f GetBottomCenter(float offsetX = 0, float offsetY = 0) const;
	Point2f GetBottomRight(float offsetX = 0, float offsetY = 0) const;
	Point2f GetTopLeft(float offsetX = 0, float offsetY = 0) const;
	Point2f GetTopCenter(float offsetX = 0, float offsetY = 0) const;
	Point2f GetTopRight(float offsetX = 0, float offsetY = 0) const;
	Point2f GetCenterLeft(float offsetX = 0, float offsetY = 0) const;
	Point2f GetCenter() const;
	Point2f GetCenterRight(float offsetX = 0, float offsetY = 0) const;
	std::vector<Point2f> GetVertices() const;
};

struct Cubef
{
	Cubef();
	explicit Cubef(float left, float bottom, float width, float height, float dept);
	explicit Cubef(Point2f bottomLeft, float width, float height, float dept);
	explicit Cubef(Rectf rect, float dept);

	float left;
	float bottom;
	float width;
	float height;
	float dept;
};

struct Color4f
{
	Color4f( );
	explicit Color4f( float r, float g, float b, float a );
	
	float r;
	float g;
	float b;
	float a;
};

struct Circlef
{
	Circlef( );
	explicit Circlef( const Point2f& center, float radius );
	explicit Circlef( float centerX, float centerY, float radius );

	Point2f center;
	float radius;
};


struct Ellipsef
{
	Ellipsef( );
	explicit Ellipsef( const Point2f& center, float radiusX, float radiusY );
	explicit Ellipsef( float centerX, float centerY, float radiusX, float radiusY );

	Point2f center;
	float radiusX;
	float radiusY;
};

struct FormationSlot
{
	Point2f positionOffset;
};

inline Point2f operator+(const Point2f& lhs, const Point2f& rhs)
{
	return Point2f{ lhs.x + rhs.x,lhs.y + rhs.y };
}

struct ResourceCost
{
	explicit ResourceCost(int food, int wood, int gold);
	bool CanAfford(const ResourceCost& playerResources) const;
	void DeductFrom(ResourceCost& playerResources);
	void AddResources(const ResourceCost& playerResources);
	void Print();

	int food;
	int wood;
	int gold;
};
