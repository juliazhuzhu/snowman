#ifndef _TOPMENU_H_
#define _TOPMENU_H_
#include "cocos2d.h"
#include "GameLayer.h"
#include "ShowNumberNode.h"

using namespace cocos2d;
class GameLayer;
class TopMenu : public Node{
public:
    
	virtual bool init(GameLayer* layer);
    static TopMenu* create(GameLayer* layer);
	void refresh();
    void bomb();
    void paint();
    void rainbow();
    void stopBomb();
    void coin();
    void bombIconFlash();
    void paintIconFlash();
    void stopPaint();
    void release();
    //CREATE_FUNC(TopMenu);
private:
	Label* highestScore_label;
	Label* level;
    ShowNumberNode* level_number;
	ShowNumberNode* targetScore;
	ShowNumberNode* curScore;
    ShowNumberNode* curCoin;
    CCSprite*   m_sprite_bomb;
    CCSprite*   m_sprite_paint;
    CCSprite*   m_sprite_rainbow;
    ShowNumberNode * highestScore;
    GameLayer*  m_layer;
    void iconFlash(CCSprite* iconSprite);
    void stopIconFlash(CCSprite* iconSprite);
};
#endif