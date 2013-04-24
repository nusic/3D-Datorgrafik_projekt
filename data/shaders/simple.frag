#version 120

//Input: Interpolated values from the vertex shader
varying vec3 fragmentColor;
varying vec3 normal;
varying vec2 UV;

uniform sampler2D textureSampler;

void main()
{
	// Output color = red
	//gl_FragColor = vec4(1,0,0,1);

	vec3 materialDiffuseColor = texture2D( textureSampler, UV ).rgb;
	vec3 materialAmbientColor = vec3(0.2,0.2,0.2) * materialDiffuseColor;
	vec3 materialSpecularColor = vec3(0.3,0.3,0.3);

	vec3 lightDirection = vec3(1, 1, -1);

	vec3 n = normalize(normal);
	vec3 l = normalize(lightDirection);

	float cosTheta = clamp(dot(-n, l), 0, 1);


	gl_FragColor = vec4(materialDiffuseColor, 1) * cosTheta + vec4(materialAmbientColor, 1);
}