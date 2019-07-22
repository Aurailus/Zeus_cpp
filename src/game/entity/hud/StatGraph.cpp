//
// Created by aurailus on 28/04/19.
//

#include "StatGraph.h"

StatGraph::StatGraph(std::string title, int graphLength, int graphScale, Texture *graphTex, Texture *textTex) :
    StatGraph(std::move(title), 244, 64, graphLength, graphScale, graphTex, textTex) {}

StatGraph::StatGraph(std::string title, int xSize, int ySize, int graphLength, int graphScale, Texture* graphTex, Texture* textTex) :
    title(std::move(title)),
    background({0.1, 0.1, 0.1, 0.2}, {0.1, 0.1, 0.1, 0.2}, {0.1, 0.1, 0.1, 0.7}, {0.1, 0.1, 0.1, 0.7}),
    graph(graphTex, graphLength, graphScale, true),
    text(textTex) {

    background.setScale({xSize, ySize, 1});
    graph.setScale({(xSize - GRAPH_PAD_X * 2) / graphLength, 28, 1});
    text.setScale(2);

    for (float &i : history) i = 0;

    setPos({0, 0});
}


void StatGraph::setPos(glm::vec2 pos) {
    text.setPos({pos.x + TEXT_PAD_X, pos.y + TEXT_PAD_Y, 0});
    graph.setPos({pos.x + GRAPH_PAD_X, pos.y + GRAPH_PAD_Y, 0});
    background.setPos({pos.x, pos.y, 0});
}

void StatGraph::update(float value) {
    graph.push_back(value);

    history[ind] = value;
    if (++ind >= 5) {
        ind = 0;

        float val = 0;
        for (float i : history) val += i / 5;

        std::string stringVal = (value == static_cast<int>(value))
                                ? std::to_string(static_cast<int>(value))
                                : Util::floatToString(value);

        text.set(title + ": " + stringVal);
    }
}

void StatGraph::draw(Renderer &renderer) {
    if (isVisible()) {
        background.draw(renderer);
        graph.draw(renderer);
        text.draw(renderer);
    }
}