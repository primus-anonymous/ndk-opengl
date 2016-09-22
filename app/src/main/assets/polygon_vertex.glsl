uniform mat4 modelView;
uniform mat4 modelViewProjection;
uniform mat3 normalMatrix;

attribute vec3 vert;
attribute vec3 vertNormal;
attribute vec2 textCoord;

varying vec2 fragTextCoord;
varying vec3 fragVert;
varying vec3 fragNormal;

void main() {

	fragVert = vec3(modelView * vec4(vert, 1.0));
	fragTextCoord = textCoord;
    fragNormal =  normalMatrix * vertNormal;
    gl_Position = modelViewProjection * vec4(vert, 1.0);
}
