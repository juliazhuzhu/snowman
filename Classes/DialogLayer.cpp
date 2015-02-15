#include "DialogLayer.h"

USING_NS_CC;


DialogLayer::DialogLayer():
    mMenu(NULL),
    mMenuItemArray(NULL),
    mTouchedMenu(false)
{
}

DialogLayer::~DialogLayer()
{
}

bool DialogLayer::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)));
        
        //onInitDialog();
        auto listener = EventListenerTouchOneByOne::create();
        
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(DialogLayer::onTouchBegan, this);
        
        //listener->onTouchMoved = CC_CALLBACK_2(PopupLayer::onTouchMoved, this);
        
        //listener->onTouchEnded = CC_CALLBACK_2(PopupLayer::onTouchEnded, this);
        
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        initMenu();

        bRet = true;
    } while (0);
    
    return bRet;
}


void DialogLayer::pushMenu(CCMenuItem *pMenuItem)
{
    if (!mMenuItemArray) {
        mMenuItemArray = CCArray::create();
    }

    mMenuItemArray->addObject(pMenuItem);
}

bool DialogLayer::initMenu()
{
    if (mMenuItemArray && mMenuItemArray->count() > 0) {
        for (int i = 0; i < mMenuItemArray->count(); i++)
        {
            if (!mMenu) {
            //Vector<MenuItem*>
                //mMenu = CCMenu::createWithArray(mMenuItemArray);
                mMenu->addChild((CCMenuItem*)mMenuItemArray->objectAtIndex(i));
               
                
            }
        }
        addChild(mMenu);
        mMenu->setPosition(CCPointZero);
    }
    return true;
}

void DialogLayer::onEnter()
{
    CCLayerColor::onEnter();

    // 屏蔽所有priority比自己大的消息
    m_listener = EventListenerTouchOneByOne::create();  //创建一个单点触摸事件 :EventListenerTouchAllAtOnce 为多点
    //设置这些事件的的回调方法
    m_listener->onTouchBegan = CC_CALLBACK_2(DialogLayer::onTouchBegan, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(DialogLayer::onTouchEnded, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(DialogLayer::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this); //事件调度器
    _eventDispatcher->setPriority(m_listener, -128);
    m_listener->setSwallowTouches(true);
    
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
}

void DialogLayer::onExit()
{
    CCLayerColor::onExit();
    //CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    _eventDispatcher->removeEventListener(m_listener);
}

bool DialogLayer::onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    // 因为拦截了所有消息(包括按钮) 所以需要将消息手动传给模态对话框上的按钮
    if (mMenu) {
        mTouchedMenu = mMenu->ccTouchBegan(pTouch, pEvent);
    }
    
    return false;
}

void DialogLayer::onTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (mTouchedMenu) {
        if (mMenu) {
            mMenu->ccTouchMoved(pTouch, pEvent);
        }
    }
}

void DialogLayer::onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (mTouchedMenu) {
        if (mMenu) {
            mMenu->ccTouchEnded(pTouch, pEvent);
        }
        mTouchedMenu = false;
    }
}

void DialogLayer::onTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (mTouchedMenu) {
        if (mMenu) {
            mMenu->ccTouchEnded(pTouch, pEvent);
        }
        mTouchedMenu = false;
    }
}
