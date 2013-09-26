//
//  StartGame.cpp
//  ReaCheeE2
//
//  Created by macbook_016 on 2013/09/24.
//
//

#include "StartGame.h"
using namespace cocos2d;

CCScene* StartGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartGame *layer = StartGame::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool StartGame::init() {
    if (!CCLayer::init()) {
        return false;
    }
    _size = CCDirector::sharedDirector()->getWinSize();
    _width = _size.width;
    _height = _size.height;
    _SIZE_RATIO = (_width + _height) / (640 + 960);
    _SIZE_RATIO_X = _width / 640;
    _SIZE_RATIO_Y = _height / 960;
    
    CCSprite *background = CCSprite::create("bg_home.png");
    background->setAnchorPoint(ccp(0.5, 0.5));
    background->setPosition(ccp(_width / 2, _height / 2));
    this->addChild(background);
    
    CCMenuItemImage *startButton = CCMenuItemImage::create(
                                                          "start.png",
                                                          "start.png",
                                                          this,
                                                          menu_selector(StartGame::onStart));
    startButton->setPosition(ccp(_width / 2, _height /2));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(startButton, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu);
    
    // pause layer
    _startLayer = CCSprite::create("frame_large.png");
    _startLayer->setScale(_SIZE_RATIO);
    _startLayer->setAnchorPoint(ccp(0.5, 1));
    _startLayer->setPosition(ccp(_width / 2, _height));
    
    CCMenuItemImage * normalItem = CCMenuItemImage::create("normal.png", "normal.png",
                                                             this, menu_selector(StartGame::onNormal));
    normalItem->setPosition(_startLayer->convertToNodeSpace(ccp(_width / 2, _height * 3.6 / 5)));
    
    CCMenuItemImage * hardItem = CCMenuItemImage::create("hard.png", "hard.png",
                                                            this, menu_selector(StartGame::onHard));
    hardItem->setPosition(_startLayer->convertToNodeSpace(ccp(_width / 2, _height * 2.8 / 5)));
    
    CCMenuItemImage * sensitiveItem = CCMenuItemImage::create("sensitive.png", "sensitive.png",
                                                         this, menu_selector(StartGame::onSensitive));
    sensitiveItem->setPosition(_startLayer->convertToNodeSpace(ccp(_width / 2, _height * 2.0 / 5)));
    
    CCMenuItemImage * stealthItem = CCMenuItemImage::create("stealth.png", "stealth.png",
                                                            this, menu_selector(StartGame::onStealth));
    stealthItem->setPosition(_startLayer->convertToNodeSpace(ccp(_width / 2, _height * 1.2 / 5)));
    
    CCMenuItemImage * backItem = CCMenuItemImage::create("quit_small.png", "quit_small.png",
                                                         this, menu_selector(StartGame::onBack));
    backItem->setPosition(_startLayer->convertToNodeSpace(ccp(_width / 2, _height * 0.55 / 5)));
    
    CCMenu *startMenu = CCMenu::create(normalItem, hardItem, sensitiveItem, stealthItem, backItem, NULL);
    startMenu->setPosition(ccp(0, 0));
    _startLayer->addChild(startMenu);
    this->addChild(_startLayer);
    _startLayer->setVisible(false);

    

    return true;
}

void StartGame::onStart(CCObject* pSender) {
    _startLayer->setVisible(true);
}

void StartGame::onNormal(CCObject* pSender) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey("level", 1);
    CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

void StartGame::onHard(CCObject* pSender) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey("level", 2);
    CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

void StartGame::onSensitive(CCObject* pSender) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey("level", 3);
    CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

void StartGame::onStealth(CCObject* pSender) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey("level", 4);
    CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

void StartGame::onBack(CCObject* pSender) {
    _startLayer->setVisible(false);
}


