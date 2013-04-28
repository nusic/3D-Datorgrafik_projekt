#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
attribute vec2 vertexUV;


// Values that doens't change depending on vertex
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 lightPosition_worldSpace;


//Output that will go to the fragment shader. 
//When it does it will be interpolated for each fragment.
varying vec3 position_worldSpace;
varying vec2 UV;

varying vec3 eyeDirection_cameraSpace;
varying vec3 lightDirection_cameraSpace;
varying vec3 normal_cameraSpace;

varying float distanceToLight;


void main(){
	gl_Position = MVP * vec4(vertexPosition, 1.0);

	position_worldSpace = (M * vec4(vertexPosition, 1.0)).xyz;

	distanceToLight = length(lightPosition_worldSpace - position_worldSpace);

	vec3 vertexPosition_cameraSpace = ( V * M * vec4(vertexPosition,1)).xyz;
	eyeDirection_cameraSpace = vec3(0,0,0) - vertexPosition_cameraSpace;

	vec3 lightPosition_cameraSpace = ( V * vec4(lightPosition_worldSpace,1)).xyz;
	lightDirection_cameraSpace = lightPosition_cameraSpace + eyeDirection_cameraSpace;


	// Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
	// (Läre vi kanske göra?!)
	normal_cameraSpace  = ( V * M * vec4(vertexNormal,0)).xyz;
	
	//normal = vertexNormal;
	UV = vertexUV;
}

