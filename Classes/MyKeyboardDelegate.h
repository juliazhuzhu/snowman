//
//  MyKeyboardDelegate.h
//  PopStars1
//
//  Created by 朱 热叶 on 14/11/15.
//
//

#ifndef __PopStars1__MyKeyboardDelegate__
#define __PopStars1__MyKeyboardDelegate__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class MyKeyboardDelegate
{
public:
    
    static MyKeyboardDelegate* getInstance();
    virtual void keyBackClicked(Node* node);
    virtual void keyMenuClicked(Node* node);
    //void endGameCallback(cocos2d::Node *pNode, void* pData);
private:
    MyKeyboardDelegate();
    void init(){};
    static MyKeyboardDelegate* _instance;
};


#endif /* defined(__PopStars1__MyKeyboardDelegate__) */
