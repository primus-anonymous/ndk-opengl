precision highp float;

uniform mat4 modelViewProjection;

attribute vec4 vert;


void main() {

	gl_Position = modelViewProjection * vert;
}
