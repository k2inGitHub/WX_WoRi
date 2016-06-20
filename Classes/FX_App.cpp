//
//  FX_App.cpp
//
//  Created by  on 12-11-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "FX_App.h" 
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ScoreWallCommon.h"
#endif

using namespace cocostudio;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace cocos2d;


static FX_App* shareGame = NULL;

FX_App* FX_App::share()
{
    if (!shareGame) {
        shareGame = new FX_App();
    }
    return shareGame;
}

FX_App::FX_App()
{
    
    gk_boss_name = __Array::create();
    gk_boss_name->retain();
    
    all_cp_num = 0;
    Android_Version = false;
    isSound = false;
    isMusic = false;
    isPush = true;
    isDoLeft = true;
    isFullScreen = true;
    
    gameMode = 0;
    
    new_game = true;
    reset_music = true;
    first_in = false;
    game_buff = 0;
    
    get_reward_index = 0;
    in_reward = false;
    game_px = false;
    chaping_num = 0;

    gold_layer_index = 0;
    
    left_pet_have = false;
    right_pet_have = false;
    left_pet_index = 0;
    right_pet_index = 0;
    
    left_pet_star = 1;
    right_pet_star = 1;
    
    left_pet_lv = 1;
    right_pet_lv = 1;
    
    left_pet_exp = 0;
    right_pet_exp = 0;
    
    sel_info_pet_lr = 0;
    
    for(int i=0; i<NUM_FIGHTERS; i++)
        g_bullet_lv[i] = 0;
    g_bullet_lv[0] = 3;
    
    
    role_index = 0;
    map_index = 0;
    
    is_best_fly = false;
    
    info_best_move = 0;
    info_best_num = 0;
    info_best_total_num = 0;
    
    info_best_gold = 0;
    info_total_game_count = 0;
    info_total_gold = 2000;
    info_total_diamond = 0;
    info_total_yzb = 1000000;

    info_total_kill = 0;
    info_total_boss_kill = 0;
    every_time_kill = 0;
    every_time_boss_kill = 0;

    info_total_use_gold = 0;
    info_total_use_diamond = 0;
    info_total_buy_diamond = 0;

    info_total_pet_num = 0;
    info_all_pet_num = 0;
    info_cc_num = 0;
    info_wq_max_lv_num = 0;
    info_pet_have_lv_up = 0;
    info_total_move = 0;
    info_total_use_item = 0;
    info_total_pet_max_lv_num = 0;
    info_use_skill_up_num = 0;
    info_get_all_item = 0;
    
    eday_game1_num = 0;
    eday_game2_num = 0;
    eday_wq_up_num = 0;
    eday_make_pet_num = 0;
    eday_boss_kill = 0;
    eday_free_pet = true;
    eday_bbox_num = 0;
    eday_buy_good_num = 0;
    eday_video_get_gold = 0;

    
    day_task_type = 0;
    
    for (int i = 0; i<NUM_FIGHTERS; i++) {
        role_open[i] = false;
    }
    role_open[0] = true;
    
    for (int i = 0; i<3; i++) {
        map_open[i] = false;
    }
    map_open[0] = true;
    
    for (int i = 0; i<CHENGJ_NUM; i++)
    {
        chengjiu_lv_index[i] = 0;
        chengjiu_get[i] = false;
    }
    
    for (int i = 0; i<10; i++)
    {
        dayTask_get[i] = false;
    }
    
//    for (int i = 0; i<CJ_0_NUM; i++) {
//        cj_open0[i] = false;
//    }
//    
//    for (int i = 0; i<CJ_1_NUM; i++) {
//        cj_open1[i] = false;
//    }
//    
//    for (int i = 0; i<CJ_0_NUM; i++) {
//        cj_get0[i] = false;
//    }
//    
//    for (int i = 0; i<CJ_1_NUM; i++) {
//        cj_get1[i] = false;
//    }
    
    for (int i = 0; i<HONOR_NUM; i++) {
        honor_open[i] = false;
        enemy_kill_num[i] = 0;
    }
    
    for (int i = 0; i<HONOR_NUM; i++) {
        for (int j = 0; j<4; j++){
            honor_get_jl[i][j] = false;
        }
    }
    
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<JJC_NUM; j++){
            jjc_open[i][j] = false;
        }
    }
    jjc_open[0][0] = true;
    
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<JJC_NUM; j++){
            jjc_success[i][j] = false;
        }
    }
    
    for (int i = 0; i<5; i++) {
        jjc_level[i] = false;
    }
    jjc_level[0] = true;
    jjc_level[1] = true;
    jjc_level[2] = true;


    jjc_index = 0;
    
    g_skill_up_num = 0;
    g_cc1500_num = 0;
    g_cc3000_num = 0;
    g_skill_down_num = 0;
    g_relive_num = 0;
    g_pet_double_exp_num = 0;
    g_dead_cc_num = 0;
    
    vPetIndex = __Array::create();
    vPetIndex->retain();
    vPetLv = __Array::create();
    vPetLv->retain();
    vPetExp = __Array::create();
    vPetExp->retain();
    vPetStar = __Array::create();
    vPetStar->retain();
    vDayTaskIndex = __Array::create();
    vDayTaskIndex->retain();
    vDayTask_id = __Array::create();
    vDayTask_id->retain();
    
    vLongWay_boss_id = __Array::create();
    vLongWay_boss_id->retain();
    vLongWay_fly = __Array::create();
    vLongWay_fly->retain();
    
    array_count = 0;
    
    role0_gz = false;
    
    teach0_complete = false;
    teach1_complete = false;
    teach2_complete = false;
    teach3_complete = false;
    
    first_fx  = false;
    
    loading_index = 0;
    
    timeval now;
    gettimeofday(&now, NULL);
    tm* tm;
    tm = localtime((time_t *)&now.tv_sec);
    
    int day = tm->tm_yday;
    
    game_first_day = true;
    game_day = day;
    
    into_game_num = 0;
    push_content = "X";
    
    map_w = MAP_WWW;

    in_battle = false;
    gotDuiHuan = false;
    
    jg_target_y = SCREEN_H;

    
    //------longWay----------
    openedbossLongWay = 1;
    
    // boss_star数据
    star_boss_data[0][0] = 2;
    star_boss_data[0][1] = 3;
    star_boss_data[0][2] = 1;
    
    star_boss_data[1][0] = 3;
    star_boss_data[1][1] = 2;
    star_boss_data[1][2] = 3;
    
    star_boss_data[2][0] = 2;
    star_boss_data[2][1] = 4;
    star_boss_data[2][2] = 3;
    
    star_boss_data[3][0] = 4;
    star_boss_data[3][1] = 3;
    star_boss_data[3][2] = 3;
    
    star_boss_data[4][0] = 3;
    star_boss_data[4][1] = 4;
    star_boss_data[4][2] = 3;
    
    star_boss_data[5][0] = 5;
    star_boss_data[5][1] = 4;
    star_boss_data[5][2] = 4;
    
    star_boss_data[6][0] = 4;
    star_boss_data[6][1] = 4;
    star_boss_data[6][2] = 5;
    
    star_boss_data[7][0] = 5;
    star_boss_data[7][1] = 4;
    star_boss_data[7][2] = 4;

    bossFighting = 0;
    
    freegold_delay_time = 0;
    freegold_sys_time = 0;
    in_freegold_state = false;

}

