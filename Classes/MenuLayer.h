#ifndef _MENULAYER_H_
#define _MENULAYER_H_
#include "cocos2d.h"
using namespace cocos2d;
class MenuLayer : public Layer{
public:
	virtual bool init();

	void startGame();
    void continueGame();
	CREATE_FUNC(MenuLayer);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void update(float dt);
    
protected:
    void startGameCallback(cocos2d::Node *pNode, void* pData);
    
private:
    
    bool bReady;
};
#endif
