#include "Pacman.h"

#include <sstream>
#include <time.h>
#include <iostream>

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv)
{




	_pacman = new Player();
	_pausenmain = new Menu();
	
	_pop = new SoundEffect();
	_crunch = new SoundEffect();


	for (int i = 0; i < GHOSTCOUNT; ++i)
	{
		_ghost[i] = new Enemy();
		_ghost[i]->direction = 0;
		_ghost[i]->speed = 0.2f;

	}
	


	for (int i = 0; i < MUNCHIECOUNT; ++i)
	{
		_munchies[i] = new Collect();
		_munchies[i]->currentFrameTime = 0;
		_munchies[i]->frame = 0;
		_munchies[i]->frameCount = 0;
	}

	for (int i = 0; i < CHERRYCOUNT; ++i)
	{
		_cherry[i] = new Collect();
		_cherry[i]->currentFrameTime = 0;
		_cherry[i]->frame = 0;
		_cherry[i]->frameCount = 0;
	}

	//pausemenu
	_pausenmain->paused = false;
	_pausenmain->pKeyDown = false;
	_pausenmain->startGame = false;
	_pausenmain->deathScreen = false;
	_pausenmain->winScreen = false;
	//pacman
	_pacman->direction = 0;
	_pacman->currentFrameTime = 0;
	_pacman->frame = 0;
	_pacman->speedMultiplier = 1.0f;
	_pacman->dead = false;
	_pacman->points = 0;
	





	Audio::Initialise();
	//Initialise important Game aspects
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();
	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}




Pacman::~Pacman()
{
	
	for (int i = 0; i < MUNCHIECOUNT; ++i)
	{
		delete _munchies[i]->cMunchie;
		delete _munchies[i]->position;
		delete _munchies[i]->rect;
		delete _munchies[i];
	}
	delete _pausenmain->background1;
	delete _pausenmain->background2;
	delete _pausenmain->background3;
	delete _pausenmain->background4;
	delete _pausenmain->rectangle;
	delete _pausenmain->stringPosition;
	delete _pacman->texture;
	delete _pacman->position;
	delete _pacman->sourceRect;
	delete _pausenmain;
	delete _pacman;
	for (int i = 0; i < CHERRYCOUNT; ++i)
	{
		delete _cherry[i]->cMunchie;
		delete _cherry[i]->position;
		delete _cherry[i]->rect;
		delete _cherry[i];
	}

	delete _pop;
	delete _crunch;
	for (int i = 0; i < GHOSTCOUNT; ++i)
	{
		delete _ghost[i]->texture;
		delete _ghost[i]->position;
		delete _ghost[i]->sourceRect;
		delete _ghost[i];
	}
}

void Pacman::LoadContent()
{
	// Load Pacman
	_pacman->texture = new Texture2D();
	_pacman->texture->Load("Textures/Pacman.tga", false);
	_pacman->position = new Vector2(350.0f, 350.0f);
	_pacman->sourceRect = new Rect(0.0f, 0.0f, 32, 32);


	for (int i = 0; i < MUNCHIECOUNT; ++i)
	{

		_munchies[i]->cMunchie = new Texture2D();
		_munchies[i]->cMunchie->Load("Textures/AllMunchies.png", false);
		_munchies[i]->rect = new Rect(0.0f, 0.0f, 12, 12);
		_munchies[i]->position = new Vector2((rand() % Graphics::GetViewportWidth() - _munchies[i]->rect->Width) , (rand() % Graphics::GetViewportHeight() - _munchies[i]->rect->Height));
	}

	for (int i = 0; i < CHERRYCOUNT; ++i)
	{
		//Load cherry
		_cherry[i]->cMunchie = new Texture2D();
		_cherry[i]->cMunchie->Load("Textures/Cherry.png", false);
		_cherry[i]->rect = new Rect(100.0f, 350.0f, 32, 32);
		_cherry[i]->position = new Vector2((rand() % Graphics::GetViewportWidth() - _cherry[i]->rect->Width), (rand() % Graphics::GetViewportHeight() - _cherry[i]->rect->Height));
		
	}





	// Set string position
	_pausenmain->cordstringPosition = new Vector2(10.0f, 25.0f);

	// Set mainmenu Parameters
	_pausenmain->background1 = new Texture2D();
	_pausenmain->background1->Load("Textures/mainmenu.png", false);
	_pausenmain->rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportWidth());
	_pausenmain->stringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);


	_pausenmain->background2 = new Texture2D();
	_pausenmain->background2->Load("Textures/pausemenu.png", false);
	_pausenmain->rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportWidth());
	_pausenmain->stringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);


	_pausenmain->background3 = new Texture2D();
	_pausenmain->background3->Load("Textures/gameover.png", false);
	_pausenmain->rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportWidth());
	_pausenmain->stringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);


	_pausenmain->background4 = new Texture2D();
	_pausenmain->background4->Load("Textures/winscreen.png", false);
	_pausenmain->rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportWidth());
	_pausenmain->stringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);



	//Initialise ghost character
	for (int i = 0; i < GHOSTCOUNT; ++i)
	{
		_ghost[i]->texture = new Texture2D();
		_ghost[i]->texture->Load("Textures/AllGhostfix.png", false);
		_ghost[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
		_ghost[i]->sourceRect = new Rect(0.0f, 0.0f, 20, 20);
	}

	//Load sounds 
	_pop->Load("Sounds/pop.wav");
	_crunch->Load("Sounds/crunch.wav");

}


