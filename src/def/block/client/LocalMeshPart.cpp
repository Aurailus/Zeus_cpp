//
// Created by aurailus on 02/12/18.
//

#include "LocalMeshPart.h"

LocalMeshPart::LocalMeshPart(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<AtlasRef> texture) :

    vertices(std::move(vertices)),
    indices(std::move(indices)),
    texture(texture) {

    //These vertex structs do (should) not have normals, so we will generate them here from the triangle information
    //To do this, we have to assume that each group of 3 indices is a triangle (which it would be hard for it to not be)
    //and that no vertexes are shared on corners or places where vectors should be interpolated.

    //Iterate through the indices to find all used vertices to add normals and adjust texture coordinates.
    for (int i = 0; i < this->indices.size()/3; i++) {
        //Get the three vertices
        MeshVertex& p1 = this->vertices[this->indices[i*3]];
        MeshVertex& p2 = this->vertices[this->indices[i*3 + 1]];
        MeshVertex& p3 = this->vertices[this->indices[i*3 + 2]];

        //Get the normal of the formed triangle
        glm::vec3 normal = glm::triangleNormal(p1.pos, p2.pos, p3.pos);

        //Set the normal on the vertices
        p1.nml = normal;
        p2.nml = normal;
        p3.nml = normal;
    }

    auto uv = texture->uv;

    //Iterate through the vertices to adjust the texture coordinates to fit the textureAtlas.
    for (MeshVertex &vertex : this->vertices) {
        //Store the old positions in texUVs
        vertex.texUVs.x = vertex.tex.x;
        vertex.texUVs.y = vertex.tex.y;
        //Generate solid coordinates for the atlas positions
        vertex.tex.x = uv.x + ((uv.z - uv.x) * vertex.tex.x);
        vertex.tex.y = uv.y + ((uv.w - uv.y) * vertex.tex.y);
    }
}
