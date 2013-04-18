#include "MyEngine.h"


MyEngine::MyEngine(){
	_curr_timeLoc = -1;
	_curr_time = 0.0;
	_isMaster = false;
	_testVar = 0;
}
MyEngine::~MyEngine(){
	delete _sound;
}

void MyEngine::myDrawFun(){
	//set current shader program
	sgct::ShaderManager::Instance()->bindShader( "SimpleColor" );
	glUniform1f( _curr_timeLoc, static_cast<float>( _curr_time ) );

	float speed = 50.0f;
	glRotatef(static_cast<float>( _curr_time ) * speed, 0.0f, 1.0f, 0.0f);

	//render a single triangle
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();

	//unset current shader program
	sgct::ShaderManager::Instance()->unBindShader();
}

void MyEngine::myPreSyncFun() {
	if( _isMaster )
	{
		_curr_time = sgct::Engine::getTime();
	}
}

void MyEngine::myInitOGLFun() {

	sgct::ShaderManager::Instance()->addShader( "SimpleColor", "data/shaders/simple.vert", "data/shaders/simple.frag" );
	sgct::ShaderManager::Instance()->bindShader( "SimpleColor" );

	_curr_timeLoc = sgct::ShaderManager::Instance()->getShader( "SimpleColor").getUniformLocation( "curr_time" );

	sgct::ShaderManager::Instance()->unBindShader();

	_sound = new MySound("data/audio/file1.wav");
}

void MyEngine::myEncodeFun() {
	sgct::SharedData::Instance()->writeDouble( _curr_time );
}

void MyEngine::myDecodeFun() {
	_curr_time = sgct::SharedData::Instance()->readDouble();
}

void MyEngine::testSet(int v) {
	if(v >= 0)
		_testVar = v;
	else
		_testVar = 0;
}

int MyEngine::testDo(){
	return _testVar;
}