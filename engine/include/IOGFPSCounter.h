#ifndef IOGFPSCOUNTER_H_
#define IOGFPSCOUNTER_H_


class IOGFPSCounter
{
public:
    virtual ~IOGFPSCounter() {}

	// updating FPS counter
	virtual void Update () = 0;

	// getting current FPS rate
	virtual long GetFPS () = 0;
};

#endif