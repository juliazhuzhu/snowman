#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

#define BOMB_COST (3)
#define RAINBOW_COST (3)
#define REPLACE_STAR_COST (3)

class GAMEDATA{
public:
	static GAMEDATA* getInstance();
	/*��ǰ�ȼ�*/
	void setCurLevel(int level);
	inline int getCurLevel(){return cur_level;}
	/*��һ�ȼ�*/
	inline int getNextLevel(){return next_level;}
	/*��߷�*/
	inline void setHistoryScore(int score){history_score = score;}
	inline int getHistoryScore(){return history_score;}
	/*��ǰ����*/
	inline void setCurScore(int score){cur_score = score;}
	inline int getCurScore(){return cur_score;}
	/*ͨ�ط���*/
	inline int getNextScore(){return next_score;}
	inline int getScoreByLevel(int level);

    inline int getCurentCoin(){return cur_coin;}
    void setCoin(int coin){cur_coin = coin;}
	/*��������*/
	int getJiangli(int size);

	void saveHighestScore();
    void saveCurrentCoin();
    void saveCurrentLevel();
    void saveCurrentScore();
    
    const int getMinBombCost() const {return BOMB_COST;}
    const int getRainbowCost() const {return RAINBOW_COST;}
    const int getReplaceStarCost() const {return REPLACE_STAR_COST;}
    void bomb();
    void rainbow();
    void replaceStar();
    void continueFromLastLevel();
    
    void charge(int coin);
    
private:
	GAMEDATA();
	void init();
private:
	static GAMEDATA* _instance;
	int cur_level;
	int next_level;
	int history_score;
	int cur_score;
	int next_score;
    int cur_coin;
	friend class MenuLayer;
};
#endif
