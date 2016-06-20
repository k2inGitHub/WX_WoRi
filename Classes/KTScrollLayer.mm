//
//  KTScrollLayer.cpp
//  colorful
//
//  Created by SongYang on 13-10-30.
//
//

#include "KTScrollLayer.h"
#include "VisibleRect.h"

void KTScrollLayer::setIndicator(const std::string& normal, const std::string& highlight)
{
    normalIndicator = normal;
    highlightIndicator = highlight;

    auto arr = __Array::createWithCapacity(m_pages->count());
    for (int i = 0; i < m_pages->count(); i++) {
        auto dot = Sprite::create(i == m_nCurPage ?highlightIndicator : normalIndicator);
        dot->setPosition(VisibleRect::bottom() + Vec2(i - (m_pages->count() - 1) * 0.5, 1) * 40);
        addChild(dot, 100);
        arr->addObject(dot);
    }
    setIndicators(arr);
}

bool KTScrollLayer::init(CCArray* pages)
{
	bool bRet = false;
	do
	{
        CC_BREAK_IF( !CCLayer::init() );
        
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCLayer *pLayer = CCLayer::create();
        
        m_pages = pages;
        CC_SAFE_RETAIN(m_pages);
        
        m_pShowPages = CCArray::create();
        CC_SAFE_RETAIN(m_pShowPages);
        CCSprite *pLast = createSprite((CCSprite *)pages->lastObject());
        CCSprite *pFirst = createSprite((CCSprite *)pages->objectAtIndex(0));
        m_pShowPages->addObject(pLast);
        for (int i = 0; i < m_pages->count(); i++) {
            m_pShowPages->addObject(m_pages->objectAtIndex(i));
        }
        m_pShowPages->addObject(pFirst);
        
        for (int i = 1; i <= m_pShowPages->count(); ++ i)
        {
            CCSprite *pSprite = (CCSprite *)m_pShowPages->objectAtIndex(i-1);
            pSprite->setPosition(ccp(visibleSize.width * (i-0.5f), visibleSize.height / 2));
            pLayer->addChild(pSprite);
        }
        
        m_pScrollView = ScrollView::create(CCSizeMake(visibleSize.width, visibleSize.height), pLayer);
        m_pScrollView->setContentOffset(CCPointZero);
        m_pScrollView->setTouchEnabled(false);
        m_pScrollView->setDelegate(this);
        m_pScrollView->setDirection(ScrollView::Direction::HORIZONTAL);
//        m_pScrollView->setBounceable(true);
//        m_pScrollView->updateInset();
        pLayer->setContentSize(CCSizeMake(visibleSize.width*m_pShowPages->count(), visibleSize.height));
        this->addChild(m_pScrollView);
		bRet = true;
        
        setCurrentPage(0, false);
        
//        CCLog("m_pages = %d", m_pages->count());
//        CCLog("m_showPages = %d", m_pShowPages->count());
        
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = CC_CALLBACK_2(KTScrollLayer::onTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(KTScrollLayer::onTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(KTScrollLayer::onTouchEnded, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(KTScrollLayer::onTouchCancelled, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        
	}while(0);
    
	return bRet;
}

CCSprite* KTScrollLayer::createSprite(CCSprite* sp)
{
    CCSprite *newSp = CCSprite::createWithSpriteFrame(sp->displayFrame());
    for (int i = 0; i < sp->getChildrenCount(); i++) {
        CCSprite *child = (CCSprite *)sp->getChildren().at(0);
        CCSprite *newChild = CCSprite::createWithSpriteFrame(child->displayFrame());
        newChild->setPosition(child->getPosition());
        newSp->addChild(newChild, child->getZOrder(), child->getTag());
        
        for (int i = 0; i < 1; i++) {
            CCAction *ac = (CCAction *)child->getActionByTag(i);
            if (ac != NULL) {
                ac = (CCAction *)ac->clone();
                newChild->runAction(ac);
            }
        }
    }
    return newSp;
}

void KTScrollLayer::setCurrentPage(int currentPage, bool animated)
{
    if (currentPage > m_pages->count()-1) {
        return;
    }
    if (currentPage < 0) {
        return;
    }
    m_nCurPage = currentPage;
    adjustPosition(animated);
    
}

void KTScrollLayer::scrollViewDidScroll(cocos2d::extension::ScrollView *view)
{
//	CCLOG("scroll");
//    CCLog("offset x = %f", view->getContentOffset().x);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
//    CCPoint  desPos = ccp(origin.x - visibleSize.width * 0, 0);
    if (view->getContentOffset().x == origin.x) {
        //滑到第一页，跳转到倒数第二页
        CCLog("滑到第一页");
        setCurrentPage(m_pages->count()-1, false);
    } else if (view->getContentOffset().x == origin.x - visibleSize.width * (m_pShowPages->count()-1)){
        //滑到最后一页，跳转到第二页
        CCLog("滑到最后一页");
        setCurrentPage(0, false);
    }
}

void KTScrollLayer::scrollViewDidZoom(cocos2d::extension::ScrollView *view)
{
//	CCLOG("zoom");
}

void KTScrollLayer::onEnter()
{
	CCLayer::onEnter();
//	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

void KTScrollLayer::onExit()
{
//	Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}


bool KTScrollLayer::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    m_fTouchOffset = m_pScrollView->getContentOffset().x;
    CCLOG("offset = %f", m_fTouchOffset);
	return true;
}

void KTScrollLayer::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bScrollCycle == false) {
        return;
    }
    CCPoint point = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	m_pScrollView->setContentOffset(ccp(m_fTouchOffset + point.x - m_touchPoint.x, false));
}

void KTScrollLayer::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	float distance = endPoint.x - m_touchPoint.x;
	if(fabs(distance) > 50)
	{
        adjustScrollView(distance);
	}
}

void KTScrollLayer::onTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	ccTouchEnded(pTouch, pEvent);
}

void KTScrollLayer::prevPage()
{
    if (m_bGestureForward == true) {
        adjustScrollView(-64);
    } else {
        adjustScrollView(64);
    }
}

void KTScrollLayer::nextPage()
{
    if (m_bGestureForward == true) {
        adjustScrollView(64);
    } else {
        adjustScrollView(-64);
    }
}

void KTScrollLayer::adjustScrollView(float offset)
{
    //默认情况是逆向手势
	if (offset < 0)
	{
        if (m_bGestureForward == true) {
            m_nCurPage --;
        } else {
            m_nCurPage ++;
        }
	} else {
        if (m_bGestureForward == true) {
            m_nCurPage ++;
        } else {
            m_nCurPage --;
        }
	}
	if (m_nCurPage < 0 && m_bScrollCycle == false) {
		m_nCurPage = 0;
	} else if (m_nCurPage < 0 && m_bScrollCycle == true) {
        m_nCurPage = -1;
    } else if(m_nCurPage > m_pages->count()-1 && m_bScrollCycle == false) {
		m_nCurPage = m_pages->count()-1;
	} else if (m_nCurPage > m_pages->count()-1 && m_bScrollCycle == true) {
        m_nCurPage = m_pages->count();
    }
//    CCLOG("将滑动到 %d", m_nCurPage);
    
    if (_indicators) {
        
        for(int i = 0; i < _indicators->count(); i++) {
            auto dot = (Sprite *)_indicators->objectAtIndex(i);
            dot->setTexture(i == m_nCurPage ? highlightIndicator : normalIndicator);
        }
    }
    
    adjustPosition(true);
}

void KTScrollLayer::adjustPosition(bool animated)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCPoint  adjustPos = ccp(origin.x - visibleSize.width * (m_nCurPage+1), 0);
    m_pScrollView->setContentOffset(adjustPos, animated);
    if (m_delegate != NULL && m_nCurPage != -1 && m_nCurPage != m_pages->count()) {
        m_delegate->scrollLayerPageNumberDidChanged(m_nCurPage);
    }
}

