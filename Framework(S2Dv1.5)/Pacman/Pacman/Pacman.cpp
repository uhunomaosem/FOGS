#include "Pacman.h"

#include <sstream>
#include <time.h>

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv)
{



	_pacman = new Player();
	_pausenmain = new Menu();
	for (int i = 0; i < MUNCHIECOUNT; ++i)
	{
		_munchies[i] = new Collect();
		_munchies[i]->currentFrameTime = 0;
		_munchies[i]->frame = 0;
		_munchies[i]->frameCount = 0;
	}

	_pausenmain->paused = false;
	_pausenmain->pKeyDown = false;
	_pausenmain->startGame = false;
	_pacman->direction = 0;
	_pacman->currentFrameTime = 0;
	_pacman->frame = 0;






	//Initialise important Game aspects
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{
	int i;
	for (i = 0; i < MUNCHIECOUNT; ++i)
	{
		delete _munchies[i]->blueTexture;
		delete _munchies[i]->invertedTexture;
		delete _munchies[i]->rect;
		delete _munchies[i];
	}
	delete _pausenmain->background;
	delete _pausenmain->rectangle;
	delete _pausenmain->stringPosition;
	delete _pacman->texture;
	delete _pacman->position;
	delete _pacman->sourceRect;
	delete _pausenmain;
	delete _pacman;

}

void Pacman::LoadContent()
{
	// Load Pacman
	_pacman->texture = new Texture2D();
	_pacman->texture->Load("Textures/Pacman.tga", false);
	_pacman->position = new Vector2(350.0f, 350.0f);
	_pacman->sourceRect = new Rect(0.0f, 0.0f, 32, 32);

	int i;
	for (i = 0; i < MUNCHIECOUNT; ++i)
	{
		// Load Munchie
		_munchies[i]->blueTexture = new Texture2D();
		_munchies[i]->blueTexture->Load("Textures/Munchie.tga", true);
		_munchies[i]->invertedTexture = new Texture2D();
		_munchies[i]->invertedTexture->Load("Textures/MunchieInverted.tga", true);
		_munchies[i]->rect = new Rect(100.0f, 450.0f, 12, 12);
	//	_munchies[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	}


	// Set string position
	_pausenmain->cordstringPosition = new Vector2(10.0f, 25.0f);

	// Set menu Parameters
	_pausenmain->background = new Texture2D();
	_pausenmain->background->Load("Textures/Transparency.png", false);
	_pausenmain->rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportWidth());
	_pausenmain->stringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);


	

}


void Pacman::Update(int elapsedTime)
{


	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	if (!_pausenmain->startGame)
	{
		//Check for start
		if (keyboardState->IsKeyDown(Input::Keys::SPACE))
			_pausenmain->startGame = true;
	}
	else
	{
		CheckPaused(keyboardState, Input::Keys::P);
		if (!_pausenmain->paused)
		{
			Input(elapsedTime, keyboardState);
			CheckViewportCollision();
			UpdatePacman(elapsedTime);
			UpdateMunchie(elapsedTime);
			
			



		}
	}



}

//Update animation for Pacman
void Pacman::UpdatePacman(int elapsedTime)
{
	_pacman->currentFrameTime += elapsedTime;
	if (_pacman->currentFrameTime > _pacman->frameTime)
	{
		_pacman->frame++;

		if (_pacman->frame >= 2)
			_pacman->frame = 0;

		_pacman->currentFrameTime = 0;
		_pacman->sourceRect->X = _pacman->sourceRect->Width * _pacman->frame;
	}
}

//Update animation for Munchie
void Pacman::UpdateMunchie(int elapsedTime)
{
	int i;
	for (i = 0; i < MUNCHIECOUNT; ++i)
	{
		_munchies[i]->currentFrameTime += elapsedTime;
		if (_munchies[i]->currentFrameTime > _munchies[i]->frameTime)
		{
			_munchies[i]->frameCount++;

			if (_munchies[i]->frameCount >= 2)
				_munchies[i]->frameCount = 0;

			_munchies[i]->currentFrameTime = 0;
		}
	}

}

