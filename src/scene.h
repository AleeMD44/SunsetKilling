/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the game, is in charge of creating the game, getting the user input, process the update and render.
*/

#ifndef SCENE_H
#define SCENE_H

#include "includes.h"
#include "camera.h"
#include "utils.h"
#include "car.h"
#include "player.h"
#include "mesh.h"
#include "utils.h"
#include "mesh.h"
#include "texture.h"
#include "fbo.h"
#include "shader.h"
#include "input.h"
#include "animation.h"
#include "entity.h"
#include "stage.h"
#include "rendertotexture.h"

class Scene
{
public:

	//some globals
	bool car = true;
	bool freecamera = false;
	bool phoneout = false;
	bool animation = false;
	RenderToTexture* ftext = NULL;
	Shader* shader = NULL;
	FBO* fbo = NULL;
	float speed = 100;
	std::vector<EntityMesh*> background;
	std::vector<EntityMesh*> players;
	std::vector<EntityMesh*> map;
	std::vector<EntityMesh*> vehicles;
	std::vector<EntityMesh*> playeritems;
	std::vector<Player*> enemies;
	std::vector<Texture*> screenshots;
	EntityMesh* mesh = NULL;
	Car* myCar;
	Player* myPlayer;
	Mesh* mesh6 = NULL;
	Matrix44 test;
	//some vars
	Camera* camera; //our global camera

	Scene(int window_width, int window_height);

	//main functions
	void render(void);
	void update(double seconds_elapsed);

};


#endif 