void FX_App::initGame()
{
    
    saveGameData_long("freegold_sys_time", freegold_sys_time);
    saveGameData_bool("in_freegold_state", in_freegold_state);

    
    saveGameData_bool("gotDuiHuan", gotDuiHuan);

    saveGameData_str("push_content", push_content.c_str());
    saveGameData_int("into_game_num", into_game_num);
    
    saveGameData_bool("game_first_day", game_first_day);
    saveGameData_int("game_day", game_day);
    saveGameData_int("get_reward_index", get_reward_index);


    saveGameData_int("g_skill_up_num", g_skill_up_num);
    saveGameData_int("g_cc1500_num", g_cc1500_num);
    saveGameData_int("g_cc3000_num", g_cc3000_num);
    saveGameData_int("g_skill_down_num", g_skill_down_num);
    saveGameData_int("g_relive_num", g_relive_num);
    saveGameData_int("g_pet_double_exp_num", g_pet_double_exp_num);
    saveGameData_int("g_dead_cc_num", g_dead_cc_num);
   
    
    for (int i = 0; i<CHENGJ_NUM; i++)
    {
        char s1[64] = {0};
        sprintf(s1,"chengjiu_lv_index%d",i);
        saveGameData_int(s1, chengjiu_lv_index[i]);
        char s2[64] = {0};
        sprintf(s2,"chengjiu_get%d",i);
        saveGameData_bool(s2, chengjiu_get[i]);
    }
    
    
    for (int i = 0; i<10; i++)
    {
        char s2[64] = {0};
        sprintf(s2,"dayTask_get%d",i);
        saveGameData_bool(s2, dayTask_get[i]);
    }
    
//    for (int i = 0; i<CJ_0_NUM; i++) {
//        char s2[64] = {0};
//        sprintf(s2,"cj_open0%d",i);
//        saveGameData_bool(s2, cj_open0[i]);
//    }
//    
//    for (int i = 0; i<CJ_1_NUM; i++) {
//        char s2[64] = {0};
//        sprintf(s2,"cj_open1%d",i);
//        saveGameData_bool(s2, cj_open1[i]);
//    }
//    
//    for (int i = 0; i<CJ_0_NUM; i++) {
//        char s2[64] = {0};
//        sprintf(s2,"cj_get0%d",i);
//        saveGameData_bool(s2, cj_get0[i]);
//    }
//    
//    for (int i = 0; i<CJ_1_NUM; i++) {
//        char s2[64] = {0};
//        sprintf(s2,"cj_get1%d",i);
//        saveGameData_bool(s2, cj_get1[i]);
//    }
    
    for (int i = 0; i<HONOR_NUM; i++) {
        char s2[64] = {0};
        sprintf(s2,"honor_open%d",i);
        saveGameData_bool(s2, honor_open[i]);
    }
    
    for (int i = 0; i<HONOR_NUM; i++) {
        for (int j = 0; j<4; j++){
            char s2[64] = {0};
            sprintf(s2,"honor_get_jl%d%d",i,j);
            saveGameData_bool(s2, honor_get_jl[i][j]);
        }
    }
    
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<JJC_NUM; j++){
            char s2[64] = {0};
            sprintf(s2,"jjc_open%d%d",i,j);
            saveGameData_bool(s2, jjc_open[i][j]);
        }
    }
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<JJC_NUM; j++){
            char s2[64] = {0};
            sprintf(s2,"jjc_success%d%d",i,j);
            saveGameData_bool(s2, jjc_success[i][j]);
        }
    }
    
    for (int i = 0; i<5; i++) {
        char s2[64] = {0};
        sprintf(s2,"jjc_level%d",i);
        saveGameData_bool(s2, jjc_level[i]);
    }
    
    for (int i = 0; i<HONOR_NUM; i++) {
        char s2[64] = {0};
        sprintf(s2,"enemy_kill_num%d",i);
        saveGameData_int(s2, enemy_kill_num[i]);
    }
    
    for (int i = 0; i<NUM_FIGHTERS; i++) {
        char s2[64] = {0};
        sprintf(s2,"role_open%d",i);
        saveGameData_bool(s2, role_open[i]);
    }
    
    for (int i = 0; i<3; i++) {
        char s2[64] = {0};
        sprintf(s2,"map_open%d",i);
        saveGameData_bool(s2, map_open[i]);
    }
    
    saveGameData_int("role_index", role_index);
    saveGameData_int("map_index", map_index);
    
    saveSelPet();
    
    saveGameData_bool("game_px", game_px);
    
    saveGameData_int("game_buff", game_buff);
    
    
    char buf[64] = {0};
    for(int i=0; i<NUM_FIGHTERS; i++)
    {
        sprintf(buf,"g_bullet_lv%d",i);
        saveGameData_int(buf, g_bullet_lv[i]);
    }
    
    saveGameData_bool("isSound", isSound);
    saveGameData_bool("isMusic", isMusic);
    saveGameData_bool("isDoLeft", isDoLeft);
    saveGameData_bool("isFullScreen", isFullScreen);

    saveGameData_int("info_best_move", info_best_move);
    saveGameData_int("info_best_num", info_best_num);
    saveGameData_int("info_best_total_num", info_best_total_num);

    saveGameData_int("info_best_gold", info_best_gold);
    saveGameData_int("info_total_game_count", info_total_game_count);
    saveGameData_int("info_total_gold", info_total_gold);
    saveGameData_int("info_total_diamond", info_total_diamond);
    saveGameData_int("info_total_yzb", info_total_yzb);


    saveGameData_int("info_total_kill", info_total_kill);
    saveGameData_int("info_total_boss_kill", info_total_boss_kill);
    saveGameData_int("every_time_kill", every_time_kill);
    saveGameData_int("every_time_boss_kill", every_time_boss_kill);

    saveGameData_int("info_total_buy_diamond", info_total_buy_diamond);

    saveGameData_int("info_total_use_diamond", info_total_use_diamond);
    saveGameData_int("info_total_use_gold", info_total_use_gold);
    saveGameData_int("info_total_pet_num", info_total_pet_num);
    saveGameData_int("info_all_pet_num", info_all_pet_num);
    saveGameData_int("info_cc_num", info_cc_num);
    saveGameData_int("info_wq_max_lv_num", info_wq_max_lv_num);
    saveGameData_int("info_pet_have_lv_up", info_pet_have_lv_up);
    saveGameData_int("info_total_move", info_total_move);
    saveGameData_int("info_total_use_item", info_total_use_item);
    saveGameData_int("info_total_pet_max_lv_num", info_total_pet_max_lv_num);
    saveGameData_int("info_use_skill_up_num", info_use_skill_up_num);
    saveGameData_int("info_get_all_item", info_get_all_item);
    
    saveGameData_int("array_count", array_count);
    
    saveGameData_bool("teach0_complete", teach0_complete);
    saveGameData_bool("teach1_complete", teach1_complete);
    saveGameData_bool("teach2_complete", teach2_complete);
    saveGameData_bool("teach3_complete", teach3_complete);
    
    saveGameData_bool("first_fx", first_fx);
    
    saveGameData_bool("role0_gz", role0_gz);
    
    saveGameData_int("eday_game1_num", eday_game1_num);
    saveGameData_int("eday_game2_num", eday_game2_num);
    saveGameData_int("eday_wq_up_num", eday_wq_up_num);
    saveGameData_int("eday_make_pet_num", eday_make_pet_num);
    saveGameData_int("eday_boss_kill", eday_boss_kill);
    saveGameData_int("eday_free_pet", eday_free_pet);
    saveGameData_int("eday_bbox_num", eday_bbox_num);
    saveGameData_int("eday_buy_good_num", eday_buy_good_num);
    
    saveGameData_int("day_task_type", day_task_type);
    saveGameData_int("eday_video_get_gold", eday_video_get_gold);

    initDayTask(0);
    
    vLongWay_boss_id->removeAllObjects();
    for (int i = 0; i<8; i++)
        vLongWay_boss_id->addObject(__String::createWithFormat("%d",1));
    for (int i = 0; i<8; i++)
    {
        char s0[64] = {0};
        sprintf(s0,"vLongWay_boss_id%d",i);
        saveGameData_int(s0, ((__String*)vLongWay_boss_id->getObjectAtIndex(i))->intValue());
    }
    
    vLongWay_fly->removeAllObjects();
    for (int i = 0; i<5; i++)
    {
        char s0[64] = {0};
        sprintf(s0,"vLongWay_fly%d",i);
        saveGameData_int(s0, -1);
    }
    
    resetNumberLongWay = 1;
    saveGameData_int("resetNumberLongWay", resetNumberLongWay);
    fightingPlaneIndex = 0;
    saveGameData_int("fightingPlaneIndex", fightingPlaneIndex);
}
void FX_App::initDayTask(int type)
{
    vDayTaskIndex->removeAllObjects();
    vDayTaskIndex->addObject(__String::createWithFormat("%d",6));
    vDayTaskIndex->addObject(__String::createWithFormat("%d",4));
    
    if(type == 0)
        vDayTaskIndex->addObject(__String::createWithFormat("%d",2));
    if(type == 1)
        vDayTaskIndex->addObject(__String::createWithFormat("%d",5));
    
    vDayTaskIndex->addObject(__String::createWithFormat("%d",0));
    vDayTaskIndex->addObject(__String::createWithFormat("%d",1));
    vDayTaskIndex->addObject(__String::createWithFormat("%d",3));
    
    int task_count = (int)vDayTaskIndex->count();
    saveGameData_int("task_count", task_count);
    for (int i = 0; i<task_count; i++)
    {
        char s0[64] = {0};
        sprintf(s0,"vDayTaskIndex%d",i);
        saveGameData_int(s0, ((__String*)vDayTaskIndex->getObjectAtIndex(i))->intValue());
    }
    //---------------------------------------------------------------
    vDayTask_id->removeAllObjects();
    for (int i = 0; i<7; i++)
    {
        int rand_id = arc4random()%3;
        vDayTask_id->addObject(__String::createWithFormat("%d",rand_id));
    }
    for (int i = 0; i<7; i++)
    {
        char s0[64] = {0};
        sprintf(s0,"vDayTask_id%d",i);
        saveGameData_int(s0, ((__String*)vDayTask_id->getObjectAtIndex(i))->intValue());
    }
    //---------------------------------------------------------------

}
void FX_App::initLongWay(bool day_first)//初始化远征boss
{
    vLongWay_boss_id->removeAllObjects();
    
    int enemy_index[8] = {0,0,0,0,0,0,0,0};
    int number = 0;
    int *temp=new int[12];
    for(int i=0;i<12;i++)
        temp[i]=i;
    
    for(int i=0;i<8;i++)
    {
        number=arc4random()%12;
        
        while(temp[number]==-1)
            number=arc4random()%12;
        
        enemy_index[i] = temp[number];
        temp[number]=-1;
    }
    delete [] temp;
    temp = NULL;
    
    for (int i = 0; i<8; i++)
    {
        CCLOG("enemy_index%d = %d",i,enemy_index[i]);
        vLongWay_boss_id->addObject(__String::createWithFormat("%d",enemy_index[i]));
    }
    for (int i = 0; i<8; i++)
    {
        char s0[64] = {0};
        sprintf(s0,"vLongWay_boss_id%d",i);
        saveGameData_int(s0, ((__String*)vLongWay_boss_id->getObjectAtIndex(i))->intValue());
    }
    
    if(day_first)
    {
        resetNumberLongWay = 1;
        saveGameData_int("resetNumberLongWay", resetNumberLongWay);
    }
    
    vLongWay_fly->removeAllObjects();
    for (int i = 0; i<5; i++)
    {
        char s0[64] = {0};
        sprintf(s0,"vLongWay_fly%d",i);
        saveGameData_int(s0, -1);
    }
    
    fightingPlaneIndex = 0;
    saveGameData_int("fightingPlaneIndex", fightingPlaneIndex);
    setFighting(false);
    
    for (int i = 0; i < 8; i++)
    {
        char str0[64] = {0};
        sprintf(str0,"giftGotLongWay%d",i);
        giftGotLongWay[i] = false;
        saveGameData_bool(str0, giftGotLongWay[i]);
    }
    
    openedbossLongWay = 1;
    saveGameData_int("openedbossLongWay", openedbossLongWay);
    //    bossFightingLongWay = 1;
    //    saveGameData_int("bossFightingLW", bossFightingLongWay);
}
// 重置队列
void FX_App::resetFightPlanes()
{
    initLongWay(false);
    
    resetNumberLongWay --;
    if (resetNumberLongWay<=0)
    {
        resetNumberLongWay = 0;
    }
    saveGameData_int("resetNumberLongWay", resetNumberLongWay);
}
void FX_App::setFighting(bool v)
{
    fighting = v;
    saveGameData_bool("fighting", fighting);
}
void FX_App::loadGame()
{
    in_freegold_state = loadGameData_bool("in_freegold_state");
    freegold_sys_time = loadGameData_long("freegold_sys_time");

    for (int i = 0; i < 8; i++)
    {
        char s0[64] = {0};
        sprintf(s0,"giftGotLongWay%d",i);
        giftGotLongWay[i] = loadGameData_bool(s0);
    }
    
    for (int i = 0; i<5; i++)
    {
        char s0[64] = {0};
        sprintf(s0,"vLongWay_fly%d",i);
        int temp_index = loadGameData_int(s0);
        if(temp_index >= 0)
            vLongWay_fly->addObject(__String::createWithFormat("%d",temp_index));
    }
    
    fighting = loadGameData_bool("fighting");
    openedbossLongWay = loadGameData_int("openedbossLongWay");
    fightingPlaneIndex = loadGameData_int("fightingPlaneIndex");
    resetNumberLongWay = loadGameData_int("resetNumberLongWay");
    
    for (int i = 0; i<8; i++)
    {
        char s0[64] = {0};
        sprintf(s0,"vLongWay_boss_id%d",i);
        vLongWay_boss_id->addObject(__String::createWithFormat("%d",loadGameData_int(s0)));
    }
    
    gotDuiHuan = loadGameData_bool("gotDuiHuan");
    push_content = UserDefault::getInstance()->getStringForKey("push_content");
    into_game_num = loadGameData_int("into_game_num");
    
    game_first_day = loadGameData_bool("game_first_day");
    game_day = loadGameData_int("game_day");
    get_reward_index = loadGameData_int("get_reward_index");
    
    g_skill_up_num = loadGameData_int("g_skill_up_num");
    g_cc1500_num = loadGameData_int("g_cc1500_num");
    g_cc3000_num = loadGameData_int("g_cc3000_num");
    g_skill_down_num = loadGameData_int("g_skill_down_num");
    g_relive_num = loadGameData_int("g_relive_num");
    g_pet_double_exp_num = loadGameData_int("g_pet_double_exp_num");
    g_dead_cc_num = loadGameData_int("g_dead_cc_num");

    
    for (int i = 0; i<CHENGJ_NUM; i++)
    {
        char s1[64] = {0};
        sprintf(s1,"chengjiu_lv_index%d",i);
        chengjiu_lv_index[i] = loadGameData_int(s1);

        char s2[64] = {0};
        sprintf(s2,"chengjiu_get%d",i);
        chengjiu_get[i] = loadGameData_bool(s2);
    }
    
    for (int i = 0; i<10; i++)
    {
        char s2[64] = {0};
        sprintf(s2,"dayTask_get%d",i);
        dayTask_get[i] = loadGameData_bool(s2);
    }
    
//    for (int i = 0; i<CJ_0_NUM; i++) {
//        char s2[64] = {0};
//        sprintf(s2,"cj_open0%d",i);
//        cj_open0[i] = loadGameData_bool(s2);
//    }
    
//    for (int i = 0; i<CJ_1_NUM; i++) {
//        char s2[64] = {0};
//        sprintf(s2,"cj_open1%d",i);
//        cj_open1[i] = loadGameData_bool(s2);
//    }
//    for (int i = 0; i<CJ_0_NUM; i++) {
//        char s2[64] = {0};
//        sprintf(s2,"cj_get0%d",i);
//        cj_get0[i] = loadGameData_bool(s2);
//    }
    
//    for (int i = 0; i<CJ_1_NUM; i++) {
//        char s2[64] = {0};
//        sprintf(s2,"cj_get1%d",i);
//        cj_get1[i] = loadGameData_bool(s2);
//    }
    
    for (int i = 0; i<HONOR_NUM; i++) {
        char s2[64] = {0};
        sprintf(s2,"honor_open%d",i);
        honor_open[i] = loadGameData_bool(s2);
    }
    
    for (int i = 0; i<HONOR_NUM; i++) {
        for (int j = 0; j<4; j++){
            char s2[64] = {0};
            sprintf(s2,"honor_get_jl%d%d",i,j);
            honor_get_jl[i][j] = loadGameData_bool(s2);
        }
    }
    
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<JJC_NUM; j++){
            char s2[64] = {0};
            sprintf(s2,"jjc_open%d%d",i,j);
            jjc_open[i][j] = loadGameData_bool(s2);
        }
    }
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<JJC_NUM; j++){
            char s2[64] = {0};
            sprintf(s2,"jjc_success%d%d",i,j);
            jjc_success[i][j] = loadGameData_bool(s2);
        }
    }
    
    for (int i = 0; i<5; i++) {
        char s2[64] = {0};
        sprintf(s2,"jjc_level%d",i);
        jjc_level[i] = loadGameData_bool(s2);
    }
    
    for (int i = 0; i<HONOR_NUM; i++) {
        char s2[64] = {0};
        sprintf(s2,"enemy_kill_num%d",i);
        enemy_kill_num[i] = loadGameData_int(s2);
    }
    
    for (int i = 0; i<NUM_FIGHTERS; i++) {
        char s2[64] = {0};
        sprintf(s2,"role_open%d",i);
        role_open[i] = loadGameData_bool(s2);
    }
    
    for (int i = 0; i<3; i++) {
        char s2[64] = {0};
        sprintf(s2,"map_open%d",i);
        map_open[i] = loadGameData_bool(s2);
    }
    
    role_index = loadGameData_int("role_index");
    map_index = loadGameData_int("map_index");
    
    left_pet_have = loadGameData_bool("left_pet_have");
    right_pet_have = loadGameData_bool("right_pet_have");

    left_pet_index = loadGameData_int("left_pet_index");
    right_pet_index = loadGameData_int("right_pet_index");
    
    left_pet_star = loadGameData_int("left_pet_star");
    right_pet_star = loadGameData_int("right_pet_star");
    
    left_pet_exp = loadGameData_int("left_pet_exp");
    right_pet_exp = loadGameData_int("right_pet_exp");
    
    left_pet_lv = loadGameData_int("left_pet_lv");
    right_pet_lv = loadGameData_int("right_pet_lv");
    
    
    game_px = loadGameData_bool("game_px");
    
    game_buff = loadGameData_int("game_buff");
    
    char buf[64] = {0};
    for(int i=0; i<NUM_FIGHTERS; i++)
    {
        sprintf(buf,"g_bullet_lv%d",i);
        g_bullet_lv[i] = loadGameData_int(buf);
    }

    isSound = loadGameData_bool("isSound");
    isMusic = loadGameData_bool("isMusic");
    isDoLeft = loadGameData_bool("isDoLeft");
    isFullScreen = loadGameData_bool("isFullScreen");

    info_best_move = loadGameData_int("info_best_move");
    info_best_num = loadGameData_int("info_best_num");
    info_best_total_num = loadGameData_int("info_best_total_num");

    info_best_gold = loadGameData_int("info_best_gold");
    info_total_game_count = loadGameData_int("info_total_game_count");
    info_total_gold = loadGameData_int("info_total_gold");
    info_total_diamond = loadGameData_int("info_total_diamond");
    info_total_yzb = loadGameData_int("info_total_yzb");


    info_total_kill = loadGameData_int("info_total_kill");
    info_total_boss_kill = loadGameData_int("info_total_boss_kill");
    every_time_kill = loadGameData_int("every_time_kill");
    every_time_boss_kill = loadGameData_int("every_time_boss_kill");

    info_total_buy_diamond = loadGameData_int("info_total_buy_diamond");

    info_total_use_diamond = loadGameData_int("info_total_use_diamond");
    info_total_use_gold = loadGameData_int("info_total_use_gold");
    info_total_pet_num = loadGameData_int("info_total_pet_num");
    info_all_pet_num = loadGameData_int("info_all_pet_num");
    info_cc_num = loadGameData_int("info_cc_num");
    info_wq_max_lv_num = loadGameData_int("info_wq_max_lv_num");
    info_pet_have_lv_up = loadGameData_int("info_pet_have_lv_up");
    info_total_move = loadGameData_int("info_total_move");
    info_total_use_item = loadGameData_int("info_total_use_item");
    info_total_pet_max_lv_num = loadGameData_int("info_total_pet_max_lv_num");
    info_use_skill_up_num = loadGameData_int("info_use_skill_up_num");
    info_get_all_item = loadGameData_int("info_get_all_item");
    
    eday_game1_num = loadGameData_int("eday_game1_num");
    eday_game2_num = loadGameData_int("eday_game2_num");
    eday_wq_up_num = loadGameData_int("eday_wq_up_num");
    eday_make_pet_num = loadGameData_int("eday_make_pet_num");
    eday_boss_kill = loadGameData_int("eday_boss_kill");
    eday_free_pet = loadGameData_int("eday_free_pet");
    eday_bbox_num = loadGameData_int("eday_bbox_num");
    eday_buy_good_num = loadGameData_int("eday_buy_good_num");
    eday_video_get_gold = loadGameData_int("eday_video_get_gold");

    day_task_type = loadGameData_int("day_task_type");

    array_count = loadGameData_int("array_count");
    
    for (int i = 0; i<array_count; i++)
    {
        char s0[64] = {0};
        sprintf(s0,"vPetIndex%d",i);
        vPetIndex->addObject(__String::createWithFormat("%d",loadGameData_int(s0)));
        
        char s1[64] = {0};
        sprintf(s1,"vPetLv%d",i);
        vPetLv->addObject(__String::createWithFormat("%d",loadGameData_int(s1)));
        
        char s2[64] = {0};
        sprintf(s2,"vPetExp%d",i);
        vPetExp->addObject(__String::createWithFormat("%d",loadGameData_int(s2)));
        
        char s3[64] = {0};
        sprintf(s3,"vPetStar%d",i);
        vPetStar->addObject(__String::createWithFormat("%d",loadGameData_int(s3)));
    }
    
    teach0_complete = loadGameData_bool("teach0_complete");
    teach1_complete = loadGameData_bool("teach1_complete");
    teach2_complete = loadGameData_bool("teach2_complete");
    teach3_complete = loadGameData_bool("teach3_complete");
    
    first_fx = loadGameData_bool("first_fx");
    role0_gz = loadGameData_bool("role0_gz");
    
    int task_count = loadGameData_int("task_count");
    for (int i = 0; i<task_count; i++)
    {
        char s0[64] = {0};
        sprintf(s0,"vDayTaskIndex%d",i);
        vDayTaskIndex->addObject(__String::createWithFormat("%d",loadGameData_int(s0)));
    }
    for (int i = 0; i<7; i++)
    {
        char s0[64] = {0};
        sprintf(s0,"vDayTask_id%d",i);
        vDayTask_id->addObject(__String::createWithFormat("%d",loadGameData_int(s0)));
    }
}

