#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include "engine.h"
#include "player.h"
#include "game.h"
#include "collision.h"
#include <string>
#include "main.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "spritesheet.h"


using namespace std;

#define WIDTH 1600
#define HEIGHT 900
#define COW_PATH "cow.png"
#define COGGERS_PATH "coggers.png"





void UpdateProjectiles()
{
	for (int i = 0; i < PROJECTILE_MAX; i++)
	{
		if (projectiles[i].alive)
		{
			projectiles[i].update();
			projectiles[i].draw();
		}		
	}
}


vector<int> GetLevels(vector<vector<int>> &levelsContainer)
{
	vector<int> theLevel;
	string levels;
	bool levelSelected = false;
	int selectedLevel = 1;
	char a;
	int numberOfLines = 0;
	

	vector<int> temp_vector;

	

	fstream infile("levels.txt", fstream::in);

	while (std::getline(infile, levels))
	{
		for (auto value : levels)
		{
			if (std::isdigit(value))
			{
				int ia = value - '0';
				temp_vector.push_back(ia);
			}
		}
		levelsContainer.push_back(temp_vector);
		temp_vector.clear();

		++numberOfLines;
	}

	

	infile.clear();
	infile.seekg(0);


	//cout << "Choose your level: ";
	//cin >> selectedLevel;

	while (selectedLevel>=numberOfLines && !levelSelected)
	{

		if(selectedLevel <= numberOfLines)
		{
			levelSelected = true;
		}
		else
		{
			cout << "That level does not exist";
		}

	}

	for (int i = 0; i <= selectedLevel; ++i)
	{
		getline(infile, levels);
	}

	getline(infile, levels);


	for (auto value : levels)
	{
		if (std::isdigit(value))
		{
			int ia = value - '0';
			theLevel.push_back(ia);
		}
	}
	infile.close();
	return theLevel;
}

void SetBrickType(vector<int> lvl1, int l)
{
	for (int i = 0; i < BRICK_ROWS; i++)
	{
		for (int j = 0; j < BRICK_COLUMNS; j++)
		{
			if (lvl1[l] == 0)
			{
				bricks[j][i].breakable = false;
			}
			if (lvl1[l] == 2)
			{
				bricks[j][i].strongWall = true;
			}
			if (lvl1[l] == 3)
			{
				bricks[j][i].alive = false;
			}
			l++;
		}
	}
}

void handle_text_ingame(SDL_Texture* message, SDL_Rect& message_rect)
{
	message_rect.x = 0;
	message_rect.y = 0;
	message_rect.w = 100;
	message_rect.h = 100;

	int xPos, yPos;
	SDL_PumpEvents();
	Uint32 buttons = SDL_GetMouseState(&xPos, &yPos);
	message_rect.x = xPos - 50;
	message_rect.y = yPos - 50;
	SDL_RenderCopy(render, message, NULL, &message_rect);
}

void GetMousePos(int &xPos, int &yPos)
{
	SDL_PumpEvents();
	Uint32 buttons = SDL_GetMouseState(&xPos, &yPos);
}

