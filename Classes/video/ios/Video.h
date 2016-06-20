#ifndef  _Video_H_
#define  _Video_H_

#include "cocos2d.h"


USING_NS_CC;


/**
 @brief    分析
 */
class  Video : public cocos2d::Ref
{
private:
    
public:
    Video();
    ~Video();
    
    
    /**
     @brief  取得唯一实例
     @return 唯一实例.
     */
    static Video* shareInstance();
    
    
    void show();
    
    
    
private:
};



#endif // _Video_H_