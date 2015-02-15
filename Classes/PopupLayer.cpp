//
//  PopupLayer.cpp
//  PopStars1
//
//  Created by 朱 热叶 on 14/11/15.
//
//

#include "PopupLayer.h"

PopupLayer::PopupLayer():
m__pMenu(NULL)
, m_contentPadding(0)
, m_contentPaddingTop(0)
, m_callbackListener(NULL)
, m_callback(NULL)
, m_data(NULL)
, m__sfBackGround(NULL)
, m__s9BackGround(NULL)
, m__ltContentText(NULL)
, m__ltTitle(NULL)
{
    
}

PopupLayer::~PopupLayer(){
    CC_SAFE_RELEASE(m__pMenu);
    CC_SAFE_RELEASE(m__sfBackGround);
    CC_SAFE_RELEASE(m__ltContentText);
    CC_SAFE_RELEASE(m__ltTitle);
    CC_SAFE_RELEASE(m__s9BackGround);
}

bool PopupLayer::init(){
    if(!Layer::init()){
        return false;
    }
    backgroundLayer = NULL;
    this->setContentSize(CCSizeZero);
    
    // 初始化需要的 Menu
    CCMenu* menu = CCMenu::create();
    menu->setPosition(CCPointZero);
    setMenuButton(menu);
    
    
    auto listener = EventListenerTouchOneByOne::create();

    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(PopupLayer::onTouchBegan, this);
    
    //listener->onTouchMoved = CC_CALLBACK_2(PopupLayer::onTouchMoved, this);
    
    //listener->onTouchEnded = CC_CALLBACK_2(PopupLayer::onTouchEnded, this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}


bool PopupLayer::onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    //
    CCLog("PopupLayer touch");
    
    return true;
}

PopupLayer* PopupLayer::create(const char *backgroundImage){
    PopupLayer* ml = PopupLayer::create();
    ml->setSpriteBackGround(CCSprite::create(backgroundImage));
    ml->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
    return ml;
}

void PopupLayer::setTitle(const char *title, int fontsize){
    CCLabelTTF* ltfTitle = CCLabelTTF::create(title, "", fontsize);
    setLabelTitle(ltfTitle);
}

void PopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop){
    CCLabelTTF* ltf = CCLabelTTF::create(text, "", fontsize);
    setLabelContentText(ltf);
    m_contentPadding = padding;
    m_contentPaddingTop = paddingTop;
}

void PopupLayer::setCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncND callfun,void* pData){
    m_callbackListener = target;
    m_callback = callfun;
    m_data = pData;
}


bool PopupLayer::addButton(const char *normalImage, const char *selectedImage, const char *title, int tag){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pCenter = ccp(winSize.width / 2, winSize.height / 2);
    
    // 创建图片菜单按钮
    CCMenuItemImage* menuImage = CCMenuItemImage::create(normalImage, selectedImage, this, menu_selector(PopupLayer::buttonCallback));
    menuImage->setTag(tag);
    menuImage->setPosition(pCenter);
    
    // 添加文字说明并设置位置
    if (strlen(title) > 0)
    {
        CCSize imenu = menuImage->getContentSize();
        CCLabelTTF* ttf = CCLabelTTF::create(title, "", 20);
        ttf->setColor(ccc3(0, 0, 0));
        ttf->setPosition(ccp(imenu.width / 2, imenu.height / 2));
        menuImage->addChild(ttf);
    }
    
    getMenuButton()->addChild(menuImage);
    return true;
}

void PopupLayer::buttonCallback(cocos2d::CCObject *pSender){
    CCNode* node = dynamic_cast<CCNode*>(pSender);
    CCLog("touch tag: %d", node->getTag());
    if (m_callback && m_callbackListener){
        (m_callbackListener->*m_callback)(node,m_data);
    }
    this->removeFromParent();
    
    if (backgroundLayer)
        backgroundLayer->removeFromParent();
}

void PopupLayer::onEnter(){
   // Layer:onEnter();
    //CCLayerColor::onEnter();
    CCLayer::onEnter();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pCenter = ccp(winSize.width / 2, winSize.height / 2);
    
    CCSize contentSize;
    // 设定好参数，在运行时加载
    if (getContentSize().equals(CCSizeZero)) {
        //getSpriteBackGround()->setPosition(ccp(winSize.width / 2, winSize.height / 2));//by yiye
        getSpriteBackGround()->setPosition(winSize.width / 2,m_posBackgroud.y);
        this->addChild(getSpriteBackGround(), 0, 0);
        contentSize = getSpriteBackGround()->getTexture()->getContentSize();
    } else {
        Scale9Sprite *background = getSprite9BackGround();
        background->setContentSize(getContentSize());
        //background->setPosition(ccp(winSize.width / 2, winSize.height / 2) );//by yiye
        background->setPosition(winSize.width / 2,m_posBackgroud.y);
        this->addChild(background, 0, 0);
        contentSize = getContentSize();
    }
    
    auto paint_arrow = CCSprite::create("paint_arrow.png");
    paint_arrow->setPosition(m_posBackgroud.x,m_posBackgroud.y-60);
    this->addChild(paint_arrow);
    // 添加按钮，并设置其位置
    this->addChild(getMenuButton());
    float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);
    
    Vector<Node*> vecArray = getMenuButton()->getChildren();
    CCObject* pObj = NULL;
    int i = 0;
    for(auto& e : vecArray){
        CCNode* node = dynamic_cast<CCNode*>(e);
        //node->setPosition(Point(winSize.width/2 - contentSize.width/2+btnWidth*(i+1),winSize.height/2-contentSize.height/3));
        node->setPosition(Point(winSize.width/2 - contentSize.width/2+btnWidth*(i+1),m_posBackgroud.y));//by xiaoye
        i++;
    }
    /*  CCARRAY_FOREACH(array, pObj){
     CCNode* node = dynamic_cast<CCNode*>(pObj);
     node->setPosition(ccp( winSize.width / 2 - contentSize.width / 2 + btnWidth * (i + 1), winSize.height / 2 - contentSize.height / 3));
     i++;
     }*/
    
    
    // 显示对话框标题
    if (getLabelTitle()){
        getLabelTitle()->setPosition(ccpAdd(pCenter, ccp(0, contentSize.height / 2 - 35.0f)));
        this->addChild(getLabelTitle());
    }
    
    // 显示文本内容
    if (getLabelContentText()){
        CCLabelTTF* ltf = getLabelContentText();
        //ltf->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        ltf->setPosition(ccp(winSize.width / 2, m_posBackgroud.y / 2));
        ltf->setDimensions(CCSizeMake(contentSize.width - m_contentPadding * 2, contentSize.height - m_contentPaddingTop));
        ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
        this->addChild(ltf);
    }
    
    // 弹出效果
    CCAction* popupLayer = CCSequence::create(CCScaleTo::create(0.0, 0.0),
                                              CCScaleTo::create(0.06, 1.05),
                                              CCScaleTo::create(0.08, 0.95),
                                              CCScaleTo::create(0.08, 1.0), NULL);
    this->runAction(popupLayer);
    
    
}

void PopupLayer::onExit(){
    
    CCLog("popup on exit.");
    CCLayer::onExit();
}