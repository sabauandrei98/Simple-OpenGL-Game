//
//
//  Created by Andrei Sabu - (p) on 3/28/19.
//

#ifndef WorldObject_hpp
#define WorldObject_hpp

#include <stdio.h>
#include<iostream>
#include<vector>

#include <IvRenderer.h>
#include <IvResourceManager.h>
#include "IvRendererHelp.h"
#include <IvVector3.h>
#include <IvVector4.h>
#include <IvMatrix44.h>
#include <IvMatrix33.h>
#include <IvLineSegment3.h>
#include <IvMath.h>
#include <IvQuat.h>
#include <IvStackAllocator.h>
#include <IvVertexFormats.h>
#include <IvVertexBuffer.h>
#include <IvIndexBuffer.h>
#include <IvFileReader.h>
#include <IvShaderProgram.h>
#include <IvUniform.h>
#include <IvImage.h>
#include <IvTexture.h>
#include <IvRenderer.h>
#include <IvRendererOGL.h>
#include "../Animator/Animator.hpp"
#include <time.h>

class RainEffect
{
public:
    RainEffect(const std::string& tag, float radius);
    ~RainEffect();
    
    void Update( float dt );
    void Render();
    
    void Draw(IvMatrix44& positionTranslate, pixelInfo p);
    void setPosition(IvVector3 pos);
    void setScale(IvVector3 scale);
    void setRotation(float rot);
    
private:
    std::vector<IvTCPVertex> vertices;
    std::vector<unsigned int> indices;
    
    IvVertexBuffer* vertexBuffer = 0;
    IvIndexBuffer*  indexBuffer = 0;
    
    IvShaderProgram* mShader;
    
    IvUniform* uniColor;
    IvUniform* uniTransform;
    IvUniform* uniTime;
    float myTime = 0;
    
    IvTCPVertex* dataPtr;
    UInt32* indexPtr;
    
    void initializeShape(const string& shapeType, float shapeRadius);
    void intializeShader(const string& objectTag);
    void intializeShapeSquare(float distFromCenter);
    
    void Entity(const std::string& tag, float radius);
    void Shape(const string& shapeType, float shapeRadius, const string& objectTag);
    std::string ENTITY_TAG;
    std::string ENTITY_SHAPE;
    std::string ENTITY_STATE = "";
    float ENTITY_RADIUS;
    
    IvMatrix44 transform;
};

#endif
