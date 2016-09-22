#ifndef NDK_BASESHAPE_H
#define NDK_BASESHAPE_H

#include <transform/Transform.h>
#include <shader/Program.h>
#include <texture/Texture.h>
#include <string>
#include <texture/AssetsReader.h>
#include <light/Light.h>
#include "IShape.h"


class BaseShape : public IShape {

public:
    BaseShape();

    void setView(const glm::tmat4x4<float> &view) override;

    void setProjection(const glm::tmat4x4<float> &projection) override;

    Transform &getTransformation() override;

    void addTexture(Texture *textures);

    void setLight(const Light &l);

    virtual ~BaseShape();

protected:

    glm::tmat4x4<float> view;
    glm::tmat4x4<float> projection;

    Transform transform;

    std::vector<float> verticies;
    std::vector<float> normals;
    std::vector<Texture *> textures;
    std::vector<float> uvs;
    Program *program;
    Light light;

    void setVerticies(const std::vector<float> &verticies);

    void setNormals(const std::vector<float> &normals);

    void setTextureCoordinates(const std::vector<float> &textureCoordinates);
};

#endif //NDK_BASESHAPE_H
