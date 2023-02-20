#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 1024
#define HEIGHT 768
#define GRID_WIDTH 20
#define GRID_HEIGHT 15
static int d = 5;
static int lt = 0,ct;
int finalScore = 0;

void CreateGrid(SDL_Window* w, SDL_Renderer* r);
void Input(SDL_Window* w, SDL_Renderer* r, int* xFood, int* yFood, int* speed, int* x, int* y, int* score,TTF_Font* font, int* finalScore);
void Quit(SDL_Window* w, SDL_Renderer* r,int finalScore);
void CreatePlayer(SDL_Window* w, SDL_Renderer* r,int* x, int* y);
void DirectionToPosition( int d,SDL_Renderer* r,SDL_Window* w, int* x, int* y, int* score, int* finalScore);
void CreateFood(SDL_Window* w, SDL_Renderer* r,int* x, int* y, int* xFood, int* yFood);
void DrawText(SDL_Window* w, SDL_Renderer* r,int* score,TTF_Font* font,int finalScore);

int main(void){
	d = 5;
	int score = 0;
	int xFood,yFood;
	int speed = 200;
	int x = GRID_WIDTH/2;
	int y = GRID_HEIGHT/2;
	xFood = rand() % GRID_WIDTH;
	yFood = rand() % GRID_HEIGHT;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("DeterminationSansWebRegular-369X.ttf",36);
	SDL_Window *w = SDL_CreateWindow("Speed Snake!",
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 WIDTH, HEIGHT,
									 0);
	SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(r);
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	SDL_RenderPresent(r);
	while(1){
		Input(w, r,&xFood,&yFood, &speed, &x, &y, &score,font,&finalScore);
	}
	return 0;
}

void Input(SDL_Window* w, SDL_Renderer* r, int* xFood, int* yFood, int* speed, int* x, int* y, int* score,TTF_Font* font,int* finalScore){
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		switch(e.type){
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym){
					case SDLK_ESCAPE:
						Quit(w,r,*finalScore);
						break;
					case SDLK_h:
						d = 2;
						break;
					case SDLK_l:
						d = 0;
						break;
					case SDLK_k:
						d = 1;
						break;
					case SDLK_j:
						d = 3;
						break;
					case SDLK_a:
						d = 2;
						break;
					case SDLK_d:
						d = 0;
						break;
					case SDLK_w:
						d = 1;
						break;
					case SDLK_s:
						d = 3;
						break;
					case SDLK_LEFT:
						d = 2;
						break;
					case SDLK_RIGHT:
						d = 0;
						break;
					case SDLK_UP:
						d = 1;
						break;
					case SDLK_DOWN:
						d = 3;
						break;
				}
		}
	}
	ct = SDL_GetTicks();
	if(ct > (lt + *speed)){
		if(*score > *finalScore){
			*finalScore = *score;
		}
		DrawText(w, r, score, font,*finalScore);
		DirectionToPosition(d,r,w,x,y,score,finalScore);
		lt = ct;
		CreateGrid(w,r);
		CreatePlayer(w,r,x,y);
		if(*x == *xFood && *y == *yFood){
			*xFood = rand() % GRID_WIDTH;
			*yFood = rand() % GRID_HEIGHT;
			*speed /= 1.1;
			*score = *score + 1000;
		}
		if(d != 5){
			*score = *score + 1;
		}
		CreateFood(w,r,x,y,xFood,yFood);
	}

}

void CreatePlayer(SDL_Window* w, SDL_Renderer* r,int* x, int* y){
	SDL_Rect rect;
	rect.x = (WIDTH/8)+(3*(*x*(WIDTH/GRID_WIDTH))/4);
	rect.y = (HEIGHT/8)+(3*(*y*(HEIGHT/GRID_HEIGHT))/4);
	rect.w = (3*WIDTH/4)/GRID_WIDTH;
	rect.h = (3*HEIGHT/4)/GRID_HEIGHT;
	SDL_SetRenderDrawColor(r,0, 140, 0, 255);
	SDL_RenderFillRect(r, &rect);
	SDL_SetRenderDrawColor(r,0, 255, 0, 255);
	SDL_RenderDrawRect(r, &rect);
	SDL_RenderPresent(r);
	SDL_UpdateWindowSurface(w);
	SDL_RenderPresent(r);
}

