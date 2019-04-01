//
//  RainEffect.cpp
//  Game
//
//  Created by Andrei Sabu - (p) on 3/28/19.
//

#include "RainEffect.hpp"


RainEffect::RainEffect(const std::string& tag, float radius)
{
    Entity(tag, radius);
}

RainEffect::~RainEffect()
{
}

void RainEffect::Entity(const std::string& tag, float radius)
{
    ENTITY_SHAPE = "square";
    ENTITY_RADIUS = radius;
    ENTITY_TAG = tag;
    
    Shape(ENTITY_SHAPE, ENTITY_RADIUS, ENTITY_TAG);
    IvRenderer::mRenderer->SetWorldMatrix(transform);
}

void RainEffect::Draw(IvMatrix44& transformPos, pixelInfo p)
{
    
    uniTransform=mShader->GetUniform("myTransform");
    uniTransform->SetValue(transformPos,0);
    
    myTime += 0.004;
    uniTime=mShader->GetUniform("u_time");
    uniTime->SetValue(myTime,0);
    
    uniColor=mShader->GetUniform("myCol");
    uniColor->SetValue(p.lightCol, 0);
    
    
    IvRenderer::mRenderer->SetShaderProgram(mShader);
    
    //DRAW
    IvRenderer::mRenderer->Draw(kTriangleStripPrim, vertexBuffer, indexBuffer);
}


void
RainEffect::Render()
{
    pixelInfo p;
    p.uv = {1, 1};
    p.color = {0,0,0,1.0};
    Draw(transform, p);
}


void RainEffect::Shape(const string& shapeType, float shapeRadius, const string& objectTag)
{
    initializeShape(shapeType, shapeRadius);
    intializeShader(objectTag);
}

void RainEffect::initializeShape(const string& shapeType, float shapeRadius)
{
    if (shapeType == "square")
        intializeShapeSquare(shapeRadius);
}

void RainEffect::intializeShader(const string& objectTag)
{
    mShader = IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram( IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile("rainEffect"),
                                                                               IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile("rainEffect"));
    
    unsigned int numVerts = (unsigned int)vertices.size();
    unsigned int numIndices =(unsigned int) indices.size();
    dataPtr = (IvTCPVertex*)IvStackAllocator::mScratchAllocator->Allocate(kIvVFSize[kTCPFormat] * numVerts);
    indexPtr = (UInt32*)IvStackAllocator::mScratchAllocator->Allocate(sizeof(UInt32)* numIndices);
    
    vector<IvVector2> textCoords;
    textCoords.push_back(IvVector2(0,0));
    textCoords.push_back(IvVector2(0.5,0));
    textCoords.push_back(IvVector2(0,0.5));
    textCoords.push_back(IvVector2(0.5,0.5));
    for ( unsigned int i = 0; i < numVerts; ++i )
    {
        dataPtr[i].position = vertices[i].position;
        dataPtr[i].texturecoord = textCoords[i];
    }
    
    //SET INDEXES
    for ( unsigned int i = 0; i < numIndices; ++i )
        indexPtr[i] = indices[i];
    
    vertexBuffer = IvRenderer::mRenderer->GetResourceManager()->CreateVertexBuffer(kTCPFormat, numVerts, dataPtr, kImmutableUsage);
    indexBuffer = IvRenderer::mRenderer->GetResourceManager()->CreateIndexBuffer(numIndices, indexPtr, kImmutableUsage);
    
}


void RainEffect::intializeShapeSquare(float distFromCenter)
{
    int dx[] = {-1,-1, 1, 1};
    int dy[] = {-1, 1,-1, 1};
    
    for(int i = 0; i < 4; i++)
    {
        IvTCPVertex vert;
        vert.position = IvVector3(-distFromCenter * dx[i], 0, -distFromCenter * dy[i]);
        vertices.push_back(vert);
        indices.push_back(i);
    }
    
}



void RainEffect::setRotation(float angle)
{
    float sintheta, costheta;
    IvSinCos(angle, sintheta, costheta);
    
    transform[0] = costheta;
    transform[2] = -sintheta;
    transform[8] = sintheta;
    transform[10] = costheta;
}

void RainEffect::setPosition(IvVector3 pos)
{
    transform[12] = pos.x;
    transform[13] = pos.y;
    transform[14] = pos.z;
}

void RainEffect::setScale(IvVector3 scale)
{
    IvMatrix44 scaleTranslation;
    scaleTranslation.Identity();
    scaleTranslation.Scaling( scale );
    transform = transform * scaleTranslation;
}
