#ifndef  _InApp_H_
#define  _InApp_H_

#include "cocos2d.h"


USING_NS_CC;


/**
 @brief    内置商店
 */
class  InApp : public cocos2d::Ref
{
private:
    
public:
    InApp();
    ~InApp();
    
    /**
     @brief  取得唯一实例
     @return 唯一实例.
     */
    static InApp* shareInstance();
    
    
    /**
     @brief  购买商品
     @param  观察者
     @param  观察者对商品购买成功事件进行监测
     @param  观察者对商品购买失败事件进行监测
     @param  商品ID
     */
    void purchaseProduct(Ref *observer,
                   SEL_CallFuncO selectorPurchased,
                   SEL_CallFuncO selectorPurchaseFailed,
                   const char* productId);
    
    void purchaseProduct_ex(Ref *observer,
                         SEL_CallFuncO selectorPurchased,
                         SEL_CallFuncO selectorPurchaseFailed,
                         const char* productId);
    
    /**
     @brief  检测商店是否可用
     @return true, 可用; false, 不可用.
     */
    bool canMakePurchases();
    
    /**
     @brief  恢复以前购买过的
     */
    void restoreProducts();
    
    
    
    
private:
};


/**
 @brief Pop out a message box
 */
void CC_DLL CCSendSMSBilling(const char * pszSMSType);

#endif // _InApp_H_