void FX_App::saveSelPet()
{
    saveGameData_bool("left_pet_have", left_pet_have);
    saveGameData_bool("right_pet_have", right_pet_have);
    
    saveGameData_int("left_pet_index", left_pet_index);
    saveGameData_int("right_pet_index", right_pet_index);
    
    saveGameData_int("left_pet_star", left_pet_star);
    saveGameData_int("right_pet_star", right_pet_star);
    
    saveGameData_int("left_pet_lv", left_pet_lv);
    saveGameData_int("right_pet_lv", right_pet_lv);
    
    saveGameData_int("left_pet_exp", left_pet_exp);
    saveGameData_int("right_pet_exp", right_pet_exp);
       
}

void FX_App::savePetData()
{
    array_count = (int)vPetIndex->count();
    saveGameData_int("array_count", array_count);
    for (int i = 0; i<array_count; i++) {
        char s0[64] = {0};
        sprintf(s0,"vPetIndex%d",i);
        saveGameData_int(s0, ((__String*)vPetIndex->getObjectAtIndex(i))->intValue());
        
        char s1[64] = {0};
        sprintf(s1,"vPetLv%d",i);
        saveGameData_int(s1, ((__String*)vPetLv->getObjectAtIndex(i))->intValue());

        char s2[64] = {0};
        sprintf(s2,"vPetExp%d",i);
        saveGameData_int(s2, ((__String*)vPetExp->getObjectAtIndex(i))->intValue());
        
        char s3[64] = {0};
        sprintf(s3,"vPetStar%d",i);
        saveGameData_int(s3, ((__String*)vPetStar->getObjectAtIndex(i))->intValue());
    }
}

