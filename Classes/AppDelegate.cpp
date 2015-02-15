#include "AppDelegate.h"
#include "MenuScene.h"
#include "Audio.h"
#include "GameScene.h"

#if (CC_PLATFORM_IOS == CC_TARGET_PLATFORM)
#include "Cocos2dxStore.h"
#include "DiamondAssets.h"
//#include "MuffinRushAssets.h"
#include "ExampleEventHandler.h"
#endif

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
#if (CC_PLATFORM_IOS == CC_TARGET_PLATFORM)
    
    //DiamondAssets *assets = DiamondAssets::create();
    DiamondAssets* assets = DiamondAssets::create();
    ExampleEventHandler* handler = new ExampleEventHandler();
        __Dictionary *commonParams = __Dictionary::create();
    commonParams->setObject(__String::create("ExampleCustomSecrt4"), "customSecret7");
    soomla::CCServiceManager::getInstance()->setCommonParams(commonParams);
    
    __Dictionary *storeParams = __Dictionary::create();
    storeParams->setObject(__String::create("ExamplePublicKy4"), "androidPublicKey7");
    storeParams->setObject(__Bool::create(true), "testPurchass7");
    
    soomla::CCStoreService::initShared(assets, storeParams);
    
    soomla::CCStoreEventDispatcher::getInstance()->addEventHandler(handler);
    

#endif

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        //glview = GLView::create("POPSTAR");
        director->setOpenGLView(glview);
    }
	glview->setDesignResolutionSize(480,800,ResolutionPolicy::EXACT_FIT);
    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    
    std::vector<std::string> searchList = CCFileUtils::sharedFileUtils()->getSearchPaths();
    searchList.push_back(std::string("Music/"));
    for(const std::string& path : searchList)
        CCLOG("* search path %s\n", path.c_str());

    

    // run
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Audio::getInstance()->initAndroid();
#else
    Audio::getInstance()->initIOS();
#endif
    Audio::getInstance()->prepare();
    
    auto scene = MenuScene::create();

    director->runWithScene(scene);
	//Audio::getInstance()->prepare();
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
