#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "cocos2d.h"
#include <string>
using namespace std;


class Audio{
public:
	static Audio* getInstance();
    void initAndroid();
    void initIOS();
	void playBGM();
	void playReadyGo();
	void playPop();
	void prepare();
	void playCombo(int size);
    void playBomb();
    void playPaint();
    void playRainbow();
private:
	static Audio* m_instance;
    string  BG_MUSIC;
    string  READY_GO;
    string  POP;
    string  COMBO_1;
    string  COMBO_2;
    string  COMBO_3;
    string  BOMB;
    string  PAINT;
    string  RAINBOW;

};
#endif