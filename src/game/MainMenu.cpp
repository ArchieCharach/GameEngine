#include "MainMenu.h"
#include "Game.h"

void MainMenu::Start()
{
	screenSize = GetCore()->GetScreen()->GetSize();

	// Instructions
	instuctions = GetCore()->AddEntity();
	std::shared_ptr<Orthagraphic> instructionRenderer = instuctions->AddComponent<Orthagraphic>("../resources/models/Instructions.obj", "../resources/shaders/Ortho.vert", "../resources/shaders/Ortho.frag");
	std::shared_ptr<Texture> instructionsTexture = instuctions->AddComponent<Texture>("../resources/textures/Black.png");
	instuctions->GetComponent<Transform>()->SetTransform(glm::vec3(screenSize.x / 2, 100, 0), 0.0f, glm::vec3(50, 50, 0));

	// Start Button
	startButton = GetCore()->AddEntity();
	std::shared_ptr<Orthagraphic> startButtonRenderer = startButton->AddComponent<Orthagraphic>("../resources/models/PlayText.obj", "../resources/shaders/Ortho.vert", "../resources/shaders/Ortho.frag");
	std::shared_ptr<Texture> startButtonTexture = startButton->AddComponent<Texture>("../resources/textures/Black.png");
	startButton->GetComponent<Transform>()->SetTransform(glm::vec3(screenSize.x / 2, screenSize.y - 150, 0), 0.0f, glm::vec3(100, 100, 0));
	std::shared_ptr<Button> button = startButton->AddComponent<Button>();
}

void MainMenu::Update()
{
	// Check Play button pressed
	if (startButton->GetComponent<Button>()->CheckClicked())
	{
		game = GetCore()->FindEntityWithComponent<Game>();
		game->GetComponent<Game>()->StartGame();
		instuctions->Destroy();
		startButton->Destroy();
		GetEntity()->Destroy();
	}
}