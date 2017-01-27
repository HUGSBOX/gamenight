#include <SDL/SDL.h>
#include "sprite.c"

SDL_Surface TRANS_FUCKING_FORM( SDL_Surface* s ){
	s = SDL_LoadBMP( "assets/zombie.bmp" );
	return *s;
}


int main( int argc, char *argv[] ){
	int active_proj = 0;
	//Declares the screen surface
	SDL_Surface* screen = NULL;
	//Desclares staddon's face surface 
	struct sprite staddon = make_sprite( "assets/fuckinstaddon.bmp" );
	//This is a very good example of the format any SDL_Rect should conform to
	staddon.pos.x=100;
	staddon.pos.y=100;
	staddon.pos.w=100;
	staddon.pos.h=100;
	//I DON'T KNOW HOW BEST TO IMPLIMENT PROJECTILES YET SO FUCK OFF 
	struct projectile proj;

	//This one's gotta be done at the start of each program (as far as I can tell)
	SDL_Init( SDL_INIT_EVERYTHING );
	
	
//SDL_SetVideoMode takes coords, bits/pixel, SDL_SWSURFACE is 'software surface', as opposed to hardware surface
	screen = SDL_SetVideoMode( 600,600,32,SDL_SWSURFACE );


	//This will put the 'staddon.Sprite' surface onto the 'screen' surface.   
	SDL_BlitSurface( staddon.Sprite, NULL, screen, NULL );

	//This is essentially what updates the screen surface and puts it onto the actual screen
	SDL_Flip( screen );

	int run = 1;

	//e will be the event poll
	SDL_Event e;

	while( run == 1){//mainloop
		while( SDL_PollEvent( &e ) != 0 ){//eventloop
			if( e.type == SDL_QUIT ){
				run=0;
			}
			if( e.type == SDL_KEYDOWN ){
				if( e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q ){
					run=0;
				}
				else if( e.key.keysym.sym == SDLK_DOWN ){
					staddon.yvel = 1;
				}
				else if( e.key.keysym.sym == SDLK_UP ){
					staddon.yvel = -1;
				}
				else if( e.key.keysym.sym == SDLK_LEFT ){
					staddon.xvel = -1;
				}
				else if( e.key.keysym.sym == SDLK_RIGHT ){
					staddon.xvel = 1;
				}
				else if( e.key.keysym.sym == SDLK_SPACE ){
					proj = make_projectile( "assets/zombie.bmp", staddon );
					active_proj = 1;
				}
				break;
			}

			if( e.type == SDL_KEYUP ){
				if( e.key.keysym.sym == SDLK_DOWN ){
					staddon.yvel=0;
				}
				if( e.key.keysym.sym == SDLK_UP ){
					staddon.yvel=0;
				}
				if( e.key.keysym.sym == SDLK_RIGHT ){
					staddon.xvel=0;
				}
				if( e.key.keysym.sym == SDLK_LEFT ){
					staddon.xvel=0;
				}
				break;
			}
		}


		//RENDERING AREA
		
		if( active_proj != 0 ){
			if( proj.lifespan == 0 ){
				active_proj = 0;
				destroy_projectile( proj );
			}
			else if( proj.lifespan >= 0 ){
				proj = propel( proj );
			}

		}

		staddon = update_pos( staddon );


//SDL_FillRect() makes sure the screen gets cleared before you move shit around, you fucking idiot
		SDL_FillRect( screen, NULL, ((0,0,0)) );
		if( active_proj != 0 ){
			SDL_BlitSurface( proj.Sprite, NULL, screen, &proj.pos );
		}
		SDL_BlitSurface( staddon.Sprite, NULL, screen, &staddon.pos );
		SDL_Flip( screen );
	}
	SDL_Quit();
	return 0;
}