//Check for collision on any wall 
void Pacman::CheckViewportCollision()
{
	// Checks if Pacman is trying to disappear 
	if (_pacman->position->X > Graphics::GetViewportWidth())
	{
		// Pacman hit right wall - reset his position
		_pacman->position->X = 0;
	}
	// Checks if Pacman is trying to disappear 
	if (_pacman->position->X + _pacman->sourceRect->Width < 0)
	{
		// Pacman hit left wall - wrap around to right wall
		_pacman->position->X = Graphics::GetViewportWidth() - _pacman->sourceRect->Width;
	}

	// Checks if Pacman is trying to disappear 
	if (_pacman->position->Y > Graphics::GetViewportHeight())
	{
		// Pacman hit right wall - reset his position
		_pacman->position->Y = 0;
	}

	// Checks if Pacman is trying to disappear 
	if (_pacman->position->Y + _pacman->sourceRect->Height < 0)
	{
		// Pacman hit left wall - wrap around to right wall
		_pacman->position->Y = Graphics::GetViewportHeight() - _pacman->sourceRect->Height;
	}
}

//Check for any inputs for movement
void Pacman::Input(int elapsedTime, Input::KeyboardState* state)
{
	// Checks if D key is pressed
	if (state->IsKeyDown(Input::Keys::D))
	{
		_pacman->position->X += _pacman->speed * elapsedTime; //Moves Pacman across X axis
		_pacman->direction = 0;

	}

	// Checks if A key is pressed
	if (state->IsKeyDown(Input::Keys::A))
	{
		_pacman->position->X -= _pacman->speed * elapsedTime; //Moves Pacman across X axis
		_pacman->direction = 2;
	}

	// Checks if W key is pressed
	if (state->IsKeyDown(Input::Keys::W))
	{
		_pacman->position->Y -= _pacman->speed * elapsedTime; //Moves Pacman across Y axis
		_pacman->direction = 3;
	}

	// Checks if S key is pressed
	if (state->IsKeyDown(Input::Keys::S))
	{
		_pacman->position->Y += _pacman->speed * elapsedTime; //Moves Pacman across Y axis
		_pacman->direction = 1;
	}
	_pacman->sourceRect->Y = _pacman->sourceRect->Height * _pacman->direction;
}

//Check if user ever press P 
void Pacman::CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey)
{

	//When p is held down game should pause or unpause
	if (state->IsKeyDown(Input::Keys::P) && !_pausenmain->pKeyDown)
	{
		_pausenmain->pKeyDown = true;
		_pausenmain->paused = _pausenmain->paused;
	}
	if (state->IsKeyUp(Input::Keys::P))
		_pausenmain->pKeyDown = false;



	
}

void Pacman::Draw(int elapsedTime)
{
	
	for (int i = 0; i < MUNCHIECOUNT; ++i)
	{
		if (_munchies[i]->frameCount == 0)
		{
			// Draws Red Munchie
			SpriteBatch::Draw(_munchies[i]->invertedTexture, _munchies[i]->rect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);


		}
		else
		{
			// Draw Blue Munchie
			SpriteBatch::Draw(_munchies[i]->blueTexture, _munchies[i]->rect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);



			if (_munchies[i]->frameCount >= 60)
				_munchies[i]->frameCount = 0;
		}

	}

	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Pacman X: " << _pacman->position->X << " Y: " << _pacman->position->Y;

	SpriteBatch::BeginDraw(); // Starts Drawing
	SpriteBatch::Draw(_pacman->texture, _pacman->position, _pacman->sourceRect); // Draws Pacman


	
	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _pausenmain->cordstringPosition, Color::Green);
	
	//Draws text to pause menu and adds transparent texture
	if (_pausenmain->paused)
	{
		std::stringstream menuStream;
		menuStream << "PAUSED!";

		SpriteBatch::Draw(_pausenmain->background, _pausenmain->rectangle, nullptr);
		SpriteBatch::DrawString(menuStream.str().c_str(), _pausenmain->stringPosition, Color::Red);
	}

	//Draws text to start menu before the game starts and adds transparent texture
	if (!_pausenmain->startGame)
	{
		std::stringstream menuStream;
		menuStream << "MAIN MENU\n";
		menuStream << "Start game by pressing space";

		SpriteBatch::Draw(_pausenmain->background, _pausenmain->rectangle, nullptr);
		SpriteBatch::DrawString(menuStream.str().c_str(), _pausenmain->stringPosition, Color::Red);
	}
	
	SpriteBatch::EndDraw(); // Ends Drawing






}