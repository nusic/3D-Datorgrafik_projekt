#version 120
//Input: Interpolated values from the vertex shader
varying vec3 position_worldSpace;
varying vec3 normal;
varying vec2 UV;

varying vec3 lightDirection_worldSpace;

uniform sampler2D textureSampler;
uniform vec3 lightPosition_worldspace;


void main()
{
	// Output color = red
	//gl_FragColor = vec4(1,0,0,1);

	vec3 materialDiffuseColor = texture2D( textureSampler, UV ).rgb;
	vec3 materialAmbientColor = vec3(0.1,0.1,0.1) * materialDiffuseColor;
	vec3 materialSpecularColor = vec3(0.1,0.1,0.1);

	float distanceToLight = length(lightPosition_worldspace - position_worldSpace);
	

	vec3 n = normalize(normal);

	vec3 p = normalize(position_worldSpace);
	//vec3 lightDirection = vec3(1,1,1);//n-1.5*p;

	vec3 l = normalize(lightDirection_worldSpace);

	float cosTheta = clamp(dot(-n, l), 0, 1);


	gl_FragColor =
		vec4(materialAmbientColor, 1) + //Ambient
		vec4(materialDiffuseColor, 1) * 5 * cosTheta / (distanceToLight * distanceToLight); //Diffuse
}