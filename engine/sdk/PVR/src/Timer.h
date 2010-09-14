#ifndef TIMER_H_
#define TIMER_H_

class CFPSCounter
{
public:
	CFPSCounter();
	virtual ~CFPSCounter();

	// updating FPS COUNTER
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