#ifndef HIGANTIMER_H
#define HIGANTIMER_H

namespace higan
{
	class Timer
	{
	public:
		static void wait(int ms);
		static unsigned long getTicks();
	};
}
#endif