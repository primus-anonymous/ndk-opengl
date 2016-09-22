varying vec2 fragTextCoord;
uniform sampler2D texture;

varying vec3 fragVert;
varying vec3 fragNormal;
uniform vec3 lighPos;
uniform float ambient;
uniform float specularExp;


void main() {

    vec3 norm = normalize(fragNormal);
    vec3 light = normalize(lighPos - fragVert);

    float diffuse = clamp(dot(norm, light), 0.0, 1.0);

    vec3 E = normalize(-fragVert); // we are in Eye Coordinates, so EyePos is (0,0,0)
    vec3 R = normalize(-reflect(light, norm));

    float specular =  pow(max(dot(R,E), 0.0), 1.5);
    specular = clamp(specular, 0.0, 1.0);

    float brightness = diffuse + ambient + specular;

    gl_FragColor =  brightness * (texture2D(texture, fragTextCoord));
}