#include "pch.h"
//#define _USE_MATH_DEFINES
//#include <cmath>
#include <algorithm>
#include <iostream>
#include "utils.h"

namespace utils
{
#pragma region OpenGLDrawFunctionality
	void ClearBackground(float r, float g, float b)
	{
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void ClearBackground()
	{
		ClearBackground(185.0f / 255.0f, 211.0f / 255.0f, 238.0f / 255.0f);
	}
	void SetColor(float r, float g, float b, float a)
	{
		glColor4f(r, g, b, a);
	}

	void SetColor(const Color4f& color)
	{
		glColor4f(color.r, color.g, color.b, color.a);
	}

	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth)
	{
		glLineWidth(lineWidth);
		glBegin(GL_LINES);
		{
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
		}
		glEnd();
	}

	void DrawLine(const Point2f& p1, const Point2f& p2, float lineWidth)
	{
		DrawLine(p1.x, p1.y, p2.x, p2.y, lineWidth);
	}

	void DrawRect(float left, float bottom, float width, float height, float lineWidth)
	{
		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(left, bottom);
			glVertex2f(left + width, bottom);
			glVertex2f(left + width, bottom + height);
			glVertex2f(left, bottom + height);
		}
		glEnd();
	}

	void DrawTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3, float lineWidth)
	{
		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(p1.x, p1.y);
			glVertex2f(p2.x, p2.y);
			glVertex2f(p3.x, p3.y);
		}
		glEnd();
	}

	void FillTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3)
	{
		glBegin(GL_TRIANGLES);
		{
			glVertex2f(p1.x, p1.y);
			glVertex2f(p2.x, p2.y);
			glVertex2f(p3.x, p3.y);
		}
		glEnd();
	}

	void DrawRect(const Point2f& bottomLeft, float width, float height, float lineWidth)
	{
		DrawRect(bottomLeft.x, bottomLeft.y, width, height, lineWidth);
	}

	void DrawRect(const Rectf& rect, float lineWidth)
	{
		DrawRect(rect.left, rect.bottom, rect.width, rect.height, lineWidth);
	}

	void FillRect(float left, float bottom, float width, float height)
	{
		glBegin(GL_POLYGON);
		{
			glVertex2f(left, bottom);
			glVertex2f(left + width, bottom);
			glVertex2f(left + width, bottom + height);
			glVertex2f(left, bottom + height);
		}
		glEnd();
	}

	void FillRect(const Point2f& bottomLeft, float width, float height)
	{
		FillRect(bottomLeft.x, bottomLeft.y, width, height);
	}

	void FillRect(const Rectf& rect)
	{
		FillRect(rect.left, rect.bottom, rect.width, rect.height);
	}

	void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth)
	{
		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			for (float angle = 0.0; angle < float(2 * g_Pi); angle += dAngle)
			{
				glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
			}
		}
		glEnd();
	}

	void DrawEllipse(const Point2f& center, float radX, float radY, float lineWidth)
	{
		DrawEllipse(center.x, center.y, radX, radY, lineWidth);
	}

	void DrawEllipse(const Ellipsef& ellipse, float lineWidth)
	{
		DrawEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY, lineWidth);
	}

	void DrawCircle(const Point2f& center, float rad, float lineWidth)
	{
		DrawEllipse(center, rad, rad, lineWidth);
	}

	void DrawCircle(const Circlef& circle, float lineWidth)
	{
		DrawCircle(circle.center, circle.radius, lineWidth);
	}

	void FillEllipse(float centerX, float centerY, float radX, float radY)
	{
		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glBegin(GL_POLYGON);
		{
			for (float angle = 0.0; angle < float(2 * g_Pi); angle += dAngle)
			{
				glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
			}
		}
		glEnd();
	}

	void FillEllipse(const Ellipsef& ellipse)
	{
		FillEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY);
	}

	void FillEllipse(const Point2f& center, float radX, float radY)
	{
		FillEllipse(center.x, center.y, radX, radY);
	}

	void FillCircle(const Point2f& center, float rad)
	{
		FillEllipse(center, rad, rad);
	}

	void FillCircle(const Circlef& circle)
	{
		FillCircle(circle.center, circle.radius);
	}

	void DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth)
	{
		if (fromAngle > tillAngle)
		{
			return;
		}

		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glLineWidth(lineWidth);
		glBegin(GL_LINE_STRIP);
		{
			for (float angle = fromAngle; angle < tillAngle; angle += dAngle)
			{
				glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
			}
			glVertex2f(centerX + radX * float(cos(tillAngle)), centerY + radY * float(sin(tillAngle)));
		}
		glEnd();

	}

	void DrawArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth)
	{
		DrawArc(center.x, center.y, radX, radY, fromAngle, tillAngle, lineWidth);
	}

	void FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle)
	{
		if (fromAngle > tillAngle)
		{
			return;
		}
		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glBegin(GL_POLYGON);
		{
			glVertex2f(centerX, centerY);
			for (float angle = fromAngle; angle < tillAngle; angle += dAngle)
			{
				glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
			}
			glVertex2f(centerX + radX * float(cos(tillAngle)), centerY + radY * float(sin(tillAngle)));
		}
		glEnd();
	}

	void FillArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle)
	{
		FillArc(center.x, center.y, radX, radY, fromAngle, tillAngle);
	}

	void DrawPolygon(const std::vector<Point2f>& vertices, bool closed, float lineWidth)
	{
		DrawPolygon(vertices.data(), vertices.size(), closed, lineWidth);
	}

	void DrawPolygon(const Point2f* pVertices, size_t nrVertices, bool closed, float lineWidth)
	{
		glLineWidth(lineWidth);
		closed ? glBegin(GL_LINE_LOOP) : glBegin(GL_LINE_STRIP);
		{
			for (size_t idx{ 0 }; idx < nrVertices; ++idx)
			{
				glVertex2f(pVertices[idx].x, pVertices[idx].y);
			}
		}
		glEnd();
	}

	void FillPolygon(const std::vector<Point2f>& vertices)
	{
		FillPolygon(vertices.data(), vertices.size());
	}

	void FillPolygon(const Point2f* pVertices, size_t nrVertices)
	{
		glBegin(GL_POLYGON);
		{
			for (size_t idx{ 0 }; idx < nrVertices; ++idx)
			{
				glVertex2f(pVertices[idx].x, pVertices[idx].y);
			}
		}
		glEnd();
	}
