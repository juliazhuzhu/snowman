#include "GameData.h"
#include "cocos2d.h"
using namespace cocos2d;
GAMEDATA* GAMEDATA::_instance = 0;
GAMEDATA::GAMEDATA(){
	this->init();
}
GAMEDATA* GAMEDATA::getInstance(){
	if(_instance == 0){
		_instance = new GAMEDATA();
	}
	return _instance;
}

void GAMEDATA::init(){
    setCurLevel(0);
	setCurScore(0);
	setHistoryScore(UserDefault::getInstance()->getIntegerForKey("highestScore",0));
    cur_coin = UserDefault::getInstance()->getIntegerForKey("curCoin",9);
    log("current coin %d", cur_coin);
}

void GAMEDATA::continueFromLastLevel(){
    setCurLevel(UserDefault::getInstance()->getIntegerForKey("curLevel",0));
    setCurScore(UserDefault::getInstance()->getIntegerForKey("curScore",0));
    setHistoryScore(UserDefault::getInstance()->getIntegerForKey("highestScore",0));
    cur_coin = UserDefault::getInstance()->getIntegerForKey("curCoin",9);
}

void GAMEDATA::setCurLevel(int level){
	if(level < 0){
		return;
	}
	cur_level = level;
	next_level = level + 1;
	next_score = getScoreByLevel(next_level);
    //saveCurrentLevel();
}

int GAMEDATA::getScoreByLevel(int level){
	int score = 0;
	if (level == 1)
	{
		score = 2000;
	}
	else if (level == 2)
	{
		score = 4500;
	}
	else if ( (level >=3) && (level <= 10) )
	{
		score = 4500 + 4000 * (level - 2);
	}
	else
	{
		score = 35500 + 5000 * (level - 10);
	}
	return score;
}

int GAMEDATA::getJiangli(int size){
	static const int jiangli[10][2] =
	{
		{0, 2000},
		{1, 1980},
		{2, 1920},
		{3, 1820},
		{4, 1680},
		{5, 1500},
		{6, 1280},
		{7, 1020},
		{8, 720},
		{9, 380}
	};
	if(size>9 || size<0){
		return 0;
	}
	return jiangli[size][1];
}


void GAMEDATA::saveHighestScore(){
	UserDefault::getInstance()->setIntegerForKey("highestScore",getHistoryScore());
}

void GAMEDATA::saveCurrentCoin(){
    UserDefault::getInstance()->setIntegerForKey("curCoin",cur_coin);
}

void GAMEDATA::saveCurrentLevel(){
    UserDefault::getInstance()->setIntegerForKey("curLevel",cur_level);
}

void GAMEDATA::saveCurrentScore(){
    UserDefault::getInstance()->setIntegerForKey("curScore",cur_score);
}

void GAMEDATA::bomb(){
    
    if (getCurentCoin() >= getMinBombCost())
        cur_coin = cur_coin - getMinBombCost();
    
    saveCurrentCoin();
}

void GAMEDATA::rainbow(){
    
    if (getCurentCoin() >= getRainbowCost())
        cur_coin = cur_coin - getRainbowCost();
    
    saveCurrentCoin();
}

void GAMEDATA::replaceStar()
{
    if (getCurentCoin() >= getReplaceStarCost())
        cur_coin = cur_coin - getReplaceStarCost();
    
    saveCurrentCoin();
}


void GAMEDATA::charge(int coin)
{
    cur_coin += coin;
    saveCurrentCoin();
}