void CreateGrid(SDL_Window* w, SDL_Renderer* r){
	SDL_Rect rect;
	rect.x = WIDTH/8;
	rect.y = HEIGHT/8;
	rect.w = 3*WIDTH/4;
	rect.h = 3*HEIGHT/4;
	SDL_SetRenderDrawColor(r, 40, 40, 40, 0);
	SDL_RenderFillRect(r, &rect);
	SDL_SetRenderDrawColor(r, 255, 255, 255,0);
	SDL_RenderDrawRect(r, &rect);
	SDL_RenderPresent(r);
}

void Quit(SDL_Window* w, SDL_Renderer* r,int finalScore){
	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	SDL_Quit();
	printf("Best score : %d\n", finalScore);
	exit(0);
}

void DirectionToPosition(int d,SDL_Renderer* r,SDL_Window* w, int* x, int* y, int* score, int* finalScore){
	if(d == 0){
		if(*x < GRID_WIDTH - 1){
			*x = *x + 1;
		}
		else{
			printf("Final score : %d\n",*score);
			SDL_DestroyRenderer(r);
			SDL_DestroyWindow(w);
			main();
		}
	}
	if(d == 3){
		if(*y < GRID_HEIGHT - 1){
			*y = *y + 1;
		}
		else{
			printf("Final score : %d\n",*score);
			SDL_DestroyRenderer(r);
			SDL_DestroyWindow(w);
			main();
		}
	}
	if(d == 2){
		if(*x > 0){
			*x = *x - 1;
		}else{
			printf("Final score : %d\n",*score);
			SDL_DestroyRenderer(r);
			SDL_DestroyWindow(w);
			main();
		}
	}
	if(d == 1){
		if(*y > 0){
			*y = *y - 1;
		}
		else{
			printf("Final score : %d\n",*score);
			SDL_DestroyRenderer(r);
			SDL_DestroyWindow(w);
			main();
		}
	}
}

void CreateFood(SDL_Window* w, SDL_Renderer* r,int* x, int* y, int* xFood, int* yFood){
	SDL_Rect rect;
	rect.x = (WIDTH/8)+(3*(*xFood*(WIDTH/GRID_WIDTH))/4);
	rect.y = (HEIGHT/8)+(3*(*yFood*(HEIGHT/GRID_HEIGHT))/4);
	rect.w = (3*WIDTH/4)/GRID_WIDTH;
	rect.h = (3*HEIGHT/4)/GRID_HEIGHT;
	SDL_SetRenderDrawColor(r,140, 0, 0, 255);
	SDL_RenderFillRect(r, &rect);
	SDL_SetRenderDrawColor(r,255, 0, 0, 255);
	SDL_RenderDrawRect(r, &rect);
	SDL_RenderPresent(r);
}

void DrawText(SDL_Window* w, SDL_Renderer* r,int* score,TTF_Font* font, int finalScore){
	char scoreString[20];
	SDL_itoa(*score, scoreString,10);
	char BestscoreString[20];
	SDL_itoa(finalScore, BestscoreString,10);
	char scorer[50] = "Score:";
	char finalscorer[50] = "Best Score:";
	strcat(scorer, scoreString);
	strcat(finalscorer, BestscoreString);
	SDL_Surface* text;
	SDL_Surface* besttext;
	SDL_Color color = { 255, 255, 255 };
	text = TTF_RenderText_Solid( font, scorer, color );
	besttext = TTF_RenderText_Solid( font, finalscorer, color );
	SDL_Texture* text_texture;
	SDL_Texture* besttext_texture;
	text_texture = SDL_CreateTextureFromSurface( r, text );
	besttext_texture = SDL_CreateTextureFromSurface( r, besttext );
	SDL_Rect dest = { 20, 20, text->w, text->h };
	SDL_Rect dest2 = { 20, 20, 300,50 };
	SDL_Rect bestdest = { (WIDTH/2)+20, 20, besttext->w, besttext->h };
	SDL_Rect bestdest2 = { (WIDTH/2)+20, 20, 300,50 };
	SDL_SetRenderDrawColor(r,0, 0, 0, 255);
	SDL_RenderFillRect(r, &dest2);
	SDL_RenderFillRect(r, &bestdest2);
	SDL_RenderCopy( r, text_texture,NULL, &dest );
	SDL_RenderCopy( r, besttext_texture,NULL, &bestdest );
}
