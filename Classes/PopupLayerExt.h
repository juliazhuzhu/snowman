//
//  PopupLayerExt.h
//  popStar
//
//  Created by 朱 热叶 on 15/2/9.
//
//

#ifndef __popStar__PopupLayerExt__
#define __popStar__PopupLayerExt__

#include <stdio.h>
#include "PopupLayer.h"

USING_NS_CC;
using namespace cocos2d::extension;


class PopupLayerExt :public PopupLayer
{
public:
    PopupLayerExt();
    CREATE_FUNC(PopupLayerExt);
    ~PopupLayerExt();
    static PopupLayerExt * create(const char* backgroundImage);
    virtual void onEnter();
    
};

class PopupLayerExit :public PopupLayerExt
{
public:
    PopupLayerExit();
    CREATE_FUNC(PopupLayerExit);
    ~PopupLayerExit();
    static PopupLayerExit * create(const char* backgroundImage);
    virtual bool addButton(const char *normalImage, const char *selectedImage, const char *title, int tag);
protected:
    virtual void buttonCallback(CCObject* pSender);
};

#endif /* defined(__popStar__PopupLayerExt__) */
