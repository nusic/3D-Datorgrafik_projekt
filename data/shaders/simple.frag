#version 120

//Input: Interpolated values from the vertex shader
varying vec3 fragmentColor;

void main()
{
	// Output color = red 
	gl_FragColor = vec4(fragmentColor,1);
}