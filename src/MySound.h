#ifndef MYSOUND_H
#define MYSOUND_H

//include open AL
#ifdef __APPLE__
    #include <OpenAL/al.h>
    #include <ALUT/alut.h>
#else
    #include <AL/al.h>
    #include <AL/alut.h>
#endif

class MySound {
public:
	MySound(const char* fileName);
	~MySound();
private:
	ALuint _buffer;
	ALuint _source;
};

#endif