//
//  PopupLayer.h
//  PopStars1
//
//  Created by 朱 热叶 on 14/11/15.
//
//

#ifndef __PopStars1__PopupLayer__
#define __PopStars1__PopupLayer__

#include <stdio.h>

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "extensions/cocos-ext.h"
#else
#include "cocos-ext.h"
#endif

#include "DialogLayer.h"

USING_NS_CC;
using namespace cocos2d::extension;


class PopupLayer :public CCLayer
{
public:
    PopupLayer();
    CREATE_FUNC(PopupLayer);
    ~PopupLayer();
    virtual bool init();
    //virtual void registerWithTouchDispatcher(void);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    
    static PopupLayer * create(const char* backgroundImage);
    void setTitle(const char* title ,int fontsize=20);
    void setContentText(const char* text ,int fontsize=20 ,int padding=50 ,int paddintTop=100);
    void setCallbackFunc(Object* target, SEL_CallFuncND callfun,void* pData);
    
    virtual bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag=0);
    virtual void onEnter();
    virtual void onExit();
    //added by yiye to set position of background image.
    void        setBackgroundPos(CCPoint pos){m_posBackgroud = pos;};
    void        setBackgroundLayer(DialogLayer* layer){backgroundLayer = layer;}
protected:
    virtual void buttonCallback(CCObject* pSender);
    
    // 文字内容两边的空白区
    int m_contentPadding;
    int m_contentPaddingTop;
    
    CCObject* m_callbackListener;
    SEL_CallFuncND m_callback;
    void*           m_data;
    CCPoint             m_posBackgroud;
    DialogLayer*        backgroundLayer;
    
    CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);
    CC_SYNTHESIZE_RETAIN(Sprite*, m__sfBackGround, SpriteBackGround);
    CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m__s9BackGround, Sprite9BackGround);
    CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltTitle, LabelTitle);
    CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltContentText, LabelContentText);
};

#endif /* defined(__PopStars1__PopupLayer__) */
