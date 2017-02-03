#include <SDL/SDL.h>
#include "sprite.c"

SDL_Surface TRANS_FUCKING_FORM( SDL_Surface* s ){
	s = SDL_LoadBMP( "assets/zombie.bmp" );
	return *s;
}


int main( int argc, char *argv[] ){

	//Declares the screen surface
	SDL_Surface* screen = NULL;
	


	//'entities' is a list of sprites that should represent every 'living' thing on the screen.
	//I'm hoping we'll never need more than 100 entities to be on the screen at a time
	struct sprite entities[100];
	//active_entities will probably maybe help the performance of the rendering loop a little
	int active_entities=0;
	
	
	//the player entity cell will always be 0
	//Also, entity creation should conform to the below format.  Assign the new entity to the cell
	//active_entities, and then increase active_entities.
	entities[active_entities] = make_sprite( "assets/fuckinstaddon.bmp" );
	active_entities++;
	entities[active_entities] = make_sprite( "assets/zombie.bmp" );


	//This one's gotta be done at the start of each program (as far as I can tell)
	SDL_Init( SDL_INIT_EVERYTHING );
	
	
	//SDL_SetVideoMode takes coords, bits/pixel, SDL_SWSURFACE is 'software surface', as opposed to hardware surface
	screen = SDL_SetVideoMode( 600,600,32,SDL_SWSURFACE );
	

	//initial coords fo shiz
	entities[0].pos.x = 10;
	entities[0].pos.y = 10;
	entities[0].pos.w = 100;
	entities[0].pos.h = 100;

	entities[1].pos.x = 400;
	entities[1].pos.y = 400;
	entities[1].pos.w = 56;
	entities[1].pos.h = 56;

	//This will put the player Sprite surface onto the screen surface.   
	SDL_BlitSurface( entities[0].Sprite, NULL, screen, &entities[0].pos );
	SDL_BlitSurface( entities[1].Sprite, NULL, screen, &entities[1].pos );

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
					entities[0].yvel = 10;
				}
				else if( e.key.keysym.sym == SDLK_w ){
					entities[0].yvel = -10;
				}
				else if( e.key.keysym.sym == SDLK_a ){
					entities[0].xvel = -10;
				}
				else if( e.key.keysym.sym == SDLK_d ){
					entities[0].xvel = 10;
				}
				else if( e.key.keysym.sym == SDLK_RIGHT ){
					if( entities[0].active_proj==1 ){
						break;
					}
					entities[0].active_proj=1;
					entities[0].proj = launch_projectile( entities[0].proj, 'e', entities[0] );
				}
				else if( e.key.keysym.sym == SDLK_LEFT ){
					if( entities[0].active_proj==1 ){
						break;
					}
					entities[0].active_proj=1;
					entities[0].proj = launch_projectile( entities[0].proj, 'w', entities[0] );
				}
				else if( e.key.keysym.sym == SDLK_UP ){
					if( entities[0].active_proj==1 ){
						break;
					}
					entities[0].active_proj=1;
					entities[0].proj = launch_projectile( entities[0].proj, 'n', entities[0] );
				}
				else if( e.key.keysym.sym == SDLK_DOWN ){
					if( entities[0].active_proj==1 ){
						break;
					}
					entities[0].active_proj=1;
					entities[0].proj = launch_projectile( entities[0].proj, 's', entities[0] );
				}
				break;
			}
			if( e.type == SDL_KEYUP ){
				if( e.key.keysym.sym == SDLK_s ){
					entities[0].yvel=0;
				}
				else if( e.key.keysym.sym == SDLK_w ){
					entities[0].yvel=0;
				}
				else if( e.key.keysym.sym == SDLK_a ){
					entities[0].xvel=0;
				}
				else if( e.key.keysym.sym == SDLK_d ){
					entities[0].xvel=0;
				}
				break;
			}
			
		}

		//Basic AI 
		if( entities[1].pos.x > entities[0].pos.x ){
			entities[1].xvel = -1;
		}
		if( entities[1].pos.x < entities[0].pos.x ){
			entities[1].xvel = 1;
		}
		if( entities[1].pos.y > entities[0].pos.y ){
			entities[1].yvel = -1;
		}
		if( entities[1].pos.y < entities[0].pos.y ){
			entities[1].yvel = 1;
		}

		//RENDERING AREA
		
		if( entities[0].active_proj == 1 ){
			if( entities[0].proj.lifespan == 0 ){
				entities[0].active_proj=0;
			}
			else if( entities[0].proj.lifespan > 0 ){
				entities[0].proj = propel( entities[0].proj );
			}
		}

		entities[0] = update_pos( entities[0] );
		entities[1] = update_pos( entities[1] );
		
		//check collisions
		for( int i=1;i<active_entities+1;i++ ){
			if( entities[0].proj.lifespan>0 ){
				if( collide_check( entities[0].proj.pos, entities[i].pos ) == 1 ){
					entities[i].alive=0;
					active_entities--;
				}
			}
			if( collide_check( entities[0].pos, entities[i].pos ) == 1 ){
				entities[0].alive=0;
			}
		}
//SDL_FillRect() makes sure the screen gets cleared before you move shit around, you fucking idiot
		SDL_FillRect( screen, NULL, ((0,0,0)) );
		

		if( entities[0].active_proj == 1 ){
			if( entities[0].proj.lifespan>0 ){
				SDL_BlitSurface( entities[0].proj.Sprite, NULL, screen, &entities[0].proj.pos );
			}
		}
		for( int i=0;i<active_entities+1;i++ ){
			if( entities[i].alive != 0 ){
				SDL_BlitSurface( entities[i].Sprite, NULL, screen, &entities[i].pos );
			}
			else{
				i--;
			}
		}
		SDL_Flip( screen );
		SDL_Delay(30);
	}	
	SDL_Quit();
	return 0;
}
