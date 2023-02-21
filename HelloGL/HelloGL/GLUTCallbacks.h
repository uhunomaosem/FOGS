#pragma once
class HelloGL;

namespace GLUTCallbacks
{
	void Init(HelloGL* gl);

	void Display();


	void Timer(int preferredRefresh);

	void KeyBoard(unsigned char key, int x, int y);
}
