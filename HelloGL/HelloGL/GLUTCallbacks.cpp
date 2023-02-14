// Includes
#include "GLUTCallbacks.h"
#include "HelloGL.h"

// Namespace implementation
namespace GLUTCallbacks
{
	namespace
	{
		// Initialise to a null pointer before we do anything
		HelloGL* helloGL = nullptr;
	}

	void Init(HelloGL* gl)
	{
		helloGL = gl;
	}

	void Display()
	{

		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}
}
