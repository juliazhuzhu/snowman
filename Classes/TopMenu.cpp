#include "TopMenu.h"
#include "Chinese.h"
#include "GameData.h"
#include "GameLayer.h"
//#include "ShowNumberNode.h"

TopMenu* TopMenu::create(GameLayer* layer){
    TopMenu* ret = new TopMenu();
    if(ret && ret->init(layer)){
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool TopMenu::init(GameLayer* layer){
	if(!Node::init()){
		return false;
	}
    int fontSize = 30;
	Size visibleSize = Director::getInstance()->getVisibleSize();
    
    int first_row_height = 30;
    highestScore = ShowNumberNode::CreateShowNumberNode("number.png", 9990000, 22, 30 );
    //int testnum = 200000;
    
    highestScore->setPosition(visibleSize.width/2+40,visibleSize.height - first_row_height);
    this->addChild(highestScore,0,0);
    highestScore->f_ShowNumber(GAMEDATA::getInstance()->getHistoryScore());

    
	highestScore_label = Label::create(
		ChineseWord("highestScore") ,
		"Verdana-Bold",fontSize
	);
	highestScore_label->setPosition(70,visibleSize.height - first_row_height);
    highestScore_label->setColor(Color3B::YELLOW);
	this->addChild(highestScore_label);
     
    int second_row_height = 85;
	level = Label::create(
		ChineseWord("guanqia") +":"+ cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextLevel())->_string,
		"Verdana-Bold",fontSize
	);
    level->setColor(Color3B::YELLOW);
	level->setPosition(50,visibleSize.height-second_row_height);
	this->addChild(level);
    
    level_number = ShowNumberNode::CreateShowNumberNode("number.png", 200, 22, 30 );
    level_number->setPosition(50+70,visibleSize.height-second_row_height);
    this->addChild(level_number,0,0);
    
    targetScore = ShowNumberNode::CreateShowNumberNode("number.png", 9990000, 22, 30 );
	
	targetScore->setPosition(visibleSize.width/2 + 40,visibleSize.height - second_row_height);
	this->addChild(targetScore,0,0);

    
    curCoin = ShowNumberNode::CreateShowNumberNode("number.png", 2000, 22, 30 );
    curCoin->setPosition(visibleSize.width/2 + 170,visibleSize.height - second_row_height);
    this->addChild(curCoin);
    
    auto diamond = CCSprite::create("diamond.png");
    diamond->setScale(0.8);
    MenuItemSprite* coinBtn = MenuItemSprite::create(diamond,diamond,CC_CALLBACK_0(TopMenu::coin,this)
                                                     );
    Menu* menuCoin = Menu::create(coinBtn,NULL);
    //menu->alignItemsVertically();
    menuCoin->setPosition(visibleSize.width/2+220,visibleSize.height-second_row_height);
    this->addChild(menuCoin);

    int thrid_row_height = 135;
    //beow is the second row
	
    curScore = ShowNumberNode::CreateShowNumberNode("number.png", 9990000, 22, 30 );
	curScore->setPosition(visibleSize.width/2 + 40 ,visibleSize.height - thrid_row_height);
	this->addChild(curScore,0,0);
    curScore->f_ShowNumber(0);
    
    
    m_sprite_bomb = CCSprite::create("Props_Bomb.png");
    //m_sprite_bomb->setScale(0.6);
    MenuItemSprite* bombBtn = MenuItemSprite::create(m_sprite_bomb,m_sprite_bomb,CC_CALLBACK_0(TopMenu::bomb,this)
                                        );
    Menu* menu = Menu::create(bombBtn,NULL);
    //menu->alignItemsVertically();
    menu->setPosition(visibleSize.width/2+110,visibleSize.height-thrid_row_height);
    this->addChild(menu);
    
    m_sprite_paint = CCSprite::create("Props_Paint.png");
    //m_sprite_paint->setScale(0.6);
    MenuItemSprite* paintBtn = MenuItemSprite::create(m_sprite_paint,m_sprite_paint,CC_CALLBACK_0(TopMenu::paint,this));
                                                     //);
    Menu* menu_paint = Menu::create(paintBtn,NULL);
    menu->alignItemsVertically();
    menu_paint->setPosition(visibleSize.width/2+160,visibleSize.height-thrid_row_height);
    this->addChild(menu_paint);
    
    m_sprite_rainbow = CCSprite::create("Props_Rainbow.png");
    //m_sprite_rainbow->setScale(0.6);
    MenuItemSprite* rainbowBtn = MenuItemSprite::create(m_sprite_rainbow,m_sprite_rainbow,CC_CALLBACK_0(TopMenu::rainbow,this)
                                                     );
    Menu* menu_rainbow = Menu::create(rainbowBtn,NULL);
    //menu->alignItemsVertically();
    menu_rainbow->setPosition(visibleSize.width/2+210,visibleSize.height-thrid_row_height);
    this->addChild(menu_rainbow);
    
    
    
    level_number->retain();
    targetScore->retain();
    curScore->retain();
    curCoin->retain();

    m_layer = layer;
    
    
	return true;
}

void TopMenu::release()
{
    level_number->release();
    targetScore->release();
    curScore->release();
    curCoin->release();
}

void TopMenu::refresh(){
	//char buf[64];
	//sprintf(buf,"%d",GAMEDATA::getInstance()->getCurScore());
	//curScore->setString(buf);
    curScore->f_ShowNumber(GAMEDATA::getInstance()->getCurScore());
    string history = ChineseWord("highestScore");// + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getHistoryScore())->_string + ChineseWord("fen");
    highestScore_label->setString(history);
    highestScore->f_ShowNumber(GAMEDATA::getInstance()->getHistoryScore());
	

    string guanqia = ChineseWord("guanqia");// + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextLevel())->_string;
	level->setString(guanqia);
    level_number->f_ShowNumber(GAMEDATA::getInstance()->getNextLevel());

	//string target = ChineseWord("mubiao") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextScore())->_string + ChineseWord("fen");
	//targetScore->setString(target);
    targetScore->f_ShowNumber(GAMEDATA::getInstance()->getNextScore());
    
    string coin = cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getCurentCoin())->_string;
    //curCoin->setString(coin);
    curCoin->f_ShowNumber(GAMEDATA::getInstance()->getCurentCoin());
}

void  TopMenu::iconFlash(CCSprite* iconSprite)
{
    CCSequence* s1 = CCSequence::create(CCScaleTo::create(0.6,0.8),CCScaleTo::create(0.6,1),NULL);
    CCRepeatForever* rep = CCRepeatForever::create(s1);
    iconSprite->runAction(rep);
}

void TopMenu::stopIconFlash(CCSprite* iconSprite)
{
    iconSprite->stopAllActions();
    iconSprite->setScale(1);
}

void TopMenu::bombIconFlash()
{
    iconFlash(m_sprite_bomb);
}

void TopMenu::bomb()
{
    m_layer->bomb();

}

void TopMenu::stopBomb()
{
    stopIconFlash(m_sprite_bomb);
}

void TopMenu::paint()
{
    m_layer->OnBtnReplaceStar();
}

void TopMenu::paintIconFlash()
{
    iconFlash(m_sprite_paint);
}

void TopMenu::stopPaint()
{
    stopIconFlash(m_sprite_paint);
}
                  
void TopMenu::coin(){
    
}

void TopMenu::rainbow()
{
    m_layer->rainbow();
    //CCRepeatForever
    //m_sprite_rainbow
}
