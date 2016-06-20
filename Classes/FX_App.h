//
//  FX_App.h
//
//  Created by  on 12-11-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef gs_FX_App_h
#define gs_FX_App_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
//#include "GG_Sp.h"
using namespace std;
using namespace CocosDenshion;


#define FONT_NAME "Arial"

#define screenSize Director::getInstance()->getVisibleSize()

#define isLandscape ((screenSize.width>screenSize.height)?1:0)
// 屏幕长边上的比率
#define LPRatio ((isLandscape==1)?screenSize.width/screenSize.height:screenSize.height/screenSize.width)

#define IS_IPHONE4 ((LPRatio == 1.5f)?1:0 )
#define IS_IPHONE5 ((LPRatio > 1.5f)?1:0 )

#define SCREEN_W  Director::getInstance()->getVisibleSize().width
#define SCREEN_H  Director::getInstance()->getVisibleSize().height
#define MAP_WWW   1136


#define ROLE_SPEED 4

#define SP_PET1     21
#define SP_PET2     22
#define SP_PET3     23
#define SP_PET4     24
#define SP_PET5     25
#define SP_PET6     26
#define SP_PET7     27
#define SP_PET8     28
#define SP_PET9     29
#define SP_PET10    30

#define SP_ENEMY_0  100
#define SP_ENEMY_1  101
#define SP_ENEMY_2  102
#define SP_ENEMY_3  103
#define SP_ENEMY_4  104
#define SP_ENEMY_5  105
#define SP_ENEMY_6  106
#define SP_ENEMY_7  107
#define SP_ENEMY_8  108
#define SP_ENEMY_9  109


#define SP_ENEMY_BOMB  120
#define SP_ENEMY_BOX   121
#define SP_ENEMY_22    122//南瓜
#define SP_ENEMY_23    123//地域犬
#define SP_ENEMY_24    124
#define SP_ENEMY_25    125
#define SP_ENEMY_26    126
#define SP_ENEMY_27    127
#define SP_ENEMY_28    128
#define SP_ENEMY_29    129
#define SP_ENEMY_30    130

#define SP_ENEMY_YS    200

#define SP_BOSS0  20000
#define SP_BOSS1  20001
#define SP_BOSS2  20002
#define SP_BOSS3  20003
#define SP_BOSS4  20004
#define SP_BOSS5  20005
#define SP_BOSS6  20006
#define SP_BOSS7  20007
#define SP_BOSS8  20008


//pet
#define BULLET10 91
#define BULLET20 92
#define BULLET30 93

#define BULLET_ENEMY23 400
//item
#define ITEM_GOLD        1
#define ITEM_SKILL_UP    2
#define ITEM_SKILL_DOWN  3
#define ITEM_XXX         4
#define ITEM_DOUBLE      5
#define ITEM_CC250       6
#define ITEM_BS0         7
#define ITEM_BS1         8
#define ITEM_BS2         9

#define HONOR_NUM     28

#define NUM_FIGHTERS   9

#define CHENGJ_NUM     18

#define DAY_TASK_NUM   5

#define JJC_NUM       10

#define AudioEngine     SimpleAudioEngine::getInstance()

#define MyApp  FX_App::share()

#define AddCache(p) SpriteFrameCache::getInstance()->addSpriteFramesWithFile(p)
#define createCache(p) Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(p))
#define createCache_img(p) Sprite::create(p)
#define spCache(r) SpriteFrameCache::getInstance()->getSpriteFrameByName(r)

#define NOTIFICATION __NotificationCenter::getInstance()

#define InterAd  "eb7ff03acf0e4ed0b7e82c13f89a287a"
#define InterAd_pad  "e7f27017a91a407e9588effd7b1f2964"

#define GameModeNormal  0
#define GameModeBoss    1
#define GameModeLongWay 2


using namespace cocos2d;

class FX_App : public Ref
{
public:
    FX_App();
    ~FX_App();
    
    static FX_App* share();
    
//    int  checkCjNum(int index);
//    int  checkCjGetNum(int index);

//    void dealCj();
    
    void addNum(Node* node,int num,const char* img,Vec2 xy,Vec2 a_xy,int z,int tag);

    void saveGameData_int(const char* key, int data);
    void saveGameData_bool(const char * key,bool data);
    void saveGameData_str(const char * key,const char* data);
    
