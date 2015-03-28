//
//  MyKeyboardDelegate.cpp
//  PopStars1
//
//  Created by 朱 热叶 on 14/11/15.
//
//

#include "MyKeyboardDelegate.h"
#include "ExitDialog.h"
#include "PopupLayerExt.h"
#include "DialogLayer.h"


MyKeyboardDelegate* MyKeyboardDelegate::_instance = 0;

MyKeyboardDelegate::MyKeyboardDelegate(){
    this->init();
}

MyKeyboardDelegate* MyKeyboardDelegate::getInstance(){
    if(_instance == 0){
        _instance = new MyKeyboardDelegate();
    }
    return _instance;
}



void MyKeyboardDelegate::keyBackClicked(Node* node)
{
    CCLog("MyKeyboardDelegate::keyBackClicked");
        //ExitDlg* dlg = ExitDlg::create();
    //CCDirector::sharedDirector()->end();
    //node->addChild(dlg);
    
    DialogLayer* dlg = DialogLayer::create();
    node->addChild(dlg);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    PopupLayerExit* pl = PopupLayerExit::create("msgbox.png");
    pl->setPosition(visibleSize.width/2,visibleSize.height/2);
    //pl->setCallbackFunc(NULL, callfuncND_selector(MenuLayer::endGameCallback),NULL);
    pl->setTitle("提示",24);
    pl->setContentText("真滴要腿粗嘛？");
    // 添加按钮，设置图片，文字，tag 信息
    pl->addButton("ok_but.png", "ok_but.png", "", 1);
    pl->addButton("cancel_but.png", "cancel_but.png", "", 2);
    
    pl->setBackgroundLayer(dlg);
    //CCLog("current opacity %d",this->getOpacity());
    //pl->setAnchorPoint(Vec2(0.5,0.5));
    
    // 添加到当前层
    node->addChild(pl);

}

void MyKeyboardDelegate::keyMenuClicked(Node* node)
{
    
}
