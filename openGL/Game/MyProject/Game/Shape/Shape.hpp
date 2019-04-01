//
//  Shape.hpp
//  Game
//
//

#ifndef Shape_hpp
#define Shape_hpp

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

class Shape
{
    
private:
    std::vector<IvTCPVertex> vertices;
    std::vector<unsigned int> indices;
    
    IvVertexBuffer* vertexBuffer = 0;
    IvIndexBuffer*  indexBuffer = 0;
    
    IvShaderProgram* mShader;
    
    IvUniform* uniColor;
    IvUniform* uniTransform;
    IvUniform* uniTexture;
    IvUniform* uniUvX;
    IvUniform* uniUvY;
    IvUniform* uniLightPos;
    IvUniform* uniLightIntensity;
    IvUniform* uniLightColor;
    
    IvTCPVertex* dataPtr;
    UInt32* indexPtr;
    
    void initializeShape(const string& shapeType, float shapeRadius);
    void intializeShader(const string& objectTag);
    
    void intializeShapeSquare(float distFromCenter);
    void dealocateBuffers();
    float getAttenuationFromDistance(IvVector3 a, IvVector3 b);
    
    bool addValueLight;
    float lightPos = 5.0f;
    
    void animateLight();
    
public:
    Shape() = default;
    Shape(const string& shapeType, float shapeRadius, const string& objectTag);
    ~Shape();
    
    void Draw(IvMatrix44& positionTranslate, pixelInfo p);
};

#endif /* Shape_hpp */
