#ifndef _HUD_LAYER_H_
#define _HUD_LAYER_H_

#include "cocos2d.h"

class HudLayer : public cocos2d::Layer
{
protected:
	cocos2d::LabelAtlas* plabelAtlas;
public:
	virtual bool init() override;

	CREATE_FUNC(HudLayer);

	void replaceHpHud();
	void replaceCoinHud();
};
#endif