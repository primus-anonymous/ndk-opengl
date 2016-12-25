uniform vec3 lighPos;
uniform float ambient;
uniform float specularExp;
uniform sampler2D texture;

uniform float xPixelOffset;
uniform float yPixelOffset;
uniform sampler2D shadowTexture;

varying vec4 fragShadowVert;
varying vec2 fragTextCoord;
varying vec3 fragVert;
varying vec3 fragNormal;

//Calculate variable bias - from http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping
float calcBias()
{
	float bias;

	vec3 n = normalize( fragNormal );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( lighPos );

	// Cosine of the angle between the normal and the light direction,
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendiular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0.0, 1.0 );

 	bias = 0.0001*tan(acos(cosTheta));
	bias = clamp(bias, 0.0, 0.01);

 	return bias;
}

float lookup( vec2 offSet)
{
	vec4 shadowMapPosition = fragShadowVert / fragShadowVert.w;

	float distanceFromLight = texture2D(shadowTexture, (shadowMapPosition +
	                               vec4(offSet.x * xPixelOffset, offSet.y * yPixelOffset, 0.05, 0.0)).st ).z;

	//add bias to reduce shadow acne (error margin)
	float bias = calcBias();

	return float(distanceFromLight > shadowMapPosition.z - bias);
}

float shadowPCF()
{
	float shadow = 1.0;

	for (float y = -1.5; y <= 1.5; y = y + 1.0) {
		for (float x = -1.5; x <= 1.5; x = x + 1.0) {
			shadow += lookup(vec2(x,y));
		}
	}

	shadow /= 16.0;
	shadow += 0.2;

	return shadow;
}

void main() {

    vec3 norm = normalize(fragNormal);
    vec3 light = normalize(lighPos - fragVert);

    float diffuse = clamp(dot(norm, light), 0.0, 1.0);

    vec3 E = normalize(-fragVert); // we are in Eye Coordinates, so EyePos is (0,0,0)
    vec3 R = normalize(-reflect(light, norm));

    float specular =  pow(max(dot(R,E), 0.0), 1.5);
    specular = clamp(specular, 0.0, 1.0);

    float brightness = diffuse + ambient + specular;

   	// Shadow
    float shadow = 0.0;

    	//if the fragment is not behind light view frustum
    if (fragShadowVert.w > 0.0) {

    shadow = shadowPCF();

    		//scale 0.0-1.0 to 0.2-1.0
    		//otherways everything in shadow would be black
    shadow = (shadow * 0.8) + 0.2;
    }


    gl_FragColor =  brightness * (texture2D(texture, fragTextCoord)) * shadow;
}