void FX_App::saveInfoData(int index)
{
    if(index == 1){
        saveGameData_int("info_best_move", info_best_move);
    }
    if(index == 2){
        saveGameData_int("info_best_num", info_best_num);
    }
    if(index == 200){
        saveGameData_int("info_best_total_num", info_best_total_num);
    }
    if(index == 3){
        saveGameData_int("info_best_gold", info_best_gold);
    }
    if(index == 4){
        saveGameData_int("info_total_game_count", info_total_game_count);
    }
    if(index == 6){
        saveGameData_int("info_total_gold", info_total_gold);
    }
    if(index == 60){
        saveGameData_int("info_total_diamond", info_total_diamond);
    }
    if(index == 600){
        saveGameData_int("info_total_yzb", info_total_yzb);
    }
    if(index == 7){
        saveGameData_int("info_total_kill", info_total_kill);
    }
    if(index == 70){
        saveGameData_int("info_total_boss_kill", info_total_boss_kill);
    }
    if(index == 8){
        saveGameData_int("info_total_use_gold", info_total_use_gold);
    }
    if(index == 80){
        saveGameData_int("info_total_use_diamond", info_total_use_diamond);
    }
    if(index == 800){
        saveGameData_int("info_total_buy_diamond", info_total_buy_diamond);
    }
    if(index == 9){
        saveGameData_int("info_total_pet_num", info_total_pet_num);
    }
    if(index == 20){
        saveGameData_int("info_all_pet_num", info_all_pet_num);
    }
    if(index == 10){
        saveGameData_int("info_cc_num", info_cc_num);
    }
    if(index == 11){
        saveGameData_int("info_wq_max_lv_num", info_wq_max_lv_num);
    }
    if(index == 12){
        saveGameData_int("info_pet_have_lv_up", info_pet_have_lv_up);
    }
    if(index == 13){
        saveGameData_int("info_total_move", info_total_move);
    }
    if(index == 14){
        saveGameData_int("info_total_use_item", info_total_use_item);
    }
    if(index == 15){
        saveGameData_int("info_total_pet_max_lv_num", info_total_pet_max_lv_num);
    }
    if(index == 16){
        saveGameData_int("info_use_skill_up_num", info_use_skill_up_num);
    }
    if(index == 17){
        saveGameData_int("info_get_all_item", info_get_all_item);
    }
}

