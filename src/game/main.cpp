#include <GameEngine\GameEngine.h>
// Include game engine

#include <iostream>
#include <memory>

class Player : public Component
{
public:
	void OnTick()
	{
		//std::cout << "Hello World" << std::endl;
	}
};

int main()
{

	std::shared_ptr<Core> core = Core::Initialize();

	std::shared_ptr<Entity> camera = core->AddEntity();
	std::shared_ptr<Camera> cam = camera->AddComponent<Camera>(glm::vec3(0, 6, -6), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


	std::shared_ptr<Entity> cat = core->AddEntity();
	std::shared_ptr<MeshRenderer> catRenderer = cat->AddComponent<MeshRenderer>();
	catRenderer->AddModel("../resources/models/cat.obj");
	std::shared_ptr<Material> material = cat->AddComponent<Material>("../resources/textures/cat.png");
	//material->LoadTexture("../resources/textures/cat.png");

	//std::shared_ptr<Entity> cube = core->AddEntity();
	//std::shared_ptr<MeshRenderer> meshRenderer = cube->AddComponent<MeshRenderer>();
	//std::shared_ptr<Material> material = cube->AddComponent<Material>();
	//material->LoadTexture("../resources/textures/wall.jpg");

	std::shared_ptr<Sound> sound = std::make_shared<Sound>("../resources/sounds/dixie_horn.ogg");
	sound->Play();

	core->Start();


	return 0;
}
