//===============================================================================
// @ Game.h
// ------------------------------------------------------------------------------
// Game core
//
// Copyright (C) 2008-2015 by James M. Van Verth and Lars M. Bishop.
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
//===============================================================================

#ifndef __GameDefs__
#define __GameDefs__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include <IvGame.h>
#include <IvRendererHelp.h>
#include <IvRendererOGL.h>
#include "Player/Player.hpp"
#include "SceneObject/SceneObject.hpp"
#include "SceneEffects/RainEffect.hpp"
#include "Enemy/Enemy.hpp"


//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class Player;

class Game : public IvGame
{
public:
    Game();
    ~Game();
    bool PostRendererInitialize();

    Player*         mPlayer;
    SceneObject*          background;
    SceneObject*         rain;
    Enemy*        enemy;
    Enemy*        enemy1;
    Enemy*        enemy2;
    Enemy*        enemy3;
    SceneObject*        shadow;
    SceneObject*        daynight;
    SceneObject* tree;
    SceneObject* fire;
    RainEffect* rainEffect;
    
    SceneObject*        tree1;
    SceneObject*        shadow1;
    //Light* light;

protected:
    virtual void UpdateObjects( float dt );
    virtual void Render();
    
private:
    Game( const Game& other );
    Game& operator=( const Game& other );
    
    void InitializeScene();

};

#endif
