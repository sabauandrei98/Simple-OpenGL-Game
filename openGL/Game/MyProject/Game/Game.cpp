//===============================================================================
// @ Game.cpp
// ------------------------------------------------------------------------------
// Game core routines
//
// Copyright (C) 2008-2015 by James M. Van Verth and Lars M. Bishop.
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
//===============================================================================

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include "Game.hpp"



//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ IvGame::Create()
//-------------------------------------------------------------------------------
// Static constructor
//-------------------------------------------------------------------------------
bool
IvGame::Create()
{
    IvGame::mGame = new Game();
    return ( IvGame::mGame != 0 );

}   // End of IvGame::Create()


//-------------------------------------------------------------------------------
// @ Game::Game()
//-------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------
Game::Game() : IvGame()
{
    // init variables
    mPlayer = 0;            // main player object
    background = 0;
    

}   // End of Game::Game()


//-------------------------------------------------------------------------------
// @ Game::~Game()
//-------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------
Game::~Game()
{
    delete mPlayer; 
    mPlayer = 0;
    
    delete background;
    background = 0;
}   // End of Game::~Game()



//-------------------------------------------------------------------------------
// @ Game::PostRendererInitialize()
//-------------------------------------------------------------------------------
// Set up internal subsystems
//-------------------------------------------------------------------------------

void Game::InitializeScene()
{

    float orderInLayer = 1;
    daynight = new SceneObject("daynight", 3.0f);
    daynight->setPosition({0 , orderInLayer, 0});
    daynight->setRotation(1.57);
    daynight->setScale({1.52f, 0, 2.7});
    
    orderInLayer += 0.001;
    rainEffect = new RainEffect("tree", 1.5f);
    rainEffect->setPosition({0 , orderInLayer, 0.0});
    rainEffect->setRotation(1.57);
    rainEffect->setScale({3.2, 0, 5.4});
    
    orderInLayer += 0.001;
    rain = new SceneObject("rain", 3.0f);
    rain->setPosition({0 , orderInLayer, 0});
    rain->setRotation(1.57);
    rain->setScale({1.6f, 0, 2.8f});
    
    
    orderInLayer += 0.001;
    tree = new SceneObject("tree", 1.5f);
    tree->setPosition({-5.5 , orderInLayer, 2});
    tree->setRotation(4.71);
    
    orderInLayer += 0.001;
    tree1 = new SceneObject("tree", 1.5f);
    tree1->setPosition({4 , orderInLayer, -1});
    tree1->setRotation(4.71);
    
    
    
    orderInLayer += 0.001;
    mPlayer = new Player("player", 0.5f);
    mPlayer->setPosition({2 , orderInLayer, 2});
    mPlayer->setRotation(1.57);
    
    
    
    orderInLayer += 0.001;
    enemy = new Enemy("enemy", 0.3f);
    enemy->setPosition({4 , orderInLayer, 0});
    enemy->setRotation(1.57);
    
    orderInLayer += 0.001;
    enemy1 = new Enemy("enemy", 0.3f);
    enemy1->setPosition({-3 , orderInLayer, 2});
    enemy1->setRotation(1.57);
    
    orderInLayer += 0.001;
    enemy2 = new Enemy("enemy", 0.3f);
    enemy2->setPosition({4 , orderInLayer, 4});
    enemy2->setRotation(1.57);
    
    orderInLayer += 0.001;
    enemy3 = new Enemy("enemy", 0.3f);
    enemy3->setPosition({-5 , orderInLayer, -4});
    enemy3->setRotation(1.57);
    
    
    
    
    orderInLayer += 0.001;
    shadow = new SceneObject("shadow", 1.5f);
    shadow->setPosition({-6.9 , orderInLayer, 2.20});
    shadow->setRotation(4);
    shadow->setScale({1.5f, 0, 1});
    
    
    orderInLayer += 0.001;
    shadow1 = new SceneObject("shadow", 1.5f);
    shadow1->setPosition({5.9 , orderInLayer, -3.8});
    shadow1->setRotation(0.7);
    shadow1->setScale({1.5f, 0, 1});
    
    
    
    
     

    
    orderInLayer += 0.001;
    background = new SceneObject("background", 3.0f);
    background->setPosition({0 , orderInLayer, 0});
    background->setRotation(1.57);
    background->setScale({1.52f, 0, 2.7});
    
    //light = new Light();
}


bool
Game::PostRendererInitialize()
{
    // Set up base class
    if ( !IvGame::PostRendererInitialize() )
        return false;

    InitializeScene();

    if (!mPlayer)
        return false;


    if (!background)
        return false;

    // Set some lights
    ::IvSetDefaultLighting();
    IvRendererOGL::mRenderer->SetBlendFunc(kSrcAlphaBlendFunc, kOneMinusSrcAlphaBlendFunc, kAddBlendOp);

    return true;
}   // End of Game::PostRendererInitialize()


//-------------------------------------------------------------------------------
// @ Game::Update()
//-------------------------------------------------------------------------------
// Main update loop
//-------------------------------------------------------------------------------
void
Game::UpdateObjects( float dt )
{
    // update player
     mPlayer->Update( dt );
    enemy->Update(dt);
    enemy1->Update(dt);
    enemy2->Update(dt);
    enemy3->Update(dt);
}   // End of Game::Update()


//-------------------------------------------------------------------------------
// @ Game::Render()
//-------------------------------------------------------------------------------
// Render stuff
//-------------------------------------------------------------------------------
void 
Game::Render()                                  // Here's Where We Do All The Drawing
{   
    // set up viewer
    //x y z
    //y = -10
    IvSetDefaultViewer(0.0f , -10.0f, 0.0f);

    // draw coordinate axes
    //IvDrawAxes();


    background ->Render();

    shadow->Render();
    shadow1->Render();

    enemy3->Render();
    enemy2->Render();
    enemy1->Render();
    enemy->Render();

    mPlayer->Render();

    tree1->Render();
    tree->Render();
    rainEffect->Render();
    
    rain->Render();

    daynight->Render();
}

