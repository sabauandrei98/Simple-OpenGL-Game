#include "Entity.hpp"

Entity::Entity(const std::string& tag, float radius) : animator(tag, "")
{
    ENTITY_SHAPE = "square";
    ENTITY_RADIUS = radius;
    ENTITY_TAG = tag;

    shapeRenderer = Shape(ENTITY_SHAPE, ENTITY_RADIUS, ENTITY_TAG);
    IvRenderer::mRenderer->SetWorldMatrix(transform);
}

void Entity::setRotation(float angle)
{
    float sintheta, costheta;
    IvSinCos(angle, sintheta, costheta);
    
    transform[0] = costheta;
    transform[2] = -sintheta;
    transform[8] = sintheta;
    transform[10] = costheta;
}

void Entity::setPosition(IvVector3 pos)
{
    transform[12] = pos.x;
    transform[13] = pos.y;
    transform[14] = pos.z;
}

void Entity::setScale(IvVector3 scale)
{
    IvMatrix44 scaleTranslation;
    scaleTranslation.Identity();
    scaleTranslation.Scaling( scale );
    transform = transform * scaleTranslation;
}


Entity::~Entity(){}
