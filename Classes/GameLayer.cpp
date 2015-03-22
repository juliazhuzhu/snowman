#include "GameLayer.h"
#include "FloatWord.h"
#include "GameData.h"
#include "Chinese.h"
#include "StarMatrix.h"
#include "MenuScene.h"
#include "Audio.h"
#include<math.h>
#include<stdio.h>
#include "ComboEffect.h"
#include "TopMenu.h"
#include "MyKeyboardDelegate.h"
#include "PopupLayer.h"
#include "PopupLayerExt.h"
#include "DialogLayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "SFGameNativeInterface.h"
#else
#include "Cocos2dxStore.h"
#include "DiamondAssets.h"

#endif

//支付回调类
class SFNativeIPayResulBackImp : public SFNativeIPayResulBack
{
    virtual void onCanceled(const char* remain)
    {
        //resultText->setString("支付取消");
    }
    virtual void onFailed(const char* remain)
    {
        //resultText->setString("支付失败");
    }
    virtual void onSuccess(const char* orderNo)
    {
        CCLog("pay okay");
        GAMEDATA::getInstance()->charge(30);
        //resultText->setString("支付成功");
    }

};

//退出回调类
class SFGameExitCallBackImpl : public SFNativeGameExitCallBack
{
    virtual void onGameExit(bool result)
    {

    //result:false 代表SDK取消退出
    if (!result) {
        return;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
        return;
#endif

        Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }


};

//支付回调
SFNativeIPayResulBackImp payCallback = SFNativeIPayResulBackImp();
//退出回调
SFGameExitCallBackImpl exitCallback = SFGameExitCallBackImpl();

bool GameLayer::init(){
	if(!Layer::init()){
		return false;
	}

	matrix = nullptr;
	this->scheduleUpdate();
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
	menu = TopMenu::create(this);
	this->addChild(menu);
    
    for (int i = 0 ; i < MAX_ERASED_NUMBER; i++)
    {
        flyNumber[i] = ShowNumberNode::CreateShowNumberNode("number.png", 2000, 22, 30 );
        flyNumber[i]->retain();
        this->addChild(flyNumber[i],0,0);
    }
    m_flyPointIndex = 0;
    
    
    label_ind = Label::create("","Arial",20);
    label_ind->setPosition(visibleSize.width/2,visibleSize.height-250);
    label_ind->setVisible(false);
    this->addChild(label_ind,1);
	
    m_arrFly = CCArray::createWithCapacity(20);
    m_arrFly->retain();
    this->floatLevelWord();
    this->schedule(schedule_selector(GameLayer::processFlyPoints), 0.1);
	
    ParticleSnow *pParticleSnow = ParticleSnow::create();
    
    this->addChild(pParticleSnow);
    
    //
    this->setKeypadEnabled(true);
    this->setKeyboardEnabled(true);
    auto listener_key = EventListenerKeyboard::create();
    listener_key->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
    //schedule(schedule_selector(HelloWorld::logic), 2.0f);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_key, this);
    
    return true;
}

void GameLayer::processFlyPoints(float dt)
{
    refreshMenu();
    
    if (m_state != READY)
        return;
    
   if (m_arrFly->count() > 0)
   {
       FlyPoint* fp = (FlyPoint*)m_arrFly->objectAtIndex(0);        
       flyNumber[m_flyPointIndex]->flyNumber(fp->number, 0.8, fp->start_pos, fp->end_pos);
       m_arrFly->removeObjectAtIndex(0);
       delete fp;
        //m_vecFly.pop
       m_flyPointIndex++;
       if (m_flyPointIndex == MAX_ERASED_NUMBER)
           m_flyPointIndex = 0;
   }
    
    
    
}

void GameLayer::floatLevelWord(){
    m_state = INIT;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_levelMsg = FloatWord::create(
		ChineseWord("guanqia") + cocos2d::String::createWithFormat(": %d",GAMEDATA::getInstance()->getNextLevel())->_string,
		50, Point(visibleSize.width,visibleSize.height/3*2)
		);
	this->addChild(_levelMsg,1);
	_levelMsg->floatIn(0.5f,CC_CALLBACK_0(GameLayer::floatTargetScoreWord,this));
	Audio::getInstance()->playReadyGo();
    
}

void GameLayer::floatTargetScoreWord(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_targetScore = FloatWord::create(
		ChineseWord("mubiao") + cocos2d::String::createWithFormat(": %d",GAMEDATA::getInstance()->getNextScore())->_string + ChineseWord("fen"),
		50, Point(visibleSize.width,visibleSize.height/3)
		);
	this->addChild(_targetScore,1);
	_targetScore->floatIn(0.5f,CC_CALLBACK_0(GameLayer::removeFloatWord,this));
}

void GameLayer::removeFloatWord(){
	_levelMsg->floatOut(0.5f,nullptr);
	_targetScore->floatOut(0.5f,CC_CALLBACK_0(GameLayer::showStarMatrix,this));
}

void GameLayer::showStarMatrix(){
	matrix = StarMatrix::create(this);
	this->addChild(matrix);
    m_state = READY;
}

void GameLayer::update(float delta){
	if(matrix){
		matrix->updateStar(delta);
	}
}

bool GameLayer::onTouchBegan(Touch* touch,Event* event){
	Point p = touch->getLocationInView();
	p = Director::getInstance()->convertToGL(p);
	CCLOG("x=%f y=%f",p.x,p.y);
	if(matrix){
		matrix->onTouch(p);
	}
	return true;
}

void GameLayer::refreshMenu(){
	menu->refresh();
}

int GameLayer::getReward(CCPoint start_pos,int nStars)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    const unsigned int nBaseTick1 = 5;
    const unsigned int nExtraTick = 20;
    const unsigned int nBaseTick2 = 25;
    int nTotalTick = 0;
    
