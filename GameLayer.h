//
//  GameLayer.h
//  ReaCheeE2
//
//  Created by macbook_016 on 2013/09/19.
//
//

#ifndef __ReaCheeE2__GameLayer__
#define __ReaCheeE2__GameLayer__

#include <iostream>
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "StartGame.h"
#include "RankingScene.h"

using namespace cocos2d;

class GameLayer : public CCLayer {
private:
    CCSprite *_mario;
    CCSprite *_line;
    CCSprite *_tap;
    CCSprite *_tap2;
    CCSprite *_tree1;
    CCSprite *_tree2;
    CCSprite *_pauseLayer;
    CCSprite *_endLayer;
    
    CCLabelTTF *_scoreLabel;
    CCLabelTTF *_endScore;
    CCLabelTTF *_rankLabel;
    CCLabelTTF *_topLabel;
    
    CCPoint _marioRoot;
    CCPoint _lineRoot;
    
    CCSize _size;
    
    bool _isContinue;
    bool _isStealth;
    
    float _dt;
    float _width;
    float _height;
    float _SIZE_RATIO;
    float _SIZE_RATIO_X;
    float _SIZE_RATIO_Y;
    
    int _score;
public:
    virtual bool init();
    static CCScene *scene();
    void menuCloseCallback(CCObject * pSender);
    void run();
    void updateBrige(float dt);
    void updateScore(float dt);
    void onContinue(CCObject * pSender);
    void onRestart(CCObject * pSender);
    void onQuit(CCObject * pSender);
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
    virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
    void closeCallback(CCObject* pSender);
    
    void endTouch(CCNode * node);
    void setEndGame(CCNode * node);
    void sensitiveCallBack(CCNode * node);
    void stealthCallBack(CCNode * node);
    void stealthCallBack2(CCNode * node);
    void score();
    
    CREATE_FUNC(GameLayer);
};

#endif /* defined(__ReaCheeE2__GameLayer__) */
