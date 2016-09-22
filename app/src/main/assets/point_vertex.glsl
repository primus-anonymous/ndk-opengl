uniform mat4 modelViewProjection;
attribute vec3 vert;

void main() {
 	gl_PointSize = 20.0;
    gl_Position = modelViewProjection * vec4(vert, 1.0);
}
