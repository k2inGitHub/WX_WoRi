//
//  FX_Play.cpp
//
//
#include "FX_Play.h"
//#include "FX_Game.h"
//#include "FX_Info.h"
//#include "FX_Shop.h"
#include "FX_App.h"
//#include "uiMenuDialog.h"
//#include "FX_Load.h"
//#include "FX_Spcial.h"
//#include "FX_Role.h"
//#include "FX_Honor.h"
//#include "Video.h"
#include "SimpleAudioEngine.h"
//#include "FX_Chengj.h"
//#include "FX_DayTask.h"
#include "FX_Menu.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Business.h"
#include "ScoreWallCommon.h"
//#include "AdsMogoInterstitial.h"
#include "HLAdManagerWrapper.hpp"

#endif

using namespace cocos2d;
using namespace CocosDenshion;

//using namespace tinyxml2;
Scene* FX_Play::scene()
{

    Scene *scene = Scene::create();
    FX_Play *layer = FX_Play::createNode();
    scene->addChild(layer);
    return scene;
}

FX_Play* FX_Play::createNode() 
{
    FX_Play *pRet = new FX_Play();
    if (pRet && pRet->initRes())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

FX_Play::~FX_Play()
{
    CCLOGINFO("delloc");
}

bool FX_Play::initRes()
{
    if (!Layer::init())
        return false;
    
    speed_step = 5;
    MyApp->play_num = 0;
    boss_in_hit = false;
    role_in_hit = false;
    game_over = false;
    
    size = (Director::getInstance())->getVisibleSize();

    Sprite *game_bg = Sprite::create("bg.jpg");
    game_bg->setPosition(Vec2(SCREEN_W/2, 0));
    game_bg->setAnchorPoint(Vec2(0.5, 0));
    this->addChild(game_bg);
    
    play_layer = Layer::create();
    this->addChild(play_layer,10);
    
    
    Sprite *line = createCache("line.png");
    line->setPosition(Vec2(SCREEN_W/2, 315));
    line->setAnchorPoint(Vec2(0.5, 0));
    play_layer->addChild(line,1);
    
    for (int i = 0; i<8; i++)
    {
        Sprite *enmey0 = createCache("enmey0_0.png");
        enmey0->setPosition(Vec2(40+80*i, SCREEN_H));
        enmey0->setAnchorPoint(Vec2(0.5, 1));
        play_layer->addChild(enmey0,2);
        
        Animation* temp_act1 = loadAct_x("enmey0_",2,0.2,0);
        Animate *act21 = Animate::create(temp_act1);
        enmey0->runAction(RepeatForever::create(act21));
    }

//----------------------------------------------
    sp_role = createCache("role0_0.png");
    sp_role->setAnchorPoint(Vec2(0.5, 0.5));
    sp_role->setPosition(Vec2(SCREEN_W/2, 90+52));
    play_layer->addChild(sp_role,12);
    
    role_act_index = 0;
    
    Sprite *teach0 = createCache("teach0.png");
    teach0->setPosition(Vec2(SCREEN_W/2, 125));
    teach0->setAnchorPoint(Vec2(0.5, 0));
    play_layer->addChild(teach0,13,1000);
    
    m_touchPoint = sp_role->getPosition();
    m_touchMoved = false;
    m_deltaPoint = Vec2::ZERO;
    
    
    Sprite *txt_point = createCache("txt_point.png");
    txt_point->setPosition(Vec2(5, 5));
    txt_point->setAnchorPoint(Vec2(0, 0));
    play_layer->addChild(txt_point,13);
    
    char t_10[64] = {0};
    sprintf(t_10,"%d",MyApp->play_num);
    MyApp->addNum10(play_layer, t_10, "best09.png", Vec2(5+97, 8), Vec2(0, 0), 13, 100);
    
    Sprite *txt_bests = createCache("txt_bests.png");
    txt_bests->setPosition(Vec2(SCREEN_W/2+5, 5));
    txt_bests->setAnchorPoint(Vec2(0, 0));
    play_layer->addChild(txt_bests,13);
    
    char t_11[64] = {0};
    sprintf(t_11,"%d",MyApp->info_best_num);
    MyApp->addNum10(play_layer, t_11, "best09.png", Vec2(SCREEN_W/2+32+97, 8), Vec2(0, 0), 13, 101);

    //---------boss---------
    sp_boss = createCache("boss0_10.png");
    sp_boss->setAnchorPoint(Vec2(0.5, 0.5));
    sp_boss->setPosition(Vec2(SCREEN_W/2, SCREEN_H/2));
    play_layer->addChild(sp_boss,11);
    Animation* temp_act1 = loadAct_x("boss0_1",2,0.5,0);
    Animate *act21 = Animate::create(temp_act1);
    sp_boss->runAction(RepeatForever::create(act21));
    
    float speed_x[2] = {-1,1};
    float speed_y[2] = {-1,1};
    boss_spx0 = speed_step*speed_x[arc4random()%2];
    boss_spy0 = speed_step*speed_y[arc4random()%2];
    
    //------------结束界面-----------------
    over_layer = Layer::create();
    this->addChild(over_layer,20);
    over_layer->setVisible(false);
    LayerColor* back_layer = LayerColor::create(Color4B(0, 0, 0, 100), SCREEN_W, SCREEN_H);
    over_layer->addChild(back_layer);
    
    int offy1 = 200;
    Sprite *txt_chengji = Sprite::create("txt_chengji.png");
    txt_chengji->setPosition(Vec2(SCREEN_W/2, SCREEN_H-offy1));
    txt_chengji->setAnchorPoint(Vec2(0.5, 1));
    over_layer->addChild(txt_chengji,11);
    
    char t_1[64] = {0};
    sprintf(t_1,"%d",MyApp->play_num);
    MyApp->addNum10(over_layer, t_1, "over09.png", Vec2(SCREEN_W/2, SCREEN_H-offy1-70), Vec2(0.5, 1), 11, 10);
    
    Sprite *txt_best = Sprite::create("txt_best.png");
    txt_best->setPosition(Vec2(SCREEN_W/2, SCREEN_H-offy1-240));
    txt_best->setAnchorPoint(Vec2(0.5, 1));
    over_layer->addChild(txt_best,11);
    
    char t_2[64] = {0};
    sprintf(t_2,"%d",MyApp->info_best_num);
    MyApp->addNum10(over_layer, t_2, "best09.png", Vec2(SCREEN_W/2, SCREEN_H-offy1-300), Vec2(0.5, 1), 11, 11);

    
    int offy0 = 0;
    if(IS_IPHONE4)
        offy0 = -80;
    
    Button *btnStart = Button::create("btn_again.png","btn_again.png","btn_again.png",Widget::TextureResType::LOCAL);
    btnStart->setAnchorPoint(Vec2(0.5,0.5));
    btnStart->setPosition(Vec2(SCREEN_W/2, offy0+448-111/2));
    over_layer->addChild(btnStart,15);
    
    btnStart->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        this->eventButton(pSender, type);
        if (type == Widget::TouchEventType::ENDED)
        {
            Scene *sc = Scene::create();
            FX_Play *temp = FX_Play::createNode();
            sc->addChild(temp);
            TransitionCrossFade *ts = TransitionCrossFade::create(0.5, sc);
            Director::getInstance()->replaceScene(ts);
            
            if(MyApp->isMusic)
            {
                SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/game_bg0.wav");
                SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_bg0.wav",true);
            }
        }
    });
    
    Button *btnBack = Button::create("btn_main.png","btn_main.png","btn_main.png",Widget::TextureResType::LOCAL);
    btnBack->setAnchorPoint(Vec2(0.5,0.5));
    btnBack->setPosition(Vec2(SCREEN_W/2, offy0+305-93/2));
    over_layer->addChild(btnBack,15,100);
    
    btnBack->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        this->eventButton(pSender, type);
        if (type == Widget::TouchEventType::ENDED)
        {
            Scene *sc = Scene::create();
            FX_Menu *temp = FX_Menu::createNode();
            sc->addChild(temp);
            TransitionCrossFade *ts = TransitionCrossFade::create(0.5, sc);
            Director::getInstance()->replaceScene(ts);
        }
    });
    
