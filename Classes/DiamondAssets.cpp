
#include "DiamondAssets.h"
#include "CCVirtualCurrency.h"
#include "CCVirtualCurrencyPack.h"
#include "CCVirtualGood.h"
#include "CCSingleUseVG.h"
#include "CCPurchaseWithMarket.h"
#include "CCPurchaseWithVirtualItem.h"
#include "CCVirtualCategory.h"
#include "CCUpgradeVG.h"
#include "CCSingleUsePackVG.h"
#include "CCEquippableVG.h"

USING_NS_CC;
using namespace soomla;




DiamondAssets *DiamondAssets::create() {
    DiamondAssets *ret = new DiamondAssets();
    ret->autorelease();
    ret->init();

    return ret;
}

bool DiamondAssets::init() {
    /** Virtual Currencies
    CCVirtualCurrency *diamondCurrency = CCVirtualCurrency::create(
            __String::create("Diamond"),
            __String::create(""),
            __String::create(DIAMOND_CURRENCY_ITEM_ID)
    );**/


    /** Virtual Currency Packs **/

    /*CCVirtualCurrencyPack *fifteenDiamondPack = CCVirtualCurrencyPack::create(
            __String::create("15 Diamond"),                                   // name
            __String::create("Test refund of an item"),                       // description
            __String::create(FIFTEENDIAMOND_PACK_PRODUCT_ID),                                   // item id
            __Integer::create(15),												// number of currencies in the pack
            __String::create(DIAMOND_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(__String::create(FIFTEENDIAMOND_PACK_PRODUCT_ID), CCDouble::create(0.99))
    );
     */
    /** Virtual Goods **/
    
   /* CCVirtualGood *fifteenDiamodGood = CCSingleUseVG::create(
                                                          __String::create("15 Diamond"),                                       // name
                                                          __String::create("Customers buy a double portion on each purchase of this cake"), // description
                                                          __String::create(FIFTEENDIAMOND_PACK_PRODUCT_ID),                                       // item id
                                                          CCPurchaseWithVirtualItem::create(
                                                                                            __String::create(FIFTEENDIAMOND_PACK_PRODUCT_ID), __Integer::create(0.99)
                                                                                            ) // the way this virtual good is purchased
                                                          );
    
    


    mGoods = __Array::create(fifteenDiamodGood,NULL);
    mGoods->retain();
    
    mCurrencies = __Array::create(diamondCurrency, NULL);
    mCurrencies->retain();*/
    

    //mCurrencyPacks = __Array::create(fifteenDiamondPack, NULL);
    //mCurrencyPacks->retain();
    
    /** Virtual Currencies **/
    CCVirtualCurrency *coinCurrency = CCVirtualCurrency::create(
                                                                __String::create("Coin"),                          // Name
                                                                __String::create("Coin currency"),                 // Description
                                                                __String::create("coin_currency_ID")               // Item ID
                                                                );
    
    /** Virtual Currency Packs **/
    
    CCVirtualCurrencyPack *hundCoinPack = CCVirtualCurrencyPack::create(
                                                                        __String::create("100 Coins"),                     // Name
                                                                        __String::create("100 coin currency units"),       // Description
                                                                        __String::create("coins_100_ID"),                  // Item ID
                                                                        __Integer::create(100),                            // Number of currencies in the pack
                                                                        __String::create("coin_currency_ID"),              // The currency associated with this pack
                                                                        CCPurchaseWithMarket::create(                      // Purchase type (with real money $)
                                                                                                     __String::create("coin_currency_ID_15diamonds"),              // Product ID
                                                                                                     __Double::create(0.99)                              // Price (in real money $)
                                                                                                     )
                                                                        );
    
    
    CCVirtualGood *diamomds = CCLifetimeVG::create(
                                                    __String::create("Magic"),                        // Name
                                                    __String::create("15 diamonds!"),                  // Description
                                                    __String::create("15_DIAMOND_ID"),                     // Item ID
                                                    CCPurchaseWithMarket::create(                      // Purchase type (with real money $)
                                                                                 __String::create("com.xiaoye.snowman.30diamonds"),                 // Product ID
                                                                                 __Double::create(0.99)                              // Price (in real money $)
                                                                                 )
                                                    );

    
    /** Virtual Categories **/
    
    CCVirtualCategory *generalCategory = CCVirtualCategory::create(
                                                                   __String::create("General"),
                                                                   __Array::create(__String::create("15_DIAMOND_ID"), NULL));
    
    mCurrencies = __Array::create(coinCurrency, NULL);
    mCurrencies->retain();
    
    mGoods = __Array::create(diamomds, NULL);
    mGoods->retain();
    
    mCurrencyPacks = __Array::create(hundCoinPack, NULL);
    mCurrencyPacks->retain();
    
    mCategories = __Array::create(generalCategory, NULL);
    mCategories->retain();
    
    //mCurrencies->clear();
    
    
    return true;
}

DiamondAssets::~DiamondAssets() {
    CC_SAFE_RELEASE(mCurrencies);
   
}

int DiamondAssets::getVersion() {
    return 0;
}

