#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const int KEYPAD_WIDTH = 300;
const int KEYPAD_HEIGHT = 400;

#define BUTTON_ROW 4
#define BUTTON_COL 3
const int BUTTON_WIDH = 100;
const int BUTTON_HEIGHT = 100;



//SDL surface
SDL_Window * window =NULL;
SDL_Surface* window_surface = NULL;
SDL_Surface* keypad = NULL;
SDL_Rect upper_right;

//button define
typedef struct{
	SDL_Point mPosition;
	char number;
}Button;
Button kBUTTON[BUTTON_ROW][BUTTON_COL];

//main SDL function
bool loadButton();
bool init();
SDL_Surface* load_media();//
void closeWindow();

//button function
void setPostion(int x, int y, int i, int j, int k);
void eventHandle(SDL_Event *e);

void setButtStat(int x, int y, int i, int j, int k)
{
	kBUTTON[i][j].mPosition.x = x;
	kBUTTON[i][j].mPosition.y = y;
	printf("x and y are %d, %d\n", x,y);
	//int f = k+48;
	
	//printf("%s %d\n", "k is now ", k);
//ascii
	if(k<=9)
	{
		kBUTTON[i][j].number = k+48;
	//	printf( "executed when k is %d\n", k);
		
	}

	else if (k==11)
	{
		//printf("button 1,0 is %c\n", kBUTTON[1][0].number);
		//printf("i and j are %d, %d\n",i, j );
		kBUTTON[i][j].number = '0';
		//printf("button 1,0 now is  %c\n", kBUTTON[1][0].number);
		//printf("i and j now are %d, %d\n",i, j );

	}
	printf("%d, %d, %c\n",kBUTTON[i][j].mPosition.x,kBUTTON[i][j].mPosition.y,kBUTTON[i][j].number );
	printf("%d, %d, %c\n",kBUTTON[1][0].mPosition.x,kBUTTON[1][0].mPosition.y,kBUTTON[1][0].number );

	
//printf("button %d,%d is at position %d, %d with number %c\n",i,j,x,y,kBUTTON[i][j].number);
//printf("k is %d\n", kBUTTON[i][j].number);
}

void eventHandle(SDL_Event *e)
{
	if(e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x,y;
		int m,n;
		SDL_GetMouseState(&x,&y);
		
		m = x/100;
		n = y/100;
		
		printf("at button %d, %d, with value %c\n", m,n,kBUTTON[m][n].number);
		printf("k is %d\n", kBUTTON[m][n].number);
	}
}
	
int main(int argc, char* args[])
{
	bool success = true;

	success = init();
	if (success)
	{			
		keypad = load_media();	        
	}

	SDL_BlitSurface(keypad, NULL, window_surface, NULL);

	SDL_UpdateWindowSurface(window);

	if(!loadButton())
	{
		printf("Failed to load button\n");
	}


	else
	{		
		bool quit = false;
		SDL_Event e;
		while(!quit)
		{
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else
						eventHandle( &e );
				
				}

		}
	
	}
	
	closeWindow();
	return 0;
}

bool init()
{
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		window = SDL_CreateWindow("Keypad v0.0.1", 1000,500, KEYPAD_WIDTH, KEYPAD_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				window_surface = SDL_GetWindowSurface(window);
			}
		}
	//	const SDL_VideoInfo* info = SDL_GetVideoInfo();
//int screenWidth = info ->current_w;
//int screenHeight = info->current_h;
//printf("%d %d\n", screenWidth, screenHeight);
	}

	return success;
}

SDL_Surface* load_media() 
{
	SDL_Surface* optimized_surface = NULL;

	SDL_Surface* loaded_surface = IMG_Load("/home/quw/sdl2/main/keypad.png");
	if (loaded_surface == NULL)
	{
		printf("Unable to load image %s! SDL_Image Error: %s\n", "/home/quw/sdl2/main/keypad.png", IMG_GetError());
	}
	else
	{
		optimized_surface = SDL_ConvertSurface(loaded_surface, window_surface->format, NULL);
		if (optimized_surface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", "/home/quw/sdl2/main/keypad.png", SDL_GetError());
		
		}

		SDL_FreeSurface(loaded_surface);
	}

	return optimized_surface;
}

bool loadButton()
{
	int k = 1;
	int i, j;
	bool success = true; 
	
	if(keypad =NULL)
	{
		printf("Failed to load keypad!\n");
		success = false;
	}
	
	else
	{
		for(i =0; i<4; i++)
		{
			for(j = 0; j<3; j++)
			{

				setButtStat(j*100, i*100, j, i,k);
				//printf("%c chicken\n", kBUTTON[j][i].number);
				//printf("k is %d\n", k);
				k++;
			}
		}

	}
	

	return success;
}

void closeWindow() 
{
	SDL_FreeSurface(keypad);

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}


