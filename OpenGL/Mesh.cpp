#include "Mesh.h"
#include "GameController.h"
#include <OBJ_Loader.h>

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);

    delete diffuseTexture;
    delete specularTexture;
}

void Mesh::Create(json::JSON& jsonData)
{
    M_ASSERT(jsonData.hasKey("Shader"), "Shader is required");
    shader = GameController::GetInstance().GetShader(jsonData["Shader"].ToString().c_str());

    if (jsonData.hasKey("Position")) LoadVec3(jsonData, "Position", position);
    if (jsonData.hasKey("Rotation")) LoadVec3(jsonData, "Rotation", rotation);
    if (jsonData.hasKey("Scale")) LoadVec3(jsonData, "Scale", scale);

    if (jsonData.hasKey("LightDirection")) LoadVec3(jsonData, "LightDirection", lightDirection);
    lightDirection = glm::normalize(lightDirection);

    if (jsonData.hasKey("LightColor")) LoadVec3(jsonData, "LightColor", lightColor);
    if (jsonData.hasKey("AmbientColor")) LoadVec3(jsonData, "AmbientColor", ambientColor);
    if (jsonData.hasKey("SpecularColor")) LoadVec3(jsonData, "SpecularColor", specularColor);
    if (jsonData.hasKey("SpecularStrength")) specularStrength = Get(jsonData, "SpecularStrength").ToFloat();

    if (jsonData.hasKey("LightType")) lightType = Get(jsonData, "LightType").ToString();

    if (jsonData.hasKey("PointLightconstant")) pointLightconstant = Get(jsonData, "PointLightconstant").ToFloat();
    if (jsonData.hasKey("PointLightlinear")) pointLightlinear = Get(jsonData, "PointLightlinear").ToFloat();
    if (jsonData.hasKey("PointLightquadratic")) pointLightquadratic = Get(jsonData, "PointLightquadratic").ToFloat();

    if (jsonData.hasKey("SpotLightconeAngle")) spotLightconeAngle = Get(jsonData, "SpotLightconeAngle").ToFloat();
    if (jsonData.hasKey("SpotLightfalloff")) spotLightfalloff = Get(jsonData, "SpotLightfalloff").ToFloat();
    
    /*vertexData = {
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };*/

    M_ASSERT(jsonData.hasKey("Model"), "Model file is required");
    LoadOBJ(jsonData["Model"].ToString());

    diffuseTexture = new Texture();
    if (diffuseMap.size() > 0) diffuseTexture->LoadTexture(diffuseMap.c_str());

    specularTexture = new Texture();
    if (specularMap.size() > 0) specularTexture->LoadTexture(specularMap.c_str());

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    //indexData = {
    //    2,0,3,2,1,0
    //};

    //glGenBuffers(1, &indexBuffer);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);
}

void Mesh::BindAttributes()
{
#pragma region Set Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glEnableVertexAttribArray(shader->GetAttrVertices());
    glVertexAttribPointer(
        shader->GetAttrVertices(),
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(shader->GetAttrNormals());
    glVertexAttribPointer(
        shader->GetAttrNormals(),
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(shader->GetAttrTexCoords());
    glVertexAttribPointer(
        shader->GetAttrTexCoords(),
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(6 * sizeof(float))
    );

    glVertexAttrib2fv(shader->GetAttrTexTranslation(), glm::value_ptr(texTranslation));

}

void Mesh::SetShaderVariables(glm::mat4 _pv, const std::list<Mesh*>& _lights)
{
    shader->SetMat4("World", world);
    shader->SetMat4("WVP", _pv * world);
    shader->SetVec3("CameraPosition", cameraPosition);

    M_ASSERT((_lights.size() <= 4), "Diffuse Shader only supports 4 lights");
    shader->SetInt("numLights", _lights.size());
    shader->SetVec3("lightColor", lightColor);
    int i = 0;
    for (auto& light : _lights)
    {
        shader->SetVec3(Concat("light[", i, "].position").c_str(), light->GetPosition());
        shader->SetVec3(Concat("light[", i, "].direction").c_str(), light->GetLightDirection());

        shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), light->GetAmbientColor());
        shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), light->GetLightColor());
        shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), light->GetSpecularColor());

        shader->SetFloat(Concat("light[", i, "].constant").c_str(), light->GetPointLightConstant());
        shader->SetFloat(Concat("light[", i, "].linear").c_str(), light->GetPointLightLinear());
        shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), light->GetPointLightQuadratic());

        shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(light->GetConeAngle()));
        shader->SetFloat(Concat("light[", i, "].falloff").c_str(), light->GetFalloff());

        i++;
    }

    shader->SetFloat("material.specularStrength", specularStrength);
    shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, diffuseTexture->GetTexture());
    shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, specularTexture->GetTexture());
}

