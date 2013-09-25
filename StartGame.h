//
//  StartGame.h
//  ReaCheeE2
//
//  Created by macbook_016 on 2013/09/24.
//
//

#ifndef __ReaCheeE2__StartGame__
#define __ReaCheeE2__StartGame__

#include <iostream>
#include "cocos2d.h"
#include "GameLayer.h"
using namespace cocos2d;

class StartGame : public cocos2d::CCLayer
{
private:
    CCSize _size;
    
    CCSprite *_startLayer;
    
    float _width;
    float _height;
    float _SIZE_RATIO;
    float _SIZE_RATIO_X;
    float _SIZE_RATIO_Y;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    void onStart(CCObject* pSender);
    void onNormal(CCObject* pSender);
    void onHard(CCObject* pSender);
    void onSensitive(CCObject* pSender);
    void onStealth(CCObject* pSender);
    void onBack(CCObject* pSender);
    CREATE_FUNC(StartGame);
};


#endif /* defined(__ReaCheeE2__StartGame__) */
