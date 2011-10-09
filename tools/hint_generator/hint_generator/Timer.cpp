#include "Timer.h"

#include <SDL_timer.h>

namespace higan
{
	void Timer::wait(int ms)
	{
		SDL_Delay(ms);
	}

	unsigned long Timer::getTicks()
	{
		return SDL_GetTicks();
	}
}