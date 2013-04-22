#version 120

//Input: Interpolated values from the vertex shader
varying vec3 fragmentColor;
varying vec3 normal;


void main()
{
	// Output color = red
	//gl_FragColor = vec4(1,0,0,1);

	vec3 lightDirection = vec3(1, -1, -1);

	vec3 n = normalize(normal);
	vec3 l = normalize(lightDirection);

	float cosTheta = clamp(dot(-n, l), 0, 1);

	vec3 localColor = vec3(0.5, 0.7, 0.7) + fragmentColor * 0.3;
	vec3 ambientColor = vec3(0.1, 0.1, 0.1);



	gl_FragColor = vec4(localColor, 1) * cosTheta + vec4(ambientColor, 1);
}