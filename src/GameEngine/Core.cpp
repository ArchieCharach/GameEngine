#include "Core.h"
#include "Entity.h"
#include "Screen.h"
#include "Transform.h"
#include "Component.h"
#include "Resources.h"
#include "Environment.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "Exception.h"

namespace GameEngine
{

	std::shared_ptr<Core> Core::Initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->running = false;
		rtn->self = rtn;
	
		rtn->screen = std::make_shared<Screen>();
		rtn->screen->Init();

		rtn->environment = std::make_shared<Environment>();
		rtn->resources = std::make_shared<Resources>();
		rtn->keyboard = std::make_shared<KeyboardHandler>();
		rtn->mouse = std::make_shared<MouseHandler>();

		rtn->device = alcOpenDevice(NULL);

		if (!rtn->device)
		{
			throw Exception("Open AL Device not found");
		}

		rtn->context = alcCreateContext(rtn->device, NULL);

		if (!rtn->context)
		{
			alcCloseDevice(rtn->device);
			throw Exception("Open AL Device closed");
		}

		if (!alcMakeContextCurrent(rtn->context))
		{
			alcDestroyContext(rtn->context);
			alcCloseDevice(rtn->device);
			throw Exception("Open AL Device Problem");
		}

		return rtn;
	}

	void Core::Start()
	{
		running = true;

		while (running) // add running bool false when stop
		{
			SDL_Event event = { 0 };

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					running = false;
				}

				if (event.type == SDL_KEYDOWN)
				{
					keyboard->SetKeyPressed(event.key.keysym.sym);
					if (keyboard->GetKeyDown("Escape"))
					{
						running = false;
					}
				}
				else if (event.type == SDL_KEYUP)
				{
					keyboard->SetKeyReleased(event.key.keysym.sym);
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					mouse->SetMouseButtonPressed(event.button);
				}
				else if (event.type == SDL_MOUSEBUTTONUP)
				{
					mouse->SetMouseButtonReleased(event.button);
				}
				else if (event.type == SDL_MOUSEMOTION)
				{
					mouse->SetMousePosition(event.motion.x, event.motion.y);
				}
			
			}

			for (int i = 0; i < entities.size(); i++)
			{
				try
				{
					entities.at(i)->Update();
				}
				catch (Exception& e)
				{
					std::cout << "Game Engine Exception: " << e.What() << std::endl;
				}
			}

			for (auto it = entities.begin(); it != entities.end(); it++)
			{
				try 
				{
					(*it)->LateUpdate();
				}
				catch (Exception& e)
				{
					std::cout << "Game Engine Exception: " << e.What() << std::endl;
				}
			}

			for (auto it = entities.begin(); it != entities.end(); )
			{
				try
				{
					if (!(*it)->isAlive)
					{
						it = entities.erase(it);
					}
					else
					{
						it++;
					}
				}
				catch (Exception& e)
				{
					std::cout << "Game Engine Exception: " << e.What() << std::endl;
				}
			}

			screen->Clear(); // Clear screen

			for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
				it != entities.end(); it++)
			{
				try
				{
					(*it)->Display();
				}
				catch (Exception& e)
				{
					std::cout << "Game Engine Exception: " << e.What() << std::endl;
				}
			}

			environment->CalculateDeltaTime();

			screen->End(); // Swap window buffers
		}

	}

	std::shared_ptr<Entity> Core::AddEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		entities.push_back(rtn);
		rtn->self = rtn;
		rtn->core = self;
		rtn->isAlive = true;
		rtn->AddComponent<Transform>();
		return rtn;
	}

	std::shared_ptr<Entity> Core::FindEntityWithTag(std::string _tag)
	{
		// Iterate through entities 
		for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
			it != entities.end(); it++)
		{
			// Iterates through all entitys tags
			if ((*it)->GetTag() == _tag)
			{
				return (*it);
			}
		}
		throw ("Entity with tag not found");

		// Otherwise return null
		return std::shared_ptr<Entity>();

	}

	void Core::Stop()
	{
		running = false;
	}

}

