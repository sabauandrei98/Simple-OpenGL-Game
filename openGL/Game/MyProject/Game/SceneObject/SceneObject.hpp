#ifndef __SceneObject__
#define __SceneObject__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include <IvMatrix44.h>
#include <IvRenderer.h>
#include <IvEventHandler.h>
#include <IvMath.h>
#include <IvVector3.h>
#include <IvRendererHelp.h>
#include <IvGame.h>
#include "../Entity/Entity.hpp"

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class SceneObject : public Entity
{
public:
    SceneObject(const std::string& tag, float radius);
    ~SceneObject();
    
    void Update( float dt );
    void Render();
    
private:
    
    void getInput(float dt);
};

#endif
