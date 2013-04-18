#include "MySound.h"
#include "sgct.h"


MySound::MySound(const char* fileName) {
#ifndef _NOSOUND_
	// only needed once
	alutInit(NULL, 0);

	_buffer = AL_NONE;
	alGenBuffers(1, &_buffer);
	alGenSources(1, &_source);
	 
	_buffer = alutCreateBufferFromFile(fileName);
	if(_buffer == AL_NONE )
	{
		sgct::MessageHandler::Instance()->print("Failed to read audio file '%s', error: %s\n", fileName, alutGetErrorString( alutGetError() ));
	}
	alSourcei(_source, AL_BUFFER, _buffer);
		
	alSourcef(_source, AL_PITCH, 1.0f);
	alSourcef(_source, AL_GAIN, 1.0f);
	alSource3f(_source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);

	alSourcei(_source, AL_LOOPING, AL_TRUE);
	alSourcePlay(_source);
#endif
}

MySound::~MySound() {
#ifndef _NOSOUND_
	alDeleteSources(1, &_buffer);
	alDeleteBuffers(1, &_buffer);
#endif
}