#pragma endregion OpenGLDrawFunctionality


#pragma region textureImplementations

	bool TextureFromFile(const std::string& path, Texture& texture)
	{
		//Load file for use as an image in a new surface.
		SDL_Surface* pLoadedSurface = IMG_Load(path.c_str());
		if (pLoadedSurface == nullptr)
		{
			std::cerr << "TextureFromFile: SDL Error when calling IMG_Load: " << SDL_GetError() << std::endl;
			return false;
		}

		TextureFromSurface(pLoadedSurface, texture);

		//Free loaded surface
		SDL_FreeSurface(pLoadedSurface);

		return true;
	}

	bool TextureFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor, Texture& texture)
	{
		// Create font
		TTF_Font* pFont{};
		pFont = TTF_OpenFont(fontPath.c_str(), ptSize);
		if (pFont == nullptr)
		{
			std::cout << "TextureFromString: Failed to load font! SDL_ttf Error: " << TTF_GetError();
			std::cin.get();
			return false;
		}

		// Create texture using this fontand close font afterwards
		bool textureOk = TextureFromString(text, pFont, textColor, texture);
		TTF_CloseFont(pFont);

		return textureOk;
	}

	bool TextureFromString(const std::string& text, TTF_Font* pFont, const Color4f& color, Texture& texture)
	{
		//Render text surface
		SDL_Color textColor{};
		textColor.r = Uint8(color.r * 255);
		textColor.g = Uint8(color.g * 255);
		textColor.b = Uint8(color.b * 255);
		textColor.a = Uint8(color.a * 255);

		SDL_Surface* pLoadedSurface = TTF_RenderText_Blended(pFont, text.c_str(), textColor);
		//SDL_Surface* pLoadedSurface = TTF_RenderText_Solid(pFont, textureText.c_str(), textColor);
		if (pLoadedSurface == nullptr)
		{
			std::cerr << "TextureFromString: Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << '\n';
			return false;
		}

		// copy to video memory
		TextureFromSurface(pLoadedSurface, texture);

		//Free loaded surface
		SDL_FreeSurface(pLoadedSurface);

		return true;
	}

	void TextureFromSurface(const SDL_Surface* pSurface, Texture& texture)
	{
		//Get image dimensions
		texture.width = float(pSurface->w);
		texture.height = float(pSurface->h);

		// Get pixel format information and translate to OpenGl format
		GLenum pixelFormat{ GL_RGB };
		switch (pSurface->format->BytesPerPixel)
		{
		case 3:
			if (pSurface->format->Rmask == 0x000000ff)
			{
				pixelFormat = GL_RGB;
			}
			else
			{
				pixelFormat = GL_BGR;
			}
			break;
		case 4:
			if (pSurface->format->Rmask == 0x000000ff)
			{
				pixelFormat = GL_RGBA;
			}
			else
			{
				pixelFormat = GL_BGRA;
			}
			break;
		default:
			std::cerr << "TextureFromSurface error: Unknow pixel format, BytesPerPixel: " << pSurface->format->BytesPerPixel << "\nUse 32 bit or 24 bit images.\n";;
			texture.width = 0;
			texture.height = 0;
			return;
		}

		//Generate an array of textures.  We only want one texture (one element array), so trick
		//it by treating "texture" as array of length one.
		glGenTextures(1, &texture.id);

		//Select (bind) the texture we just generated as the current 2D texture OpenGL is using/modifying.
		//All subsequent changes to OpenGL's texturing state for 2D textures will affect this texture.
		glBindTexture(GL_TEXTURE_2D, texture.id);

		// check for errors.
		GLenum e = glGetError();
		if (e != GL_NO_ERROR)
		{
			std::cerr << "TextureFromSurface, error binding textures, Error id = " << e << '\n';
			texture.width = 0;
			texture.height = 0;
			return;
		}

		//Specify the texture's data.  This function is a bit tricky, and it's hard to find helpful documentation.  A summary:
		//   GL_TEXTURE_2D:    The currently bound 2D texture (i.e. the one we just made)
		//               0:    The mipmap level.  0, since we want to update the base level mipmap image (i.e., the image itself,
		//                         not cached smaller copies)
		//         GL_RGBA:    Specifies the number of color components in the texture.
		//                     This is how OpenGL will store the texture internally (kinda)--
		//                     It's essentially the texture's type.
		//      surface->w:    The width of the texture
		//      surface->h:    The height of the texture
		//               0:    The border.  Don't worry about this if you're just starting.
		//     pixelFormat:    The format that the *data* is in--NOT the texture! 
		//GL_UNSIGNED_BYTE:    The type the data is in.  In SDL, the data is stored as an array of bytes, with each channel
		//                         getting one byte.  This is fairly typical--it means that the image can store, for each channel,
		//                         any value that fits in one byte (so 0 through 255).  These values are to be interpreted as
		//                         *unsigned* values (since 0x00 should be dark and 0xFF should be bright).
		// surface->pixels:    The actual data.  As above, SDL's array of bytes.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w, pSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pSurface->pixels);

		//Set the minification and magnification filters.  In this case, when the texture is minified (i.e., the texture's pixels (texels) are
		//*smaller* than the screen pixels you're seeing them on, linearly filter them (i.e. blend them together).  This blends four texels for
		//each sample--which is not very much.  Mipmapping can give better results.  Find a texturing tutorial that discusses these issues
		//further.  Conversely, when the texture is magnified (i.e., the texture's texels are *larger* than the screen pixels you're seeing
		//them on), linearly filter them.  Qualitatively, this causes "blown up" (overmagnified) textures to look blurry instead of blocky.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void DeleteTexture(Texture& texture)
	{
		glDeleteTextures(1, &texture.id);
	}

	void DrawTexture(const Texture& texture, const Point2f& dstBottomLeft, const Rectf& srcRect)
	{
		Rectf dstRect{ dstBottomLeft.x, dstBottomLeft.y, srcRect.width, srcRect.height };
		DrawTexture(texture, dstRect, srcRect);
	}


	void DrawTexture(const Texture& texture, const Rectf& dstRect, const Rectf& srcRect)
	{
		// Determine texture coordinates using srcRect and default destination width and height
		float textLeft{};
		float textRight{};
		float textTop{};
		float textBottom{};

		float defaultDstWidth{};
		float defaultDstHeight{};
		if (!(srcRect.width > 0.0f && srcRect.height > 0.0f)) // No srcRect specified
		{
			// Use complete texture
			textLeft = 0.0f;
			textRight = 1.0f;
			textTop = 0.0f;
			textBottom = 1.0f;

			defaultDstHeight = texture.height;
			defaultDstWidth = texture.width;
		}
		else // srcRect specified
		{
			// Convert to the range [0.0, 1.0]
			textLeft = srcRect.left / texture.width;
			textRight = (srcRect.left + srcRect.width) / texture.width;
			textTop = (srcRect.bottom - srcRect.height) / texture.height;
			textBottom = srcRect.bottom / texture.height;

			defaultDstHeight = srcRect.height;
			defaultDstWidth = srcRect.width;
		}

		// Determine vertex coordinates
		float vertexLeft{ dstRect.left };
		float vertexBottom{ dstRect.bottom };
		float vertexRight{};
		float vertexTop{};
		if (!(dstRect.width > 0.0f && dstRect.height > 0.0f)) // If no size specified use default size
		{
			vertexRight = vertexLeft + defaultDstWidth;
			vertexTop = vertexBottom + defaultDstHeight;
		}
		else
		{
			vertexRight = vertexLeft + dstRect.width;
			vertexTop = vertexBottom + dstRect.height;
		}

		// Tell opengl which texture we will use
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		// set the texture mode https://open.gl/textures
		float color[] = { 1.0f, 0.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		// Draw
		glEnable(GL_TEXTURE_2D);
		{
			glBegin(GL_QUADS);
			{
				glTexCoord2f(textLeft, textBottom);
				glVertex2f(vertexLeft, vertexBottom);

				glTexCoord2f(textLeft, textTop);
				glVertex2f(vertexLeft, vertexTop);

				glTexCoord2f(textRight, textTop);
				glVertex2f(vertexRight, vertexTop);

				glTexCoord2f(textRight, textBottom);
				glVertex2f(vertexRight, vertexBottom);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

	}
#pragma endregion textureImplementations


#pragma region CollisionFunctionality
	float GetDistance(const Point2f& point1, const Point2f& point2) 
	{
		return sqrtf(powf(point2.x - point1.x, 2) + powf(point2.y - point1.y, 2));
	}
	float GetDistance(float p1x, float p1y, float p2x, float p2y)
	{
		return sqrtf(powf(p2x - p1x, 2) + powf(p2y - p1y, 2));
	}
	Point2f GetMiddle(const Point2f& pointA, const Point2f& pointB)
	{
		return Point2f{ (pointA.x + pointB.x) / 2.f, (pointA.y + pointB.y) / 2.f };
	}
	Point2f GetMiddle(float p1x, float p1y, float p2x, float p2y)
	{
		return Point2f{ (p1x + p2x) / 2.f, (p1y + p2y) / 2.f };
	}
	Point2f GetMiddle(const Rectf& rect)
	{
		return Point2f{ rect.left + rect.width / 2.f,rect.bottom + rect.height / 2.f };
	}
	bool IsPointInCircle(const Point2f& p, const Circlef& c)
	{
		return (p.x >= c.center.x - c.radius && p.x <= c.center.x + c.radius
			&& p.y >= c.center.y - c.radius && p.y <= c.center.y + c.radius);
	}
	bool IsPointInRect(const Point2f& p, const Rectf& r)
	{
		return (p.x >= r.left && p.x <= r.left + r.width &&
			p.y >= r.bottom && p.y <= r.bottom + r.height);
	}
	bool IsOverlapping(const Rectf& rect1, const Rectf& rect2)
	{
		Point2f topLeftPos1{ rect1.left,rect1.bottom+rect1.height };
		Point2f bottomRightPos1{ rect1.left + rect1.width,rect1.bottom };
		Point2f topLeftPos2{ rect2.left,rect2.bottom+rect2.height };
		Point2f bottomRightPos2{ rect2.left + rect2.width,rect2.bottom };
		
		if (topLeftPos1.x == bottomRightPos1.x || topLeftPos1.y == bottomRightPos1.y
			|| topLeftPos2.x == bottomRightPos1.x || topLeftPos2.y == bottomRightPos2.y)return false;
		if (topLeftPos1.x >= bottomRightPos2.x || topLeftPos2.x >= bottomRightPos1.x)return false;
		if (bottomRightPos1.y >= topLeftPos2.y || bottomRightPos2.y >= topLeftPos1.y)return false;

		return true;
	}
	bool IsOverlapping(const Circlef& c1, const Circlef& c2)
	{
		const float distance{ GetDistance(c1.center,c2.center)*GetDistance(c1.center,c2.center) };
		const float radSquared{ powf((c1.radius + c2.radius),2) };
		return (distance < radSquared);
	}
	bool IsOverlapping(const Circlef& circle, const Rectf& rect)
	{
		Circlef rectCircle{ GetMiddle(rect),rect.width / 2.f };
		return IsOverlapping(circle, rectCircle);
	}
#pragma endregion CollisionFunctionality

#pragma region OwnFunctions
	int GetRand(int min, int max)
	{
		return ((rand() % int(max)) + min);
	}

	float GetRand(float min, float max)
	{
		return ((rand() % int(max * 100)) + min * 100) / 100;
	}
	float ConvertToRadians(float degrees)
	{
		return degrees * (g_Pi / 180);
	}
	float ConvertToDegrees(float radians)
	{
		return radians * (180 / g_Pi);
	}
	Point2f CreateCoordinatesFromRads(float radius, float radians, const Point2f& offset)
	{
		const float x = offset.x + (radius * cosf(radians));
		const float y = offset.y + (radius * sinf(radians));
		return Point2f{ x, y };
	}
	int GetIndex(int rowIdx, int colIdx, int nrCols)
	{
		return rowIdx * nrCols + colIdx;
	}
	int GetRowIndex(int index, int nrCols)
	{
		return index/nrCols;
	}
	int GetColIndex(int index, int nrCols)
	{
		return index % nrCols;
	}
#pragma endregion OwnFunctions

#pragma region drawFunctions
	void DrawSquares(Point2f& position, float squareSize, float amount)
	{
		float newSize{};
		for (int i{}; i < amount; ++i)
		{
			SetColor(0, 0, 0);
			Rectf rect{ position.x,position.y,newSize,newSize };
			DrawRect(rect);
			position.x += squareSize / amount / 2;
			position.y += squareSize / amount / 2;
			newSize -= squareSize / amount;
		}
	}
	void DrawEguilateralTriangle(const Point2f& position, float size, bool isFilled)
	{
		const float angle{ 60.f };
		const Point2f position2{ CreateCoordinatesFromRads(size, ConvertToRadians(angle), position) };
		const Point2f position3{ position.x + size,position.y };
		if (isFilled)
		{
			FillTriangle(position, position2, position3);
		}
		else
		{
			DrawTriangle(position, position2, position3);
		}
	}
	void DrawPentagram(const Point2f& center, float radius)
	{
		const int pentaPointsAmount{ 5 };
		const float angle{ g_Pi / pentaPointsAmount };
		Point2f pentaPoints[pentaPointsAmount]{};
		for (int i{}; i < pentaPointsAmount; ++i)
		{
			switch (i)
			{
			case 0:
				pentaPoints[i] = Point2f{ cosf(2 * angle) * radius + center.x,sinf(2 * angle) * radius + center.y };
				break;
			case 1:
				pentaPoints[i] = Point2f{ cosf(2 * angle * 3) * radius + center.x,sinf(2 * angle * 3) * radius + center.y };
				break;
			case 2:
				pentaPoints[i] = Point2f{ cosf(2 * angle * 5) * radius + center.x,sinf(2 * angle * 5) * radius + center.y };
				break;
			case 3:
				pentaPoints[i] = Point2f{ cosf(2 * angle * 2) * radius + center.x,sinf(2 * angle * 2) * radius + center.y };
				break;
			case 4:
				pentaPoints[i] = Point2f{ cosf(2 * angle * 4) * radius + center.x,sinf(2 * angle * 4) * radius + center.y };
				break;
			}
		}
		DrawPolygon(pentaPoints,pentaPointsAmount);
	}
	void DrawRotatingPentagram(const Point2f& center, float radius, AngleSpeed pAngleSpeed)
	{
		const int pentaPointsAmount{ 5 };
		const float angle{ g_Pi/pentaPointsAmount + ConvertToRadians(pAngleSpeed.angle) };
		Point2f pentaPoints[pentaPointsAmount]{};
		for (int i{ 0 }; i < 5; ++i)
		{
			switch (i)
			{
			case 0:
				pentaPoints[i] = Point2f{ cosf(2 * angle) * radius + center.x,sinf(2 * angle) * radius + center.y };
				break;
			case 1:
				pentaPoints[i] = Point2f{ cosf(2 * angle * 3) * radius + center.x,sinf(2 * angle * 3) * radius + center.y };
				break;
			case 2:
				pentaPoints[i] = Point2f{ cosf(2 * angle * 5) * radius + center.x,sinf(2 * angle * 5) * radius + center.y };
				break;
			case 3:
				pentaPoints[i] = Point2f{ cosf(2 * angle * 2) * radius + center.x,sinf(2 * angle * 2) * radius + center.y };
				break;
			case 4:
				pentaPoints[i] = Point2f{ cosf(2 * angle * 4) * radius + center.x,sinf(2 * angle * 4) * radius + center.y };
				break;
			}
		}
		DrawPolygon(pentaPoints, 5);
	}
	void DrawRadiantRect(Point2f& position, float width, float height, Color4f& startColor, const Color4f& endColor)
	{
		const float gradientIncrement{ 1.f / width };
		for (int i{}; i < width; ++i)
		{
			SetColor(startColor);
			DrawLine(position, Point2f{ position.x,position.y + height });
			if (startColor.r < endColor.r)
			{
				startColor.r += gradientIncrement;
			}
			else
			{
				startColor.r -= gradientIncrement;
			}
			if (startColor.g < endColor.g)
			{
				startColor.g += gradientIncrement;
			}
			else
			{
				startColor.g -= gradientIncrement;
			}
			if (startColor.b < endColor.b)
			{
				startColor.b += gradientIncrement;
			}
			else
			{
				startColor.b -= gradientIncrement;;
			}
			if (startColor.a < endColor.a)
			{
				startColor.a += gradientIncrement;
			}
			else
			{
				startColor.a -= gradientIncrement;
			}
			position.x++;
		}
	}
	void DrawDotGrid(Point2f& position, float radius, float offSet, float cols, float rows)
	{
		float startYpos{ position.y };
		for (int i{}; i < cols; ++i)
		{
			for (int j{}; j < rows; ++j)
			{
				FillEllipse(position, radius, radius);
				position.y += radius * 2 + offSet;
			}
			position.y = startYpos;
			position.x += radius * 2 + offSet;
		}
	}
#pragma endregion drawFunctions

#pragma region VectorMath
	void DrawVector(const Vector2f& vector, const Point2f& startPos)
	{
		const float lenght{ -10.f };
		const float angle{ 30 };
		const float atan = ConvertToRadians(90) - atan2f(vector.x, vector.y);
		const float vectorLength{ Length(vector) };
		const Point2f endPoint{ CreateCoordinatesFromRads(vectorLength,atan,startPos) };
		DrawLine(startPos, endPoint);
		Point2f triangleBottomLeft{ CreateCoordinatesFromRads(lenght, atan + ConvertToRadians(angle), endPoint) };
		Point2f triangleBottomRight{ CreateCoordinatesFromRads(lenght, atan - ConvertToRadians(angle), endPoint) };
		FillTriangle(endPoint, triangleBottomLeft, triangleBottomRight);
	}
	std::string ToString(const Vector2f& vector)
	{
		std::string vectorString{};
		vectorString += "[" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + "]";
		return vectorString;
	}
	Vector2f Add(const Vector2f& v1, const Vector2f& v2)
	{
		Vector2f addition{ v1.x + v2.x,v1.y+v2.y };
		return addition;
	}
	Vector2f Subtract(const Vector2f& v1, const Vector2f& v2)
	{
		Vector2f subtraction{ v1.x - v2.x,v1.y - v2.y };
		return subtraction;
	}
	float Dot(const Vector2f& v1, const Vector2f& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}
	float Cross(const Vector2f& v1, const Vector2f& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}
	float Length(const Vector2f& vector)
	{
		return sqrtf(powf(vector.x, 2) + powf(vector.y, 2));
	}
	Vector2f Scale(const Vector2f& v1, float scalar)
	{
		Vector2f scaledVector{ v1.x * scalar,v1.y * scalar };
		return scaledVector;
	}
	Vector2f Normalize(const Vector2f& v1)
	{
		Vector2f normal{ v1.x / Length(v1), v1.y / Length(v1) };
		return normal;
	}
	float AngleBetween(const Vector2f& v1, const Vector2f& v2)
	{
		return ConvertToDegrees(atan2(Cross(v1,v2),Dot(v1,v2)));
	}
	bool AreEqual(const Vector2f& v1, const Vector2f& v2)
	{
		float Xdifference{ v2.x - v1.x };
		float Ydifference{ v2.y - v1.y };
		return Xdifference <= 0.001f && Ydifference <= 0.001f;
	}
	Vector2f CalculateProjection(const Vector2f& v, Vector2f& v2, float angle)
	{
		Point2f coords{ CreateCoordinatesFromRads(Length(v),ConvertToRadians(angle)) };
		Vector2f newVector{ coords.x,coords.y };
		v2 = newVector;
		Vector2f normal{ Normalize(v) };
		float dotProduct{ Dot(newVector, normal)} ;
		return Scale(normal, dotProduct);
	}
	Vector2f CreateVector(const Point2f& p1, const Point2f& p2)
	{
		Vector2f direction{};
		direction.x = p2.x - p1.x;
		direction.y = p2.y - p1.y;
		return direction;
	}
#pragma endregion VectorMath
}