#include <SDL/SDL.h>

//This file will create a more unified programming interface for sprites
//It's fairly simple - the surface, rect, and all other attributes associated 
//with your sprite will be in the same place.  Functions for sprite manipulation
//will also live here.


//Every sprite's attributes should live here.
//This (eventually) means: 
// * HP
// * Inventory 
// * Experience
// * Etc etc etc
struct projectile{
	SDL_Surface* Sprite;
	SDL_Rect pos;
	int vel;
	int lifespan;
};
struct sprite {
	SDL_Surface* Sprite;
	SDL_Rect pos;
	struct projectile proj[5];
	int xvel;
	int yvel;
	int active_proj;
		
};

//Sprite constructor
//Use this function for very easy sprite creation.
//Hand it the path to the bmp (relative to the source 
//dir) and assign the value it returns to your sprite
//struct. 
struct sprite make_sprite( char* path_to_image ){
	struct sprite new_sprite;
	new_sprite.Sprite = SDL_LoadBMP( path_to_image );
	new_sprite.pos.x=100;
	new_sprite.pos.y=100;
	new_sprite.pos.h=100;
	new_sprite.pos.w=100;
	new_sprite.xvel=0;
	new_sprite.yvel=0;
	new_sprite.active_proj=0;
	for( int i=0;i<5;i++){
		new_sprite.proj[i].Sprite = SDL_LoadBMP( "assets/zombie.bmp" );
		new_sprite.proj[i].pos.x=0;
		new_sprite.proj[i].pos.y=0;
		new_sprite.proj[i].lifespan=0;
		new_sprite.proj[i].vel=2;
	}
	return new_sprite;
}
//Projectile constructor.  Works much the same as the sprite constructor, 
//except that it takes a second param - which should be the sprite launching 
//the projectile.  Projectiles are handled slightly differenly because they 
//have such short lifespans.
struct projectile make_projectile( char* path_to_image, struct sprite psource ){
	struct projectile new_projectile;
	new_projectile.Sprite = SDL_LoadBMP( path_to_image );
	new_projectile.pos.h=56;
	new_projectile.pos.w=56;
	new_projectile.pos.x=psource.pos.x;
	new_projectile.pos.y=psource.pos.y;
	new_projectile.vel=2;
	new_projectile.lifespan=500;
	return new_projectile;
}
//Projectile destructor 
void destroy_projectile( struct projectile proj ){
	SDL_FreeSurface ( proj.Sprite );
}

//Movement-related functions
struct sprite update_pos( struct sprite spr ){
	spr.pos.y+=spr.yvel;
	spr.pos.x+=spr.xvel;
	return spr;
}
//reinits the projectile to the sprite's position
struct projectile launch_projectile( struct projectile prj, struct sprite psource ){
	prj = make_projectile( "assets/zombie.bmp", psource );
	return prj;
}
struct projectile propel( struct projectile prj ){
	prj.pos.x+=prj.vel;
	prj.lifespan--;
	return prj;
}
