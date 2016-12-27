#ifndef NDK_BASESHAPE_H
#define NDK_BASESHAPE_H

#include <transform/Transform.h>
#include <texture/Texture.h>
#include <string>

class BaseShape {

public:
    BaseShape(std::string k);

    Transform &getTransformation();

    void addTexture(Texture *textures);

    void addTexture(std::vector<Texture*> textures);

    std::string getKey();

    virtual ~BaseShape();

    std::vector<float> &getVerticies();

    std::vector<float> &getNormals();

    std::vector<float> &getTextureCoordinates();

    std::vector<Texture *> &getTextures();

protected:

    Transform transform;

    std::vector<float> verticies;
    std::vector<float> normals;
    std::vector<Texture *> textures;
    std::vector<float> uvs;

    std::string key;

};

#endif //NDK_BASESHAPE_H