    for (int i=1; i <= nStars; i++)
    {
        if (i == 1)
        {
            nTotalTick = nBaseTick1;
            FlyPoint* fp = new FlyPoint;
            fp->number = nBaseTick1;
            fp->dt = 1.5;
            fp->start_pos = start_pos;//ccp(visibleSize.width/2,visibleSize.height/2);
            fp->end_pos = ccp(visibleSize.width/2,visibleSize.height-135);
           
            m_arrFly->addObject(fp);
            //flyNumber[i]->flyNumber(nBaseTick1, 1, ,ccp(visibleSize.width/2,visibleSize.height-135));
        }
        else if (i == 2)
        {
            //nTotalTick = nBaseTick1;
            FlyPoint* fp = new FlyPoint;
            fp->number = nBaseTick2;
            fp->dt = 1.5;
            fp->start_pos = start_pos;//ccp(visibleSize.width/2 ,visibleSize.height/2);
            fp->end_pos = ccp(visibleSize.width/2,visibleSize.height-135);
            m_arrFly->addObject(fp);
            //flyNumber[i]->flyNumber(nBaseTick2, 1, ccp(visibleSize.width/2 + 60,visibleSize.height/2),ccp(visibleSize.width/2,visibleSize.height-135));
            nTotalTick = nTotalTick + nBaseTick2 ;
        }
        else
        {
            nTotalTick = nBaseTick1;
            FlyPoint* fp = new FlyPoint;
            fp->number = nExtraTick*(i-2)+nBaseTick2;
            fp->dt = 1.5;
            fp->start_pos = start_pos;//ccp(visibleSize.width/2 ,visibleSize.height/2);
            fp->end_pos = ccp(visibleSize.width/2,visibleSize.height-135);
            m_arrFly->addObject(fp);
            nTotalTick = nTotalTick + nBaseTick2 + nExtraTick*(i-2);
            //flyNumber[i]->flyNumber(nExtraTick*(i-2), 1, ccp(visibleSize.width/2 + 100,visibleSize.height/2),ccp(visibleSize.width/2,visibleSize.height-135));
        }
    }
    
    return nTotalTick;
}


void GameLayer::showLinkNum(CCPoint start_pos,int size){
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
   
	/*string s = String::createWithFormat("%d",size)->_1string + ChineseWord("lianji") +
		String::createWithFormat("%d",size*size*5)->_string + ChineseWord("fen");
	linkNum->setString(s);
	linkNum->setVisible(true);*/
    //flyNumber->setPosition(visibleSize.width/2,visibleSize.height/2);
    //for (int i = 1 ; i <= size ; i ++)
      //  flyNumber[i-1]->flyNumber(i*5, 0.8, ccp(visibleSize.width/2,visibleSize.height/2),ccp(visibleSize.width/2,visibleSize.height));
    getReward(start_pos,size);
}

void GameLayer::hideLinkNum(){
	label_ind->setVisible(false);
}

