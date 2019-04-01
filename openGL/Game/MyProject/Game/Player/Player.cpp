//===============================================================================
// @ Player.cpp
// ------------------------------------------------------------------------------
// Player object
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


#include "Player.hpp"


Player::Player(const std::string& tag, float radius) : Entity(tag, radius){}
Player::~Player(){}


void Player::getInput(float dt)
{
    IvMatrix44 positionTranslation;
    float x = 0.0f, y = 0.0f, z = 0.0f;
    
    
    //TRANSLATION
    if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
        x -= 3.0f*dt;
       
    if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
        x += 3.0f*dt;
    
    if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
        z -= 3.0f*dt;
    
    if (IvGame::mGame->mEventHandler->IsKeyDown('w'))
        z += 3.0f*dt;
    
    positionTranslation.Translation( IvVector3(x, y, z) );
    IvMatrix44 identity; identity.Identity();
    transform =   positionTranslation * transform * identity; //scaleTranslation * rotationTranslation ;
}


void 
Player::Update( float dt )
{
    getInput(dt);
}

void
Player::Render()                                    
{
    pixelInfo p = this->animator.getNextAnimation(this->ENTITY_TAG, this->ENTITY_STATE);
    shapeRenderer.Draw(transform, p);
}
