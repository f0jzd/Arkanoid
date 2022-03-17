#include "engine.h"

SDL_Window* window;
SDL_Renderer* render;

bool keys[SDL_NUM_SCANCODES] = { false };
KeyState keys_state[SDL_NUM_SCANCODES] = { false };

float delta_time = 0.f;
int frameNumber;

bool GetKey(SDL_Scancode key)
{
	return keys_state[key].state;
	
}
bool GetKeyPressed(SDL_Scancode key)
{
	return keys_state[key].state && keys_state[key].changeFrame == frameNumber;
	
}
bool GetKeyReleased(SDL_Scancode key)
{
	return !keys_state[key].state && keys_state[key].changeFrame == frameNumber;
	
}