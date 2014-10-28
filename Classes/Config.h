#ifndef _CONFIG_H_
#define _CONFIG_H_

#define TYPE_BRICK   1		/*砖块*/

#define TYPE_HERO    2		/*英雄-我*/
#define TYPE_MONSTER 4		/*怪物-敌*/
#define TYPE_ANIMAL	 8		/*生物-中立的*/

#define TYPE_PRIZE   16		/*战利品*/
#define TYPE_COIN	 32		/*金币*/
#define TYPE_WEAPON  64		/*子弹等武器*/
#define TYPE_ARTICLE	 128	/*可交互的物体*/

/*
#define TYPE_ANIMAL	 256
#define TYPE_ANIMAL	 512
#define TYPE_ANIMAL	 1024
#define TYPE_ANIMAL	 2048
#define TYPE_ANIMAL	 4096
#define TYPE_ANIMAL	 8192
#define TYPE_ANIMAL	 16384
*/
#define TYPE_NOTHING	 32768

/*朝向*/
enum DIR
{
	DIR_LEFT,
	DIR_RIGHT
};

enum MOVE
{
	MOVE_STOP,
	MOVE_LEFT,
	MOVE_RIGHT,
};

#endif

