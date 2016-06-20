//
//  FX_Menu.cpp
//
//  Created by  on 12-11-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "FX_Menu.h"
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
//#include "uiMenuWorldLongWay.h"
#include "FX_Play.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Business.h"
#include "ScoreWallCommon.h"
//#include "AdsMogoInterstitial.h"
#include "HLAdManagerWrapper.hpp"

#endif

using namespace cocos2d;
using namespace CocosDenshion;

//using namespace tinyxml2;
Scene* FX_Menu::scene()
{

    Scene *scene = Scene::create();
    FX_Menu *layer = FX_Menu::createNode();
    scene->addChild(layer);
    return scene;
}

FX_Menu* FX_Menu::createNode() 
{
    FX_Menu *pRet = new FX_Menu();
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

FX_Menu::~FX_Menu()
{
    CCLOGINFO("delloc");
}

bool FX_Menu::initRes()
{
    if ( !Layer::init() )
    {
        return false;
    }
    BannerShow();
    
//    MyApp->task_flag = 1;
//    if(taskShowVedio() > 0)
//        MyApp->task_flag = 0;
//    CCLOG("******************** task_flag = %d",MyApp->task_flag);

    //--------
//    checkFeedback();
    //-----------------------------
//    MyApp->all_cp_num++;
//    int inser = 3;
//    if(inserShowEx()>=0)
//        inser = inserShowEx();
//    
//    CCLOG("******************** all_cp_num = %d",MyApp->all_cp_num);
//    if(inser>0&&MyApp->all_cp_num>=inser)
//    {
//        MyApp->all_cp_num = 0;
//        MyApp->inser_ads_index = 0;
//        AdsMogoInterstitial::sharedInterstitial()->showInterstitial();
//    }
    //-------------------------------------------------------------
//    MyApp->limit_bullet_lv = 10;
//    int temp_bullet_lv = um_on_off((char*)"jinji_open");
//    if(temp_bullet_lv>=0)
//        MyApp->limit_bullet_lv = temp_bullet_lv;
//    CCLOG("******************** temp_bullet_lv = %d",temp_bullet_lv);

    
    yun_time = 5;
    //------------------------------------------------------------
    MyApp->in_battle = false;
    MyApp->in_reward = false;
    
    size = (Director::getInstance())->getVisibleSize();

    
    if(MyApp->new_game)
    {
        MyApp->new_game = false;
        
        if (MyApp->isHaveSaveFile())
            MyApp->loadGame();
        else
            MyApp->initGame();
    }
    
    if(MyApp->into_game_num<3)
    {
        MyApp->into_game_num++;
        MyApp->saveGameData_int("into_game_num", MyApp->into_game_num);
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(MyApp->into_game_num>=3)
    {
        CCLOG("%s",MyApp->push_content.c_str());
        const char* temp_str = um_on_off_str((char*)"content1.5");
        CCLOG("%s",temp_str);
        
        int is_push = um_on_off((char*)"Push1.5");
        if(is_push == 1)
        {
            if(strcmp(temp_str, MyApp->push_content.c_str()))
            {
                MyApp->saveGameData_str("push_content", temp_str);
                MyApp->push_content = UserDefault::getInstance()->getStringForKey("push_content");
                
                pushOther();
            }
        }
    }
#endif
    
    ts_state = false;
    
    if(MyApp->isMusic)
    {
        SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/game_bg0.wav");
        SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_bg0.wav",true);
    }
    
    AddCache("game_res.plist");

    CCLOG("SCREEN_W = %f",SCREEN_W);
    CCLOG("SCREEN_H = %f",SCREEN_H);
    
    Sprite *game_bg = Sprite::create("bg.jpg");
    game_bg->setPosition(Vec2(size.width/2, 0));
    game_bg->setAnchorPoint(Vec2(0.5, 0));
    this->addChild(game_bg);
//----------------------------------------------
    role_big = Sprite::create("txt_cover.png");
    role_big->setAnchorPoint(Vec2(0.5, 1));
    role_big->setPosition(MyApp->Vec2Auto(SCREEN_W/2, SCREEN_H-100));
    this->addChild(role_big,12);
    
    
    int offy1 = 0;
    if(IS_IPHONE4)
        offy1 = -110;
    
    Sprite *game_cover = Sprite::create("cover_role.png");
    game_cover->setPosition(Vec2(size.width/2, offy1+480));
    game_cover->setAnchorPoint(Vec2(0.5, 0));
    this->addChild(game_cover,11);
//--------------------------------------------------------------------------

    int offy0 = 0;
    if(IS_IPHONE4)
        offy0 = -80;
    
    Button *btnStart = Button::create("btn_start.png","btn_start.png","btn_start.png",Widget::TextureResType::LOCAL);
    btnStart->setAnchorPoint(Vec2(0.5,0.5));
    btnStart->setPosition(Vec2(SCREEN_W/2, offy0+448-111/2));
    this->addChild(btnStart,15);
    
    btnStart->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        this->eventButton(pSender, type);
        if (type == Widget::TouchEventType::ENDED)
        {
            Scene *sc = Scene::create();
            FX_Play *temp = FX_Play::createNode();
            sc->addChild(temp);
            TransitionCrossFade *ts = TransitionCrossFade::create(0.5, sc);
            Director::getInstance()->replaceScene(ts);
        }
    });
    
    Button *btnSound_on = Button::create("btn_sound_on.png","btn_sound_on.png","btn_sound_on.png",Widget::TextureResType::LOCAL);
    btnSound_on->setAnchorPoint(Vec2(0.5,0.5));
    btnSound_on->setPosition(Vec2(SCREEN_W/2, offy0+185-93/2));
    this->addChild(btnSound_on,15,100);
    
    btnSound_on->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        this->eventButton(pSender, type);
        if (type == Widget::TouchEventType::ENDED)
        {
            MyApp->isMusic = false;
            MyApp->saveGameData_bool("isMusic", MyApp->isMusic);
            SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
            
            MyApp->isSound = false;
            MyApp->saveGameData_bool("isSound", MyApp->isSound);
            
            this->getChildByTag(100)->setVisible(false);
            this->getChildByTag(101)->setVisible(true);
        }
    });
    
    Button *btnSound_off = Button::create("btn_sound_off.png","btn_sound_off.png","btn_sound_off.png",Widget::TextureResType::LOCAL);
    btnSound_off->setAnchorPoint(Vec2(0.5,0.5));
    btnSound_off->setPosition(Vec2(SCREEN_W/2, offy0+185-93/2));
    this->addChild(btnSound_off,15,101);
    
    btnSound_off->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        this->eventButton(pSender, type);
        if (type == Widget::TouchEventType::ENDED)
        {
            MyApp->isMusic = true;
            MyApp->saveGameData_bool("isMusic", MyApp->isMusic);
            SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_bg0.wav",true);
            
            MyApp->isSound = true;
            MyApp->saveGameData_bool("isSound", MyApp->isSound);
            
            this->getChildByTag(100)->setVisible(true);
            this->getChildByTag(101)->setVisible(false);
        }
    });
    
    
    
    if(soundShow())
    {
        if(MyApp->isMusic&&MyApp->isSound){
            btnSound_on->setVisible(true);
            btnSound_off->setVisible(false);
        }
        else{
            btnSound_on->setVisible(false);
            btnSound_off->setVisible(true);
        }
    }
    else{
        btnSound_on->setVisible(false);
        btnSound_off->setVisible(false);
    }
    