void GameLayer::floatLeftStarMsg(int leftNum){
    m_state = ENDING;
    //stageClear(this);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* leftStarMsg1 = FloatWord::create(ChineseWord("shengyu") + String::createWithFormat("%d",leftNum)->_string +ChineseWord("ge"), 
		50,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(leftStarMsg1);
    int jiangLiScore = GAMEDATA::getInstance()->getJiangli(leftNum);
	FloatWord* leftStarMsg2 = FloatWord::create(ChineseWord("jiangli") + String::createWithFormat("%d",jiangLiScore)->_string + ChineseWord("fen"),
		50,Point(visibleSize.width,visibleSize.height/2 - 50));
	this->addChild(leftStarMsg2);

    if((GAMEDATA::getInstance()->getCurScore() + jiangLiScore) >= GAMEDATA::getInstance()->getNextScore())
    {
        stageClear(this);
    }
	leftStarMsg1->floatInOut(0.5f,1.0f,
				[=](){
					hideLinkNum();
					matrix->setNeedClear(true);
					GAMEDATA* data = GAMEDATA::getInstance();
					data->setCurScore(data->getCurScore() + jiangLiScore);
					if(data->getCurScore() > data->getHistoryScore()){
						data->setHistoryScore(data->getCurScore());
					}
					refreshMenu();
				});
	leftStarMsg2->floatInOut(0.5f,1.0f,nullptr);
}

void GameLayer::gotoNextLevel(){
    //stageClear(this);
    m_arrFly->removeAllObjects();
	refreshMenu();
	floatLevelWord();
    GAMEDATA::getInstance()->saveCurrentLevel();
    GAMEDATA::getInstance()->saveCurrentScore();
}

void GameLayer::gotoGameOver(){
	//������߷�?
    m_state = ENDING;
    gameOver(this);
	GAMEDATA::getInstance()->saveHighestScore();
	//Ʈ�֣��л�scene
	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* gameOver = FloatWord::create(
		"GAME OVER",80,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(gameOver);
    m_arrFly->release();
    menu->release();
    gameOver->floatIn(2.0f,[]{Director::getInstance()->replaceScene(MenuScene::create());});
}


void GameLayer::bomb(){
    
    if (m_state != READY)
        return;
    
    if (GAMEDATA::getInstance()->getCurentCoin() >= GAMEDATA::getInstance()->getMinBombCost())
    {
        menu->bombIconFlash();
        bombIndication();
        matrix->placeBomb();
        //hint
        m_state = MAGIC;
    }
    else
        noCoinIndication();
}

void GameLayer::bombCompleate()
{
    //erase hint
    GAMEDATA::getInstance()->bomb();
    Audio::getInstance()->playBomb();
    refreshMenu();
    menu->stopBomb();
    hideLinkNum();
    m_state = READY;
}

void GameLayer::replaceStarIndication()
{
    string s = ChineseWord("replaceStarInd");
    label_ind->setColor(Color3B::YELLOW);
    label_ind->setString(s);
    label_ind->setVisible(true);
}

void GameLayer::buttonCallback(cocos2d::Node *pNode, void* pData){
    CCLog("button call back. tag: %d", pNode->getTag());
    matrix->compleateReplaceStar();
    if (pNode->getTag() != -1)
    {
        Star* star = (Star*)pData;
        star->setColor(pNode->getTag());
        star->setTexture(star->getImage(pNode->getTag()));
        GAMEDATA::getInstance()->replaceStar();
        Audio::getInstance()->playPaint();
    }
    replaceStarCompleate();
}

void GameLayer::replaceStarCompleate()
{
    menu->stopPaint();
    hideLinkNum();
    m_state = READY;
}

void GameLayer::OnBtnReplaceStar()
{
    if (m_state != READY)
        return;
    if (GAMEDATA::getInstance()->getCurentCoin() >= GAMEDATA::getInstance()->getReplaceStarCost())
    {
        m_state = MAGIC;
    	menu->paintIconFlash();
    	replaceStarIndication();
    	matrix->replaceStar();
    }
    else
    	noCoinIndication();
    
    
}

void GameLayer::replaceStar(Star* star)
{
    m_state = MAGIC;
    
    DialogLayer* dlg = DialogLayer::create();
    this->addChild(dlg);

    PopupLayer* pl = PopupLayer::create("paint_bg.png");
    pl->setCallbackFunc(this, callfuncND_selector(GameLayer::buttonCallback),(void*)star);
    // 添加按钮，设置图片，文字，tag 信息
    pl->addButton("tomato.png", "tomato.png", "", Star::color::PURPLE);
    pl->addButton("carrot.png", "carrot.png", "", Star::color::RED);
    pl->addButton("artichoke.png", "artichoke.png", "", Star::color::GREEN);
    pl->addButton("leek.png", "leek.png", "", Star::color::BLUE);
    pl->addButton("chilli.png", "chilli.png", "", Star::color::YELLOW);
    pl->addButton("paint_back.png", "paint_back.png", "", -1);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    pl->setBackgroundPos(ccp(star->getPosition().x,star->getPosition().y + 100));
    
    pl->setBackgroundLayer(dlg);
    CCLog("current opacity %d",this->getOpacity());
    
    //pl->setPosition(visibleSize.width/2,visibleSize.height/2+200);
    // 添加到当前层
    this->addChild(pl);
}

void GameLayer::rainbow(){
    
    if(m_state != READY)
        return;
    
    if (GAMEDATA::getInstance()->getCurentCoin() >= GAMEDATA::getInstance()->getRainbowCost())
    {
        matrix->rainbow();
        GAMEDATA::getInstance()->rainbow();
        Audio::getInstance()->playRainbow();
    }
    else{
        noCoinIndication();
    }
    
    
}

void GameLayer::chargeCallback(cocos2d::Node *pNode,void* pData)
{
    CCLog("button call back. tag: %d", pNode->getTag());
    if (pNode->getTag() == 1)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        //GAMEDATA::getInstance()->charge(15);
        soomla::CCError *err;
        int balance = soomla::CCStoreInventory::sharedStoreInventory()->getItemBalance("15_DIAMOND_ID");
        if (balance > 0)
            soomla::CCStoreInventory::sharedStoreInventory()->takeItem("15_DIAMOND_ID", 1);
        
        balance = soomla::CCStoreInventory::sharedStoreInventory()->getItemBalance("15_DIAMOND_ID");

        soomla::CCStoreInventory::sharedStoreInventory()->buyItem("15_DIAMOND_ID", &err);
        if (err != NULL)
        {
            CCLOG("charge error %s",err->getInfo());
            
            /*switch code {
             case SOOMLA_EXCEPTION_ITEM_NOT_FOUND:
             // itemNotFoundException was raised
             break;
             case SOOMLA_EXCEPTION_INSUFFICIENT_FUNDS:
             // insufficienFundsException was raised
             break;
             case SOOMLA_EXCEPTION_NOT_ENOUGH_GOODS:
             // notEnoughGoodsException was raised
             break;*/
            
        }
        else
        {
            //GAMEDATA::getInstance()->charge(15);
            hideLinkNum();
        }
#else #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        //CCLOG("recharge");
        CCLOG("PluginChannel pay");
        SFGameNativeInterface::setSFIPayResulBack(&payCallback);
        //支付，参数为计费点编号
        SFGameNativeInterface::pay("1");
        //PluginChannel::getInstance()->payment();//调用渠道支付
        hideLinkNum();
#endif
    }

}