void Pacman::Update(int elapsedTime)
{




	if (!Audio::IsInitialised())
	{
		std::cout << "Audio is not initialised" << std::endl;
	}

	if (!_pop->IsLoaded())
	{
		std::cout << "pop member sound efffect not loaded" << std::endl;
	}


	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();


	if (!_pausenmain->startGame)
	{
		//Check for start
		if (keyboardState->IsKeyDown(Input::Keys::SPACE))
		{
			_pausenmain->startGame = true;
			
		}


	}
	else
	{
		
		if (!_pausenmain->paused)
		{

			Input(elapsedTime, keyboardState);
			CheckViewportCollision();
			UpdatePacman(elapsedTime);
			UpdateMunchie(elapsedTime);
			UpdateCherry(elapsedTime);
			UpdateGhost(elapsedTime);
			CheckGhostCollisions();
			CheckMunchieCollisions();
			CheckCherryCollisions();
			if (_pacman->points == 75)
			{
				_pausenmain->winScreen = true;
			}
		}
		
	}

	CheckPaused(keyboardState);

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
	for (int i = 0; i < MUNCHIECOUNT; ++i)
	{
		_munchies[i]->currentFrameTime += elapsedTime;
		if (_munchies[i]->currentFrameTime > _munchies[i]->frameTime)
		{
			_munchies[i]->frame++;

			if (_munchies[i]->frame >= 2)
				_munchies[i]->frame = 0;

			_munchies[i]->currentFrameTime = 0;
			_munchies[i]->rect->X = _munchies[i]->rect->Width * _munchies[i]->frame;
		}
	}

}

//Update animation for cherry
void Pacman::UpdateCherry(int elapsedTime)
{
	for (int i = 0; i < CHERRYCOUNT; ++i)
	{
		_cherry[i]->currentFrameTime += elapsedTime;
		if (_cherry[i]->currentFrameTime > _cherry[i]->frameTime)
		{
			_cherry[i]->frame++;

			if (_cherry[i]->frame >= 2)
				_cherry[i]->frame = 0;

			_cherry[i]->currentFrameTime = 0;
			_cherry[i]->rect->X = _cherry[i]->rect->Width * _cherry[i]->frame;
		}
	}

}


void Pacman::UpdateGhost(int elapsedTime)
{
	for (int i = 0; i < GHOSTCOUNT; ++i)
	{
		if (_ghost[i]->direction == 0) //Moves Right 
		{
			_ghost[i]->position->X += _ghost[i]->speed * elapsedTime;

		}
		else if (_ghost[i]->direction == 2) //Moves Left 
		{
			_ghost[i]->position->X -= _ghost[i]->speed * elapsedTime;

		}


		if (_ghost[i]->position->X + _ghost[i]->sourceRect->Width >=
				Graphics::GetViewportWidth()) //Hits Right edge 
		{
			_ghost[i]->direction = 2; //Change direction 
		}

		else if (_ghost[i]->position->X <= 0) //Hits left edge 
		{
			_ghost[i]->direction = 0; //Change direction 

		}
		/*_ghost[i]->sourceRect->Y = _ghost[i]->sourceRect->Height * _ghost[i]->direction;*/

	}
}



void Pacman::CheckGhostCollisions()
{
	// Local Variables
	int i = 0;
	int bottom1 = _pacman->position->Y + _pacman->sourceRect->Height;
	int bottom2 = 0;
	int left1 = _pacman->position->X;
	int left2 = 0;
	int right1 = _pacman->position->X + _pacman->sourceRect->Width;
	int right2 = 0;
	int top1 = _pacman->position->Y;
	int top2 = 0;
	

	for (i = 0; i < GHOSTCOUNT; i++)
	{
		// Populate variables with Ghost data
		bottom2 = _ghost[i]->position->Y + _ghost[i]->sourceRect->Height;
		left2 = _ghost[i]->position->X;
		right2 = _ghost[i]->position->X + _ghost[i]->sourceRect->Width;
		top2 = _ghost[i]->position->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
		{
			i = GHOSTCOUNT;
			_pausenmain->deathScreen = true;
			
		}
	}


}

void Pacman::CheckMunchieCollisions()
{
	// Local Variables
	int i = 0;
	int bottom1 = _pacman->position->Y + _pacman->sourceRect->Height;
	int bottom2 = 0;
	int left1 = _pacman->position->X;
	int left2 = 0;
	int right1 = _pacman->position->X + _pacman->sourceRect->Width;
	int right2 = 0;
	int top1 = _pacman->position->Y;
	int top2 = 0;


	for (i = 0; i < MUNCHIECOUNT; i++)
	{
		// Populate variables with Ghost data
		bottom2 = _munchies[i]->position->Y + _munchies[i]->rect->Height;
		left2 = _munchies[i]->position->X;
		right2 = _munchies[i]->position->X + _munchies[i]->rect->Width;
		top2 = _munchies[i]->position->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
		{
			
			_munchies[i]->position->Y = -100;
			_munchies[i]->position->X = -100;
			_pacman->points += 1;
			i = MUNCHIECOUNT;
			Audio::Play(_pop);


		}
	}


}


