#pragma once
#include <SDL/SDL.h>


extern SDL_Window* window;
extern SDL_Renderer* render;

struct KeyState
{
	bool state = false; //basic bool to check if the key is pressed
	int changeFrame = 0;
};


bool GetKey(SDL_Scancode key);
bool GetKeyPressed(SDL_Scancode key);
bool GetKeyReleased(SDL_Scancode key);

extern bool keys[SDL_NUM_SCANCODES];
extern KeyState keys_state[SDL_NUM_SCANCODES];

extern float delta_time;
extern int frameNumber;

