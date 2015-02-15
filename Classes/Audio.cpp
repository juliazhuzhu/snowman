#include "Audio.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
// android effect only support ogg
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


Audio* Audio::m_instance = nullptr;
Audio* Audio::getInstance(){
	if(m_instance == nullptr){
		m_instance = new Audio();
        //m_instance->init();
        //m_instance->prepare();

	}
	return m_instance;
}

void Audio::initAndroid()
{
    BG_MUSIC        = "music.wav";
    READY_GO        = "readygo.ogg";
    POP             = "pop.mp3";
    COMBO_1         = "combo_1.ogg";
    COMBO_2         = "combo_2.ogg";
    COMBO_3         = "combo_3.ogg";
    BOMB            = "Props_Bomb.ogg";
    PAINT           = "Props_Paint.ogg";
    RAINBOW         = "Props_Rainbow.ogg";

}

void Audio::initIOS()
{
    BG_MUSIC        = "music.mp3";
    READY_GO        = "readygo.mp3";
    POP             = "pop.mp3";
    COMBO_1         = "combo_1.mp3";
    COMBO_2         = "combo_2.mp3";
    COMBO_3         = "combo_3.mp3";
    BOMB            = "Props_Bomb.mp3";
    PAINT           = "Props_Paint.mp3";
    RAINBOW         = "Props_Rainbow.mp3";
    


}

void Audio::playBGM(){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BG_MUSIC.c_str(),true);
}

void Audio::playReadyGo(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(READY_GO.c_str(),false);
}

void Audio::playPop(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(POP.c_str(),false);
}

void Audio::playBomb(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(BOMB.c_str(),false);
}

void Audio::playPaint(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(PAINT.c_str(),false);
}

void Audio::playRainbow(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(RAINBOW.c_str(),false);
}

void Audio::playCombo(int size){
	if(size < 5)
		return;
	if(size >= 10){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(COMBO_3.c_str(),false);
	}else if(size >= 7){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(COMBO_2.c_str(),false);
	}else {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(COMBO_1.c_str(),false);
	}
}
void Audio::prepare(){
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_MUSIC);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BG_MUSIC.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(READY_GO.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(POP.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(COMBO_1.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(COMBO_2.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(COMBO_3.c_str());
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BOMB.c_str());
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(PAINT.c_str());
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(RAINBOW.c_str());
}
