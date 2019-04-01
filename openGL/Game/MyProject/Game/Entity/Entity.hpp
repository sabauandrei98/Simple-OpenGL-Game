#ifndef __Entity__
#define __Entity__

#include <IvMatrix44.h>
#include <IvRenderer.h>
#include <IvEventHandler.h>
#include <IvMath.h>
#include <IvVector3.h>
#include <IvRendererHelp.h>
#include <IvGame.h>
#include "../Shape/Shape.hpp"
#include "../Animator/Animator.hpp"

class Entity
{
public:
    Entity(const std::string& tag, float radius);
    virtual ~Entity();

    void setPosition(IvVector3 pos);
    void setScale(IvVector3 scale);
    void setRotation(float rot);
    
    Animator animator;
    
protected:
    
    std::string ENTITY_TAG;
    std::string ENTITY_SHAPE;
    std::string ENTITY_STATE = "";
    float ENTITY_RADIUS;
    
    IvMatrix44 transform;
    Shape shapeRenderer;

};

#endif