FX_App::~FX_App()
{
    CCLOGINFO("delloc");
}

//int FX_App::checkCjNum(int index)
//{
//    int cj_num = 0;
//    
//    if(index == 0){
//        for (int i = 0; i<CJ_0_NUM; i++) {
//            if(cj_open0[i]){
//                cj_num++;
//            }
//        }
//    }
//    if(index == 1){
//        for (int i = 0; i<CJ_1_NUM; i++) {
//            if(cj_open1[i]){
//                cj_num++;
//            }
//        }
//    }
//    return cj_num;
//}
//int FX_App::checkCjGetNum(int index)
//{
//    int cj_get_num = 0;
//    
//    if(index == 0)
//    {
//        for (int i = 0; i<CJ_0_NUM; i++) {
//            if(cj_open0[i]&&!cj_get0[i])
//            {
//                cj_get_num++;
//            }
//        }
//    }
//    if(index == 1)
//    {
//        for (int i = 0; i<CJ_1_NUM; i++) {
//            if(cj_open1[i]&&!cj_get1[i])
//            {
//                cj_get_num++;
//            }
//        }
//    }
//    return cj_get_num;
//}
int  FX_App::dealDayTask()
{
    int dat_task_num = 0;
    
    task_flag = 1;
    if(taskShowVedio() > 0)
        task_flag = 0;
    
    for (int i = task_flag; i<(int)MyApp->vDayTaskIndex->count(); i++)
    {
        int temp_index = ((__String*)MyApp->vDayTaskIndex->getObjectAtIndex(i))->intValue();
        int get_num = getDayTask_num(temp_index);
        int max_num = getDayTask_max_num(temp_index);
        
        if(!MyApp->dayTask_get[temp_index]&&get_num >= max_num)
        {
            dat_task_num++;
        }
    }
    return dat_task_num;

}
int FX_App::getDayTask_jiangli_num(int index)
{
    int temp_num[3][7] =
    {
        {1000, 2,1000,   1,10,1,5},
        {2000, 3,2000,2000,15,1,5},
        {5000, 3,3000,  10,20,1,5},
    };
    int temp_id = ((__String*)MyApp->vDayTask_id->getObjectAtIndex(index))->intValue();
    
    return temp_num[temp_id][index];
}
int FX_App::getDayTask_jiangli_id(int index)
{
    int temp_num[3][7] =
    {
        {50, 3,50, 1,51,2,51},
        {50, 2,50,50,51,2,51},
        {50, 4,50,51,51,2,51},
    };
    int temp_id = ((__String*)MyApp->vDayTask_id->getObjectAtIndex(index))->intValue();
    
    return temp_num[temp_id][index];
}
int FX_App::getDayTask_max_num(int index)
{
    int temp_num[3][7] =
    {
        { 5000, 500,3,1,10,1,taskShowVedio()},
        {10000,1000,4,2,15,1,taskShowVedio()},
        {30000,3000,5,3,20,1,taskShowVedio()},
    };
    int temp_id = ((__String*)MyApp->vDayTask_id->getObjectAtIndex(index))->intValue();

    return temp_num[temp_id][index];
}
int FX_App::getDayTask_num(int index)
{
    int info_data[7] =
    {
        MyApp->eday_game1_num,
        MyApp->eday_game2_num,
        MyApp->eday_wq_up_num,
        MyApp->eday_make_pet_num,
        MyApp->eday_boss_kill,
        MyApp->eday_buy_good_num,
        MyApp->eday_video_get_gold,
    };
    return info_data[index];
}

