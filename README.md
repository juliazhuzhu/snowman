# snowman
added by xiaoye on Feb 15th, 2015.

cocos2dx 3.4

http://soom.la ios 支付

https://github.com/soomla/cocos2dx-store

https://github.com/soomla/soomla-cocos2dx-core

还有jansson
直接把 jansson 目录拖到 popStar目录下，不能拖到cocos2d_libs.xcodeproj的对应目录下.

android pay 使用的1sdk

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



AnySDK的接口包在PluginChannel.cpp中
参考http://www.anysdk.com/2014/11/1566
github 简单那使用http://rogerdudler.github.io/git-guide/index.zh.html

从MAC MINI迁移到MAC PRO上的时候遇到一个问题。
在MAC PRO环境搭建好以后，编译运行游戏，在ANDROID总是遇到这么一个问题， LIBC Fatal error (SIGILL).
IOS 没有问题。
所以应该不是APP层面的问题，应该是环境或者参数设定的问题。
注意到，在运行build_native.sh出现告警，提示
Android NDK: WARNING: APP_PLATFORM android-19 is larger than android:minSdkVersion 9 in ./AndroidMan
解决办法
只需要在你的工程的：
Application.mk
文件中添加如下代码即可：
[cpp] view plaincopy
APP_PLATFORM := android-9
重新编译运行，问题解决。
