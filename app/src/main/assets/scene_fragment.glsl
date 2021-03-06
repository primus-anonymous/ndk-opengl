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


float lookup( vec2 offSet)
{
	vec4 shadowMapPosition = fragShadowVert / fragShadowVert.w;

	float distanceFromLight = texture2D(shadowTexture, (shadowMapPosition +
	                               vec4(offSet.x * xPixelOffset, offSet.y * yPixelOffset, 0.05, 0.0)).st ).z;

	float bias = 0.004;

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
    shadow = (shadow * 0.8) + 0.2;
    }

    gl_FragColor =  brightness * (texture2D(texture, fragTextCoord)) * shadow;
}