//
//  RankingScene.h
//  ReaCheeE2
//
//  Created by macbook_016 on 2013/09/30.
//
//

#ifndef __ReaCheeE2__RankingScene__
#define __ReaCheeE2__RankingScene__

#include <iostream>
#include "cocos2d.h"
#include "StartGame.h"
using namespace cocos2d;
class RankingScene : public cocos2d::CCLayer
{
private:
    CCSize _size;
    
    CCArray * _array;
    
    CCSprite * _normalOver;
    CCSprite * _hardOver;
    CCSprite * _sensitiveOver;
    CCSprite * _stealthOver;
    
    float _width;
    float _height;
    float _SIZE_RATIO;
    float _SIZE_RATIO_X;
    float _SIZE_RATIO_Y;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    void onNormal(CCObject * pSender);
    void onHard(CCObject * pSender);
    void onSensitive(CCObject * pSender);
    void onStealth(CCObject * pSender);
    void onQuit(CCObject * pSender);
    
    CREATE_FUNC(RankingScene);
};


#endif /* defined(__ReaCheeE2__RankingScene__) */
