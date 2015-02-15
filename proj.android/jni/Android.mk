LOCAL_PATH := $(call my-dir)
$(call import-add-path,$(LOCAL_PATH)/../)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
		../../Classes/Audio.cpp \
		../../Classes/GameScene.cpp \
		../../Classes/Chinese.cpp \
		../../Classes/ComboEffect.cpp \
		../../Classes/FloatWord.cpp \
		../../Classes/GameData.cpp \
		../../Classes/GameLayer.cpp \
		../../Classes/LayerChangeUtil.cpp \
		../../Classes/MenuLayer.cpp \
		../../Classes/LevelMsgLayer.cpp \
		../../Classes/MenuScene.cpp \
		../../Classes/Star.cpp \
		../../Classes/StarMatrix.cpp \
		../../Classes/StarParticle.cpp \
		../../Classes/TopMenu.cpp \
		../../Classes/NumberSprite.cpp \
		../../Classes/ShowNumberNode.cpp \
		../../Classes/MyKeyboardDelegate.cpp \
		../../Classes/ExitDialog.cpp \
		../../Classes/DialogLayer.cpp \
		../../Classes/PopupLayer.cpp \
		../../Classes/XMLParser.cpp \
		../../Classes/PluginChannel.cpp	\
		../../Classes/PopupLayerExt.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
		$(LOCAL_PATH)/../protocols/android \
		$(LOCAL_PATH)/../protocols/include

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += PluginProtocolStatic

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,protocols/android)
