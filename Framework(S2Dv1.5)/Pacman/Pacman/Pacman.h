#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif
#define MUNCHIECOUNT 50
#define GHOSTCOUNT 32
// Just need to include main header file
#include "S2D/S2D.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;


struct Player
{
	float speedMultiplier;
	int currentFrameTime;
	int direction;
	int frame;
	Rect* sourceRect;
	Texture2D* texture;
	Vector2* position;
	const int frameTime = 160;
	const float speed = 0.1f;
	bool dead;
};

struct Collect
{
	int frame;
	int currentFrameTime;
	int frameCount;
	Rect* rect;
	Texture2D* blueTexture;
	Texture2D* invertedTexture;
	Vector2* position;
	const int frameTime = 600;
	Texture2D* cMunchie;
};

struct Menu
{
	Texture2D* background;
	Rect* rectangle;
	Vector2* stringPosition;
	bool paused;
	bool pKeyDown;
	bool startGame;
	Vector2* cordstringPosition;
};

struct Enemy
{
	Vector2* position;
	Texture2D* texture;
	Rect* sourceRect;
	int direction;
	float speed;
	int frame;
	int currentFrameTime;
	int frameCount;
	const int frameTime = 160;
};




// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
class Pacman : public Game
{
private:
	//// Data to represent Pacman
	//Vector2* _pacmanPosition;
	//Rect* _pacmanSourceRect;
	//Texture2D* _pacmanTexture;
	//int _pacmanDirection;
	//int _pacmanFrame;
	//int _pacmanCurrentFrameTime;
	//const int _cpacmanFrameTime;

	//// Data to represent Munchie
	//int _frameCount;
	//Rect* _munchieRect;
	//Texture2D* _munchieBlueTexture;
	//Texture2D* _munchieInvertedTexture;
	//const int _cMunchieFrameTime;
	//int _munchieFrame;
	//int _munchieCurrentFrameTime;

	//// Position for String
	//Vector2* _stringPosition;

	//// Constant data for Game variables 
	//const float _cPacmanSpeed;

	//// Data for menu
	//Texture2D* _menuBackground;
	//Rect* _menuRectangle;
	//Vector2* _menuStringPosition;
	//bool _paused;
	//bool _pKeyDown;
	//bool _startGame;

	Player* _pacman;
	Collect* _munchies[MUNCHIECOUNT];
	Menu* _pausenmain;
	Collect* _cherry;
	Enemy* _ghost[GHOSTCOUNT];
	SoundEffect* _pop;
	SoundEffect* _bgm;

	//Input methods 
	void Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState*mouseState);


	//Check methods
	void CheckPaused(Input::KeyboardState* state);
	void CheckViewportCollision();
	void CheckGhostCollisions();
	void CheckMunchieCollisions();

	//Update methods
	void UpdatePacman(int elapsedTime);
	void UpdateMunchie(int elapsedTime);
	void UpdateCherry(int elapsedTime);
	void UpdateGhost(int elapsedTime);

public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);


};