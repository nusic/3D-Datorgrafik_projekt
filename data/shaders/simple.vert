#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
attribute vec2 vertexUV;

// Values that doens't change depending on vertex
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;

uniform float currentTime;
uniform float globalRandom;

//Light data
const int MAX_NUMBER_OF_LIGHTS = 7;
uniform int numberOfLights;
uniform vec3 lightPosition_worldSpace[MAX_NUMBER_OF_LIGHTS];
uniform vec3 lightDirection_worldSpace[MAX_NUMBER_OF_LIGHTS];

//Output that will go to the fragment shader.
//When it does it will be interpolated for each fragment.
varying vec3 position_worldSpace;
varying vec2 UV;
varying vec3 viewDirectionToVertex_viewSpace;
varying vec3 normal_viewSpace;

varying vec3 lightDirectionToVertex_viewSpace[MAX_NUMBER_OF_LIGHTS];
varying vec3 lightDirection_viewSpace[MAX_NUMBER_OF_LIGHTS];



void main(){
	gl_Position = MVP * vec4(vertexPosition, 1.0);

	position_worldSpace = (M * vec4(vertexPosition, 1.0)).xyz;


	vec3 vertexPosition_viewSpace = ( V * M * vec4(vertexPosition,1)).xyz;
	//viewDirectionToVertex_viewspace is directed towards the camera
	viewDirectionToVertex_viewSpace = vec3(0,0,0) + vertexPosition_viewSpace;

	for (int i = 0; i < MAX_NUMBER_OF_LIGHTS; ++i)
	{
		lightDirection_viewSpace[i] = (V * vec4(lightDirection_worldSpace[i], 0)).xyz;

		vec3 lightPosition_viewSpace = ( V * vec4(lightPosition_worldSpace[i],1)).xyz;
		lightDirectionToVertex_viewSpace[i] = viewDirectionToVertex_viewSpace - lightPosition_viewSpace;
	}


	// Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
	// (Läre vi kanske göra?!)
	normal_viewSpace  = ( V * M * vec4(vertexNormal,0)).xyz;

	//normal = vertexNormal;
	UV = vertexUV;
}