//    Button *btnLoop = Button::create("btn_top.png","btn_top.png","btn_top.png",Widget::TextureResType::LOCAL);
//    btnLoop->setAnchorPoint(Vec2(0.5,0.5));
//    btnLoop->setPosition(Vec2(SCREEN_W/2, offy0+185-93/2));
//    over_layer->addChild(btnLoop,15);
//    
//    btnLoop->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
//        this->eventButton(pSender, type);
//        if (type == Widget::TouchEventType::ENDED)
//        {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//            loopShow();
//#endif
//        }
//    });
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(FX_Play::onTouchBegan,this);
    touchListener->onTouchMoved = CC_CALLBACK_2(FX_Play::onTouchMoved,this);
    touchListener->onTouchEnded = CC_CALLBACK_2(FX_Play::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void FX_Play::updateTime(float dt)
{}
void FX_Play::showVideo()
{}
void FX_Play::goBossFight()
{}
void FX_Play::goNormalFight()
{}
void FX_Play::videoPlayed(Ref* rtn)
{}
void FX_Play::closeDialogCallback(Node *pNode)
{
    if (pNode->getTag() == 27)//战机到达10级
    {
        goNormalFight();
    }
    if (pNode->getTag() == 28)//拥有2架以上战机
    {
        menuRole(NULL);
    }
}
void FX_Play::aniCallback_menu(Armature * armature, MovementEventType type, const std::string& movementID)
{
    if (type == COMPLETE)
    {
        if(movementID.compare("efx_main_begin") == 0)
        {
            armature->getAnimation()->play("efx_main_ing", -1, 1);
        }
    }
}
void FX_Play::eventButton(Ref* pSender,Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::BEGAN)
        ((Node*)pSender)->setScale(1.1f);
    if (type == Widget::TouchEventType::CANCELED)
        ((Node*)pSender)->setScale(1.0f);
    if (type == Widget::TouchEventType::ENDED)
    {
        ((Node*)pSender)->setScale(1.0f);
        MyApp->playSfx("sound/click.aif");
    }
}

