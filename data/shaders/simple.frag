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
varying vec3 normal_cameraSpace;
varying vec2 UV;

varying vec3 eyeDirection_cameraSpace;

//Light data
varying vec3 lightDirection_cameraSpace[maxNumberOfLights];
varying float distanceToLight[maxNumberOfLights];
varying vec3 lightDirectionVector_cameraSpace[maxNumberOfLights];

//uniform vec3 lightPosition_worldspace;


void main()
{

	vec3 materialDiffuseColor = texture2D( textureSampler, UV ).rgb;
	vec3 materialAmbientColor = vec3(0.05,0.05,0.05) * materialDiffuseColor;
	vec3 materialSpecularColor = vec3(0.7,0.7,0.7);

	//float distanceToLight = length(lightPosition_worldspace - position_worldSpace);

	vec3 n = normalize(normal_cameraSpace);
	// Eye vector (towards the camera)
	vec3 e = normalize(eyeDirection_cameraSpace);

	//vec3 p = normalize(position_worldSpace);
	//vec3 lightDirection = vec3(1,1,1);//n-1.5*p;

	vec4 finalFragColor = vec4(materialAmbientColor, 1); //Ambient

	for (int i = 0; i < numberOfLights && i < maxNumberOfLights; ++i){

		vec3 l = normalize(lightDirection_cameraSpace[i]);
		float cosTheta = clamp(dot(n, l), 0, 1);

		// Direction in which the triangle reflects the light
		vec3 r = reflect(-l,n);
		float cosAlpha = clamp( dot( e,r ), 0,1 );

		float directionalIntensity;
		if (directional[i] == 1){
			vec3 ld = normalize(lightDirectionVector_cameraSpace[i]);
			float cosPhi = clamp(dot(l, ld), 0, 1);

			directionalIntensity = pow(cosPhi, lightSpread[i]);
		}
		else
			directionalIntensity = 1;

		float distanceSquare = distanceToLight[i] * distanceToLight[i];

		finalFragColor +=
			vec4(materialDiffuseColor, 1) * vec4(lightColor[i], 1) * directionalIntensity *
			lightIntensity[i] * cosTheta / (distanceSquare); + //Diffuse

			vec4(materialSpecularColor, 1) * vec4(lightColor[i], 1) * directionalIntensity *
			lightIntensity[i] * pow(cosAlpha, 10) / (distanceSquare); //Specular
	}

	gl_FragColor = finalFragColor;
		
}