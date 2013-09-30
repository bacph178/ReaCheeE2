//
//  RankingScene.cpp
//  ReaCheeE2
//
//  Created by macbook_016 on 2013/09/30.
//
//

#include "RankingScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
CCScene* RankingScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    RankingScene *layer = RankingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool RankingScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    _size = CCDirector::sharedDirector()->getWinSize();
    _width = _size.width;
    _height = _size.height;
    _SIZE_RATIO = (_width + _height) / (640 + 960);
    _SIZE_RATIO_X = _width / 640;
    _SIZE_RATIO_Y = _height / 960;
    _array = new CCArray;
    
    CCSprite *background = CCSprite::create("bg.png");
    background->setAnchorPoint(ccp(0.5, 0.5));
    background->setPosition(ccp(_width / 2, _height / 2));
    this->addChild(background);
    
    CCSprite *scoreLayer = CCSprite::create("rankBg.png");
    scoreLayer->setAnchorPoint(ccp(0.5, 0.5));
    scoreLayer->setPosition(ccp(_width / 2, _height / 2));
    this->addChild(scoreLayer);
    
    CCMenuItemImage * normal =
    CCMenuItemImage::create("rankNormal.png", "rankNormal.png", this,
                            menu_selector(RankingScene::onNormal));
    normal->setPosition(ccp(96 * _SIZE_RATIO_X, 826 * _SIZE_RATIO_Y));
    _normalOver = CCSprite::create("rankNomal_over.png");
    _normalOver->setPosition(normal->getPosition());
    this->addChild(_normalOver, 1);
    
    CCMenuItemImage * hard =
    CCMenuItemImage::create("rankHard.png", "rankHard.png", this,
                            menu_selector(RankingScene::onHard));
    hard->setPosition(ccp(246 * _SIZE_RATIO_X, 826 * _SIZE_RATIO_Y));
    _hardOver = CCSprite::create("rankHard_over.png");
    _hardOver->setPosition(hard->getPosition());
    this->addChild(_hardOver,1);
    _hardOver->setVisible(false);
    
    CCMenuItemImage * sensitive =
    CCMenuItemImage::create("rankSensitive.png", "rankSensitive.png",this,
                            menu_selector(RankingScene::onSensitive));
    sensitive->setPosition(ccp(396 * _SIZE_RATIO_X, 826 * _SIZE_RATIO_Y));
    
    _sensitiveOver = CCSprite::create("rankSensitive_over.png");
    _sensitiveOver->setPosition(sensitive->getPosition());
    this->addChild(_sensitiveOver, 1);
    _sensitiveOver->setVisible(false);
    
    CCMenuItemImage * stealth =
    CCMenuItemImage::create("rankSteath.png", "rankSteath.png", this,
                            menu_selector(RankingScene::onStealth));
    stealth->setPosition(ccp(545 * _SIZE_RATIO_X, 826 * _SIZE_RATIO_Y));
    _stealthOver = CCSprite::create("rankSteath_over.png");
    _stealthOver->setPosition(stealth->getPosition());
    this->addChild(_stealthOver, 1);
    _stealthOver->setVisible(false);

    CCMenu * pMenu = CCMenu::create(normal, hard, sensitive, stealth, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu);

    for (int i = 0; i < 10; i++) {
        char rankBuf[10] = {0};
        char scoreBuf[10] = {0};
        sprintf(rankBuf, "%d", i + 1);
        sprintf(scoreBuf, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey(rankBuf));
        _scoreLabel = CCLabelTTF::create(scoreBuf, "Time new Roman", 50);
        if (i < 5) {
            _scoreLabel->setPosition(ccp(_width / 2.8,
                                        (610 - 90 * (i % 5)) * _SIZE_RATIO_Y));
        } else {
            _scoreLabel->setPosition(ccp(_width * 3.2 / 4,
                                        (610 - 90 * (i % 5)) * _SIZE_RATIO_Y));
        }
        this->addChild(_scoreLabel);
        _array->addObject(_scoreLabel);
    }

    return true;
}

void RankingScene::onNormal(CCObject *pSender) {
    _normalOver->setVisible(true);
    _hardOver->setVisible(false);
    _sensitiveOver->setVisible(false);
    _stealthOver->setVisible(false);
    for (int i = 0; i < 10; i++) {
        char rankBuf[10] = {0};
        char scoreBuf[10] = {0};
        sprintf(rankBuf, "%d", i + 1);
        sprintf(scoreBuf, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey(rankBuf));
        CCLabelTTF * scoreLabel = (CCLabelTTF *)_array->objectAtIndex(i);
        scoreLabel->setString(scoreBuf);
    }
    
}

void RankingScene::onHard(CCObject * pSender) {
    _normalOver->setVisible(false);
    _hardOver->setVisible(true);
    _sensitiveOver->setVisible(false);
    _stealthOver->setVisible(false);
    for (int i = 0; i < 10; i++) {
        char rankBuf[10] = {0};
        char scoreBuf[10] = {0};
        sprintf(rankBuf, "%d", i + 11);
        sprintf(scoreBuf, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey(rankBuf));
        CCLabelTTF * scoreLabel = (CCLabelTTF *)_array->objectAtIndex(i);
        scoreLabel->setString(scoreBuf);
    }
}

void RankingScene::onSensitive(CCObject * pSender) {
    _normalOver->setVisible(false);
    _hardOver->setVisible(false);
    _sensitiveOver->setVisible(true);
    _stealthOver->setVisible(false);
    for (int i = 0; i < 10; i++) {
        char rankBuf[10] = {0};
        char scoreBuf[10] = {0};
        sprintf(rankBuf, "%d", i + 21);
        sprintf(scoreBuf, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey(rankBuf));
        CCLabelTTF * scoreLabel = (CCLabelTTF *)_array->objectAtIndex(i);
        scoreLabel->setString(scoreBuf);
    }
}

void RankingScene::onStealth(CCObject * pSender) {
    _normalOver->setVisible(false);
    _hardOver->setVisible(false);
    _sensitiveOver->setVisible(false);
    _stealthOver->setVisible(true);
    for (int i = 0; i < 10; i++) {
        char rankBuf[10] = {0};
        char scoreBuf[10] = {0};
        sprintf(rankBuf, "%d", i + 31);
        sprintf(scoreBuf, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey(rankBuf));
        CCLabelTTF * scoreLabel = (CCLabelTTF *)_array->objectAtIndex(i);
        scoreLabel->setString(scoreBuf);
    }
}