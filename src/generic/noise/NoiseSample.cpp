//
// Created by aurailus on 15/02/19.
//

#include <cmath>
#include "NoiseSample.h"
#include "../helpers/Interpolation.h"

NoiseSample::NoiseSample(int hPrecision, int vPrecision) {
    this->hPrecision = hPrecision;
    this->vPrecision = vPrecision;

    data = std::vector<std::vector<std::vector<float>>>();
    data.reserve((unsigned int)hPrecision + 1);

    for (int i = 0; i <= hPrecision; i++) {
        std::vector<std::vector<float>> subdata;
        subdata.reserve((unsigned int)vPrecision + 1);

        for (int j = 0; j <= vPrecision; j++) {
            subdata.emplace_back((unsigned int)hPrecision + 1);
        }

        data.push_back(subdata);
    }
}

void NoiseSample::set(glm::vec3 pos, float value) {
    if (pos.x < 0 || pos.y < 0 || pos.z < 0 || pos.x > hPrecision || pos.y > vPrecision || pos.z > hPrecision) {
        std::cerr << "Invalid index [1]" << std::endl;
        return;
    }

    data[(int)pos.x][(int)pos.y][(int)pos.z] = value;
}

float NoiseSample::get(glm::vec3& pos) {
    int xInt = (int)pos.x;
    int yInt = (int)pos.y;
    int zInt = (int)pos.z;

    int offsetH = (int)(16.0f / hPrecision);
    int offsetV = (int)(16.0f / vPrecision);

    auto xBase = xInt / offsetH;
    auto yBase = yInt / offsetV;
    auto zBase = zInt / offsetH;

    float xFac = (xInt % offsetH) / (16.0f / hPrecision);
    float yFac = (yInt % offsetV) / (16.0f / vPrecision);
    float zFac = (zInt % offsetH) / (16.0f / hPrecision);

    auto p000 = data[xBase][yBase][zBase];
    auto p100 = data[xBase + 1][yBase][zBase];
    auto p001 = data[xBase][yBase][zBase + 1];
    auto p101 = data[xBase + 1][yBase][zBase + 1];

    if (vPrecision > 1) {
        auto p010 = data[xBase][yBase + 1][zBase];
        auto p110 = data[xBase + 1][yBase + 1][zBase];
        auto p011 = data[xBase][yBase + 1][zBase + 1];
        auto p111 = data[xBase + 1][yBase + 1][zBase + 1];

        return Interpolation::trilerp(
                p000, p100, p001, p101,
                p010, p110, p011, p111,
                xFac, zFac, yFac
        );
    }
    else {
        return Interpolation::bilerp(
                p000, p100, p001, p101, xFac, zFac
        );
    }
}