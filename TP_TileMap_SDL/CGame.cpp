#include "CGame.h"


CGame::CGame()
{
	bRunning = true;

	pWindow = NULL;
	pRenderer = NULL;

	for (int n_i = 0; n_i < WHEIGHT / SIZETILE; n_i++) {
		for (int n_j = 0; n_j < WWIDTH / SIZETILE; n_j++) {
			decor[n_i][n_j] = 0;
		}
	}
}

CGame::~CGame()
{
}

bool CGame::init(const char* title, int xpos, int ypos, int flags)
{
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success\n";
		// init the window
		pWindow = SDL_CreateWindow(title, xpos, ypos, WWIDTH, WHEIGHT, flags);
		// window initsuccess
		if (pWindow != 0) {
			std::cout << "window creation success\n";
			pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
			// renderer init success
			if (pRenderer != 0) {
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}

	//Game is on
	bRunning = true;

	ifstream mymap;

	textureManager.loadPNG("./Assets/Decor.png", "decor", pRenderer);
	mymap.open("Decor.txt");

	//Get the information of the tile in the array
	for (int n_i = 0; n_i < 31; n_i++) {
		for (int n_j = 0; n_j < 31; n_j++) {
			mymap >> decor[n_i][n_j];
		}
	}
	mymap.close();


	std::cout << "init success\n";
}

void CGame::render()
{
	//Background
	SDL_SetRenderDrawColor(pRenderer, 126,192, 238, 255);
	SDL_RenderClear(pRenderer); // clear the renderer to the draw color

	//Draw the tile

	for (int n_i = 0; n_i < 31; n_i++) {
		for (int n_j = 0; n_j < 31; n_j++) {
			textureManager.drawTile("decor", n_j, n_i, SIZETILE, SIZETILE, pRenderer, decor[n_i][n_j], 10);
		}
	}

	

	SDL_RenderPresent(pRenderer); // draw to the screen
}

void CGame::update()
{

}

void CGame::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			bRunning = false;
			break;
			//Input release
		default:
			break;
		}
	}
}

void CGame::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();

}

bool CGame::getBRunning()
{
	return bRunning;
}

void CGame::setBRunning(bool bRunning)
{
	this->bRunning = bRunning;
}