void GameLayer::noCoinIndication()
{
    string s = ChineseWord("noCoinInd");
    label_ind->setColor(Color3B::YELLOW);
    label_ind->setString(s);
    label_ind->setVisible(true);
    

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //CCLOG("recharge");
    //CCLOG("PluginChannel pay");
    //PluginChannel::getInstance()->payment();//调用渠道支付
//#else
    
    DialogLayer* dlg = DialogLayer::create();
    this->addChild(dlg);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    PopupLayerExt* pl = PopupLayerExt::create("msgbox.png");
    pl->setPosition(visibleSize.width/2,visibleSize.height/2);
    pl->setCallbackFunc(this, callfuncND_selector(GameLayer::chargeCallback),NULL);
    pl->setTitle("提示",24);
    pl->setContentText("购买30颗钻石，花费6元");
    // 添加按钮，设置图片，文字，tag 信息
    pl->addButton("ok_but.png", "ok_but.png", "", 1);
    pl->addButton("cancel_but.png", "cancel_but.png", "", 2);
            
    pl->setBackgroundLayer(dlg);
    CCLog("current opacity %d",this->getOpacity());
            //pl->setAnchorPoint(Vec2(0.5,0.5));
            
            // 添加到当前层
    this->addChild(pl);
    
    
//#endif
}

void GameLayer::bombIndication()
{
    string s = ChineseWord("bombInd");
    label_ind->setColor(Color3B::YELLOW);
    label_ind->setString(s);
    label_ind->setVisible(true);
    
    //MyKeyboardDelegate::getInstance()->keyBackClicked(this);
    //string s = "please chose a 3x3 square.";
    //linkNum->setString(s);
    //linkNum->setVisible(true);
    
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
    {
        MyKeyboardDelegate::getInstance()->keyBackClicked(this);
    }
#endif
    
}