void FX_Play::menuRole(Ref* sp)
{

}

void FX_Play::updateYun(float dt)
{
    yun_time+=dt;
    if(yun_time>5)
    {
        yun_rand = int(CCRANDOM_0_1()*1000)%10;
        yun_time = 0;
        float rand_y = CCRANDOM_0_1()*(SCREEN_H-500);
        float rand_y1 = CCRANDOM_0_1()*(SCREEN_H-500);
        
        if(yun_rand>4)
        {
            Sprite* yuan_cai = createCache("cloud.png");
            yuan_cai->setAnchorPoint(Vec2(0, 1));
            yuan_cai->setPosition(Vec2(SCREEN_W, 500+rand_y));
            this->addChild(yuan_cai,5);
            //    yuan_cai->setScale(1+CCRANDOM_0_1());
            
            MoveBy* act0 = MoveBy::create(5+CCRANDOM_0_1()*5, Vec2(-SCREEN_W-211, 0));
            RemoveSelf* act1 = RemoveSelf::create();
            yuan_cai->runAction((Sequence*)Sequence::create(act0,act1, NULL));
        }
        else
        {
            Sprite* yuan_cai2 = createCache("cloud.png");
            yuan_cai2->setAnchorPoint(Vec2(1, 1));
            yuan_cai2->setPosition(Vec2(0, 500+rand_y1));
            this->addChild(yuan_cai2,5);
            //    yuan_cai2->setScale(1+CCRANDOM_0_1());
            yuan_cai2->setFlippedX(true);
            
            MoveBy* act10 = MoveBy::create(5+CCRANDOM_0_1()*5, Vec2(SCREEN_W+211, 0));
            RemoveSelf* act11 = RemoveSelf::create();
            yuan_cai2->runAction((Sequence*)Sequence::create(act10,act11, NULL));
        }
    }
}

