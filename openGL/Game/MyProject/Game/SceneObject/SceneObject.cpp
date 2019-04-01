#include "SceneObject.hpp"

SceneObject::SceneObject(const std::string& tag, float radius) : Entity(tag, radius){}
SceneObject::~SceneObject(){}

void
SceneObject::Render()
{
    pixelInfo p = this->animator.getNextAnimation(this->ENTITY_TAG, this->ENTITY_STATE);
    shapeRenderer.Draw(transform, p);
}