void KTScrollLayer::setScrollCycle(bool scrollCycle)
{
    m_bScrollCycle = scrollCycle;
}

bool KTScrollLayer::getScrollCycle()
{
    return m_bScrollCycle;
}

KTScrollLayer::KTScrollLayer() : m_nCurPage(-1), m_pScrollView(NULL), m_pages(NULL), m_delegate(NULL), m_bGestureForward(false), m_bScrollCycle(false), m_pShowPages(NULL), _indicators(nullptr)
{

}

KTScrollLayer::~KTScrollLayer()
{
    m_delegate = NULL;
    CC_SAFE_RELEASE_NULL(m_pages);
    CC_SAFE_RELEASE_NULL(m_pShowPages);
}

#pragma mark - getter setter

bool KTScrollLayer::isGestureForward()
{
    return m_bGestureForward;
}

void KTScrollLayer::setGestureForward(bool gestureForward)
{
    m_bGestureForward = gestureForward;
}
CCArray* KTScrollLayer::getPages()
{
    return m_pages;
}
void KTScrollLayer::setPages(CCArray *pages)
{
    if (m_pages != pages)
    {
        CC_SAFE_RETAIN(pages);
        CC_SAFE_RELEASE(m_pages);
        m_pages = pages;
        
        m_pShowPages->removeAllObjects();
        CCSprite *pLast = createSprite((CCSprite *)pages->lastObject());
        CCSprite *pFirst = createSprite((CCSprite *)pages->objectAtIndex(0));
        m_pShowPages->addObject(pLast);
        for (int i = 0; i < m_pages->count(); i++) {
            m_pShowPages->addObject(m_pages->objectAtIndex(i));
        }
        m_pShowPages->addObject(pFirst);
    }
}