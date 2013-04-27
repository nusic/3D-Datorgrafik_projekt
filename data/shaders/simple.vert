#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
attribute vec2 vertexUV;


// Values that doens't change depending on vertex
uniform mat4 MVP;
uniform mat4 M;
uniform vec3 lightPosition_worldSpace;


//Output that will go to the fragment shader. 
//When it does it will be interpolated for each fragment.
varying vec3 position_worldSpace;
varying vec3 normal;
varying vec2 UV;

varying vec3 eyeDirection_cameraSpace;
varying vec3 lightDirection_worldSpace;


void main(){
	gl_Position = MVP * vec4(vertexPosition, 1.0);

	position_worldSpace = (M * vec4(vertexPosition, 1.0)).xyz;
	normal = vertexNormal;
	UV = vertexUV;

	lightDirection_worldSpace = position_worldSpace - lightPosition_worldSpace;

}

