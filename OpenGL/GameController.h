#pragma once

#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

class GameController
{
public:
	static GameController& GetInstance()
	{
		static GameController instance;
		return instance;
	}

	void Initialize();
	void RunGame();
	void Load();

	Shader* GetShader(const char* shaderName)
	{
		auto itr = shaders.find(shaderName);
		assert(itr != shaders.end());
		return itr->second;
	}

private:
	std::map<std::string, Shader*> shaders;

	std::list<Mesh*> meshes;
	std::list<Mesh*> lights;

	Camera* camera = nullptr;

	inline explicit GameController() = default;
	inline ~GameController() = default;
	inline explicit GameController(GameController const&) = delete;
	inline GameController& operator=(GameController const&) = delete;
};

#endif

