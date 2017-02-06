//Game Night RPG
//Code:
//Will Cannon <williamcannon1996@gmail.com>
//Justice Johnstone 
//Graphics:
//Liam Staddon

#include <SDL/SDL.h>
#include "sprite.c"

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
	for( int i=1;i<20;i++ ){
		entities[active_entities] = make_sprite( "assets/zombie.bmp" );
		active_entities++;
	}


	//This one's gotta be done at the start of each program (as far as I can tell)
	SDL_Init( SDL_INIT_EVERYTHING );
	
	
	//SDL_SetVideoMode takes coords, bits/pixel, SDL_SWSURFACE is 'software surface', as opposed to hardware surface
	screen = SDL_SetVideoMode( 1250,700,32,SDL_SWSURFACE );
	

	//initial coords fo shiz
	entities[0].pos.x = 500;
	entities[0].pos.y = 10;
	entities[0].pos.w = 50;
	entities[0].pos.h = 50;

	for( int i=1;i<20;i++ ){
		entities[i].pos.w=50;
		entities[i].pos.h=50;
		entities[i].pos.x=30*i;
		entities[i].pos.y=70*i;
		entities[i].alive=2;
	}

	SDL_SetColorKey( screen, SDL_TRUE, ((255,0,255)) );

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
		//RENDERING AREA
		SDL_FillRect( screen, NULL, (255, 255, 255) );//never forget this
		//Basic AI 
		for( int i=1;i<active_entities;i++ ){
			if( entities[i].alive!=0 ){
				if( entities[i].pos.x > entities[0].pos.x ){
					entities[i].xvel = -3;
				}
				if( entities[i].pos.x < entities[0].pos.x ){
					entities[i].xvel = 3;
				}
				if( entities[i].pos.y > entities[0].pos.y ){
					entities[i].yvel = -3;
				}
				if( entities[i].pos.y < entities[0].pos.y ){
					entities[i].yvel = 3;
				}
				entities[i] = update_collider_x( entities[i] );
				for( int n=1;n<active_entities;n++ ){
					if( entities[n].alive!=0 ){
						if( collide_check( entities[i].collider, entities[n].pos ) == 1 && i!=n ){
							entities[i].collider=entities[i].pos;
							entities[i].xvel=0;
						}
					}
				}
				entities[i] = update_collider_y( entities[i] );
				for( int n=1;n<active_entities;n++ ){
					if( entities[n].alive!=0 ){
						if( collide_check( entities[i].collider, entities[n].pos ) == 1 && i!=n ){
							entities[i].collider=entities[i].pos;
							entities[i].yvel=0;
						}
					}
				}
				entities[i] = update_pos( entities[i] );
				SDL_BlitSurface( entities[i].Sprite, NULL, screen, &entities[i].pos );
			}
		}
		
		if( entities[0].alive!=0 ){
			if( entities[0].active_proj == 1 ){
				if( entities[0].proj.lifespan == 0 ){
					entities[0].active_proj=0;
				}
				else if( entities[0].proj.lifespan > 0 ){
					entities[0].proj = propel( entities[0].proj );
					SDL_BlitSurface( entities[0].proj.Sprite, NULL, screen, &entities[0].proj.pos );
				}
			}
		}
		if( entities[0].alive!=0 ){
			entities[0] = update_pos( entities[0] );
		}
		if( entities[0].alive!=0 ){
			SDL_BlitSurface( entities[0].Sprite, NULL, screen, &entities[0].pos );
		}
		//check collisions
		for( int i=1;i<active_entities;i++ ){
			if( entities[i].alive!=0 ){	
				if( entities[0].proj.lifespan>0 ){
					if( collide_check( entities[0].proj.pos, entities[i].pos ) == 1 ){
						entities[i].alive--;
						entities[0].proj.lifespan=0;
					}
				}
				if( collide_check( entities[i].pos, entities[0].pos ) == 1 ){
					entities[0].alive=0;
				}
			}
		}
		
		if( entities[0].alive==0 ){
			entities[0].respawn++;
			if( entities[0].respawn==100 ){
				entities[0].alive=1;
				entities[0].pos.x=10;
				entities[0].pos.y=10;
				entities[0].respawn=0;
			}
		}
		SDL_Flip( screen );
		SDL_Delay(30);
	}
	SDL_Quit();
	return 0;
}
