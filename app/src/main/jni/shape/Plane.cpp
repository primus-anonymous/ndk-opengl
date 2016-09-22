#include "Plane.h"

Plane::Plane(AssetsReader &reader, int width, int height) {

    generateVert(width, height);
    Shader vertexShader(GL_VERTEX_SHADER, reader.readString("polygon_vertex.glsl").c_str());
    Shader fragmentShader(GL_FRAGMENT_SHADER, reader.readString("polygon_fragment.glsl").c_str());

    program = new Program();
    program->attachShader(vertexShader);
    program->attachShader(fragmentShader);
    program->link();
}

void Plane::generateVert(int width, int height) {

    int halfWidth = width / 2;
    int halfHeight = height / 2;

    for (int j = -halfHeight; j < halfHeight; j++) {
        for (int i = -halfWidth; i < halfWidth; i++) {

            verticies.push_back(i);
            verticies.push_back(0);
            verticies.push_back(j);

            verticies.push_back(i + 1);
            verticies.push_back(0);
            verticies.push_back(j);

            verticies.push_back(i);
            verticies.push_back(0);
            verticies.push_back(j + 1);

            verticies.push_back(i + 1);
            verticies.push_back(0);
            verticies.push_back(j + 1);


            normals.push_back(0);
            normals.push_back(1);
            normals.push_back(0);

            normals.push_back(0);
            normals.push_back(1);
            normals.push_back(0);

            normals.push_back(0);
            normals.push_back(1);
            normals.push_back(0);

            normals.push_back(0);
            normals.push_back(1);
            normals.push_back(0);

            uvs.push_back(0.0f);
            uvs.push_back(1.0f);

            uvs.push_back(1.0f);
            uvs.push_back(1.0f);

            uvs.push_back(0.0f);
            uvs.push_back(0.0f);

            uvs.push_back(1.0f);
            uvs.push_back(0.0f);

        }
    }
}

void Plane::draw() {

    program->use();

    auto position = program->assignAttributLocationShaderParam("vert", 3, verticies);
    auto model = transform.modelMatrix();
    auto modelView = view * model;
    auto modelViewProjection = projection * modelView;
    auto norm = program->assignAttributLocationShaderParam("vertNormal", 3, normals);

    program->assignUniform("modelView", modelView);
    program->assignUniform("modelViewProjection", modelViewProjection);

    glm::tmat3x3<float> model3x3(modelView);

    program->assignUniform("normalMatrix", glm::transpose(glm::inverse(model3x3)));
    program->assignUniform("lighPos", glm::vec3(
            view * glm::vec4(light.getX(), light.getY(), light.getZ(), 1.0)));
    program->assignUniform("ambient", light.getAmbientComponent());
    program->assignUniform("specularExp", light.getSpecularExp());

    auto txt = program->assignAttributLocationShaderParam("textCoord", 2, uvs);

    glActiveTexture(GL_TEXTURE0);
    // Bind the texture to this unit.
    glBindTexture(GL_TEXTURE_2D, textures[0]->getGlTexture());
    // Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.

    glUniform1i(program->getUniformShaderParam("texture"), 0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, verticies.size() / 3);

    glDisableVertexAttribArray(position);
    glDisableVertexAttribArray(txt);
    glDisableVertexAttribArray(norm);

}