//    Button *btnLoop = Button::create("btn_top.png","btn_top.png","btn_top.png",Widget::TextureResType::LOCAL);
//    btnLoop->setAnchorPoint(Vec2(0.5,0.5));
//    btnLoop->setPosition(Vec2(SCREEN_W/2, offy0+305-93/2));//(SCREEN_W/2, offy0+185-93/2)
//    this->addChild(btnLoop,15);
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
    touchListener->onTouchBegan = CC_CALLBACK_2(FX_Menu::onTouchBegan,this);
    touchListener->onTouchMoved = CC_CALLBACK_2(FX_Menu::onTouchMoved,this);
    touchListener->onTouchEnded = CC_CALLBACK_2(FX_Menu::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void FX_Menu::updateTime(float dt)
{
    if(MyApp->in_freegold_state&&shipinShow(0))
    {
        MyApp->freegold_delay_time--;
        
        string limit_t = MyApp->formatTime(MyApp->freegold_delay_time);
        
        MyApp->addTextNumEx(this->getChildByTag(191900), limit_t, 83, 9, 17, Color3B(255,255,255));

        if(MyApp->freegold_delay_time==0)
        {
            MyApp->freegold_delay_time = 0;
            MyApp->in_freegold_state = false;
            
            Button *btnVideo = (Button*)rootNode->getChildByTag(39)->getChildByTag(200);
            btnVideo->setVisible(true);
            this->getChildByTag(191900)->setVisible(false);

        }
    }
}
void FX_Menu::showVideo()
{
    if(!MyApp->in_freegold_state)
    {
        MyApp->in_freegold_state = true;
        MyApp->saveGameData_bool("in_freegold_state", MyApp->in_freegold_state);
        
        MyApp->freegold_sys_time = (int)MyApp->getSysTime();
        MyApp->saveGameData_long("freegold_sys_time", MyApp->freegold_sys_time);
        
        MyApp->refrushTime();
        
        
        Button *btnVideo = (Button*)rootNode->getChildByTag(39)->getChildByTag(200);
        btnVideo->setVisible(false);
        this->getChildByTag(191900)->setVisible(true);

        //-------------------
        //    if(shipinCount()-MyApp->eday_video_get_gold>0)
        {
            NOTIFICATION->addObserver(this, callfuncO_selector(FX_Menu::videoPlayed), "VideoPlayed", NULL);
            MyApp->inser_ads_index = 10;
//            AdsMogoInterstitial::sharedInterstitial()->showInterstitial();
            HLAdManagerWrapper::showUnsafeInterstitial();
        }
        //    else
        //    {
        //        MyApp->dlg_ts_index = 1;
        //        uiMenuDialog *dlg = uiMenuDialog::create(106);
        //        this->addChild(dlg, 100000);
        //    }
    }
    
}
void FX_Menu::goBossFight()
{
    bool flag = false;
    for (int i = 0; i<NUM_FIGHTERS; i++)
    {
        if(MyApp->g_bullet_lv[i]>=MyApp->limit_bullet_lv-1)
            flag = true;
    }
    if(flag){
        MyApp->gameMode = GameModeBoss;
        menuShop(NULL);
    }
    else{
    
    }
}
void FX_Menu::goNormalFight()
{
    MyApp->gameMode = GameModeNormal;
    menuShop(NULL);
}
void FX_Menu::videoPlayed(Ref* rtn)
{
    NOTIFICATION->removeObserver(this, "VideoPlayed");
    
//    int max_bullet = 0;
//    for (int i = 0; i<NUM_FIGHTERS; i++)
//    {
//        if(max_bullet<MyApp->g_bullet_lv[i])
//            max_bullet = MyApp->g_bullet_lv[i];
//    }
//    
//    int level_bs = 1;
//    if(max_bullet>=1&&max_bullet<=10)
//        level_bs = 1;
//    if(max_bullet>=11&&max_bullet<=20)
//        level_bs = 2;
//    if(max_bullet>=21&&max_bullet<=30)
//        level_bs = 3;
//    if(max_bullet>=31&&max_bullet<=40)
//        level_bs = 4;
//    if(max_bullet>=41&&max_bullet<=50)
//        level_bs = 5;
//    if(max_bullet>=51&&max_bullet<=60)
//        level_bs = 6;
    
    int min_gold = shipinGoldMin();
    int max_gold = shipinGoldMax();
    int add_gold = (min_gold+arc4random()%max_gold)*100;
    
    MyApp->info_total_gold+=add_gold;
    MyApp->saveInfoData(6);
    
    MyApp->eday_video_get_gold++;
    MyApp->saveGameData_int("eday_video_get_gold", MyApp->eday_video_get_gold);
    
    char t_m[64] = {0};
    sprintf(t_m, "恭喜获得%d金币",add_gold);
    
    if(BannerReceived())
        MyApp->infoKuangEx(this, t_m);
    else
        MyApp->infoKuang(this, t_m);
    
//    MyApp->addTextNum(rootNode->getChildByTag(39)->getChildByTag(200), (shipinCount()-MyApp->eday_video_get_gold), 110, 38, 20, Color3B(114,29,32));

}
void FX_Menu::closeDialogCallback(Node *pNode)
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
void FX_Menu::aniCallback_menu(Armature * armature, MovementEventType type, const std::string& movementID)
{
    if (type == COMPLETE)
    {
        if(movementID.compare("efx_main_begin") == 0)
        {
            armature->getAnimation()->play("efx_main_ing", -1, 1);
        }
    }
}
void FX_Menu::eventButton(Ref* pSender,Widget::TouchEventType type)
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

void FX_Menu::menuRole(Ref* sp)
{

}

void FX_Menu::updateYun(float dt)
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
void FX_Menu::updateGame(float dt)
{
//    int gx0 = main_back0->getPosition().x;
//    int gy0 = main_back0->getPosition().y;
//    int gx1 = main_back1->getPosition().x;
//    int gy1 = main_back1->getPosition().y;
//    
//    if(gy0>-FX_App::share()->map_w){
//        main_back0->setPosition(Vec2(gx0, gy0-(2)));
//    }
//    else{
//        main_back0->setPosition(Vec2(gx0, gy1+FX_App::share()->map_w-(2)));
//    }
//    
//    if(gy1>-FX_App::share()->map_w){
//        main_back1->setPosition(Vec2(gx1, gy1-(2)));
//    }
//    else{
//        main_back1->setPosition(Vec2(gx1, gy0+FX_App::share()->map_w-(2)));
//    }
}

Animation* FX_Menu::loadAct_x(const char* str,int frameCount,float delay,int index)
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
void FX_Menu::menuXingJi(Ref* pSender)
{
}
void FX_Menu::menuHonor(Ref* pSender)
{
}

void FX_Menu::menuStart(Ref* pSender)
{
}
void FX_Menu::menuInfo(Ref* pSender)
{
}

void FX_Menu::menuShop(Ref* pSender)
{
}

void FX_Menu::menuLoop(Ref* pSender)
{

    if(FX_App::share()->in_reward)
        return;

    MyApp->playSfx("sound/click.aif");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    loopShow();
#endif
}

void FX_Menu::addBTN_ex(const char* img,Node* toNode,Vec2 xy,Vec2 anchor,const ccMenuCallback selector,bool vis,int z,int tag)
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

void FX_Menu::addBTN(const char* img,const char* img_sel,Vec2 xy,const ccMenuCallback selector,bool vis,int z,int tag)
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

bool FX_Menu::onTouchBegan(Touch *touch,Event *pEvent)
{
    return true;
}

void FX_Menu::onTouchMoved(Touch *touch,Event *pEvent)
{
    
}

void FX_Menu::onTouchEnded(Touch *touch,Event *pEvent)
{
    
}
void FX_Menu::onEnterTransitionDidFinish()
{
//    menu_title->getAnimation()->play("efx_main_begin",-1, 0);
//    menu_title->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(FX_Menu::aniCallback_menu,this));
    
    this->schedule(schedule_selector(FX_Menu::updateGame), 0.02f);
    this->schedule(schedule_selector(FX_Menu::updateYun));

    Layer::onEnterTransitionDidFinish();
    
//    timeval now;
//    gettimeofday(&now, NULL);
//    tm* tm;
//    tm = localtime((time_t *)&now.tv_sec);
//    
//    int day = tm->tm_yday;
//    CCLOG("day = %d",day);
//    CCLOG("game_day = %d",MyApp->game_day);
//    
////    FX_Spcial *spcial = FX_Spcial::createNode();
////    this->addChild(spcial, 1000000,12121212);
//
//    if(MyApp->game_first_day)
//    {
//        CCLOG("game_first_day");
//        
//        FX_Spcial *spcial = FX_Spcial::createNode();
//        this->addChild(spcial, 1000000,12121212);
//        FX_App::share()->in_reward = true;
//        FX_App::share()->get_reward_index = 0;
//        FX_App::share()->saveGameData_int("get_reward_index", MyApp->get_reward_index);
//
//        FX_App::share()->game_day = day;
//        FX_App::share()->saveGameData_int("game_day", MyApp->game_day);
//    }
//    else
//    {
//        if(abs(day-FX_App::share()->game_day) == 1)
//        {
//            MyApp->game_day = day;
//            
//            FX_Spcial *spcial = FX_Spcial::createNode();
//            this->addChild(spcial, 1000000,12121212);
//            FX_App::share()->in_reward = true;
//        }
//        if(abs(day-FX_App::share()->game_day) > 1)
//        {
//            MyApp->game_day = day;
//            
//            FX_Spcial *spcial = FX_Spcial::createNode();
//            this->addChild(spcial, 1000000,12121212);
//            FX_App::share()->in_reward = true;
//            FX_App::share()->get_reward_index = 0;
//            FX_App::share()->saveGameData_int("get_reward_index", FX_App::share()->get_reward_index);
//        }
//    }
//    //-----------------------------
//    
//    if(MyApp->first_in&&inserShowEvery())
//    {
//        MyApp->first_in = false;
//        MyApp->inser_ads_index = 0;
//        AdsMogoInterstitial::sharedInterstitial()->showInterstitial();
//    }
//    
//    if(MyApp->dealDayTask()>0)
//        this->getChildByTag(9999)->setVisible(true);
//    else
//        this->getChildByTag(9999)->setVisible(false);
//    //--
//    if(MyApp->loadGameData_bool("FeedbackNew"))
//        this->getChildByTag(9998)->setVisible(true);
//    else
//        this->getChildByTag(9998)->setVisible(false);
}

void FX_Menu::onExit()
{
    CCLOG("exit");
    
//    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/efx_mainhd.csb");

    this->unscheduleAllCallbacks();
    this->removeAllChildrenWithCleanup(true);
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    Layer::onExit();
}
