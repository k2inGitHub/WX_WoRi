//
//  FX_Menu.h
//
//  Created by  on 12-11-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef gs_FX_Menu_h
#define gs_FX_Menu_h

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace cocos2d;

class FX_Menu : public Layer
{
private:
    Size size;
//    Sprite* main_back0;
//    Sprite* main_back1;
//    CCSprite* touch_start;
    Sprite* role_big;
    Armature* menu_title;
    LayerColor* back_layer;
    LayerColor* ts_layer;
    
    bool ts_state;
    int ts_type;
    int select_map_btn;
    int select_role_btn;
    
    Node *rootNode;

    float yun_time;
    int  yun_rand;

public:
    void updateYun(float dt);

    void updateTime(float dt);

    void showVideo();

    void goBossFight();
    
    void goNormalFight();
    
    void videoPlayed(Ref* rtn);

    void closeDialogCallback(Node *pNode);

    void eventButton(Ref* pSender,Widget::TouchEventType type);
    void aniCallback_menu(Armature * armature, MovementEventType type, const std::string& movementID);
    
    void menuStart(Ref* sp);
    
    
    virtual bool initRes();
    ~FX_Menu();
    static FX_Menu* createNode();
    void onExit();
    void updateGame(float dt);
    void onEnterTransitionDidFinish();
    static Scene* scene();
    
    void menuXingJi(Ref* pSender);
    void menuHonor(Ref* pSender);
    void menuRole(Ref* pSender);
    void menuInfo(Ref* pSender);
    void menuShop(Ref* pSender);
    void menuLoop(Ref* pSender);
    
    void addBTN(const char* img,const char* img_sel,Vec2 xy,const ccMenuCallback selector,bool vis,int z,int tag);
    void addBTN_ex(const char* img,Node* toNode,Vec2 xy,Vec2 anchor,const ccMenuCallback selector,bool vis,int z,int tag);
    
    Animation* loadAct_x(const char* str,int frameCount,float delay,int index);
    
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch* touch, Event* event);
};

#endif
