//
//  WXGoldLayer.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/6.
//
//

#ifndef WXGoldLayer_hpp
#define WXGoldLayer_hpp

#include "KTPauseLayer.h"
#include <vector>

class WXGoldLayer : public KTPauseLayer{
    
public:
    
    virtual void pauseLayerDidMakeSure(KTPauseLayer *layer) override;
    
    void finalSort();
    
    void randomSort();
    
    void closeCard(Ref *ref);
    
    virtual void onEnter() override;
    
    ~WXGoldLayer();
    
    void onAlertViewClick(Ref *ref);
    
    Vector<Button *> _openedCards;
    
    std::vector<int> _openedIdx;
    
    int _openCounter;
    
    CC_SYNTHESIZE(int, _openNum, OpenNum);
    
    std::vector<int> getRandomSequence(int length);
    
    std::vector<int> getRandomSequence(std::vector<int> source);
    
    int golds[8] = {100,100,100,200,200,200,500,1000};
    
    int changeIdxes[9][2] = {{6,8}, {0,7}, {2,5}, {1,2}, {6,7}, {1,7}, {2,7}, {0,2}, {2,4}};
    
    std::string rewardString;
    
    bool _opened;
    
    void showResult(Button *card, int gold);
    
    void showAll();
    
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
    Vector<Button *> _backCards;
    
    Vector<Sprite *> _frontCards;
    
    virtual bool init() override;
    
    CREATE_FUNC(WXGoldLayer);
};

#endif /* WXGoldLayer_hpp */
