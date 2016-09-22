#include "Polygon.h"


Polygon::Polygon(AssetsReader &reader, const std::vector<float> &ver,
                 const std::vector<float> &norm, const std::vector<float> & textCoords, int toDraw) : toDraw(toDraw) {

    setNormals(norm);
    setVerticies(ver);
    setTextureCoordinates(textCoords);

    Shader vertexShader(GL_VERTEX_SHADER, reader.readString("polygon_vertex.glsl").c_str());
    Shader fragmentShader(GL_FRAGMENT_SHADER, reader.readString("polygon_fragment.glsl").c_str());

    program = new Program();
    program->attachShader(vertexShader);
    program->attachShader(fragmentShader);
    program->link();
}

Polygon::~Polygon() {

}


void Polygon::draw() {
    program->use();

    auto position = program->assignAttributLocationShaderParam("vert", 3, verticies);
    auto norm = program->assignAttributLocationShaderParam("vertNormal", 3, normals);

    auto model = transform.modelMatrix();

    auto modelView = view * model;
    auto modelViewProjection = projection * modelView;

    program->assignUniform("modelView", modelView);
    program->assignUniform("modelViewProjection", modelViewProjection);

    glm::tmat3x3<float> model3x3(modelView);

    program->assignUniform("normalMatrix", glm::transpose(glm::inverse(model3x3)));
    program->assignUniform("lighPos", glm::vec3(
            view * glm::vec4(light.getX(), light.getY(), light.getZ(), 1.0)));
    program->assignUniform("ambient", light.getAmbientComponent());
    program->assignUniform("specularExp", light.getSpecularExp());

    auto txt = program->assignAttributLocationShaderParam("textCoord", 2, uvs);

    for (int i = 0; i < textures.size(); i++) {

        glActiveTexture(GL_TEXTURE0);
        // Bind the texture to this unit.
        glBindTexture(GL_TEXTURE_2D, textures[i]->getGlTexture());
        // Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.

        glUniform1i(program->getUniformShaderParam("texture"), 0);

        glDrawArrays(GL_TRIANGLES, (toDraw / textures.size()) * i, toDraw / textures.size());

    }

    glDisableVertexAttribArray(position);
    glDisableVertexAttribArray(txt);
    glDisableVertexAttribArray(norm);
}

