#include "MenuLayer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Audio.h"
#include "MyKeyboardDelegate.h"
#include "PopupLayerExt.h"
#include "DialogLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "PluginChannel.h"
#endif

bool MenuLayer::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*��ʼ������*/
	Sprite* background = Sprite::create("bg_menuscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	Sprite* title = Sprite::create("title_2.png");
#else
    Sprite* title = Sprite::create("title.png");
#endif
    title->setPosition(visibleSize.width/2,visibleSize.height/2+200);
    this->addChild(title,-1);
	
    ParticleSnow *pParticleSnow = ParticleSnow::create();
    
    this->addChild(pParticleSnow);
	/*��ʼ���˵�*/
	MenuItemImage* startBtn = MenuItemImage::create(
		"menu_start.png","menu_start.png",CC_CALLBACK_0(MenuLayer::startGame,this)
		);
	Menu* menu = Menu::create(startBtn,NULL);
	menu->alignItemsVertically();
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu);
    
    MenuItemImage* continueBtn = MenuItemImage::create(
                                                    "menu_continue.png","menu_continue.png",CC_CALLBACK_0(MenuLayer::continueGame,this)
                                                    );
    
    Menu* continue_menu = Menu::create(continueBtn,NULL);
    continue_menu->alignItemsVertically();
    continue_menu->setPosition(visibleSize.width/2,visibleSize.height/2-70);
    this->addChild(continue_menu);
    this->setKeypadEnabled(true);
    this->setKeyboardEnabled(true);
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(MenuLayer::onKeyReleased, this);
        //schedule(schedule_selector(HelloWorld::logic), 2.0f);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    bReady = false;



    this->scheduleUpdate();
    
	return true;
}

void MenuLayer::continueGame(){
    CCLOG("CONTINUE!");
    GAMEDATA::getInstance()->continueFromLastLevel();

/*#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (AgentManager::getInstance()->getChannelId() != "1001")//mm
    {
        CCLOG("PluginChannel Login");
        bReady = true;
        PluginChannel::getInstance()->login();//调用渠道登陆
     }
     else
       Director::getInstance()->replaceScene(GameScene::create());
#else*/
    Director::getInstance()->replaceScene(GameScene::create());
//#endif
    
}



void MenuLayer::startGameCallback(cocos2d::Node *pNode, void* pData){
    CCLog("button call back. tag: %d", pNode->getTag());
    if (pNode->getTag() == 1)
    {
        GAMEDATA::getInstance()->init();
/*#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if (AgentManager::getInstance()->getChannelId() != "1001")//mm
        {
        	CCLOG("PluginChannel Login");
        	bReady = true;
        	PluginChannel::getInstance()->login();//调用渠道登陆
        }
        else
        	Director::getInstance()->replaceScene(GameScene::create());
#else*/
        Director::getInstance()->replaceScene(GameScene::create());
//#endif
    }
    
}

void MenuLayer::startGame(){
	CCLOG("START!");

    if (UserDefault::getInstance()->getIntegerForKey("curLevel",0) > 0)
    {
        DialogLayer* dlg = DialogLayer::create();
        this->addChild(dlg);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        PopupLayerExt* pl = PopupLayerExt::create("msgbox.png");
        pl->setPosition(visibleSize.width/2,visibleSize.height/2);
        pl->setCallbackFunc(this, callfuncND_selector(MenuLayer::startGameCallback),NULL);
        pl->setTitle("提示",24);
        pl->setContentText("重新开始?之前的游戏进度会被清除哦!");
        // 添加按钮，设置图片，文字，tag 信息
        pl->addButton("ok_but.png", "ok_but.png", "", 1);
        pl->addButton("cancel_but.png", "cancel_but.png", "", 2);
        
        pl->setBackgroundLayer(dlg);
        CCLog("current opacity %d",this->getOpacity());
        //pl->setAnchorPoint(Vec2(0.5,0.5));
        
        // 添加到当前层
        this->addChild(pl);
        return;
    }
    GAMEDATA::getInstance()->init();
/*#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLOG("PluginChannel channel Id:%s",AgentManager::getInstance()->getChannelId().c_str());
    if (AgentManager::getInstance()->getChannelId() != "1001")//mm
    {
        CCLOG("PluginChannel Login");
        bReady = true;
        PluginChannel::getInstance()->login();//调用渠道登陆
    }
    else
    	Director::getInstance()->replaceScene(GameScene::create());
#else*/
	Director::getInstance()->replaceScene(GameScene::create());
//#endif
}

void MenuLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	CCLOG("key pressed!");
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
    {
        MyKeyboardDelegate::getInstance()->keyBackClicked(this);
    }
}

void MenuLayer::update(float dt)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
   /* if(PluginChannel::getInstance()->isLogined()&&bReady)//判断登陆状态
    {
        Director::getInstance()->replaceScene(GameScene::create());
    }*/
#endif
}



