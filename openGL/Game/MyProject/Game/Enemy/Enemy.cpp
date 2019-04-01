//===============================================================================
// @ Enemy.cpp
// ------------------------------------------------------------------------------
// Enemy object
//
// Copyright (C) 2008-2015 by James M. Van Verth and Lars M. Bishop.
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// This example demonstrates the three basic transforms and how they interact
// with each other.   At each frame we append transforms to the current matrix,
// which is stored for the next frame.  The key commands are:
//
// I, K - translate in x
// J, L - translate in y
// U, O - rotate around z axis
// P, : - uniformly scale
//
//===============================================================================

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------


#include "Enemy.hpp"


Enemy::Enemy(const std::string& tag, float radius) : Entity(tag, radius)
{
    patrolPoints.push_back({1,0,5});
    patrolPoints.push_back({5,0,2});
    patrolPoints.push_back({3,0,4});
    patrolPoints.push_back({-3,0,4});
    patrolPoints.push_back({-5,0,-4});
    patrolPoints.push_back({4,0,-4});
    patrolPoints.push_back({2,0,-3});
    patrolPoints.push_back({-4,0,-3});
    patrolPoints.push_back({-3,0,-5});
    patrolPoints.push_back({-3,0,3});
    patrolPoints.push_back({-2,0,2});
    patrolPoints.push_back({4,0,-3});
    patrolPoints.push_back({3,0,-4});
    patrolPoints.push_back({5,0,-3});
    patrolPoints.push_back({5,0,-4});
    patrolPoints.push_back({3,0,4});
    patrolPoints.push_back({2,0,5});
    patrolPoints.push_back({5,0,5});
    patrolPoints.push_back({4,0,2});
    
    toPosition = getPatrolPoint();
}   // End of Enemy::Enemy()


Enemy::~Enemy()
{
}   // End of Enemy::~Enemy()


float Enemy::getDistance(IvVector3 a, IvVector3 b)
{
    float dist = (a.x - b.x)*(a.x - b.x) + (a.z - b.z) * (a.z - b.z);
    dist = sqrt (dist);
   
    return dist;
}

IvVector3 Enemy::getPatrolPoint()
{
    int index = 0;
    float dist = 100;
    
    for(int i = 0; i < patrolPoints.size(); i++)
    {
        float ds = getDistance({transform[12], 0, transform[13]}, patrolPoints[i]);
        if (ds < dist)
        {
            dist = ds;
            index = i;
        }
    }
    patrolIndex = index;
    return patrolPoints[index];
}


void Enemy::getInput(float dt)
{
    IvMatrix44 positionTranslation;
    //IvMatrix44 rotationTranslation;
    //IvMatrix44 scaleTranslation;
    
    //scaleTranslation.Identity();
    //rotationTranslation.Identity();
    //float s = 1.0f;
    //float r = 0.0f;
    
    float x = 0, y = 0, z = 0;
    
    
    
    if(transform[12] > toPosition.x)
        x -= 0.4 * dt;
    
    if(transform[12] < toPosition.x)
        x += 0.4 * dt;
    
    if(transform[14] > toPosition.z)
        z -= 0.4 * dt;
    
    if(transform[14] < toPosition.z)
        z += 0.4 * dt;
    
    
    if (abs(transform[12] - toPosition.x) < 0.4f  && abs(transform[14] - toPosition.z) < 0.4f)
    {
        patrolIndex = rand() % patrolPoints.size();
        
        toPosition = patrolPoints[patrolIndex];
    }
    
    //scaleTranslation.Scaling( IvVector3(s,s,s) );
    //rotationTranslation.RotationX( r );
    positionTranslation.Translation( IvVector3(x, y, z) );
    
    IvMatrix44 identity; identity.Identity();
    transform =   positionTranslation * transform * identity; //scaleTranslation * rotationTranslation ;
}


void 
Enemy::Update( float dt )
{
    getInput(dt);
}

void
Enemy::Render()                                    
{
    pixelInfo p = this->animator.getNextAnimation(this->ENTITY_TAG, this->ENTITY_STATE);
    shapeRenderer.Draw(transform, p);
}
