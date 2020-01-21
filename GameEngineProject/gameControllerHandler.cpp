#include "GameControllerHandler.h"



GameControllerHandler::GameControllerHandler()
{
	controller = NULL;

	setupController();
}


GameControllerHandler::~GameControllerHandler()
{

}

void GameControllerHandler::close()
{
	//cleanup any memory reserved to describe this controller
	if (controller != NULL) {
		SDL_GameControllerClose(controller);
		controller = NULL;
	}
}

void GameControllerHandler::setupController()
{
	//joysticks can be game pads, joysticks, steering wheels, guns, dance mats etc)
	//lets see how many are currently attached to the computer
	int numJoySticks = SDL_NumJoysticks();

	//lets loop through them, joystick ids start at id = 0
	for (int joyStickID = 0; joyStickID < numJoySticks; joyStickID++)
	{
		//check if this joystick is a game controller (xbox, ps or logitech controller)
		if (SDL_IsGameController(joyStickID)) {
			//if it is, setup controller with this joystick
			controller = SDL_GameControllerOpen(joyStickID);
			//we are done, exit loop
			break;
		}
	}
}

void GameControllerHandler::update(SDL_Event * event)
{
	if (controller != NULL)
	{
		//grab the joystick id of the connected controller
		SDL_JoystickID joyStickID = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));


		//if controller removed
		if (controller != NULL && event->type == SDL_JOYDEVICEREMOVED)
		{
			if (event->jdevice.which == joyStickID) {
				close();
				return;
			}
		}

		//check if events triggered are from this game controller
		if (event->cdevice.which == joyStickID)
		{


			//IF button is pressed
			if (event->type == SDL_CONTROLLERBUTTONDOWN)
			{
				//Note: think of all controllers as Xbox controllers.
				//E.G ps4 controllers X button lines up with xbox's A button
				if (event->cbutton.button == SDL_CONTROLLER_BUTTON_A)
				{
					////reset hero position
					//hero->pos.x = 200;
					//hero->pos.y = 200;
				}
			}
		}
	}



	//if controller added
	if (controller == NULL && event->type == SDL_JOYDEVICEADDED)
	{
		//check if this joystick is a game controller (xbox, ps or logitech controller)
		if (SDL_IsGameController(event->jdevice.which)) {
			//if it is, setup controller with this joystick
			controller = SDL_GameControllerOpen(event->jdevice.which);
		}
	}
}

void GameControllerHandler::updateHeld()
{

}