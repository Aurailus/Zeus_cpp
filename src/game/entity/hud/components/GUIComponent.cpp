#include <utility>

//
// Created by aurailus on 27/07/19.
//

#include "GUIComponent.h"

GUIComponent::GUIComponent(const std::string& key) :
    key(key) {}

void GUIComponent::setScale(glm::vec2 scale) {
    this->scale = scale;
    entity.setScale({scale.x, scale.y, 1});
}

glm::vec2 GUIComponent::getScale() {
    return scale;
}

void GUIComponent::setPadding(glm::vec4 padding) {
    this->padding = padding;
}

glm::vec4 GUIComponent::getPadding() {
    return padding;
}

void GUIComponent::setPos(glm::vec2 pos) {
    this->pos = pos;
    if (parent != nullptr) {
        glm::vec3 parentPos = parent->entity.getPos();
        pos += glm::vec2{parentPos.x, parentPos.y};
        pos += glm::vec2{parent->getPadding().w, parent->getPadding().x};
    }
    entity.setPos({pos.x, pos.y, 0});
    for (const auto& child : children) {
        child->updatePos();
    }
}

glm::vec2 GUIComponent::getPos() {
    return pos;
}

void GUIComponent::add(std::shared_ptr<GUIComponent> component) {
    component->parent = this;
    component->updatePos();
    children.push_back(std::move(component));
}

void GUIComponent::remove(std::string key) {
    for (auto it = children.cbegin(); it != children.cend(); it++) {
        if (it->get()->key == key) {
            children.erase(it);
            return;
        }
    }
}

void GUIComponent::draw(Renderer& renderer) {
    entity.draw(renderer);
    for (const auto& child : children) {
        child->draw(renderer);
    }
}

void GUIComponent::setVisible(bool visible) {
    Drawable::setVisible(visible);
    entity.setVisible(visible);
    for (const auto& child : children) {
        child->setVisible(visible);
    }
}

void GUIComponent::updatePos() {
    glm::vec2 realPos(pos);
    if (parent != nullptr) {
        glm::vec3 parentPos = parent->entity.getPos();
        realPos += glm::vec2{parentPos.x, parentPos.y};
        realPos += glm::vec2{parent->getPadding().w, parent->getPadding().x};
    }
    entity.setPos({realPos.x, realPos.y, 0});
    for (const auto& child : children) {
        child->updatePos();
    }
}