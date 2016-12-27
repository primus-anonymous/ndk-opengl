#include "VertexAttribute.h"

VertexAttribute::VertexAttribute(GLint attr) : attribute(attr) {

}

void VertexAttribute::enable() {
    glEnableVertexAttribArray(attribute);
}

void VertexAttribute::disable() {
    glDisableVertexAttribArray(attribute);
}





