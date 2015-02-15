//
//  PopupLayerExt.cpp
//  popStar
//
//  Created by 朱 热叶 on 15/2/9.
//
//

#include "PopupLayerExt.h"




PopupLayerExt::PopupLayerExt()
{
    
}

PopupLayerExt::~PopupLayerExt()
{
    
}

PopupLayerExt* PopupLayerExt::create(const char *backgroundImage){
    PopupLayerExt* ml = PopupLayerExt::create();
    ml->setSpriteBackGround(CCSprite::create(backgroundImage));
    ml->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
    return ml;
}

void PopupLayerExt::onEnter(){
    // Layer:onEnter();
    //CCLayerColor::onEnter();
    CCLayer::onEnter();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pCenter = ccp(winSize.width / 2, winSize.height / 2);
    
    CCSize contentSize;
    // 设定好参数，在运行时加载
    if (getContentSize().equals(CCSizeZero)) {
        getSpriteBackGround()->setPosition(0,0);//ccp(winSize.width / 2, winSize.height / 2));//by yiye
        //getSpriteBackGround()->setPosition(winSize.width / 2,m_posBackgroud.y);
        this->addChild(getSpriteBackGround(),0,0);
        contentSize = getSpriteBackGround()->getTexture()->getContentSize();
    } else {
        Scale9Sprite *background = getSprite9BackGround();
        background->setContentSize(getContentSize());
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2) );//by yiye
        //background->setPosition(winSize.width / 2,m_posBackgroud.y);
        this->addChild(background, 0, 0);
        contentSize = getContentSize();
    }
    
    //auto paint_arrow = CCSprite::create("paint_arrow.png");
    //paint_arrow->setPosition(m_posBackgroud.x,m_posBackgroud.y-60);
    //this->addChild(paint_arrow);
    // 添加按钮，并设置其位置
    this->addChild(getMenuButton());
    float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);
    
    Vector<Node*> vecArray = getMenuButton()->getChildren();
    CCObject* pObj = NULL;
    int i = 0;
    for(auto& e : vecArray){
        CCNode* node = dynamic_cast<CCNode*>(e);
        node->setPosition(Point(0 - contentSize.width/2+btnWidth*(i+1),0-contentSize.height/3));
        //node->setPosition(Point(winSize.width/2 ,winSize.height/2));
        //node->setPosition(Point(winSize.width/2 - contentSize.width/2+btnWidth*(i+1),m_posBackgroud.y));//by xiaoye
        i++;
    }
    /*  CCARRAY_FOREACH(array, pObj){
     CCNode* node = dynamic_cast<CCNode*>(pObj);
     node->setPosition(ccp( winSize.width / 2 - contentSize.width / 2 + btnWidth * (i + 1), winSize.height / 2 - contentSize.height / 3));
     i++;
     }*/
    
    
    // 显示对话框标题
    if (getLabelTitle()){
        //getLabelTitle()->setPosition(0,0);//ccpAdd(pCenter, ccp(0, contentSize.height / 2 - 35.0f)));
        getLabelTitle()->setPosition(0,140);//ccpAdd(pCenter, ccp(0, contentSize.height / 2 - 35.0f)));
        this->addChild(getLabelTitle());
    }
    
    // 显示文本内容
    if (getLabelContentText()){
        CCLabelTTF* ltf = getLabelContentText();
        ltf->setPosition(ccp(0,-80));
        //ltf->setPosition(ccp(winSize.width / 2, m_posBackgroud.y / 2));//by xiaoye
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


PopupLayerExit::PopupLayerExit()
{
    
}

PopupLayerExit::~PopupLayerExit()
{
    
}

PopupLayerExit* PopupLayerExit::create(const char *backgroundImage){
    PopupLayerExit* ml = PopupLayerExit::create();
    ml->setSpriteBackGround(CCSprite::create(backgroundImage));
    ml->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
    return ml;
}

bool PopupLayerExit::addButton(const char *normalImage, const char *selectedImage, const char *title, int tag){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pCenter = ccp(winSize.width / 2, winSize.height / 2);
    
    // 创建图片菜单按钮
    CCMenuItemImage* menuImage = CCMenuItemImage::create(normalImage, selectedImage, this, menu_selector(PopupLayerExit::buttonCallback));
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

void PopupLayerExit::buttonCallback(cocos2d::CCObject *pSender){
    CCNode* node = dynamic_cast<CCNode*>(pSender);
    CCLog("PopupLayerExit touch tag: %d", node->getTag());
    if (m_callback && m_callbackListener){
        (m_callbackListener->*m_callback)(node,m_data);
    }
    this->removeFromParent();
    
    if (backgroundLayer)
        backgroundLayer->removeFromParent();
    
    if (node->getTag() == 1)
    {
        CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }

}


