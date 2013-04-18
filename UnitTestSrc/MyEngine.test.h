#include "../src/MyEngine.h"


TEST (MyEngineTest, TestSet)
{
	
	MyEngine *engine = new MyEngine();

	// test that constructor sets correct value
	EXPECT_EQ(0,engine->testDo());

	// test that setTest sets in the correct way
	engine->testSet(10);
	EXPECT_EQ(10,engine->testDo());

	// test that setTest sets in the correct way
	engine->testSet(-1);
	EXPECT_EQ(0,engine->testDo());

}