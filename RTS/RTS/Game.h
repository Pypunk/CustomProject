#pragma once
#include "SelectionRect.h"
#include "UnitManager.h"
#include "Camera.h"
#include "Forest.h"
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
	Point2f m_MousePos;
	const Window m_Window;
	SelectionRect m_SelectionRect;
	UnitManager m_UnitManager;
	Camera* m_pCamera;
	Rectf m_CameraRect;
	Forest m_Forest;
	float m_ScreenWidth;
	float m_ScreenHeight;
	float m_ClickTimer;
	bool m_SingleClickDetected;
	bool m_DoubleClickDetected;
	int m_MouseClick;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
};