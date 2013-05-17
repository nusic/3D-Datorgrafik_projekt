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

varying vec4 shadowCoord[MAX_NUMBER_OF_LIGHTS];

uniform sampler2D shadowMap01; //Tyvärr går det inte att skapa arrayer med sampler2D
uniform sampler2D shadowMap02; //Totalt 16 samplers är maximalt (Hårdvaran eller openGl)
uniform sampler2D shadowMap03; //En används till texturen så 15 st shadowmaps.
uniform sampler2D shadowMap04; //MAX_NUMBER_OF_LIGHTS får dock inte vara mer än 11
uniform sampler2D shadowMap05; //för då har man allokerat för mycket minne (gäller iaf Kalles grafikkort)
uniform sampler2D shadowMap06;
uniform sampler2D shadowMap07;
uniform sampler2D shadowMap08;
uniform sampler2D shadowMap09;
uniform sampler2D shadowMap10;
uniform sampler2D shadowMap11;
uniform sampler2D shadowMap12;
uniform sampler2D shadowMap13;
uniform sampler2D shadowMap14;
uniform sampler2D shadowMap15;


void main()
{

	vec3 materialDiffuseColor = texture2D( textureSampler, UV ).rgb;

	vec3 materialAmbientColor = vec3(0.2,0.4,0.6) * materialDiffuseColor;

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


		float visibility = 0.0;

		// Detta skulle ha varit en for-loop men eftersom det inte verkar gå att skapa arrayer av sampler2D görs det på detta sätt.
		// Här skulle man även kunna göra så kallat Poisson sampling för att få skuggorna mjukare. Det visar sig dock att beräkningarna
		// blir alldeles för många och det laggar alldeles för mycket.
		if 		(i == 0) { 	if(texture2D(shadowMap01, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 1) { 	if(texture2D(shadowMap02, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 2) { 	if(texture2D(shadowMap03, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 3) { 	if(texture2D(shadowMap04, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 4) { 	if(texture2D(shadowMap05, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 5) { 	if(texture2D(shadowMap06, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 6) { 	if(texture2D(shadowMap07, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 7) { 	if(texture2D(shadowMap08, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 8) { 	if(texture2D(shadowMap09, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 9) { 	if(texture2D(shadowMap10, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 10){ 	if(texture2D(shadowMap11, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 11){ 	if(texture2D(shadowMap12, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 12){ 	if(texture2D(shadowMap13, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 13){ 	if(texture2D(shadowMap14, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}
		else if (i == 14){ 	if(texture2D(shadowMap15, ((shadowCoord[i].xy) / shadowCoord[i].w) + vec2(0, 0)).r >= shadowCoord[i].z / shadowCoord[i].w) visibility += 1;}

		finalFragColor += visibility * (
			vec4(materialDiffuseColor, 1) * vec4(lightColor[i], 1) * directionalIntensity *
			lightIntensity[i] * cosTheta * (invDistSquare) + //Diffuse

			vec4(materialSpecularColor, 1) * vec4(lightColor[i], 1) * directionalIntensity *
			lightIntensity[i] * pow(cosAlpha, 5) * (invDistSquare)); //Specular
	}

	gl_FragColor = finalFragColor;

}
