//
//  Animator.cpp
//  Game
//
//  Created by Andrei Sabu - (p) on 3/26/19.
//

#include "Animator.hpp"

Animator::Animator(const std::string& tag, const std::string& state)
{
    if (tag == "background")
    {
        initializeBackground();
    }
    
    if (tag == "player")
    {
        initializePlayer();
    }
    
    if (tag == "rain")
    {
        initializeRain();
    }
    
    if (tag == "enemy")
    {
        initializeEnemy();
    }
    if (tag == "shadow")
    {
        initializeShadow();
    }
    if (tag == "tree")
    {
        initializeTree();
    }
    if (tag == "daynight")
    {
        initializeDaynight();
    }
    
    if (tag == "fire")
    {
        initializeFire();
    }
}


void Animator::initializeBackground()
{
    addTexture("background.tga");
}

void Animator::initializeFire()
{
    for(int i = 1; i <= 20; i++)
    {
        addTexture("fire" + std::to_string(i) + ".tga");
    }

}

void Animator::initializeShadow()
{
    addTexture("shadow.tga");
    
}

void Animator::initializeRain()
{
    addTexture("rain.tga");
    
}

void Animator::initializePlayer()
{
    addTexture("player.tga");
}

void Animator::initializeEnemy()
{
    addTexture("zombie1.tga");
    addTexture("zombie2.tga");
    zombieOffsetFrame = (float)(rand() % 100 + 1) / 1000;
}

void Animator::initializeTree()
{
    addTexture("tree.tga");
}

void Animator::initializeDaynight()
{
    addTexture("daynight.tga");
    frameOffset = 1;
}


pixelInfo Animator::getNextBackgroundAnimation()
{
    pixelInfo p;
    p.texture = textures[0];
    p.uv = {0, 0};
    p.color = {1.0,1.0,1.0,1.0};
    return p;
}



pixelInfo Animator::getNextDaynightAnimation()
{
    if(frameOffset >= 1)
        addValue = false;
    
    if(frameOffset <= 0.25)
        addValue = true;
    
    if(addValue)
    {
        frameOffset += 0.00075f;
    }
    else
        frameOffset -= 0.00075f;
    
    pixelInfo p;
    p.texture = textures[0];
    p.uv = {1, 1};
    p.color = {0,0.0,0.0,frameOffset};
    
    return p;
}

pixelInfo Animator::getNextPlayerAnimation()
{
    pixelInfo p;
    p.texture = textures[0];
    p.uv = {1, 1};
    p.color = {1.0,1.0,1.0,1.0};
    return p;
}

pixelInfo Animator::getNextEnemyAnimation()
{
    pixelInfo p;
    frameOffset += zombieOffsetFrame;
    if(frameOffset < 1)
        p.texture = textures[0];
    
    if(frameOffset > 1)
        p.texture = textures[1];
    
    if (frameOffset > 2)
        frameOffset = 0;
    
 
    p.uv = {1, 1};
    p.color = {1.0,1.0,1.0,1.0};
    return p;
}

pixelInfo Animator::getNextShadowAnimation()
{
    if(frameOffset > 1)
        addValue = false;
    
    if(frameOffset < 0)
        addValue = true;
    
    if(addValue)
    {
        frameOffset += 0.001f;
    }
    else
        frameOffset -= 0.001;
    
    pixelInfo p;
    p.texture = textures[0];
    p.uv = {1, 1};
    p.color = {0.1,0.1,0.1,0.8};
    return p;
}

pixelInfo Animator::getNextTreeAnimation()
{
    pixelInfo p;
    p.texture = textures[0];
    p.uv = {1, 1};
    p.color = {1.0,1.0,1.0,1.0};

    return p;
}


pixelInfo Animator::getNextRainAnimation()
{
    frameOffset += 0.01f;
    if (frameOffset > 1)
        frameOffset -= 1;
    
    pixelInfo p;
    p.texture = textures[0];
    p.uv = {1, 1 + frameOffset};
    p.color = {1.0,1.0,1.0,1.0};
    return p;
    
}

pixelInfo Animator::getNextFireAnimation()
{
    fireIndex += 1;
    
    pixelInfo p;
    fireIndex %= 270;
    int index = fireIndex / 15;
    p.texture = textures[index];
    
    p.uv = {1, 1};
    p.color = {1.0,1.0,1.0,1.0};
    return p;
}

pixelInfo Animator::getNextAnimation(const std::string& tag, const std::string& state)
{
    if (tag == "rain")
        return getNextRainAnimation();
    
    if (tag == "player")
        return getNextPlayerAnimation();
    
    if (tag == "enemy")
        return getNextEnemyAnimation();
    
    if (tag == "shadow")
        return getNextShadowAnimation();
    
    if (tag == "tree")
        return getNextTreeAnimation();
    
    if (tag == "daynight")
        return getNextDaynightAnimation();
    
    if(tag == "fire")
        return getNextFireAnimation();
    
    return getNextBackgroundAnimation();
}

void Animator::addTexture(const std::string& spriteName)
{
    
    IvImage* image = IvImage::CreateFromFile(spriteName.c_str());
    
    if (image)
    {
        textures.push_back(IvRenderer::mRenderer->GetResourceManager()->CreateTexture((image->GetBytesPerPixel() == 4) ? kRGBA32TexFmt : kRGB24TexFmt,image->GetWidth(), image->GetHeight(), image->GetPixels(), kImmutableUsage));
        delete image;
        image = 0;
    }
}
