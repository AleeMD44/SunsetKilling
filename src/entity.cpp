#include "entity.h"
#include "game.h"
EntityMesh::EntityMesh() {
	mesh = new Mesh();
	texture = new Texture();
	shader = new Shader();
}
EntityMesh::EntityMesh(const char* meshName, const char* textureName, Vector4 colorC, const char* namee, bool animatedd) {
	texture = Texture::Get(textureName);
	mesh = Mesh::Get(meshName);
	color = colorC;

	// example of shader loading using the shaders manager
	if (animatedd) {
		skeleton = new Skeleton();
		shader = Shader::Get("data/shaders/phonganim.vs", "data/shaders/phonganim.ps");
	}
	else {
		shader = Shader::Get("data/shaders/phong.vs", "data/shaders/phong.ps");
	}
	name = namee;
	model.setIdentity();
	animated = animatedd;
	noColision = false;
}
void EntityMesh::render()
{

	Vector3 lightPos = { Game::instance->scene->background[1]->model.m[12] + 300,Game::instance->scene->background[1]->model.m[13] + 100,Game::instance->scene->background[1]->model.m[14] };

	Camera* camera = Camera::current;

	shader->enable();

	shader->setUniform("u_color", color);
	shader->setTexture("u_texture", texture, 0);
	shader->setMatrix44("modelView", this->model);
	shader->setMatrix44("viewprojection", Game::instance->scene->camera->viewprojection_matrix);
	shader->setUniform3("ka", Vector3(1.8, 1.8, 1.8));
	shader->setUniform3("ks", Vector3(1, 1, 1));
	shader->setUniform3("kd", Vector3(8, 8, 8));
	shader->setFloat("shininessVal", 80);
	shader->setUniform3("ia", Vector3(0.4, 0.4, 0.4));
	shader->setUniform3("id", Vector3(0.1, 0.1, 0.1));
	shader->setUniform3("is", Vector3(4.5, 4.4, 4.2));
	shader->setUniform3("lightPos", lightPos);
	shader->setUniform3("eyePos", camera->eye);

	if (animated) {
		mesh->renderAnimated(GL_TRIANGLES, skeleton);
	}
	else {
		mesh->render(GL_TRIANGLES);
	}

	shader->disable();
}
