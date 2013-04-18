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

	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
		 -1.5f, -0.5f, 0.0f,
		 2.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

void MyEngine::myInitOGLFun() {

	sgct::ShaderManager::Instance()->addShader( 
		"SimpleColor", "data/shaders/simple.vert", "data/shaders/simple.frag" );
	sgct::ShaderManager::Instance()->bindShader( "SimpleColor" );


	_curr_timeLoc = sgct::ShaderManager::Instance()->getShader( "SimpleColor").getUniformLocation( "curr_time" );

	sgct::ShaderManager::Instance()->unBindShader();

	_sound = new MySound("data/audio/file1.wav");

	////////////////////

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}



void MyEngine::myPreSyncFun() {
	if( _isMaster )
	{
		_curr_time = sgct::Engine::getTime();
	}
}



void MyEngine::myDrawFun(){


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0, // The attribute we want to configure
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);



	//set current shader program
	/*sgct::ShaderManager::Instance()->bindShader( "SimpleColor" );
	glUniform1f( _curr_timeLoc, static_cast<float>( _curr_time ) );

	float speed = 50.0f;
	glRotatef(static_cast<float>( _curr_time ) * speed, 0.0f, 1.0f, 0.0f);


	//render a single triangle
	glBegin(GL_TRIANGLES);
	for(int i = 0; i<1000; i++){
		glVertex3f(-0.5f, -0.5f, i*0.5f);
		glVertex3f(0.0f, 0.5f, i*0.5f);
		glVertex3f(0.5f, -0.5f, i*0.5f);
	}
	glEnd();


	//unset current shader program
	sgct::ShaderManager::Instance()->unBindShader();*/
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