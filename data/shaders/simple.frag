#version 120



uniform sampler2D textureSampler;

//Light data
uniform int numberOfLights;
const int maxNumberOfLights = 16;
uniform vec3 lightColor[maxNumberOfLights];
uniform float lightIntensity[maxNumberOfLights];
uniform float lightSpread[maxNumberOfLights];
uniform int directional[maxNumberOfLights];


//Input: Interpolated values from the vertex shader
varying vec3 position_worldSpace;
varying vec3 normal_viewSpace;
varying vec2 UV;

varying vec3 viewDirectionToVertex_viewSpace;

//Light data
varying vec3 lightDirectionToVertex_viewSpace[maxNumberOfLights];
varying float distanceToLight[maxNumberOfLights];
varying vec3 lightDirection_viewSpace[maxNumberOfLights];

//uniform vec3 lightPosition_worldspace;


void main()
{

	vec3 materialDiffuseColor = texture2D( textureSampler, UV ).rgb;
	vec3 materialAmbientColor = vec3(0.2,0.2,0.2) * materialDiffuseColor;
	vec3 materialSpecularColor = vec3(0.7,0.7,0.7);

	//float distanceToLight = length(lightPosition_worldspace - position_worldSpace);

	vec3 n = normalize(normal_viewSpace);
	// Eye vector (towards the camera)
	vec3 e = normalize(viewDirectionToVertex_viewSpace);

	//vec3 p = normalize(position_worldSpace);
	//vec3 lightDirection = vec3(1,1,1);//n-1.5*p;

	vec4 finalFragColor = vec4(materialAmbientColor, 1); //Ambient


	float directionalIntensity;
	float cosTheta;
	vec3 l;
	vec3 r;
	float cosAlpha;
	float cosPhi;
	float distanceSquare;
	for (int i = 0; i < numberOfLights && i < maxNumberOfLights; ++i){

		l = normalize(lightDirectionToVertex_viewSpace[i]);
		cosTheta = clamp(dot(-n, l), 0, 1);

		// Direction in which the triangle reflects the light
		r = reflect(l,n);
		cosAlpha = clamp( dot( e,-r ), 0,1 );

		
		if (directional[i] == 1){
			vec3 ld = normalize(lightDirection_viewSpace[i]);
			cosPhi = clamp(dot(l, ld), 0, 1);

			directionalIntensity = pow(cosPhi, lightSpread[i]);
		}
		else
			directionalIntensity = 1;

		distanceSquare = distanceToLight[i] * distanceToLight[i];

		finalFragColor +=
			vec4(materialDiffuseColor, 1) * vec4(lightColor[i], 1) * directionalIntensity *
			lightIntensity[i] * cosTheta / (distanceSquare) + //Diffuse

			vec4(materialSpecularColor, 1) * vec4(lightColor[i], 1) * directionalIntensity *
			lightIntensity[i] * pow(cosAlpha, 10) / (distanceSquare); //Specular
	}

	gl_FragColor = finalFragColor;
		
}