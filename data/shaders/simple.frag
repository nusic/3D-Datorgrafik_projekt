#version 120


uniform sampler2D textureSampler;

//Light data
uniform int numberOfLights;
const int MAX_NUMBER_OF_LIGHTS = 1;
uniform vec3 lightPosition_worldSpace[MAX_NUMBER_OF_LIGHTS];
uniform vec3 lightColor[MAX_NUMBER_OF_LIGHTS];
uniform float lightIntensity[MAX_NUMBER_OF_LIGHTS];
uniform float lightSpread[MAX_NUMBER_OF_LIGHTS];
uniform int directional[MAX_NUMBER_OF_LIGHTS];

uniform float currentTime;
uniform float globalRandom;

//Input: Interpolated values from the vertex shader
varying vec3 position_worldSpace;
varying vec3 normal_viewSpace;
varying vec2 UV;

varying vec3 viewDirectionToVertex_viewSpace;

//Light data
varying vec3 lightDirectionToVertex_viewSpace[MAX_NUMBER_OF_LIGHTS];
varying vec3 lightDirection_viewSpace[MAX_NUMBER_OF_LIGHTS];

varying vec4 shadowCoord;
uniform sampler2D shadowMap;

//uniform vec3 lightPosition_worldspace;



void main()
{

	vec3 materialDiffuseColor = texture2D( textureSampler, UV ).rgb;
	vec3 materialAmbientColor = vec3(0.1,0.0,0.0) * materialDiffuseColor;
	vec3 materialSpecularColor = vec3(0.7,0.7,0.7);

	vec3 n = normalize(normal_viewSpace);
	// Eye vector (away from the camera)
	vec3 e = normalize(viewDirectionToVertex_viewSpace);

	vec4 finalFragColor = vec4(materialAmbientColor, 1); //Ambient


	float directionalIntensity;
	float cosTheta;
	vec3 l;
	vec3 r;
	float cosAlpha;
	float cosPhi;
	float distanceToLight;
	float distanceSquare;
	float invDistSquare;

	for (int i = 0; i < MAX_NUMBER_OF_LIGHTS; ++i){

		l = normalize(lightDirectionToVertex_viewSpace[i]);
		cosTheta = clamp(dot(-n, l), 0, 1);

		// Direction in which the triangle reflects the light
		r = reflect(l,n);
		cosAlpha = clamp( dot( e,-r ), 0,1 );


		//if (directional[i] == 1){
		vec3 ld = normalize(lightDirection_viewSpace[i]);
		cosPhi = clamp(dot(l, ld), 0, 1);

		directionalIntensity = pow(cosPhi, lightSpread[i]);	
		//}
		//else
		//	directionalIntensity = 1;
		distanceToLight = length(lightPosition_worldSpace[i] - position_worldSpace);
		distanceSquare = distanceToLight * distanceToLight;

//		float invDistSquare = clamp(1 - 0.2 * distanceToLight[i], 0, 1);
		invDistSquare = 1.0f/(distanceSquare);


		//float visibility = shadow2D( shadowMap, vec3(shadowCoord.xy, (shadowCoord.z)/shadowCoord.w) ).r;

		
		float visibility = 0.0;
		
		for (float x = -0.0001; x <= 0.0001; x+=0.00005){
			for (float y = -0.0001; y <= 0.0001; y+=0.00005){
				if(texture2D(shadowMap, (shadowCoord.xy / shadowCoord.w)).r >= shadowCoord.z / shadowCoord.w)
					visibility += 1.0;
			}	
		}
		visibility /= 16.0;
		


		finalFragColor += visibility * (
			vec4(materialDiffuseColor, 1) * vec4(lightColor[i], 1) * directionalIntensity *
			lightIntensity[i] * cosTheta * (invDistSquare) + //Diffuse

			vec4(materialSpecularColor, 1) * vec4(lightColor[i], 1) * directionalIntensity *
			lightIntensity[i] * pow(cosAlpha, 5) * (invDistSquare)); //Specular
	}

	gl_FragColor = finalFragColor;

}
