# snowman
added by xiaoye on Feb 15th, 2015.

cocos2dx 3.3

http://soom.la ios 支付

https://github.com/soomla/cocos2dx-store

https://github.com/soomla/soomla-cocos2dx-core

还有jansson

android pay 使用的anysdk

ios 支付调试的时候，需要建立SANDIBOX账户，在IOS的设置中也设置该账户

https://itunesconnect.apple.com/WebObjects/iTunesConnect.woa,完善银行账户信息

在iTune创建app时，这里的Bundle ID一定要跟你的项目中的info.plist中的Bundle ID一致.

soomla使用的是jansson数据库，一但把Assets创建就会存在在APP中，要想重新来，得删除app，还有就是可能得改变

__Dictionary *commonParams = __Dictionary::create();
commonParams->setObject(__String::create("ExampleCustomSecret"), "customSecret");
soomla::CCServiceManager::getInstance()->setCommonParams(commonParams);
__Dictionary *storeParams = __Dictionary::create();
storeParams->setObject(__String::create("ExamplePublicKey"), "androidPublicKey");

的值。

AnySDK的借口包在PluginChannel.cpp中
参考http://www.anysdk.com/2014/11/1566