const char* FX_App::getDayTask_str(int index,int num)
{
    static char t_25[64] = {0};
    
    if(index == 0)
        sprintf(t_25,"经典模式单局飞行%d米",num);
    if(index == 1)
        sprintf(t_25,"杀戮模式单局击杀%d架敌机",num);
    if(index == 2)
        sprintf(t_25,"强化战机火力%d次",num);
    if(index == 3)
        sprintf(t_25,"抽取僚机%d次",num);
    if(index == 4)
        sprintf(t_25,"杀戮模式击杀%d个boss",num);
    if(index == 5)
        sprintf(t_25,"购买任意%d个道具",num);
    if(index == 6)
        sprintf(t_25,"完成%d次精品推荐",num);
    return t_25;
}
int  FX_App::dealChenjiu()
{
    int chengjiu_num = 0;
    for (int i = 0; i<CHENGJ_NUM; i++)
    {
        if((MyApp->chengjiu_lv_index[i] == (MyApp->chengjiu_lv_num[i]-1))&&MyApp->chengjiu_get[i])
        {
            
        }
        else
        {
            int temp_lv = MyApp->chengjiu_lv_index[i];
            
            int temp_num = MyApp->chengjiu_data[i][temp_lv][0];
            
            int open_num = 0;
            for (int i = 0; i<NUM_FIGHTERS; i++)
                if(MyApp->role_open[i])
                    open_num++;
            
            int info_data[CHENGJ_NUM] =
            {
                MyApp->every_time_kill,
                MyApp->info_total_buy_diamond,
                MyApp->info_total_use_gold,
                MyApp->info_total_use_diamond,
                open_num,
                MyApp->every_time_boss_kill,
                MyApp->info_total_boss_kill,
                MyApp->info_total_move,
                MyApp->info_total_kill,
                MyApp->info_total_use_gold+MyApp->info_total_gold,
                MyApp->info_total_use_item,
                MyApp->info_total_game_count,
                MyApp->info_wq_max_lv_num,
                MyApp->info_all_pet_num,
                MyApp->info_total_pet_max_lv_num,
                MyApp->info_best_move,
                MyApp->info_cc_num,
                MyApp->info_best_num,
            };
            int get_num = info_data[i];
            
            if(get_num >= temp_num)
            {
                chengjiu_num++;
            }
        }
    }
    return chengjiu_num;
}
//void FX_App::dealCj()
//{
//    bool flag0[CJ_0_NUM] =
//    {
//        false,false,false,false,false,false,false,false,false,false,
//        false,false,false,false,false,false,false,false,false,false,
//        false,false,false,false,false,false,false,false,false,false,
//        false,false,false,false,false,false,false,false,false,false,
//        false,false,false,false,false,
//    };
//    bool flag1[CJ_1_NUM] = {
//        false,false,false,false,false,false,false,false,false,false,
//        false,false,false,false,
//    };
//    int T_MOVE[7] = {5000,10000,20000,50000,100000,200000,1000000};
//    for (int i = 0; i<7; i++) {
//        if(!cj_open0[i]){
//            if(info_total_move>=T_MOVE[i]){
//                cj_open0[i] = true;
//                flag0[i] = true;
//            }
//        }
//    }
//    
//    int KILL[7] = {100,500,1000,2000,5000,10000,20000};//20000
//    for (int i = 7; i<14; i++) {
//        if(!cj_open0[i]){
//            if(info_total_kill>=KILL[i-7]){
//                cj_open0[i] = true;
//                flag0[i] = true;
//            }
//        }
//    }
//    
//    int GOLD[10] = {2000,5000,10000,20000,50000,100000,200000,500000,1000000,2000000};
//    for (int i = 14; i<24; i++) {
//        if(!cj_open0[i]){
//            if((info_total_gold+info_total_use_gold)>=GOLD[i-14]){
//                cj_open0[i] = true;
//                flag0[i] = true;
//            }
//        }
//    }
//    
//    int USE_ITEM[5] = {10,20,50,100,200};
//    for (int i = 24; i<29; i++) {
//        if(!cj_open0[i]){
//            if(info_total_use_item>=USE_ITEM[i-24]){
//                cj_open0[i] = true;
//                flag0[i] = true;
//
//            }
//        }
//    }
//    
//    int DEAD[5] = {10,20,50,100,200};//200
//    for (int i = 29; i<34; i++) {
//        if(!cj_open0[i]){
//            if(info_total_game_count>=DEAD[i-29]){
//                cj_open0[i] = true;
//                flag0[i] = true;
//            }
//        }
//    }
//
//    if(!cj_open0[34]){
//        if(info_wq_max_lv_num==1){
//            cj_open0[34] = true;
//            flag0[34] = true;
//
//        }
//    }
//    if(!cj_open0[35]){
//        if(info_wq_max_lv_num==2){
//            cj_open0[35] = true;
//            flag0[35] = true;
//
//        }
//    }
//    if(!cj_open0[36]){
//        if(info_wq_max_lv_num==3){
//            cj_open0[36] = true;
//            flag0[36] = true;
//        }
//    }
//    
//    int PET_NUM[4] = {1,3,5,10};
//    for (int i = 37; i<41; i++) {
//        if(!cj_open0[i]){
//            if(info_all_pet_num>=PET_NUM[i-37]){
//                cj_open0[i] = true;
//                flag0[i] = true;
//            }
//        }
//    }
//    
//    if(!cj_open0[41]){
//        if(info_pet_have_lv_up==1){
//            cj_open0[41] = true;
//            flag0[41] = true;
//
//        }
//    }
//    if(!cj_open0[42]){
//        if(info_total_pet_max_lv_num==1){
//            cj_open0[42] = true;
//            flag0[42] = true;
//
//        }
//    }
//    if(!cj_open0[43]){
//        if(info_total_pet_max_lv_num==5){
//            cj_open0[43] = true;
//            flag0[43] = true;
//
//        }
//    }
//    if(!cj_open0[44]){
//        if(info_total_pet_max_lv_num==10){
//            cj_open0[44] = true;
//            flag0[44] = true;
//
//        }
//    }
////-----------------------------------
//    int MOVE1[4] = {2000,5000,10000,30000};
//    for (int i = 0; i<4; i++) {
//        if(!cj_open1[i]){
//            if(info_best_move>=MOVE1[i]){
//                cj_open1[i] = true;
//                flag1[i] = true;
//
//            }
//        }
//    }
//    
//    int CC[3] = {1,5,10};
//    for (int i = 4; i<7; i++) {
//        if(!cj_open1[i]){
//            if(info_cc_num>=CC[i-4]){
//                cj_open1[i] = true;
//                flag1[i] = true;
//            }
//        }
//    }
//    
//    if(!cj_open1[7]){
//        if(info_use_skill_up_num>=3){
//            cj_open1[7] = true;
//            flag1[7] = true;
//        }
//    }
//    
//    if(!cj_open1[8]){
//        if(info_get_all_item==1){
//            cj_open1[8] = true;
//            flag1[8] = true;
//        }
//    }
//    
//    int NUM[5] = {10000,20000,50000,100000,200000};
//    for (int i = 9; i<14; i++) {
//        if(!cj_open1[i]){
//            if(info_best_num>=NUM[i-9]){
//                cj_open1[i] = true;
//                flag1[i] = true;
//            }
//        }
//    }
//    
//    
//    //save
//    for (int i = 0; i<CJ_0_NUM; i++) {
//        char s2[64] = {0};
//        sprintf(s2,"cj_open0%d",i);
//        if(flag0[i])
//          saveGameData_bool(s2, cj_open0[i]);
//    }
//    
//    for (int i = 0; i<CJ_1_NUM; i++) {
//        char s2[64] = {0};
//        sprintf(s2,"cj_open1%d",i);
//        if(flag1[i])
//          saveGameData_bool(s2, cj_open1[i]);
//    }
//}
bool FX_App::checkHonor()
{
    int kkk_num = 18;
    int enemy_index[18] = {0,1,2,3,4,5,6,7,8,9,20,21,22,23,24,25,26,27};
    int kill_num[4] = {100,500,1000,2000};
    int kill_num_big[4] = {10,50,200,500};
    
    int jl_len = 0;
    
    for (int index = 0; index<kkk_num; index++)
    {
        if(enemy_index[index]<22){
            for (int i = 0; i<4; i++) {
                if(FX_App::share()->enemy_kill_num[enemy_index[index]]>=kill_num[i]){
                    if(!FX_App::share()->honor_get_jl[index][i])
                        jl_len++;
                }
            }
        }
        else{
            for (int i = 0; i<4; i++) {
                if(FX_App::share()->enemy_kill_num[enemy_index[index]]>=kill_num_big[i]){
                    if(!FX_App::share()->honor_get_jl[index][i])
                        jl_len++;
                }
            }
        }
    }
    if(jl_len>0)
        return true;
    
    return false;
}