void FX_Play::updateRolePosition(float dt)
{
    if(m_touchMoved == false)
        return;
    
    Vec2 pos = sp_role->getPosition();
    pos.x = pos.x + m_deltaPoint.x;
    
    const int XYLimitedRange = 40;
    if(pos.y<XYLimitedRange)
    {
        pos.y = XYLimitedRange;
    }
    else if(pos.y > screenSize.height-XYLimitedRange)
    {
        pos.y = screenSize.height-XYLimitedRange;
    }
    if(pos.x<XYLimitedRange)
    {
        pos.x = XYLimitedRange;
    }
    else if(pos.x > screenSize.width-XYLimitedRange)
    {
        pos.x = screenSize.width-XYLimitedRange;
    }
    sp_role->setPosition(pos);
    
    m_touchMoved = false;
}
void FX_Play::updateGame(float dt)
{
    if(game_over)
        return;
    
    if(!boss_in_hit)
    {
        Vec2 pos = sp_boss->getPosition();
        pos.x = pos.x + boss_spx0;
        pos.y = pos.y + boss_spy0;
        
        const int XYLimitedRange = 88;
        if(pos.y<315+XYLimitedRange)
        {
            pos.y = 315+XYLimitedRange;
            boss_spy0 = -boss_spy0;
        }
        else if(pos.y > SCREEN_H-120-XYLimitedRange)
        {
            pos.y = SCREEN_H-120-XYLimitedRange;
            boss_spy0 = -boss_spy0;
            
        }
        if(pos.x<XYLimitedRange)
        {
            pos.x = XYLimitedRange;
            boss_spx0 = -boss_spx0;
            
        }
        else if(pos.x > SCREEN_W-XYLimitedRange)
        {
            pos.x = SCREEN_W-XYLimitedRange;
            boss_spx0 = -boss_spx0;
            
        }
        sp_boss->setPosition(pos);
        
        
        Rect role_rect = Rect(sp_role->getPosition().x-40, sp_role->getPosition().y-40, 80, 80);
        Rect boss_rect = Rect(sp_boss->getPosition().x-70, sp_boss->getPosition().y-70, 140, 140);

        if(!role_in_hit&&role_rect.intersectsRect(boss_rect))
        {
            boss_in_hit = true;
            role_in_hit = true;
            
            MyApp->play_num++;
            char t_10[64] = {0};
            sprintf(t_10,"%d",MyApp->play_num);
            ((LabelAtlas*)play_layer->getChildByTag(100))->setString(t_10);
            
            addHitEfx(0,sp_role->getPosition().x,sp_role->getPosition().y+40);

            sp_role->stopActionByTag(1111);
            
            MoveTo* act0 = MoveTo::create(0.5, Vec2(sp_role->getPosition().x,90+52));
            CallFuncN* act1= CallFuncN::create(CC_CALLBACK_1(FX_Play::move_over2,this));
            Sequence* act_x0 = (Sequence*)Sequence::create(act0,act1,NULL);
            sp_role->runAction(act_x0);
            
            
            sp_boss->stopAllActions();
            Animation* temp_act1 = loadAct_x("boss0_2",1,0.5,0);
            Animate *act21 = Animate::create(temp_act1);
            DelayTime* act4 = DelayTime::create(0);
            CallFuncN* act5= CallFuncN::create(CC_CALLBACK_1(FX_Play::move_over3,this));
            sp_boss->runAction((Sequence*)Sequence::create(act21,act4,act5, NULL));
        }

    }
}

