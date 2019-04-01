#include "Shape.hpp"


Shape::Shape(const string& shapeType, float shapeRadius, const string& objectTag)
{
    initializeShape(shapeType, shapeRadius);
    intializeShader(objectTag);
}

void Shape::initializeShape(const string& shapeType, float shapeRadius)
{
    if (shapeType == "square")
        intializeShapeSquare(shapeRadius);
}

void Shape::intializeShader(const string& objectTag)
{
    mShader = IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram( IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile(objectTag.c_str()),
                                                                               IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile(objectTag.c_str()));
    
    unsigned int numVerts = (unsigned int)vertices.size();
    unsigned int numIndices =(unsigned int) indices.size();
    dataPtr = (IvTCPVertex*)IvStackAllocator::mScratchAllocator->Allocate(kIvVFSize[kTCPFormat] * numVerts);
    indexPtr = (UInt32*)IvStackAllocator::mScratchAllocator->Allocate(sizeof(UInt32)* numIndices);
    
    vector<IvVector2> textCoords;
    textCoords.push_back(IvVector2(0,0));
    textCoords.push_back(IvVector2(1,0));
    textCoords.push_back(IvVector2(0,1));
    textCoords.push_back(IvVector2(1,1));
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


void Shape::intializeShapeSquare(float distFromCenter)
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

void Shape::animateLight()
{
    if (lightPos > 10.0f)
        addValueLight = false;
    if(lightPos < 3.0f)
        addValueLight = true;
    
    if(addValueLight)
        lightPos += 0.005f;
    else
        lightPos -= 0.005f;
}

float Shape::getAttenuationFromDistance(IvVector3 a, IvVector3 b)
{
    float dist = (a.x - b.x)*(a.x - b.x) + (a.z - b.z) * (a.z - b.z);
    dist = sqrt (dist);
    float max = lightPos;
    if (dist >= max)
        dist = max;
    
    return dist / max;
}

void Shape::Draw(IvMatrix44& transformPos, pixelInfo p)
{
    
    animateLight();
    
    //DEFINE UNIFORMS
    uniTexture=mShader->GetUniform("myTexture");
    uniTexture->SetValue(p.texture);
    
    
    uniColor=mShader->GetUniform("myColor");
    uniColor->SetValue(p.color,0);
    
    uniLightColor=mShader->GetUniform("lightColor");
    uniLightColor->SetValue(p.lightCol,0);
    
    
    uniTransform=mShader->GetUniform("myTransform");
    uniTransform->SetValue(transformPos,0);
    
    uniLightIntensity=mShader->GetUniform("lightIntensity");
    uniLightIntensity->SetValue(lightPos/10.0f,0);
    
    float result = getAttenuationFromDistance({transformPos[12], transformPos[13], transformPos[14]}, p.lightPos);
    
    uniLightPos=mShader->GetUniform("lightAttenuation");
    uniLightPos->SetValue(result,0);
    
    uniUvX=mShader->GetUniform("uvX");
    uniUvX->SetValue(p.uv.x,0);
    
    uniUvY=mShader->GetUniform("uvY");
    uniUvY->SetValue(p.uv.y,0);
    
    IvRenderer::mRenderer->SetShaderProgram(mShader);
    
    //DRAW
    IvRenderer::mRenderer->Draw(kTriangleStripPrim, vertexBuffer, indexBuffer);
    
}

void Shape::dealocateBuffers()
{
    if (vertexBuffer != 0) {
        IvRenderer::mRenderer->GetResourceManager()->Destroy(vertexBuffer);
        vertexBuffer = 0;
    }
    
    if (indexBuffer != 0) {
        IvRenderer::mRenderer->GetResourceManager()->Destroy(indexBuffer);
        indexBuffer = 0;
    }
}

Shape::~Shape()
{
    //dealocateBuffers();
}
 