void Mesh::CalculateTransform()
{
    world = glm::translate(glm::mat4(1.0f), position);
    world = glm::rotate(world, rotation.y, glm::vec3(0, 1, 0));
    world = glm::rotate(world, rotation.x, glm::vec3(1, 0, 0));
    world = glm::rotate(world, rotation.z, glm::vec3(0, 0, 1));
    world = glm::scale(world, scale);
}

void Mesh::Render(glm::mat4 _wvp, const std::list<Mesh*>& _lights)
{
    glUseProgram(shader->GetProgramID());

    CalculateTransform();
    SetShaderVariables(_wvp, _lights);
    BindAttributes();
    
    glDrawArrays(GL_TRIANGLES, 0, vertexData.size()/8);

    glDisableVertexAttribArray(shader->GetAttrVertices());
    //glDisableVertexAttribArray(shader->GetAttrColors());
    glDisableVertexAttribArray(shader->GetAttrNormals());
    glDisableVertexAttribArray(shader->GetAttrTexCoords());
    glDisableVertexAttribArray(shader->GetAttrTexTranslation());
}

std::string Mesh::Concat(const std::string& _s1, int _index, const std::string& _s2)
{
    std::string index = std::to_string(_index);
    return (_s1 + index + _s2);
}

void Mesh::LoadVec3(json::JSON& jsonData, const char* name, glm::vec3& vec)
{
    json::JSON& data = Get(jsonData, name);

    vec.x = Get(data, "r").ToFloat() ? Get(data, "r").ToFloat() : Get(data, "x").ToFloat();
    vec.y = Get(data, "g").ToFloat() ? Get(data, "g").ToFloat() : Get(data, "y").ToFloat();
    vec.z = Get(data, "b").ToFloat() ? Get(data, "b").ToFloat() : Get(data, "z").ToFloat();
}

void Mesh::LoadOBJ(const std::string& _filename)
{
    objl::Loader loader;

    M_ASSERT(loader.LoadFile(_filename) == true, "Failed to load mesh");

    for (auto& currentMesh: loader.LoadedMeshes)
    {
        for (auto& vertex : currentMesh.Vertices)
        {
            vertexData.push_back(vertex.Position.X);
            vertexData.push_back(vertex.Position.Y);
            vertexData.push_back(vertex.Position.Z);
            vertexData.push_back(vertex.Normal.X);
            vertexData.push_back(vertex.Normal.Y);
            vertexData.push_back(vertex.Normal.Z);
            vertexData.push_back(vertex.TextureCoordinate.X);
            vertexData.push_back(vertex.TextureCoordinate.Y);
        }
    }

    std::string mapKd = loader.LoadedMaterials[0].map_Kd;
    const size_t lastSlashKdIdx = mapKd.find_last_of("\\/");
    if (std::string::npos != lastSlashKdIdx)
    {
        diffuseMap = "../Assets/Textures/" + mapKd.erase(0, lastSlashKdIdx + 1);
    }

    std::string mapKs = loader.LoadedMaterials[0].map_Ks;
    const size_t lastSlashKsIdx = mapKs.find_last_of("\\/");
    if (std::string::npos != lastSlashKsIdx)
    {
        specularMap = "../Assets/Textures/" + mapKs.erase(0, lastSlashKsIdx + 1);
    }
}