void FX_Play::move_over3(Node* pSender)
{
    boss_in_hit = false;
    
    float speed_x[2] = {-1,1};
    float speed_y[2] = {-1,1};
    
    speed_step+=0.3;
    boss_spx0 = speed_step*speed_x[arc4random()%2];
    boss_spy0 = speed_step*speed_y[arc4random()%2];
    
    Animation* temp_act2 = loadAct_x("boss0_1",2,0.5,0);
    Animate *act22 = Animate::create(temp_act2);
    RepeatForever* act3 =  RepeatForever::create(act22);
    sp_boss->runAction(act3);
}
void FX_Play::addHitEfx(int type,float x,float y)
{
    if(type == 0)
    {
        Sprite *temp_efx=createCache("efx_hit0.png");
        temp_efx->setPosition(Vec2(x,y));
        play_layer->addChild(temp_efx,800);
        Animation* temp_act = loadAct_x("efx_hit",3,0.05,0);
        Animate *act0 = Animate::create(temp_act);
        CallFuncN* act1 = CallFuncN::create(CC_CALLBACK_1(FX_Play::act_over,this));
        temp_efx->runAction((Sequence*)Sequence::create(act0,act1, NULL));
    }
}
void FX_Play::act_over(Node* pSender)
{
    play_layer->removeChild(pSender,true);
}
Animation* FX_Play::loadAct_x(const char* str,int frameCount,float delay,int index)
{
    Vector<SpriteFrame*> array;
    for(int i = 0; i < frameCount; i++)
    {
        char t[32] = {0};
        sprintf(t, "%s%d.png",str,i);
        
        SpriteFrame *frame = spCache(t);
        if (frame == NULL) {
            Texture2D *pTexture = Director::getInstance()->getTextureCache()->addImage(t);
            Rect rect = Rect::ZERO;
            rect.size = pTexture->getContentSize();
            frame = SpriteFrame::createWithTexture(pTexture, rect);
            SpriteFrameCache::getInstance()->addSpriteFrame(frame, t);
        }
        array.pushBack(frame);
    }
    return Animation::createWithSpriteFrames(array, delay);
}
void FX_Play::menuXingJi(Ref* pSender)
{

}
void FX_Play::menuHonor(Ref* pSender)
{

}

void FX_Play::menuStart(Ref* pSender)
{}
void FX_Play::menuInfo(Ref* pSender)
{}

void FX_Play::menuShop(Ref* pSender)
{}

void FX_Play::menuLoop(Ref* pSender)
{}

void FX_Play::addBTN_ex(const char* img,Node* toNode,Vec2 xy,Vec2 anchor,const ccMenuCallback selector,bool vis,int z,int tag)
{
    Sprite* normal = createCache((img));
    normal->setColor(Color3B::WHITE);
    Sprite* selected = createCache((img));
    selected->setColor(Color3B(150, 150, 150));
    MenuItemSprite* temp = MenuItemSprite::create(normal,selected,NULL,selector);
    temp->setTag(tag);
    temp->setAnchorPoint(anchor);
    
    Menu* tempButton = Menu::create(temp, NULL);
    tempButton->setPosition(xy);
    tempButton->setVisible(vis);
    toNode->addChild(tempButton,z,tag);
}

void FX_Play::addBTN(const char* img,const char* img_sel,Vec2 xy,const ccMenuCallback selector,bool vis,int z,int tag)
{
    Sprite* normal = createCache((img));
    Sprite* selected = createCache((img_sel));
    MenuItemSprite* temp = MenuItemSprite::create(normal,selected,NULL,selector);
    
    temp->setTag(tag);
	    
    Menu* tempButton = Menu::create(temp, NULL);
    tempButton->setPosition(xy);
    tempButton->setVisible(vis);
    this->addChild(tempButton,z,tag);
}

