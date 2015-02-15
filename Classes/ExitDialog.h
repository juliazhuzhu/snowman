#ifndef _EXITDLG_H_
#define _EXITDLG_H_

#include "DialogLayer.h"
USING_NS_CC;
class ExitDlg : public DialogLayer
{
public:
    virtual bool onInitDialog();

    CREATE_FUNC(ExitDlg);

public:
    /** 确认和退出按钮 */
    void okMenuItemCallback(CCObject *obj);
    void cancelMenuItemCallback(CCObject *obj);
};

#endif