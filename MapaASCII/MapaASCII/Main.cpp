#define NOMINMAX

#include <cstdio>
#include <Windows.h>
#include "Application.h"

void main()
{
	// console warning if I forget release ram
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetBreakAlloc(758);

	bool _running = true;
	Application* _app = new Application();
	
	_app->init();

	while (_running)
	{
		_app->update();

		// press the scape key to exit
		if (GetAsyncKeyState(VK_ESCAPE))
			_running = false;
	}

	if (_app)
		delete(_app);
}