bool FX_Play::onTouchBegan(Touch *touch,Event *pEvent)
{
    if(role_act_index>0)
        return false;
    Vec2 point = touch->getLocation();
    Director::getInstance()->convertToGL(point);
    
    m_touchPoint = touch->getLocation();
    m_deltaPoint = Vec2::ZERO;
    
    play_layer->getChildByTag(1000)->setVisible(false);
    
    return true;
}

void FX_Play::onTouchMoved(Touch *touch,Event *pEvent)
{
    if(role_act_index==0)
    {
        m_touchPoint = touch->getLocation();
        m_deltaPoint = touch->getDelta();
        m_touchMoved = true;
    }
}

void FX_Play::onTouchEnded(Touch *touch,Event *pEvent)
{
    if(role_act_index==0)
    {
        m_touchPoint = touch->getLocation();
        m_deltaPoint = Vec2::ZERO;
        role_act_index = 1;
        
        sp_role->setDisplayFrame(spCache("role0_1.png"));

        MoveBy* act0 = MoveBy::create(1.2, Vec2(0,SCREEN_H-300));
        CallFuncN* act1 = CallFuncN::create(CC_CALLBACK_1(FX_Play::move_over0,this));
        DelayTime* act2 = DelayTime::create(1);
        CallFuncN* act3 = CallFuncN::create(CC_CALLBACK_1(FX_Play::move_over1,this));
        Sequence* act_x0 = (Sequence*)Sequence::create(act0,act1,act2,act3,NULL);
        act_x0->setTag(1111);
        sp_role->runAction(act_x0);
        
        MyApp->playSfx("sound/jump.wav");
    }
}

void FX_Play::move_over0(Node* pSender)
{
    sp_role->setDisplayFrame(spCache("role0_2.png"));
    game_over = true;
    
    if(MyApp->isMusic)
    {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/game_over.wav");
        SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_over.wav",false);
    }

}
void FX_Play::move_over1(Node* pSender)
{
    if(MyApp->play_num>MyApp->info_best_num)
    {
        MyApp->info_best_num = MyApp->play_num;
        MyApp->saveGameData_int("info_best_num", MyApp->info_best_num);
        
        uploadLoop1(MyApp->info_best_num);
    }
    
    char t_10[64] = {0};
    sprintf(t_10,"%d",MyApp->play_num);
    ((LabelAtlas*)over_layer->getChildByTag(10))->setString(t_10);
    
    char t_11[64] = {0};
    sprintf(t_11,"%d",MyApp->info_best_num);
    ((LabelAtlas*)over_layer->getChildByTag(11))->setString(t_11);
    
    play_layer->setVisible(false);
    over_layer->setVisible(true);
    
    
    int inser = 0;
    if(inserShow()>0)
    {
        inser = inserShow();

        MyApp->chaping_num++;

        if(MyApp->chaping_num>=inser)
        {
            MyApp->chaping_num = 0;
            MyApp->inser_ads_index = 0;
//            AdsMogoInterstitial::sharedInterstitial()->showInterstitial();
            HLAdManagerWrapper::showUnsafeInterstitial();
        }
    }
}
void FX_Play::move_over2(Node* pSender)
{
    sp_role->setDisplayFrame(spCache("role0_0.png"));
    role_act_index = 0;
    role_in_hit = false;
}
void FX_Play::onEnterTransitionDidFinish()
{
    this->schedule(schedule_selector(FX_Play::updateGame));
    this->schedule(schedule_selector(FX_Play::updateYun));
    this->schedule(schedule_selector(FX_Play::updateRolePosition));

    Layer::onEnterTransitionDidFinish();
}

void FX_Play::onExit()
{
    CCLOG("exit");

    this->unscheduleAllCallbacks();
    this->removeAllChildrenWithCleanup(true);
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    Layer::onExit();
}
