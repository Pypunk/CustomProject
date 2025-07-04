#include "pch.h"
#include "structs.h"
#include <vector>
#include <iostream>

//-----------------------------------------------------------------
// Window Constructors
//-----------------------------------------------------------------
Window::Window( const std::string& title , float width , float height , bool isVSyncOn )
	:title{ title }
	,width{ width }
	,height{ height }
	,isVSyncOn{ isVSyncOn }
{
}

//-----------------------------------------------------------------
// Point2f Constructors
//-----------------------------------------------------------------
Point2f::Point2f( )
	:Point2f{ 0.0f, 0.0f }
{
}
Point2f::Point2f( float x, float y )
	:x{ x }, y{ y }
{
}

//-----------------------------------------------------------------
//Point3f Constructors
//-----------------------------------------------------------------
Point3f::Point3f()
	:Point3f{0.f,0.f,0.f}
{
}
Point3f::Point3f(float x, float y, float z)
	:x{x},y{y},z{z}
{
}

//-----------------------------------------------------------------
// Rectf Constructors
//-----------------------------------------------------------------
Rectf::Rectf( )
	:Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Rectf::Rectf( float left, float bottom, float width, float height )
	:left{ left }
	,bottom{ bottom }
	,width{ width }
	,height{ height }
{
}

Rectf::Rectf(Point2f bottomLeft, float width, float height)
	:left{bottomLeft.x}
	,bottom{bottomLeft.y}
	,width{width}
	,height{height}
{
}

void Rectf::Log() const
{
	std::cout << "Left: " << Rectf::left << std::endl;
	std::cout << "Bottom: " << Rectf::bottom << std::endl;
	std::cout << "Width: " << Rectf::width << std::endl;
	std::cout << "Height: " << Rectf::height << std::endl;
}

void Rectf::SetBottomLeft(const Point2f& point)
{
	Rectf::left = point.x;
	Rectf::bottom = point.y;
}

Point2f Rectf::GetBottomLeft(float offsetX, float offsetY) const
{
	return Point2f(Rectf::left + offsetX, Rectf::bottom + offsetY);
}

Point2f Rectf::GetBottomCenter(float offsetX, float offsetY) const
{
	return Point2f(Rectf::left + Rectf::width / 2.f + offsetX, Rectf::bottom + offsetY);
}

Point2f Rectf::GetBottomRight(float offsetX, float offsetY) const
{
	return Point2f(Rectf::left + Rectf::width + offsetX, Rectf::bottom + offsetY);
}

Point2f Rectf::GetTopLeft(float offsetX, float offsetY) const
{
	return Point2f(Rectf::left + offsetX, Rectf::bottom + Rectf::height + offsetY);
}

Point2f Rectf::GetTopCenter(float offsetX, float offsetY) const
{
	return Point2f(Rectf::left + Rectf::width / 2.f + offsetX, Rectf::bottom + Rectf::height + offsetY);
}

Point2f Rectf::GetTopRight(float offsetX, float offsetY) const
{
	return Point2f(Rectf::left + Rectf::width + offsetX, Rectf::bottom + Rectf::height + offsetY);
}

Point2f Rectf::GetCenterLeft(float offsetX, float offsetY) const
{
	return Point2f(Rectf::left + offsetX, Rectf::bottom + Rectf::height / 2.f + offsetY);
}

Point2f Rectf::GetCenter() const
{
	return Point2f(Rectf::left + Rectf::width / 2.f, Rectf::bottom + Rectf::height / 2.f);
}

Point2f Rectf::GetCenterRight(float offsetX, float offsetY) const
{
	return Point2f(Rectf::left + Rectf::width + offsetX, Rectf::bottom + Rectf::height / 2.f + offsetY);
}

std::vector<Point2f> Rectf::GetVertices() const
{
	std::vector<Point2f> vertices;
	vertices.push_back(Rectf::GetBottomLeft());
	vertices.push_back(Rectf::GetTopLeft());
	vertices.push_back(Rectf::GetTopRight());
	vertices.push_back(Rectf::GetBottomRight());
	return vertices;
}

//-----------------------------------------------------------------
// Color4f Constructors
//-----------------------------------------------------------------
Color4f::Color4f( )
	:Color4f{ 0.0f, 0.0f, 0.0f, 1.0f }
{
}

Color4f::Color4f( float r, float g, float b, float a )
	:r{ r }
	,g{ g }
	,b{ b }
	,a{ a }
{
}

//-----------------------------------------------------------------
// Circlef Constructors
//-----------------------------------------------------------------
Circlef::Circlef( )
	:Circlef{ 0.0f, 0.0f, 0.0f }
{
}

Circlef::Circlef( float centerX, float centerY, float radius )
	:Circlef{ Point2f{ centerX, centerY }, radius }
{
}

Circlef::Circlef( const Point2f& center, float radius )
	:center{ center }
	,radius{ radius }
{
}

//-----------------------------------------------------------------
// Ellipsef Constructors
//-----------------------------------------------------------------
Ellipsef::Ellipsef( )
	:Ellipsef{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}


Ellipsef::Ellipsef( const Point2f& center, float radiusX, float radiusY )
	: center{ center }
	, radiusX{ radiusX }
	, radiusY{ radiusY }
{
}

Ellipsef::Ellipsef( float centerX, float centerY, float radiusX, float radiusY )
	: Ellipsef{ Point2f{ centerX, centerY }, radiusX, radiusY }
{
}

Cubef::Cubef()
	:Cubef{0.f,0.f,0.f,0.f,0.f}
{
}

Cubef::Cubef(float left, float bottom, float width, float height, float dept)
	: left{ left }
	, bottom{ bottom }
	, width{ width }
	, height{ height }
	, dept{ dept }
{
}

Cubef::Cubef(Point2f bottomLeft, float width, float height, float dept)
	:Cubef{ bottomLeft.x,bottomLeft.y,width,height,dept }
{
}

Cubef::Cubef(Rectf rect, float dept)
	:Cubef{ rect.GetBottomLeft(),rect.width,rect.height,dept }
{
}

ResourceCost::ResourceCost(int food, int wood, int gold)
	:food(food)
	,wood(wood)
	,gold(gold)
{
}

bool ResourceCost::CanAfford(const ResourceCost& playerResources) const
{
	return playerResources.wood >= wood &&
		playerResources.gold >= gold &&
		playerResources.food >= food;
}

void ResourceCost::DeductFrom(ResourceCost& playerResources)
{
	playerResources.wood -= wood;
	playerResources.gold -= gold;
	playerResources.food -= food;
}

void ResourceCost::AddResources(const ResourceCost& playerResources)
{
	wood += playerResources.wood;
	food += playerResources.food;
	gold += playerResources.gold;
}

void ResourceCost::Print()
{
	std::cout << "Wood: " << wood << "\nFood: " << food << "\nGold: " << gold << "\n";
}
