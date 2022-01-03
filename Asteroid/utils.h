#pragma once
#include "structs.h"
#include <vector>

namespace utils
{

	const float g_Pi{ 3.1415926535f };

#pragma region OpenGLDrawFunctionality
	void ClearBackground(float r, float g, float b);
	void ClearBackground();
	// Choose a floating point value for each color component between 0.0f and 1.0f. The a (alpha) is optional.
	// Usage: SetColor(1.0f, 0.0f, 0.0f); set the drawing color to red
	void SetColor(float r, float g, float b, float a = 1);
	// Pass a Color4f object to the function
	void SetColor(const Color4f& color);

	// Draws a line by connecting the two points specified by (x1,y1) and (x2,y2)
	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth = 1.0f);
	// Draws a line by connecting the two points specified by p1 and p1
	void DrawLine(const Point2f& p1, const Point2f& p2, float lineWidth = 1.0f);

	void DrawTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3, float lineWidth = 1);
	void FillTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3);
	void DrawRect(float left, float bottom, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Point2f& bottomLeft, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Rectf& rect, float lineWidth = 1.0f);
	void FillRect(float left, float bottom, float width, float height);
	void FillRect(const Point2f& bottomLeft, float width, float height);
	void FillRect(const Rectf& rect);

	void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const Point2f& center, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const Ellipsef& ellipse, float lineWidth = 1.0f);
	void DrawCircle(const Point2f& center, float rad, float lineWidth = 1.f);
	void DrawCircle(const Circlef& circle, float lineWidth = 1.f);
	void FillEllipse(float centerX, float centerY, float radX, float radY);
	void FillEllipse(const Ellipsef& ellipse);
	void FillEllipse(const Point2f& center, float radX, float radY);
	void FillCircle(const Point2f& center, float rad);
	void FillCircle(const Circlef& circle);

	// Draws an arc. The angle parameters are in radians, not in degrees.
	void DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
	// Draws an arc. The angle parameters are in radians, not in degrees.
	void DrawArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
	// Fills an arc. The angle parameters are in radians, not in degrees.
	void FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle);
	// Fills an arc. The angle parameters are in radians, not in degrees.
	void FillArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle);

	void DrawPolygon(const std::vector<Point2f>& vertices, bool closed = true, float lineWidth = 1.0f);
	void DrawPolygon(const Point2f* pVertices, size_t nrVertices, bool closed = true, float lineWidth = 1.0f);
	void FillPolygon(const std::vector<Point2f>& vertices);
	void FillPolygon(const Point2f* pVertices, size_t nrVertices);
#pragma endregion OpenGLDrawFunctionality

#pragma region TextureFunctionality

	struct Texture
	{
		GLuint id;
		float width;
		float height;
	};

	bool TextureFromFile(const std::string& path, Texture& texture);
	bool TextureFromString(const std::string& text, TTF_Font* pFont, const Color4f& textColor, Texture& texture);
	bool TextureFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor, Texture& texture);
	void TextureFromSurface(const SDL_Surface* pSurface, Texture& textureData);
	void DrawTexture(const Texture& texture, const Point2f& dstBottomLeft, const Rectf& srcRect = {});
	void DrawTexture(const Texture& texture, const Rectf& dstRect, const Rectf& srcRect = {});
	void DeleteTexture(Texture& texture);
#pragma endregion TextureFunctionality

#pragma region CollisionFunctionality
	float GetDistance(const Point2f& point1, const Point2f& point2);
	float GetDistance(float p1x, float p1y, float p2x, float p2y);
	Point2f GetMiddle(const Point2f& pointA, const Point2f& pointB);
	Point2f GetMiddle(float p1x, float p1y, float p2x, float p2y);
	Point2f GetMiddle(const Rectf& rect);
	bool IsPointInCircle(const Point2f& p, const Circlef& c);
	bool IsPointInRect(const Point2f& p, const Rectf& r);
	bool IsOverlapping(const Rectf& r1, const Rectf& r2);
	bool IsOverlapping(const Circlef& c1, const Circlef& c2);
	bool IsOverlapping(const Circlef& circle, const Rectf& rect);
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
#pragma endregion OwnFunctions

#pragma region drawFunctions
	void DrawSquares(Point2f& position, float squareSize, float amount);
	void DrawEguilateralTriangle(const Point2f& position, float size, bool isFilled = true);
	void DrawPentagram(const Point2f& center, float radius);
	void DrawRotatingPentagram(const Point2f& center, float radius, AngleSpeed pAngleSpeed);
	void DrawRadiantRect(Point2f& position, float width, float height, Color4f& startColor, const Color4f& endColor);
	void DrawDotGrid(Point2f& position, float radius, float offSet, float cols, float rows);
#pragma endregion drawFunctions

#pragma region VectorMath
	void DrawVector(const Vector2f& vector, const Point2f& startPos = {});
	std::string ToString(const Vector2f& vector);
	Vector2f Add(const Vector2f& v1, const Vector2f& v2);
	Vector2f Subtract(const Vector2f& v1, const Vector2f& v2);
	float Dot(const Vector2f& v1, const Vector2f& v2);
	float Cross(const Vector2f& v1, const Vector2f& v2);
	float Length(const Vector2f& vector);
	Vector2f Scale(const Vector2f& v1, float scalar);
	Vector2f Normalize(const Vector2f& v1);
	float AngleBetween(const Vector2f& v1, const Vector2f& v2);
	bool AreEqual(const Vector2f& v1, const Vector2f& v2);
	Vector2f CalculateProjection(const Vector2f& v, Vector2f& v2, float angle);
	Vector2f CreateVector(const Point2f& p1, const Point2f& p2);
#pragma endregion VectorMath
}