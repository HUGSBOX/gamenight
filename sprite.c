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
struct sprite {
	SDL_Surface* Sprite;
	SDL_Rect pos;
	int xvel;
	int yvel;
	
};
struct projectile {
	SDL_Surface* Sprite;
	SDL_Rect pos;
	int xvel;
	int yvel;
	int lifespan;//this describes how many loops the projectile will live for 
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
	new_projectile.xvel=2;
	new_projectile.yvel=0;
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
struct projectile propel( struct projectile prj ){
	prj.pos.y+=prj.yvel;
	prj.pos.x+=prj.xvel;
	prj.lifespan--;
	return prj;
}
