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


Entity::~Entity()
{
    
}