bool FX_App::isHaveSaveFile()
{
    if(!UserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml"))
    {
        UserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml", true);
        UserDefault::getInstance()->flush();//提交
        //        CCLog("存储文件不存在,头次开始加载游戏");
        return false;
    }
    else{
        //        CCLog("存储文件已存在");
        return true;
    }
}
//保存游戏数据
void FX_App::saveGameData_int(const char * key,int data)
{
    UserDefault::getInstance()->setIntegerForKey(key, data);
    UserDefault::getInstance()->flush();
}
void FX_App::saveGameData_bool(const char * key,bool data)
{
    UserDefault::getInstance()->setBoolForKey(key, data);
    UserDefault::getInstance()->flush();
}

void FX_App::saveGameData_str(const char * key,const char* data)
{
    UserDefault::getInstance()->setStringForKey(key, data);
    UserDefault::getInstance()->flush();
}

void FX_App::saveGameData_long(const char * key, long data)
{
    char input[128];
    sprintf(input,"%ld", data);
    saveGameData_str(key, input);
}

long FX_App::loadGameData_long(const char * key)
{
    string input = UserDefault::getInstance()->getStringForKey(key);
    return atol(input.c_str());
}

//读取游戏数据
int FX_App::loadGameData_int(const char * key)
{
    return UserDefault::getInstance()->getIntegerForKey(key);
}
bool FX_App::loadGameData_bool(const char * key)
{
    return UserDefault::getInstance()->getBoolForKey(key);
}

void FX_App::addNum(Node* node,int num,const char* img,Vec2 xy,Vec2 a_xy,int z,int tag)
{
    char *sss = new char[100];
    sprintf(sss,"%d", num);
    
    Sprite *sprite = createCache_img(img);
    int ItemWidth = sprite->getContentSize().width/10;
    int ItemHeight = sprite->getContentSize().height;
    
    LabelAtlas* lable_best_num = LabelAtlas::create(sss,img, ItemWidth, ItemHeight, '0');
    
    lable_best_num->setAnchorPoint(a_xy);
    lable_best_num->setPosition(xy);
    node->addChild(lable_best_num,z,tag);
}
void FX_App::addNum10(Node* node,const char* num,const char* img,Vec2 xy,Vec2 a_xy,int z,int tag)
{
    if(node->getChildByTag(tag))
        node->removeChildByTag(tag);
    
    Sprite *sprite = createCache_img(img);
    int ItemWidth = sprite->getContentSize().width/10;
    int ItemHeight = sprite->getContentSize().height;
    
    LabelAtlas* lable_best_num = LabelAtlas::create(num,img, ItemWidth, ItemHeight, '0');
    
    lable_best_num->setAnchorPoint(a_xy);
    lable_best_num->setPosition(xy);
    node->addChild(lable_best_num,z,tag);
}
void FX_App::addNum11(Node* node,const char* num,const char* img,Vec2 xy,Vec2 a_xy,int z,int tag)
{
    if(node->getChildByTag(tag))
        node->removeChildByTag(tag);
    
    Sprite *sprite = createCache_img(img);
    int ItemWidth = sprite->getContentSize().width/11;
    int ItemHeight = sprite->getContentSize().height;
    
    LabelAtlas* lable_best_num = LabelAtlas::create(num,img, ItemWidth, ItemHeight, '/');
    
    lable_best_num->setAnchorPoint(a_xy);
    lable_best_num->setPosition(xy);
    node->addChild(lable_best_num,z,tag);
}
void FX_App::playSfx(const char* pszFile)
{
    if(MyApp->isSound)
        AudioEngine->playEffect(pszFile, false);
}

Vec2 FX_App::Vec2Auto(float x, float y)
{
    return Vec2(x, y);
}
const char* FX_App::getRoelBulletStr(int role_index)
{
    static char t[64] = {0};
    if(role_index <= 5)
    {
        sprintf(t, "%d_%d.png", role_index+1, g_bullet_lv[role_index]+1);
    }
    else
    {
        if(role_index == 6)
        {
            if(g_bullet_lv[role_index]+1 <= 46)
                sprintf(t, "%d_%d.png", role_index+1, g_bullet_lv[role_index]+1);
            else
                sprintf(t, "%d_%d.png", role_index+1, 46);
        }
        if(role_index == 7)
        {
            if(g_bullet_lv[role_index]+1 <= 50)
                sprintf(t, "%d_%d.png", role_index+1, g_bullet_lv[role_index]+1);
            else
                sprintf(t, "%d_%d.png", role_index+1, 50);
        }
        if(role_index == 8)
        {
            if(g_bullet_lv[role_index]+1 <= 19)
                sprintf(t, "%d_%d.png", role_index+1, 1);
            else if(g_bullet_lv[role_index]+1 >= 20&&g_bullet_lv[role_index]+1 <= 39)
                sprintf(t, "%d_%d.png", role_index+1, 2);
            else if(g_bullet_lv[role_index]+1 >= 40&&g_bullet_lv[role_index]+1 <= 59)
                sprintf(t, "%d_%d.png", role_index+1, 3);
            else if(g_bullet_lv[role_index]+1 >= 60)
                sprintf(t, "%d_%d.png", role_index+1, 4);
        }
    }
    return t;
}

void FX_App::infoKuang(Node* node,const char* info)
{
    Sprite *box = Sprite::create("menu/lead_lanpsd.png");
    box->setAnchorPoint(Vec2(0.5f,1.0f));
    Size size = Director::getInstance()->getWinSize();
    box->setPosition(Vec2(size.width/2.0f, size.height*1.20f));
    node->addChild(box, 20001);
    
    Text *txt = Text::create("恭喜获得", "Arial", 24);
    txt->setContentSize(Size(box->getContentSize().width, box->getContentSize().height));
    txt->setPosition(Vec2(box->getContentSize().width/2, box->getContentSize().height/2));
    box->addChild(txt);
    
    char t_num[256] = {0};
    sprintf(t_num,"%s",info);
    txt->setString(t_num);
    
    MoveTo *act1 = MoveTo::create(0.2f, Vec2(size.width/2.0f, size.height));
    DelayTime *act2 = DelayTime::create(2.0f);
    MoveTo *act3 = MoveTo::create(0.2f, Vec2(size.width/2.0f, size.height*1.2f));
    RemoveSelf *act4 = RemoveSelf::create();
    box->runAction(Sequence::create(act1, act2, act3, act4, NULL));
}
void FX_App::infoKuangEx(Node* node,const char* info)
{
    Sprite *box = Sprite::create("menu/lead_lanpsd.png");
    box->setAnchorPoint(Vec2(0.5f,1.0f));
    Size size = Director::getInstance()->getWinSize();
    box->setPosition(Vec2(size.width/2.0f, size.height*1.20f));
    node->addChild(box, 20001);
    
    Text *txt = Text::create("恭喜获得", "Arial", 24);
    txt->setContentSize(Size(box->getContentSize().width, box->getContentSize().height));
    txt->setPosition(Vec2(box->getContentSize().width/2, box->getContentSize().height/2));
    box->addChild(txt);
    
    char t_num[256] = {0};
    sprintf(t_num,"%s",info);
    txt->setString(t_num);
    
    MoveTo *act1 = MoveTo::create(0.2f, Vec2(size.width/2.0f, size.height-100));
    DelayTime *act2 = DelayTime::create(2.0f);
    MoveTo *act3 = MoveTo::create(0.2f, Vec2(size.width/2.0f, size.height*1.2f));
    RemoveSelf *act4 = RemoveSelf::create();
    box->runAction(Sequence::create(act1, act2, act3, act4, NULL));
}
void FX_App::addTextNum(Node* node,int num,float x,float y,int size,const Color3B& color)
{
    if(node->getChildByTag(191919))
        node->removeChildByTag(191919);
    Text *txt = Text::create("恭喜获得", "Arial", size);
    txt->setPosition(Vec2(x, y));
    node->addChild(txt,1,191919);
    
    txt->setColor(color);
    
    char t_num[256] = {0};
    sprintf(t_num,"%d",num);
    txt->setString(t_num);
}
void FX_App::addTextNumEx(Node* node,const std::string &num,float x,float y,int size,const Color3B& color)
{
    if(node->getChildByTag(191919))
        node->removeChildByTag(191919);
    Text *txt = Text::create("恭喜获得", "Arial", size);
    txt->setPosition(Vec2(x, y));
    node->addChild(txt,1,191919);
    
    txt->setColor(color);
    
    char t_num[256] = {0};
    sprintf(t_num,"倒计时%s",num.c_str());
    txt->setString(t_num);
}
void FX_App::addText(Node* node,const char* num,float x,float y,int size,const Color3B& color)
{
    Text *txt = Text::create("恭喜获得", "Arial", size);
    txt->setPosition(Vec2(x, y));
    node->addChild(txt,1);
    
    Text *txt1 = Text::create("恭喜获得", "Arial", size);
    txt1->setPosition(Vec2(x+0.5, y-0.5));
    node->addChild(txt1,2);
    
    txt->setColor(color);
    txt1->setColor(color);
    
    char t_num[256] = {0};
    sprintf(t_num,"%s",num);
    txt->setString(t_num);
    txt1->setString(t_num);
    
}
void FX_App::addNumNew(Node* node,const char* num,const char* img,Vec2 xy,Vec2 a_xy,int z,int tag)
{
    char *sss = new char[100];
    sprintf(sss,"%s", num);
    
    Sprite *sprite = Sprite::create(img);
    int ItemWidth = sprite->getContentSize().width/11;
    int ItemHeight = sprite->getContentSize().height;
    
    LabelAtlas* lable_best_num = LabelAtlas::create(sss,img, ItemWidth, ItemHeight, '/');
    
    lable_best_num->setAnchorPoint(a_xy);
    lable_best_num->setPosition(xy);
    node->addChild(lable_best_num,z,tag);
}
void FX_App::MakeEvevt(const char* flag)
{
    BBClickEvent((char*)flag);
}
void FX_App::MakeEvevt2(const char* flag,const char* flag2)
{
    BBClickEventEx((char*)flag,(char*)flag2);
}
void FX_App::readCSV_ChengjData(int index)
{
}

void FX_App::fightBoss(int num)
{
    bossFighting = num;
    saveGameData_int("bossFighting", num);
}
void FX_App::getGiftLongWay(int index)
{
    giftGotLongWay[index] = true;
    char str0[64] = {0};
    sprintf(str0,"giftGotLongWay%d",index);
    saveGameData_bool(str0, true);
}

void FX_App::removeBossAll()
{
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/BOSS-001.csb");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/BOSS-002.csb");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/BOSS_003.csb");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/BOSS-004.csb");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/BOSS_005.csb");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/BOSS-006.csb");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/BOSS-007.csb");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/BOSS_008.csb");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/boss001.csb");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/boss002.csb");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/boss11.csb");
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("ain/BOSS-010.csb");
}
long FX_App::getSysTime()
{
    timeval now;
    gettimeofday(&now, NULL);
    
    return now.tv_sec;
}
void FX_App::refrushTime()
{
    if(in_freegold_state)
    {
        freegold_delay_time = shipinTime()+(int)(freegold_sys_time-getSysTime());
        if(freegold_delay_time<0)
            freegold_delay_time = 0;
    }
}
std::string FX_App::formatTime(int time)
{
    char limit_t[64] = {0};
    if(time%60>=10)
    {
        if(time/60>=10)
            sprintf(limit_t, "%d:%d",time/60,time%60);
        else
            sprintf(limit_t, "0%d:%d",time/60,time%60);
    }
    else
    {
        if(time/60>=10)
            sprintf(limit_t, "%d:0%d",time/60,time%60);
        else
            sprintf(limit_t, "0%d:0%d",time/60,time%60);
    }
    return limit_t;
}
