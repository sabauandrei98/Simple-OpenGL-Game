//
//  Animator.hpp
//  Game
//
//  Created by Andrei Sabu - (p) on 3/26/19.
//

#ifndef Animator_hpp
#define Animator_hpp

#include <stdio.h>
#include <vector>
#include <IvVector2.h>
#include <IvTexture.h>
#include <IvImage.h>
#include <IvRenderer.h>
#include <IvResourceManager.h>
#include <utility>

struct pixelInfo{
    IvTexture* texture;
    IvVector2 uv;
    IvVector4 color;
    IvVector3 lightPos = {0, 0, 0};
    IvVector4 lightCol = {1, 0.1, 0.1, 1};
};

class Animator
{
public:
    Animator(const std::string& tag, const std::string& state);
    virtual ~Animator(){};
    
    pixelInfo getNextAnimation(const std::string& tag, const std::string& state);

private:
    
    int currentIndex = 0;
    float zombieOffsetFrame = 0;
    float frameOffset = 0;
    std::string state = "";
    bool addValue = true;
    std::vector<IvTexture*> textures;
    IvVector2 uv;
    
    float lightPos = -5.0f;
    bool addValueLight = true;
    
    void initializeBackground();
    void initializeRain();
    void initializePlayer();
    void initializeEnemy();
    void initializeShadow();
    void initializeTree();
    void initializeDaynight();
    
    void animateLight();
    
    void addTexture(const std::string& spriteName);
    
    pixelInfo getNextBackgroundAnimation();
    pixelInfo getNextRainAnimation();
    pixelInfo getNextPlayerAnimation();
    pixelInfo getNextEnemyAnimation();
    pixelInfo getNextShadowAnimation();
    pixelInfo getNextTreeAnimation();
    pixelInfo getNextDaynightAnimation();
};

#endif /* Animator_hpp */