    int loadGameData_int(const char* key);
    bool loadGameData_bool(const char* key);
    
    bool isHaveSaveFile();
    
    void initGame();
    void loadGame();
    
    void initDayTask(int type);
    void initLongWay(bool day_first);


    void saveInfoData(int index);
    void savePetData();
    
    void saveSelPet();
    bool checkHonor();
    
    Vec2 Vec2Auto(float x, float y);
    void playSfx(const char* pszFile);

    void addNum10(Node* node,const char* num,const char* img,Vec2 xy,Vec2 a_xy,int z,int tag);
    void addNum11(Node* node,const char* num,const char* img,Vec2 xy,Vec2 a_xy,int z,int tag);
    const char* getRoelBulletStr(int role_index);
    void infoKuang(Node* node,const char* info);
    void infoKuangEx(Node* node,const char* info);
    void addNumNew(Node* node,const char* num,const char* img,Vec2 xy,Vec2 a_xy,int z,int tag);
    void MakeEvevt(const char* flag);
    void MakeEvevt2(const char* flag,const char* flag2);

    void readCSV_ChengjData(int index);

    int  dealChenjiu();
    int  dealDayTask();
    int  getDayTask_num(int index);
    int  getDayTask_max_num(int index);
    int  getDayTask_jiangli_id(int index);
    int  getDayTask_jiangli_num(int index);

    const char* getDayTask_str(int index,int num);

    void removeBossAll();
    
    void addTextNum(Node* node,int num,float x,float y,int size,const Color3B& color);
    void addText(Node* node,const char* num,float x,float y,int size,const Color3B& color);
    void addTextNumEx(Node* node,const std::string &num,float x,float y,int size,const Color3B& color);

    void saveGameData_long(const char * key, long data);
    long loadGameData_long(const char * key);
    
    //-------longWay-------
    void fightBoss(int num);
    void resetFightPlanes();
    void setFighting(bool v);
    void getGiftLongWay(int index);
    
    
    long getSysTime();
    void refrushTime();
    std::string formatTime(int time);

public:
    
    bool in_freegold_state;
    int freegold_delay_time;
    long freegold_sys_time;

    bool skilling;
    bool in_battle;
    
    Vec2 save_role_p;
    float boss_pro_angle[2];
    float boss_pro_x[3];
    float boss_pro_y[3];

    bool in_hit_ing;
    int  in_hit_time;
    
    float bullet_rect[20][50];

    int boss_index;
    int boss_temp_index;

    __Array* gk_boss_name;

    int boss_shoot_id[20][20];
    float boss_data[20][40];
    float boss_bullet_data[50][30];
    float boss_move_data[20];
    
    int boss_shoot_num[20];
    float boss_shoot_x[20][10];
    float boss_shoot_y[20][10];

    float nor_bullet_data[20][20][30];
    float game_data[50];
    
    float enemy_data[50][30];
    
    int chengjiu_data[CHENGJ_NUM][20][10];
    int chengjiu_lv_num[CHENGJ_NUM];
    int chengjiu_lv_index[CHENGJ_NUM];
    bool chengjiu_get[CHENGJ_NUM];
    
    bool dayTask_get[10];


    int in_boss_state;
    bool before_boss_state;
    float boss_time;
    int gameMode;
    int boss_distance;
    bool boss_result_show;
    int boss_result_step;
    int boss_result_level;
    int boss_count;
    int boss_level;
    int boss_hp;

    int boss_b_num;//弹幕个数
    int limit_boss_time;
    bool boss_ys_state;
    int boss_ys_time;

    int can_relive_num;

    int ask_kuang_index;
    int chaping_num;
    int all_cp_num;

    bool isDoLeft;
    bool isFullScreen;

    bool new_game;
    bool reset_music;
    bool isSound;
    bool isMusic;
    bool isPush;
    bool Android_Version;
    
    bool super_state;
    bool end_cc_state;
    int  end_cc_speed;
    int super_state_time;
    int super_state_max_time;
    int super_index;
    
    
    bool left_pet_have;
    bool right_pet_have;
    
    int left_pet_index;
    int right_pet_index;
    
    int left_pet_star;
    int right_pet_star;
    
    int left_pet_lv;
    int right_pet_lv;
    
    int left_pet_exp;
    int right_pet_exp;
    
    int cj_back_index;
    
