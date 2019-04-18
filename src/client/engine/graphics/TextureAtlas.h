//
// Created by aurailus on 16/04/19.
//

#ifndef ZEUS_DYNAMICATLAS_H
#define ZEUS_DYNAMICATLAS_H

#include <vector>
#include <vec2.hpp>
#include <glew.h>
#include <tgmath.h>
#include <memory>
#include <map>
#include "Texture.h"
#include "AtlasRef.h"

class DynamicAtlas {
public:
    DynamicAtlas() = default;
    explicit DynamicAtlas(unsigned int width, unsigned int height = 0);

    void loadFromDirectory(std::string dirStr);

    Texture& getTexture();

    std::shared_ptr<AtlasRef> addTexture(unsigned char* data, std::string name, int pixelWidth, int pixelHeight);
    glm::vec4 getTextureUVs(std::string& name);

    ~DynamicAtlas();
private:
    void createMissingTexture();
    glm::vec2 findSpace(int w, int h);

    unsigned int width = 0, height = 0;
    Texture t;

    std::vector<bool> empty;
    std::map<std::string, std::shared_ptr<AtlasRef>> textures;
};


#endif //ZEUS_DYNAMICATLAS_H
