//
//  FX_Play.h
//
//

#ifndef gs_FX_Play_h
#define gs_FX_Play_h

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace cocos2d;

class FX_Play : public Layer
{
private:
    
    
    int role_act_index;
    
    Vec2 m_touchPoint;
    bool m_touchMoved;
    Vec2 m_deltaPoint;
    
    Size size;

    Sprite* sp_role;
    Layer* over_layer;
    Layer* play_layer;
    Sprite* sp_boss;
    float boss_spx0;
    float boss_spy0;
    
    
    int role_in_hit;
    bool boss_in_hit;
    int ts_type;
    int select_map_btn;
    int select_role_btn;
    
    Node *rootNode;

    float yun_time;
    int  yun_rand;

    bool game_over;
    float speed_step;
public:
    void act_over(Node* pSender);

    void addHitEfx(int type,float x,float y);

    void move_over0(Node* pSender);
    void move_over1(Node* pSender);
    void move_over2(Node* pSender);
    void move_over3(Node* pSender);

    void updateRolePosition(float dt);

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
    ~FX_Play();
    static FX_Play* createNode();
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