void Pacman::CheckCherryCollisions()
{
	// Local Variables
	int i = 0;
	int bottom1 = _pacman->position->Y + _pacman->sourceRect->Height;
	int bottom2 = 0;
	int left1 = _pacman->position->X;
	int left2 = 0;
	int right1 = _pacman->position->X + _pacman->sourceRect->Width;
	int right2 = 0;
	int top1 = _pacman->position->Y;
	int top2 = 0;


	for (i = 0; i < CHERRYCOUNT; i++)
	{
		// Populate variables with Ghost data
		bottom2 = _cherry[i]->position->Y + _cherry[i]->rect->Height;
		left2 = _cherry[i]->position->X;
		right2 = _cherry[i]->position->X + _cherry[i]->rect->Width;
		top2 = _cherry[i]->position->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
		{

			_cherry[i]->position->Y = -100;
			_cherry[i]->position->X = -100;
			_pacman->points += 5;
			i = CHERRYCOUNT;
			Audio::Play(_crunch);


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
		_pacman->position->X += _pacman->speed * elapsedTime * _pacman->speedMultiplier; //Moves Pacman across X axis
		_pacman->direction = 0;
		
	}

	// Checks if A key is pressed
	if (state->IsKeyDown(Input::Keys::A))
	{
		_pacman->position->X -= _pacman->speed * elapsedTime  * _pacman->speedMultiplier; //Moves Pacman across X axis
		_pacman->direction = 2;
	}

	// Checks if W key is pressed
	if (state->IsKeyDown(Input::Keys::W))
	{
		_pacman->position->Y -= _pacman->speed * elapsedTime * _pacman->speedMultiplier; //Moves Pacman across Y axis
		_pacman->direction = 3;
	}

	// Checks if S key is pressed
	if (state->IsKeyDown(Input::Keys::S))
	{
		_pacman->position->Y += _pacman->speed * elapsedTime * _pacman->speedMultiplier; //Moves Pacman across Y axis
		_pacman->direction = 1;
	}
	_pacman->sourceRect->Y = _pacman->sourceRect->Height * _pacman->direction;

	//Speed Multiplier 
	if (state->IsKeyDown(Input::Keys::LEFTSHIFT))
	{
		//Apply multiplier 
		_pacman->speedMultiplier = 2.0f;
	}
	else
	{
		//Reset multiplier 
		_pacman->speedMultiplier = 1.0f;
	}









}

//Check if user ever press P 
void Pacman::CheckPaused(Input::KeyboardState* state)
{

	//When p is held down game should pause or unpause
	if (state->IsKeyDown(Input::Keys::P) && !_pausenmain->pKeyDown)
	{
		_pausenmain->pKeyDown = true;
		_pausenmain->paused = !_pausenmain->paused;

	}
	if (state->IsKeyUp(Input::Keys::P))
	{
		_pausenmain->pKeyDown = false;
		
	}

}

void Pacman::Draw(int elapsedTime)
{
	SpriteBatch::BeginDraw(); // Starts Drawing





	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Player Points: " << _pacman->points;



	//draws munchies
	for (int i = 0; i < MUNCHIECOUNT; ++i)
	{
		SpriteBatch::Draw(_munchies[i]->cMunchie, _munchies[i]->position, _munchies[i]->rect);
	}



	SpriteBatch::Draw(_pacman->texture, _pacman->position, _pacman->sourceRect); // Draws Pacman

	for (int i = 0; i < CHERRYCOUNT; ++i)
	{
		SpriteBatch::Draw(_cherry[i]->cMunchie, _cherry[i]->position, _cherry[i]->rect); // Draws Cherry
	}
	

	//Draw ghost
	for (int i = 0; i < GHOSTCOUNT; ++i)
	{
		SpriteBatch::Draw(_ghost[i]->texture, _ghost[i]->position, _ghost[i]->sourceRect);
	}
	
	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _pausenmain->cordstringPosition, Color::Green);
	
	//Draws text to pause menu and adds transparent texture
	if (_pausenmain->paused)
	{


		SpriteBatch::Draw(_pausenmain->background2, _pausenmain->rectangle, nullptr);

	}

	//Draws text to start menu before the game starts and adds transparent texture
	if (!_pausenmain->startGame)
	{


		SpriteBatch::Draw(_pausenmain->background1, _pausenmain->rectangle, nullptr);

	}
	
	

	//Draws text for game over
	if (_pausenmain->deathScreen)
	{
		


		SpriteBatch::Draw(_pausenmain->background3, _pausenmain->rectangle, nullptr);
	}



  	if (_pausenmain->winScreen)
	{


		SpriteBatch::Draw(_pausenmain->background4, _pausenmain->rectangle, nullptr);

	}


	SpriteBatch::EndDraw(); // Ends Drawing
}