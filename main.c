#include <SDL/SDL.h>
#include "sprite.c"

SDL_Surface TRANS_FUCKING_FORM( SDL_Surface* s ){
	s = SDL_LoadBMP( "assets/zombie.bmp" );
	return *s;
}


int main( int argc, char *argv[] ){

	//Declares the screen surface
	SDL_Surface* screen = NULL;
	//Desclares staddon's face sprite
	struct sprite staddon = make_sprite( "assets/fuckinstaddon.bmp" );
	//This is a very good example of the format any SDL_Rect should conform to
	staddon.pos.x=100;
	staddon.pos.y=100;
	staddon.pos.w=100;
	staddon.pos.h=100;
	//I DON'T KNOW HOW BEST TO IMPLIMENT PROJECTILES YET SO FUCK OFF 
	

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
				else if( e.key.keysym.sym == SDLK_s ){
					staddon.yvel = 1;
				}
				else if( e.key.keysym.sym == SDLK_w ){
					staddon.yvel = -1;
				}
				else if( e.key.keysym.sym == SDLK_a ){
					staddon.xvel = -1;
				}
				else if( e.key.keysym.sym == SDLK_d ){
					staddon.xvel = 1;
				}
				else if( e.key.keysym.sym == SDLK_RIGHT ){
					if( staddon.active_proj==1 ){
						break;
					}
					staddon.active_proj=1;
					staddon.proj = launch_projectile( staddon.proj, 'e', staddon );
				}
				else if( e.key.keysym.sym == SDLK_LEFT ){
					if( staddon.active_proj==1 ){
						break;
					}
					staddon.active_proj=1;
					staddon.proj = launch_projectile( staddon.proj, 'w', staddon );
				}
				else if( e.key.keysym.sym == SDLK_UP ){
					if( staddon.active_proj==1 ){
						break;
					}
					staddon.active_proj=1;
					staddon.proj = launch_projectile( staddon.proj, 'n', staddon );
				}
				else if( e.key.keysym.sym == SDLK_DOWN ){
					if( staddon.active_proj==1 ){
						break;
					}
					staddon.active_proj=1;
					staddon.proj = launch_projectile( staddon.proj, 's', staddon );
				}
				break;
			}
			if( e.type == SDL_KEYUP ){
				if( e.key.keysym.sym == SDLK_s ){
					staddon.yvel=0;
				}
				else if( e.key.keysym.sym == SDLK_w ){
					staddon.yvel=0;
				}
				else if( e.key.keysym.sym == SDLK_a ){
					staddon.xvel=0;
				}
				else if( e.key.keysym.sym == SDLK_d ){
					staddon.xvel=0;
				}
				break;
			}
			
		}


		//RENDERING AREA
		
		if( staddon.active_proj == 1 ){
			if( staddon.proj.lifespan == 0 ){
				staddon.active_proj=0;
			}
			else if( staddon.proj.lifespan > 0 ){
				staddon.proj = propel( staddon.proj );
			}
		}

		staddon = update_pos( staddon );


//SDL_FillRect() makes sure the screen gets cleared before you move shit around, you fucking idiot
		SDL_FillRect( screen, NULL, ((0,0,0)) );
		
		if( staddon.active_proj == 1 ){
			if( staddon.proj.lifespan>0 ){
				SDL_BlitSurface( staddon.proj.Sprite, NULL, screen, &staddon.proj.pos );
			}
		}
		
		SDL_BlitSurface( staddon.Sprite, NULL, screen, &staddon.pos );
		SDL_Flip( screen );
	}	
	SDL_Quit();
	return 0;
}
