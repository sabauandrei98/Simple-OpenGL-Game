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


#include "SceneObject.hpp"


SceneObject::SceneObject(const std::string& tag, float radius) : Entity(tag, radius)
{
    
}


SceneObject::~SceneObject()
{
}

void
SceneObject::Render()
{
    pixelInfo p = this->animator.getNextAnimation(this->ENTITY_TAG, this->ENTITY_STATE);
    shapeRenderer.Draw(transform, p);
}
