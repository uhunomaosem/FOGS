#include "Pacman.h"

#include <sstream>

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv), _cPacmanSpeed(0.1f), _cpacmanFrameTime(160), _cMunchieFrameTime(600)
{
	_frameCount = 0;
	_paused = false;
	_pKeyDown = false;
	_startGame = false;
	_pacmanDirection = 0;
	_pacmanCurrentFrameTime = 0;
	_pacmanFrame = 0;
	//Initialise important Game aspects
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{
	delete _pacmanTexture;
	delete _pacmanSourceRect;
	delete _munchieBlueTexture;
	delete _munchieInvertedTexture;
	delete _munchieRect;
	delete _menuBackground;
	delete _menuRectangle;
	delete _stringPosition;
	delete _menuStringPosition;
	delete _pacmanPosition;

}

void Pacman::LoadContent()
{
	// Load Pacman
	_pacmanTexture = new Texture2D();
	_pacmanTexture->Load("Textures/Pacman.tga", false);
	_pacmanPosition = new Vector2(350.0f, 350.0f);
	_pacmanSourceRect = new Rect(0.0f, 0.0f, 32, 32);

	// Load Munchie
	_munchieBlueTexture = new Texture2D();
	_munchieBlueTexture->Load("Textures/Munchie.tga", true);
	_munchieInvertedTexture = new Texture2D();
	_munchieInvertedTexture->Load("Textures/MunchieInverted.tga", true);
	_munchieRect = new Rect(100.0f, 450.0f, 12, 12);

	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);

	// Set menu Parameters
	_menuBackground = new Texture2D();
	_menuBackground->Load("Textures/Transparency.png", false);
	_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportWidth());
	_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);
}

void Pacman::Update(int elapsedTime)
{

	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	if (!_startGame)
	{
		//Check for start
		if (keyboardState->IsKeyDown(Input::Keys::SPACE))
			_startGame = true;
	}
	else
	{
		CheckPaused(keyboardState, Input::Keys::P);
		if (!_paused)
		{
			Input(elapsedTime, keyboardState);
			CheckViewportCollision();
			UpdatePacman(elapsedTime);
			UpdateMunchie(elapsedTime);



		}
	}



}

void Pacman::UpdatePacman(int elapsedTime, int _pacmanCurrentFrameTime, const int _cpacmanFrameTime, int _pacmanFrame, Rect* _pacmanSourceRect)
{
	_pacmanCurrentFrameTime += elapsedTime;
	if (_pacmanCurrentFrameTime > _cpacmanFrameTime)
	{
		_pacmanFrame++;

		if (_pacmanFrame >= 2)
			_pacmanFrame = 0;

		_pacmanCurrentFrameTime = 0;
		_pacmanSourceRect->X = _pacmanSourceRect->Width * _pacmanFrame;
	}
}
void Pacman::UpdateMunchie(int elapsedTime, int _munchieCurrentFrameTime, const int _cMunchieFrameTime, int _munchieFrame, Rect* _munchieSourceRect, int _frameCount)
{
	_munchieCurrentFrameTime += elapsedTime;
	if (_munchieCurrentFrameTime > _cMunchieFrameTime)
	{
		_frameCount++;

		if (_frameCount >= 2)
			_frameCount = 0;

		_munchieCurrentFrameTime = 0;
	}
}

void Pacman::CheckViewportCollision(Vector2* _pacmanPosition, Rect* _pacmanSourceRect)
{

	// Checks if Pacman is trying to disappear 
	if (_pacmanPosition->X > Graphics::GetViewportWidth())
	{
		// Pacman hit right wall - reset his position
		_pacmanPosition->X = 0;
	}
	// Checks if Pacman is trying to disappear 
	if (_pacmanPosition->X + _pacmanSourceRect->Width < 0)
	{
		// Pacman hit left wall - wrap around to right wall
		_pacmanPosition->X = Graphics::GetViewportWidth() - _pacmanSourceRect->Width;
	}

	// Checks if Pacman is trying to disappear 
	if (_pacmanPosition->Y > Graphics::GetViewportHeight())
	{
		// Pacman hit right wall - reset his position
		_pacmanPosition->Y = 0;
	}

	// Checks if Pacman is trying to disappear 
	if (_pacmanPosition->Y + _pacmanSourceRect->Height < 0)
	{
		// Pacman hit left wall - wrap around to right wall
		_pacmanPosition->Y = Graphics::GetViewportHeight() - _pacmanSourceRect->Height;
	}
}

void Pacman::Input(int elapsedTime, Input::KeyboardState* state)
{
	// Checks if D key is pressed
	if (state->IsKeyDown(Input::Keys::D))
	{
		_pacmanPosition->X += _cPacmanSpeed * elapsedTime; //Moves Pacman across X axis
		_pacmanDirection = 0;

	}

	// Checks if A key is pressed
	if (state->IsKeyDown(Input::Keys::A))
	{
		_pacmanPosition->X -= _cPacmanSpeed * elapsedTime; //Moves Pacman across X axis
		_pacmanDirection = 2;
	}

	// Checks if W key is pressed
	if (state->IsKeyDown(Input::Keys::W))
	{
		_pacmanPosition->Y -= _cPacmanSpeed * elapsedTime; //Moves Pacman across Y axis
		_pacmanDirection = 3;
	}

	// Checks if S key is pressed
	if (state->IsKeyDown(Input::Keys::S))
	{
		_pacmanPosition->Y += _cPacmanSpeed * elapsedTime; //Moves Pacman across Y axis
		_pacmanDirection = 1;
	}
}

void Pacman::CheckPaused(Input::KeyboardState* state, Input::Keys ,bool _paused, bool _startGame, bool _pKeyDown, int _pacmanDirection, Rect* _pacmanSourceRect)
{

	//When p is held down game should pause or unpause
	if (state->IsKeyDown(Input::Keys::P) && !_pKeyDown)
	{
		_pKeyDown = true;
		_paused = !_paused;
	}
	if (state->IsKeyUp(Input::Keys::P))
		_pKeyDown = false;



	_pacmanSourceRect->Y = _pacmanSourceRect->Height * _pacmanDirection;
}

void Pacman::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Pacman X: " << _pacmanPosition->X << " Y: " << _pacmanPosition->Y;

	SpriteBatch::BeginDraw(); // Starts Drawing
	SpriteBatch::Draw(_pacmanTexture, _pacmanPosition, _pacmanSourceRect); // Draws Pacman

	if (_frameCount == 0)
	{
		// Draws Red Munchie
		SpriteBatch::Draw(_munchieInvertedTexture, _munchieRect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);


	}
	else
	{
		// Draw Blue Munchie
		SpriteBatch::Draw(_munchieBlueTexture, _munchieRect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);



		if (_frameCount >= 60)
			_frameCount = 0;
	}

	
	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);
	
	//Draws text to pause menu and adds transparent texture
	if (_paused)
	{
		std::stringstream menuStream;
		menuStream << "PAUSED!";

		SpriteBatch::Draw(_menuBackground, _menuRectangle, nullptr);
		SpriteBatch::DrawString(menuStream.str().c_str(), _menuStringPosition, Color::Red);
	}

	//Draws text to start menu before the game starts and adds transparent texture
	if (!_startGame)
	{
		std::stringstream menuStream;
		menuStream << "MAIN MENU\n";
		menuStream << "Start game by pressing space";

		SpriteBatch::Draw(_menuBackground, _menuRectangle, nullptr);
		SpriteBatch::DrawString(menuStream.str().c_str(), _menuStringPosition, Color::Red);
	}
	
	SpriteBatch::EndDraw(); // Ends Drawing






}