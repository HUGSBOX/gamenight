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
	SDL_Rect collider;
	struct projectile proj;
	int xvel;
	int yvel;
	int active_proj;
	int alive;
	int respawn;
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
	new_sprite.alive=1;
	new_sprite.respawn=0;
	new_sprite.active_proj=0;
	new_sprite.proj.Sprite = SDL_LoadBMP( "assets/dot.bmp" );
	new_sprite.proj.dir = 'e';
	new_sprite.proj.lifespan=0;
	new_sprite.proj.pos.x=100;
	new_sprite.proj.pos.y=100;
	new_sprite.proj.pos.h=10;
	new_sprite.proj.pos.w=10;
	new_sprite.proj.xvel=20;
	new_sprite.proj.yvel=20;
	new_sprite.collider=new_sprite.pos;
	SDL_SetColorKey( new_sprite.Sprite, SDL_TRUE, ((255,0,255)) );
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
	prj.Sprite = SDL_LoadBMP( "assets/dot.bmp" );
	prj.pos.x=psource.pos.x + (psource.pos.w / 2);
	prj.pos.y=psource.pos.y + (psource.pos.h / 2);
	prj.pos.w=10;
	prj.pos.h=10;
	prj.dir=direction;
	prj.lifespan=10;
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
int collide_check( SDL_Rect rect1, SDL_Rect rect2 ){
	int bottomA = rect1.y + rect1.h;
	int bottomB = rect2.y + rect2.h;
	int rightSideA = rect1.x + rect1.w;
	int rightSideB = rect2.x + rect2.w;
	int leftSideA = rect1.x;
	int leftSideB = rect2.x;;
	int topA = rect1.y;
	int topB = rect2.y;;
	if( rect2.x >= leftSideA && rect2.x <= rightSideA ){
		if( rect2.y >= topA && rect2.y <= bottomA ){
			return 1;
		}
	}
	if( rect1.x >= leftSideB && rect1.x <= rightSideB ){
		if( rect1.y >= topB && rect1.y <= bottomB ){
			return 1;
		}
	}
	if( rightSideA >= leftSideB && rightSideB >= leftSideA ){
		if( topA <= bottomB && topB <= bottomA ){
			return 1;
		}
	}
	return 0;
}
struct sprite update_collider_x( struct sprite spr ){
	spr.collider.x+=spr.xvel;
	return spr;
}
struct sprite update_collider_y( struct sprite spr ){
	spr.collider.y+=spr.yvel;
	return spr;
}
