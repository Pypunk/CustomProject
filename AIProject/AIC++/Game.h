#pragma once
#include <vector>
#include "Unit.h"
#include "Buidling.h"

class Game final
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;
	static const int m_AmountOfObjects{6};
	std::vector<GameObject*> m_pObjects;
	std::vector<Unit*> selectedUnits;
	std::vector<Building*> selectedBuildings;
	Point2f m_MousePos;
	class SelectionRect* selectionRect;
	bool m_IsRightMousePressed;
	Point2f m_RightMouseStartPos;
	Point2f m_RightMouseEndPos;
	Point2f m_RightCurrentPos;
	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
	std::vector<Point2f> GenerateRotatedFormationOffsets(int unitCount, float spacing, const Vector2f& facing);
	void IssueDirectionalCommand(const Point2f& start, const Point2f& end);

};