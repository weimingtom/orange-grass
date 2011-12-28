#ifndef OGFPSCOUNTER_H_
#define OGFPSCOUNTER_H_

#include <IOGFPSCounter.h>

class COGFPSCounter : public IOGFPSCounter
{
public:
	COGFPSCounter();
	virtual ~COGFPSCounter();

	// updating FPS counter
	virtual void Update ();

	// getting current FPS rate
	virtual long GetFPS ()  { return (long)fps; }

private:

	float fps;
	float speedfactor;

	LARGE_INTEGER tickspersecond;
	LARGE_INTEGER currentticks;
	LARGE_INTEGER framedelay;
};

#endif
