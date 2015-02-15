#include "ComboEffect.h"
void showComboEffect(int size,Node* node){
	if(size<5)
		return;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* comboSprite;
	if(size>=10){
		comboSprite = Sprite::create("combo_3.png");
	}else if(size>=7){
		comboSprite = Sprite::create("combo_2.png");
	}else{
		comboSprite = Sprite::create("combo_1.png");
	}

	comboSprite->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	node->addChild(comboSprite);

	Blink* blink = Blink::create(1.0f,5);
	CallFunc* remove = CallFunc::create([=](){comboSprite->removeFromParentAndCleanup(true);});
	Sequence* action = Sequence::create(blink,remove,nullptr);
	comboSprite->runAction(action);
}

void stageClear(Node* node){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* comboSprite;
    
    comboSprite = Sprite::create("stage_clear.png");
   
    
    comboSprite->setPosition(Point(visibleSize.width/2,visibleSize.height/2 + 150));
    node->addChild(comboSprite);
    
    Blink* blink = Blink::create(1.0f,5);
    CallFunc* remove = CallFunc::create([=](){comboSprite->removeFromParentAndCleanup(true);});
    Sequence* action = Sequence::create(blink,remove,nullptr);
    comboSprite->runAction(action);
}

void gameOver(Node* node)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* comboSprite;
    
    comboSprite = Sprite::create("GameOver.png");
    
    
    comboSprite->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    node->addChild(comboSprite);
    
    CCFadeOut* fadeout = CCFadeOut::create(2.0f);
    CallFunc* remove = CallFunc::create([=](){comboSprite->removeFromParentAndCleanup(true);});
    Sequence* action = Sequence::create(fadeout,remove,nullptr);
    comboSprite->runAction(action);
}
