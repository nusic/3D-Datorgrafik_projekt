#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
attribute vec2 vertexUV;

// Values that doens't change depending on vertex
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;

//Light data
uniform int numberOfLights;
const int maxNumberOfLights = 16;
uniform vec3 lightPosition_worldSpace[maxNumberOfLights];
uniform vec3 lightDirection_worldSpace[maxNumberOfLights];

//Output that will go to the fragment shader. 
//When it does it will be interpolated for each fragment.
varying vec3 position_worldSpace;
varying vec2 UV;
varying vec3 eyeDirection_cameraSpace;

varying vec3 lightDirection_cameraSpace[maxNumberOfLights];
//The lightDirectionVector is the direction the light is pointing,
//the lightDirection is the direction from the eye to the light.
varying vec3 lightDirectionVector_cameraSpace[maxNumberOfLights];
varying float distanceToLight[maxNumberOfLights];

varying vec3 normal_cameraSpace;




void main(){
	gl_Position = MVP * vec4(vertexPosition, 1.0);

	position_worldSpace = (M * vec4(vertexPosition, 1.0)).xyz;


	vec3 vertexPosition_cameraSpace = ( V * M * vec4(vertexPosition,1)).xyz;
	eyeDirection_cameraSpace = vec3(0,0,0) - vertexPosition_cameraSpace;

	for (int i = 0; i < numberOfLights && i < maxNumberOfLights; ++i)
	{
		lightDirectionVector_cameraSpace[i] = (V * vec4(lightDirection_worldSpace[i], 0)).xyz;

		distanceToLight[i] = length(lightPosition_worldSpace[i] - position_worldSpace);
		vec3 lightPosition_cameraSpace = ( V * vec4(lightPosition_worldSpace[i],1)).xyz;
		lightDirection_cameraSpace[i] = lightPosition_cameraSpace + eyeDirection_cameraSpace;
	}


	// Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
	// (Läre vi kanske göra?!)
	normal_cameraSpace  = ( V * M * vec4(vertexNormal,0)).xyz;
	
	//normal = vertexNormal;
	UV = vertexUV;
}