    int day_task_layer_index;

    
    int g_bullet_lv[NUM_FIGHTERS];
    
    int g_skill_up_num;
    int g_cc1500_num;
    int g_cc3000_num;
    int g_skill_down_num;
    int g_relive_num;
    int g_pet_double_exp_num;
    int g_dead_cc_num;
    

    int role_index;
    int map_index;
    
    bool is_best_fly;
//    int gold_num_all;
    
    int info_get_all_item;
    int info_use_skill_up_num;
    int info_cc_num;
    int info_wq_max_lv_num;
    int info_pet_have_lv_up;
    int info_total_move;
    int info_total_use_item;
    int info_total_pet_max_lv_num;
    
    int info_best_move;
    int info_best_num;
    
    int info_best_total_num;

    int info_best_gold;
    int info_total_game_count;
//    int info_total_game_time;
    int info_total_gold;
    int info_total_diamond;
    int info_total_yzb;

    int info_total_boss_kill;
    int every_time_boss_kill;

    int every_time_kill;
    int info_total_kill;
    
    int info_total_use_gold;
    int info_total_use_diamond;
    int info_total_buy_diamond;

    int info_total_pet_num;
    int info_all_pet_num;
    
    int eday_game1_num;
    int eday_game2_num;
    int eday_wq_up_num;
    int eday_make_pet_num;
    int eday_boss_kill;
    bool eday_free_pet;
    int  eday_bbox_num;
    int eday_buy_good_num;
    int day_task_type;
    int eday_video_get_gold;
    
    
    int every_time_bbox_num;
    int boss_box_jiangli_index[5];
    int boss_box_pet_type[5];
    
    
    int starshop_chou_index[10];
    int starshop_chou_pet_type[10];
    int starshop_chou_count;
    bool starshop_chou_free;

    int limit_bullet_lv;//杀戮模式等级限制

    
    __Array* vPetIndex;
    __Array* vPetLv;
    __Array* vPetExp;
    __Array* vPetStar;
    
    __Array* vDayTaskIndex;
    __Array* vDayTask_id;
    
    __Array* vLongWay_boss_id;
    __Array* vLongWay_fly;

    int task_flag;

    int array_count;
    
    int speed_up;
    
    bool role_open[NUM_FIGHTERS];
    
    bool map_open[3];
    
    bool honor_open[HONOR_NUM];
    int enemy_kill_num[HONOR_NUM];
    bool honor_get_jl[HONOR_NUM][4];
    
    bool jjc_open[5][JJC_NUM];
    bool jjc_success[5][JJC_NUM];
    bool jjc_level[5];

    int jjc_index;

    bool double_bullet;
    int double_bullet_time;
    float jg_target_y;
    
    int cj_start_num0;
    int cj_end_num0;
    int cj_start_num1;
    int cj_end_num1;
    
    int sel_info_pet_lr;
    bool sel_pet_can_deal;
    int sel_pet_deal_index;
    
    
    bool dead_state;
    int dead_state_time;
    
    bool ask_relive_state;


    int result_jl;
    int result_num;
    int result_gold;
    
    bool can_update;
    bool pet_cancel_btn_hide;
    
    int gold_layer_index;
    
    int jfq_index;
    
    int game_pet_get_exp;
    
    bool first_in;
    int game_buff;
    
    int load_layer_index;
    
    bool game_px;//游戏评星
    bool first_fx;//首次分享
    
    bool role0_gz;

    
    bool teach0_complete;
    bool teach1_complete;
    bool teach2_complete;
    bool teach3_complete;

    int loading_index;
    
    int get_reward_index;
    bool in_reward;
    bool in_make_pet;
    bool game_first_day;
    int game_day;
    
    bool sel_pet_open;

    int into_game_num;
    std::string push_content;
    
//    int sell_pet_flag;
    
    int map_w;
    bool is_pad;
    
    bool gotDuiHuan;
    
    int inser_ads_index;

    //------longWay----------
    int openedbossLongWay;
    float star_boss_data[8][3];
    int bossFighting;
    int resetNumberLongWay;
    int fightingPlaneIndex;//远征战机队列中正在出战战机
    bool fighting;
    bool giftGotLongWay[8];
    
    int lw_giftIndex;
    bool lw_role_layer;
    
    bool longWay_success;

    int dlg_ts_index;
    
    int role_back_index;
    
    int play_num;
};

#endif
