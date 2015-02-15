

#ifndef __DiamondAssets_H_
#define __DiamondAssets_H_

#include "CCStoreAssets.h"
#include "cocos2d.h"

#define DIAMOND_CURRENCY_ITEM_ID "com.xiaoye.snowman.onediamond"
#define FIFTEENDIAMOND_PACK_PRODUCT_ID "com.xiaoye.snowman.15diamonds"

class DiamondAssets: public soomla::CCStoreAssets {
    
public:
    
    DiamondAssets():mCurrencies(NULL),mCurrencyPacks(NULL),mGoods(NULL)
    {}

    virtual ~DiamondAssets();

    static DiamondAssets *create();
    bool init();

    virtual int getVersion();

    virtual cocos2d::__Array *getCurrencies(){return mCurrencies;}
    
    virtual cocos2d::__Array *getGoods() {return mGoods;}
    
    virtual cocos2d::__Array *getCurrencyPacks() {return mGoods;}
    
    virtual cocos2d::__Array *getCategories() {return mCategories;}

    
protected:
    
    cocos2d::__Array *mCurrencies;
    cocos2d::__Array *mCurrencyPacks;
    cocos2d::__Array *mGoods;
    cocos2d::__Array *mCategories;
    
};


#endif //__DiamondAssets_H_
