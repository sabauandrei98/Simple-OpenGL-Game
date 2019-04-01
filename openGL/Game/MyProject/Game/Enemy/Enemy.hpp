#ifndef __EnemyDefs__
#define __EnemyDefs__

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

class Enemy : public Entity
{
public:
    Enemy(const std::string& tag, float radius);
    ~Enemy();

    
    void Update( float dt );
    void Render();

private:
    
    vector<IvVector3> patrolPoints;
    IvVector3 getPatrolPoint();
    float getDistance(IvVector3 a, IvVector3 b);
    IvVector3 toPosition;
    int patrolIndex = 0;

    void getInput(float dt);
};

#endif