int main()
{

	/*SDL_Surface* gWindow = NULL;
	SDL_Surface* gScreenSurface = NULL;
	SDL_Surface* gPNGSurface = NULL;*/

	vector<vector<int>> levels;

	vector<int> lvl1 = GetLevels(levels);

	Brick placedBrick[BRICK_MAX];

	int selectedLevel = 0;
	
	///INITILIZATION
	SDL_Init(SDL_INIT_EVERYTHING);//Initialize the usage of everything
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0); //A structure to refer to the window we just made
	render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


	//IMG Initialization
	SDL_Texture* img = NULL;
	auto img2 = IMG_LoadTexture(render, COW_PATH);
	IMG_Init(IMG_INIT_PNG);

	sprite_sheet cow;
	sprite_sheet coggers;

	coggers.load(COGGERS_PATH,112,112);
	cow.load(COW_PATH,112,122);


	SDL_Color white = { 255,255,255,255 };
	SDL_Color black = { 0, 0, 0 ,255 };


	//Font Initialization
	TTF_Init();
	TTF_Font* roboto = TTF_OpenFont("res/roboto.ttf",90);
	if (!roboto)
	{
		cout << "Something went Wrong";
	}
	TTF_Init();
	TTF_Font* runescape_uf = TTF_OpenFont("res/runescape_uf.ttf", 90);
	if (!runescape_uf)
	{
		cout << "runescape finna broke";
	}


	//Text on mouse initialization
	/*
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(roboto, "Hello", white);
	SDL_Texture* message = SDL_CreateTextureFromSurface(render, surfaceMessage);
	SDL_Rect message_rect;*/


	//Image Variables
	int frame = 0;
	float frameTimer = 0.f;


	int placedB = 0;


	//MAIN LOOP HANDLER + TICKS
	bool running = true;
	bool selectLevel = true;
	Uint64 previousTicks = SDL_GetPerformanceCounter();


	

	//ETC
	string playerText = "";
	string instructtonText = "Choose a level: 1 - " + to_string(levels.size());

	//Get mouse position in window
	int xPos = 0, yPos= 0;//For mouse position
	//GetMousePos(xPos, yPos); //method that gets the actual position

	//Text input thing
	
	SDL_Surface* InputTextSurface = TTF_RenderText_Solid(runescape_uf, playerText.c_str(), white);
	if (!InputTextSurface) {
		cout << "Failed to render text: " << TTF_GetError() << endl;
	}
	SDL_Surface* InstructionTextSurface = TTF_RenderText_Solid(runescape_uf, instructtonText.c_str(), white);
	if (!InstructionTextSurface) {
		cout << "Failed to render text: " << TTF_GetError() << endl;
	}
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(render,InputTextSurface );
	SDL_Texture* instruction_texture = SDL_CreateTextureFromSurface(render,InstructionTextSurface );
	SDL_Rect dest;
	SDL_Rect dest2;

	bool ranning = true;


	Point mouse;

	while (ranning)
	{

		
		mouse.x = xPos;
		mouse.y = yPos;
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);

		SDL_PumpEvents();
		Uint32 buttons = SDL_GetMouseState(&xPos, &yPos);

		SDL_Event ev;

		SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
		auto bawks = AABB::make_from_position_size(1300, 800, 100, 100);
		draw_filled_box(bawks);

		
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_MOUSEBUTTONDOWN:

				if (!aabb_point_intersect(bawks, mouse))
				{
					cout << "Ounga" << endl;
					SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

					buttons = SDL_GetMouseState(&xPos, &yPos);
					auto bawks = AABB::make_from_position_size(xPos, yPos, 100, 100);
					placedBrick[placedB].x = xPos;
					placedBrick[placedB].y = yPos;
					placedBrick[placedB].draw();
					placedB++;
				}
				

				break;

			case SDL_KEYDOWN:
			{
				if (ev.key.repeat)
				{
					break;
				}
				int scancode = ev.key.keysym.scancode;
				if (scancode == SDL_SCANCODE_ESCAPE)
				{
					ranning = false;
					SDL_Quit();
				}
				break;
			}
			}

			

			if (ev.type == SDL_MOUSEBUTTONDOWN && aabb_point_intersect(bawks, mouse))
			{
				cout << "Hovering button" << endl;
			}
		}

		

		

		

		for (size_t i = 0; i <= placedB; i++)
		{

			Brick& brick = placedBrick[i];

			AABB box = AABB::make_from_position_size(brick.x, brick.y, brick.w, brick.h);

			if (aabb_point_intersect(box, mouse))
			{
				cout << "sldzkdfhdskl adsh adsjlfg " << endl;
			}
		}

		


		
		SDL_RenderPresent(render);
	}


	return 0;



	while (selectLevel) {


		

		
		SDL_RenderClear(render);

		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		auto bawks = AABB::make_from_position_size(100, 100, 100, 100);
		draw_filled_box(bawks);

		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);

		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_TEXTINPUT && playerText.length()<1 && *ev.text.text != ' ')
			{
				playerText += ev.text.text;
				cout << " > " << playerText << endl;
			}
			if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && !playerText.empty()) 
			{
				playerText.pop_back();
				cout << " > " << playerText << endl;
			}
			else if (ev.type == SDL_KEYDOWN)
			{
				int scancode = ev.key.keysym.scancode;
				if (scancode == SDL_SCANCODE_ESCAPE)
				{
					selectLevel = false;
					running = false;
					break;
				}
				if (scancode == SDL_SCANCODE_RETURN)
				{

					for (auto val : playerText)
					{
						if (std::isdigit(val))
						{
							if (int ia = val - '0' <= levels.size())
							{
								selectedLevel = (val - '0') - 1;
								selectLevel = false;
								break;
							}
							if (int ia = val - '0' > levels.size())
							{
								SDL_DestroyTexture(instruction_texture);
								SDL_FreeSurface(InstructionTextSurface);
								instructtonText = "Idiot, choose a level between 1 - " + to_string(levels.size());
								InstructionTextSurface = TTF_RenderText_Solid(runescape_uf, instructtonText.c_str(), white);
								instruction_texture = SDL_CreateTextureFromSurface(render, InstructionTextSurface);


							}

						}
					}

				}

				keys[scancode] = true;//Sets the specific key bool to true, depending on the key we press.
				break;
			}
			
		}

		SDL_Surface* text_surf = TTF_RenderText_Solid(runescape_uf, playerText.c_str(), white);
		if (!playerText.empty()) {
			
			text_texture = SDL_CreateTextureFromSurface(render, text_surf);
			dest.x = WIDTH/2 - (text_surf->w / 2.0f);
			dest.y = HEIGHT/2 - (text_surf->h/2.0f);
			dest.w = text_surf->w;
			dest.h = text_surf->h;

			
		}
		SDL_Surface* text_surf2 = TTF_RenderText_Solid(runescape_uf, instructtonText.c_str(), white);
		if (!instructtonText.empty()) {

			instruction_texture = SDL_CreateTextureFromSurface(render, text_surf2);
			dest2.x = WIDTH / 2 - (text_surf2->w / 2.0f);
			dest2.y = HEIGHT / 2 - (text_surf2->h / 2.0f)-120;
			dest2.w = text_surf2->w;
			dest2.h = text_surf2->h;
		}

		SDL_RenderCopy(render, text_texture, NULL, &dest);
		SDL_RenderCopy(render, instruction_texture, NULL, &dest2);
		SDL_RenderPresent(render);

		SDL_DestroyTexture(text_texture);
		SDL_FreeSurface(text_surf);
		SDL_DestroyTexture(instruction_texture);
		SDL_FreeSurface(text_surf2);


	}
		
	SDL_StopTextInput();

	while (running)
	{
		frameNumber++;

		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 deltaTicks = ticks - previousTicks;
		previousTicks = ticks;
		delta_time = (float)deltaTicks / SDL_GetPerformanceFrequency();

		//printf("FPS %f\n", 1.f / delta_time);

		SDL_Event event;
		while (SDL_PollEvent(&event))//puuting if here works, but then it only reads one event while using the while keeps handling more than one event in the queue?
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
			{
				if (event.key.repeat)
				{
					break;
				}
				int scancode = event.key.keysym.scancode;
				if (scancode == SDL_SCANCODE_ESCAPE)
					running = false;

				keys[scancode] = true;//Sets the specific key bool to true, depending on the key we press.
				keys_state[scancode].state = true;
				keys_state[scancode].changeFrame = frameNumber;

				break;
			}
			case SDL_KEYUP:
			{
				int scancode = event.key.keysym.scancode;

				if (scancode == SDL_SCANCODE_SPACE)
				{
					player.space = false;
				}

				keys_state[scancode].state = false;
				keys_state[scancode].changeFrame = frameNumber;

				keys[scancode] = false;
				break;

			}
			}
		}
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderClear(render);
		

		player.update();
		player.draw();

		wall->draw_walls();
		wall->draw_roof();
		

		//handle_text_ingame(message, message_rect);
		

		


		for (int i = 0; i < 30; i++)
		{
			wall[i].draw();
		}


	
		for (int i = 0; i < BRICK_COLUMNS; i++)
		{
			for (int j = 0; j < BRICK_ROWS; j++)
			{
				bricks[i][j].x = bricks[i][j].margin * i + bricks[i][j].margin;
				bricks[i][j].y = bricks[i][j].h * j + bricks[i][j].h * 1.5;
			}
		}

		int l = 0;

		SetBrickType(levels[selectedLevel], l);

		frameTimer += delta_time;

		for (int i = 0; i < PROJECTILE_MAX; i++)
		{
			if (projectiles[i].alive)
			{
				coggers.draw((int)(frameTimer * 20) % 60, projectiles[i].x- projectiles[i].w/2, projectiles[i].y- projectiles[i].h/2,projectiles[i].h,projectiles[i].w);
				projectiles[i].update();
				projectiles[i].draw();
			}
		}
		
		

		for (int i = 0; i < BRICK_COLUMNS; i++)
		{
			for (int j = 0; j < BRICK_ROWS; j++)
			{
				if (bricks[i][j].alive)
				{
					cow.draw((int)(frameTimer*20) % 21, bricks[i][j].x - bricks[i][j].w/2, bricks[i][j].y - bricks[i][j].h / 2, bricks[i][j].w, bricks[i][j].h);
				}
				bricks[i][j].draw();
			}
		}



		//drawSprites(img, imgH, imgW, 5,img2, cow);

				

		SDL_RenderPresent(render);


		SDL_Delay(16);

		if (player.playerLives <= 0)
		{
			SDL_Quit();
			running = false;
		}
	}
	return 0;

}