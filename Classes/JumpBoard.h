#ifndef _JUMP_BOARD_H_
#define _JUMP_BOARD_H_

#include "GameObject.h"

class JumpBoard : public GameObject
{
public:
	virtual bool init(float x, float y, float width, float height) override;

	CREATE_FUNC_4(JumpBoard, float, float, float, float);

	virtual void BeginContact(GameObject* other, b2Contact* contact);

};

#endif