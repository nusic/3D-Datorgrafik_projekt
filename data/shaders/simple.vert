#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;

//Output that will go to the fragment shader. When it does it will be interpolated for each fragment.
varying vec3 fragmentColor;

void main(){
	gl_Position = vec4(vertexPosition_modelspace, 1.0);

	//Output the color depending of the position of the vertex to make it a bit interesting
	fragmentColor = vertexPosition_modelspace;
}

