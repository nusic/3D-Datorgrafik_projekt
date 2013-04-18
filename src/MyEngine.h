#ifndef MYENGINE_H
#define MYENGINE_H

#include "sgct.h"
#include "MySound.h"

class MyEngine {
public:
	MyEngine();
	~MyEngine();

	void myDrawFun();
	void myPreSyncFun();
	void myInitOGLFun();
	void myEncodeFun();
	void myDecodeFun();

	void setMaster(bool master) { _isMaster = master; };

	void testSet(int v);
	int testDo();

private:
	double _curr_time;
	int _curr_timeLoc;
	bool _isMaster;
	int _testVar;
	MySound *_sound;
};

#endif