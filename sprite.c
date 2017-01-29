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
	char dir;
	int xvel;
	int yvel;
	int lifespan;
};
struct sprite {
	SDL_Surface* Sprite;
	SDL_Rect pos;
	struct projectile proj;
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
	new_sprite.proj.Sprite = SDL_LoadBMP( "assets/zombie.bmp" );
	new_sprite.proj.dir = 'e';
	new_sprite.proj.lifespan=0;
	new_sprite.proj.pos.x=100;
	new_sprite.proj.pos.y=100;
	new_sprite.proj.pos.h=56;
	new_sprite.proj.pos.w=56;
	new_sprite.proj.xvel=2;
	new_sprite.proj.yvel=2;
	return new_sprite;
}

//Movement-related functions
struct sprite update_pos( struct sprite spr ){
	spr.pos.y+=spr.yvel;
	spr.pos.x+=spr.xvel;
	return spr;
}
//reinits the projectile to the sprite's position
struct projectile launch_projectile( struct projectile prj, char direction, struct sprite psource ){
	prj.Sprite = SDL_LoadBMP( "assets/zombie.bmp" );
	prj.pos.x=psource.pos.x;
	prj.pos.y=psource.pos.y;
	prj.dir=direction;
	prj.lifespan=400;
	return prj;
}
struct projectile propel( struct projectile prj){
	if( prj.dir=='e' ){
		prj.pos.x+=prj.xvel;
	}
	else if( prj.dir=='w' ){
		prj.pos.x-=prj.xvel;
	}
	else if( prj.dir=='n' ){
		prj.pos.y-=prj.yvel;
	}
	else if( prj.dir=='s' ){
		prj.pos.y+=prj.yvel;
	}
	prj.lifespan--;
	return prj;
}
