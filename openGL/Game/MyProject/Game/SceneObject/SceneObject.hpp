

//===============================================================================
// @ Player.h
// ------------------------------------------------------------------------------
// Player object
//
// Copyright (C) 2008-2015 by James M. Van Verth and Lars M. Bishop.
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
//===============================================================================

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
