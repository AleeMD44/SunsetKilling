#ifndef ENTITY //macros to ensure the code is included once
#define ENTITY

#include "utils.h"
#include "mesh.h"
#include "texture.h"
#include "animation.h"

class Entity
{
public:

	std::string name;
	Matrix44 model;
	Matrix44 global_model;
	BoundingBox aabb;

};

class EntityMesh : public Entity
{
public:
	//Attributes of this class 
	Mesh* mesh;
	Texture* texture;
	Shader* shader;
	Skeleton* skeleton;
	std::vector<Animation*> animations;
	Vector4 color;
	bool animated;
	bool noColision;

	//methods overwritten 
	EntityMesh::EntityMesh();
	EntityMesh::EntityMesh(const char* meshName, const char* textureName, Vector4 colorC, const char* namee, bool animatedd);
	void render();
};


#endif