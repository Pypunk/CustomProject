#pragma once

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
	const Rectf noRect{};
	const Rectf yesRect{};
	Rectf nextRect{};
	class Texture* m_pYesText;
	class Texture* m_pNoText;
	class Texture* m_pNextTest;
	class Texture* m_pQnA;
	class Texture* m_pEndTexture;
	class Texture* m_pHeart;
	bool isYes;
	bool isNo;
	bool isEnd;
	bool showNext;
	int clickCounter{};
	float timer{};
	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
};