#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_
#include "cocos2d.h"
#include "FloatWord.h"
#include "TopMenu.h"
#include "StarMatrix.h"
#include "ShowNumberNode.h"

#define MAX_ERASED_NUMBER (20)

using namespace cocos2d;
class StarMatrix;
class TopMenu;
class GameLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void floatLevelWord();
	void floatTargetScoreWord();
	void removeFloatWord();
	void showStarMatrix();
	virtual void update(float delta);
	virtual bool onTouchBegan(Touch* touch,Event* event);
	void refreshMenu();
	void showLinkNum(CCPoint start_pos,int size);
	void hideLinkNum();
	void floatLeftStarMsg(int leftNum);
	void gotoNextLevel();
	void gotoGameOver();
    void bomb();
    void bombCompleate();
    void rainbow();
    void bombIndication();
    void replaceStarIndication();
    void noCoinIndication();
    void OnBtnReplaceStar();
    void replaceStar(Star* star);
    void replaceStarCompleate();
    int getState(){ return m_state;}
    enum {INIT, READY, ENDING,MAGIC} m_state;
private:
	FloatWord* _levelMsg;
	FloatWord* _targetScore;
	TopMenu* menu;
	StarMatrix* matrix;
	Label* label_ind;
    ShowNumberNode* flyNumber[MAX_ERASED_NUMBER];
    int getReward(CCPoint start_pos,int nStars);
    void processFlyPoints(float dt);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void buttonCallback(cocos2d::Node *pNode,void* pData);
    void chargeCallback(cocos2d::Node *pNode,void* pData);
    
    class FlyPoint: public Ref{
    public:
        int number;
        CCPoint start_pos;
        CCPoint end_pos;
        float dt;
    };
    int m_flyPointIndex;
    
    CCArray*     m_arrFly;
    
};
#endif