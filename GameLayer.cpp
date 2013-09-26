//
//  GameLayer.cpp
//  ReaCheeE2
//
//  Created by macbook_016 on 2013/09/19.
//
//

#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

CCScene * GameLayer::scene(){
    CCScene * scene = CCScene::create();
    GameLayer *layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init(){
    if ( !CCLayer::init() ) {
        return false;
    }
    _size = CCDirector::sharedDirector()->getWinSize();
    _width = _size.width;
    _height = _size.height;
    _SIZE_RATIO = (_width + _height) / (640 + 960);
    _SIZE_RATIO_X = _width / 640;
    _SIZE_RATIO_Y = _height / 960;
    _score = 0;
    _isContinue = true;
    _marioRoot = ccp(20 * _SIZE_RATIO_X, 200 * _SIZE_RATIO_Y);
    _lineRoot = ccp(25 * _SIZE_RATIO_X, 200 * _SIZE_RATIO_Y);
    
    CCSprite *background = CCSprite::create("bg.png");
    background->setAnchorPoint(ccp(0.5, 0.5));
    background->setPosition(ccp(_width / 2, _height / 2));
    this->addChild(background);
    
    CCSprite *table_mark = CCSprite::create("table_mark.png");
    table_mark->setAnchorPoint(ccp(0.5, 0.5));
    table_mark->setPosition(ccp(_width / 2, 900 * _SIZE_RATIO_Y));
    this->addChild(table_mark);
    
    _scoreLabel = CCLabelTTF::create("00", "Time new Roman", 50);
    _scoreLabel->setPosition(ccp(_width / 2, 870 * _SIZE_RATIO_Y));
    _scoreLabel->setColor(ccc3(0, 0, 0));
    this->addChild(_scoreLabel);
    
    _mario = CCSprite::create("1.png");
    _mario->setAnchorPoint(ccp(0.5, 0));
    _mario->setPosition(_marioRoot);
    this->addChild(_mario);
    
    CCSprite * marioTree = CCSprite::create("line.png");
    marioTree->setAnchorPoint(ccp(1, 1));
    marioTree->setPosition(_lineRoot);
    this->addChild(marioTree);
    
    _tree1 = CCSprite::create("line.png");
    _tree1->setAnchorPoint(ccp(1, 1));
    _tree1->setPosition(ccp(300 * _SIZE_RATIO_X, 200 * _SIZE_RATIO_Y));
    this->addChild(_tree1);
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("level") == 4) {
        CCScaleTo *scale = CCScaleTo::create(0.1, 1);
        CCCallFuncN *stealth = CCCallFuncN::create(this,callfuncN_selector(GameLayer::stealthCallBack));
        CCSequence *tree1 = CCSequence::create(scale, stealth, NULL);
        _tree1->runAction(tree1);
    }

    _tree2 = CCSprite::create("line.png");
    _tree2->setAnchorPoint(ccp(1, 1));
    this->addChild(_tree2);
    
    _tap = CCSprite::create("btn_push.png");
    _tap->setAnchorPoint(ccp(0.5 , 0));
    _tap->setPosition(ccp(_size.width / 2, 0));
    this->addChild(_tap);
    
    _tap2 = CCSprite::create("btn_push_over.png");
    _tap2->setAnchorPoint(ccp(0.5 , 0));
    _tap2->setPosition(ccp(_size.width / 2, 0));
    _tap2->setVisible(false);
    this->addChild(_tap2);
    
    _line = CCSprite::create("line03.png");
    _line->setScaleY(0);
    _line->setAnchorPoint(CCPointZero);
    _line->setPosition(_lineRoot);
    this->addChild(_line, 1000);
    
    // pause layer
    _pauseLayer = CCSprite::create("frame_small.png");
    _pauseLayer->setScale(_SIZE_RATIO);
    _pauseLayer->setAnchorPoint(ccp(0.5, 1));
    _pauseLayer->setPosition(ccp(_width / 2, _height));
    
    CCMenuItemImage * continueItem = CCMenuItemImage::create("continue.png", "continue.png",
                                                        this, menu_selector(GameLayer::onContinue));
    continueItem->setPosition(_pauseLayer->convertToNodeSpace(ccp(_width / 2, _height * 3.6 / 5)));
    CCMenuItemImage * restartItem = CCMenuItemImage::create("restart.png", "restart.png",
                                                            this, menu_selector(GameLayer::onRestart));
    restartItem->setPosition(_pauseLayer->convertToNodeSpace(ccp(_width / 2, _height * 2.8 / 5)));
    CCMenuItemImage * quitItem = CCMenuItemImage::create("quit.png", "quit.png",
                                                         this, menu_selector(GameLayer::onQuit));
    quitItem->setPosition(_pauseLayer->convertToNodeSpace(ccp(_width / 2, _height*2 / 5)));
    CCMenu *pauseMenu = CCMenu::create(continueItem, restartItem, quitItem, NULL);
    pauseMenu->setPosition(ccp(0, 0));
    _pauseLayer->addChild(pauseMenu);
    this->addChild(_pauseLayer,1);
    _pauseLayer->setVisible(false);
    
    //end Layer
    _endLayer = CCSprite::create("frame_small.png");
    _endLayer->setScale(_SIZE_RATIO);
    _endLayer->setAnchorPoint(ccp(0.5, 1));
    _endLayer->setPosition(ccp(_width / 2, _height));
    
    _endScore = CCLabelTTF::create("00", "Time New Roman", 200);
    _endScore->setPosition(_endLayer->convertToNodeSpace(ccp(320 * _SIZE_RATIO_X, 650 * _SIZE_RATIO_Y)));
    _endScore->setColor(ccc3(0, 0, 0));
    _endLayer->addChild(_endScore);
    CCMenuItemImage * restart = CCMenuItemImage::create("restart_small.png", "restart_small.png",
                                                        this, menu_selector(GameLayer::onRestart));
    restart->setPosition(_endLayer->convertToNodeSpace(ccp(-135 * _SIZE_RATIO_X, -100 * _SIZE_RATIO_Y)));
    CCMenuItemImage * quit = CCMenuItemImage::create("quit_small.png", "quit_small.png",
                                                     this, menu_selector(GameLayer::onQuit));
    quit->setPosition(_endLayer->convertToNodeSpace(ccp(145 * _SIZE_RATIO_X, -100 * _SIZE_RATIO_Y)));
    CCMenu * endMenu = CCMenu::create(restart, quit, NULL);
   // endMenu->setPosition(ccp(0, 0));
    _endLayer->addChild(endMenu);
    this->addChild(_endLayer, 1);
    _endLayer->setVisible(false);
    
    
    CCMenuItemImage *pCloseItem =
    CCMenuItemImage::create("menu.png", "menu.png",
                            this,menu_selector(GameLayer::closeCallback));
    pCloseItem->
    setPosition(ccp(600 * _SIZE_RATIO_X, 900 * _SIZE_RATIO_Y));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu);
    this->schedule( schedule_selector(GameLayer::updateScore), 0.1 );
    
    this->setTouchEnabled(true);
    return true;
}

void GameLayer::menuCloseCallback(CCObject * pSender) {
    CCScene *pScene = HelloWorld::scene();
    CCDirector::sharedDirector()->runWithScene(pScene);
}

void GameLayer::run() {
    CCAnimation * animation = CCAnimation::create();
    for (int i = 2; i < 9; i++) {
        char szImageFileName[10] = {0};
        sprintf(szImageFileName, "%d.png", i);
        animation->addSpriteFrameWithFileName(szImageFileName);
    }
    animation->setDelayPerUnit(0.1);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(5);
    CCAnimate *animate = CCAnimate::create(animation);
    _mario->runAction(animate);
}

void GameLayer::updateBrige(float dt) {
    _dt++;
    int a = CCUserDefault::sharedUserDefault()->getIntegerForKey("level");
    if (a != 3) {
        _line->setScaleY(_dt);
        _line->setScaleX(1);
    }
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent * event) {
    if (_isContinue) {
        CCPoint location =
        this->getParent()->
        convertTouchToNodeSpace((CCTouch*)( pTouches->anyObject()));
        if (_tap->boundingBox().containsPoint(location)) {
            _dt = 1;
            _tap2->setVisible(true);
            this->schedule( schedule_selector(GameLayer::updateBrige), 0.1 );
        }

    }
}

void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent * event) {
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent * event) {
    if (_isContinue) {
        _isContinue = false;
        _tap2->setVisible(false);
        float withLine = _line->getContentSize().height * _dt;
        CCPoint treeBackPoint = ccp(_mario->getPositionX(), 200);
        CCPoint treeBackPoint2 = ccp(_mario->getPositionX(), 200);
        CCPoint lineBackPoint = ccp(_mario->getPositionX() - withLine, 200);
        CCPoint location =
            this->getParent()->
                convertTouchToNodeSpace((CCTouch*)( pTouches->anyObject()));
        
        if (_tap->boundingBox().containsPoint(location)) {
            this->unschedule( schedule_selector(GameLayer::updateBrige));
            _tree1->setVisible(true);
            _tree2->setVisible(true);
            CCRotateBy * rotate = CCRotateBy::create(0.1f, 90);
            if (CCUserDefault::sharedUserDefault()->getIntegerForKey("level") == 3) {
                CCCallFuncN *sen = CCCallFuncN::create(this,callfuncN_selector(GameLayer::sensitiveCallBack));
                CCSequence *lineSq = CCSequence::create(sen, rotate, NULL);
                _line->runAction(lineSq);
            } else {
                _line->runAction(rotate);
            }
            this->run();
            CCPoint taget = ccp(_mario->getPositionX() + withLine + 10, 200);
            CCPoint finalTaget = ccp(_tree1->getPositionX(), 200);
            CCPoint finalTaget2 = ccp(_tree2->getPositionX(), 200);
            CCMoveTo *move = CCMoveTo::create(3, taget);
            CCRect treeRect1 = _tree1->boundingBox();
            CCRect treeRect2 = _tree2->boundingBox();
            if (treeRect1.containsPoint(taget) || treeRect2.containsPoint(taget)) {
                _score++;
                int b = _score / 3;
                if (b >= 5) {
                    b = rand() % 5;
                }
                int a = 0;
                CCCallFuncN *endtouch = CCCallFuncN::create(this,callfuncN_selector(GameLayer::endTouch));
                if (treeRect1.containsPoint(taget)) {
                    CCMoveTo *finalMove = CCMoveTo::create(4, finalTaget);
                    CCDelayTime * delay = CCDelayTime::create(4);
                    CCMoveTo *marioBack = CCMoveTo::create(1, _marioRoot);
                    CCSequence *sq = CCSequence::create(finalMove, marioBack, NULL);
                    _mario->runAction(sq);
                    
                    CCMoveTo *treeBack = CCMoveTo::create(1, treeBackPoint);
                    CCSequence *sq2 = CCSequence::create(delay, treeBack, NULL);
                    _tree1->runAction(sq2);
                    
                    CCMoveTo *lineBack = CCMoveTo::create(1, lineBackPoint);
                    CCScaleTo * scale = CCScaleTo::create(0, 0);
                    CCMoveTo *lineBack1 = CCMoveTo::create(0.1, _lineRoot);
                    CCRotateBy * rotate1 = CCRotateBy::create(0.1f, 270);
                    CCSequence *sq3 = CCSequence::create(delay, lineBack, scale,
                                                         lineBack1, rotate1, NULL);
                    _line->runAction(sq3);
                    _line->setPosition(_lineRoot);
                    
                    _tree2->setPosition(ccp((680 + _tree2->getContentSize().width / (b + 1)) * _SIZE_RATIO_X, 200 * _SIZE_RATIO_Y));
                    _tree2->setScaleX(1 - b * 0.2);
                    
                    do {
                        a = rand() % 680;
                    } while (a <= _tree2->getContentSize().width / (b +1) + 30);
                    CCDelayTime *delay2 = CCDelayTime::create(4);
                    CCMoveBy *moveBy = CCMoveBy::create(1, ccp(-a, 0));
                    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("level") == 4) {
                        CCCallFuncN *stealth = CCCallFuncN::create(this,callfuncN_selector(GameLayer::stealthCallBack2));
                        CCSequence *sq4 = CCSequence::create(delay2, moveBy, endtouch, stealth, NULL);
                        _tree2->runAction(sq4);
                    } else {
                        CCSequence *sq4 = CCSequence::create(delay2, moveBy, endtouch, NULL);
                        _tree2->runAction(sq4);
                    }
                } else {
                    CCMoveTo *finalMove = CCMoveTo::create(4, finalTaget2);
                    CCDelayTime * delay = CCDelayTime::create(4);
                    CCMoveTo *marioBack = CCMoveTo::create(1, _marioRoot);
                    CCSequence *sq = CCSequence::create(finalMove, marioBack, NULL);
                    _mario->runAction(sq);
                    
                    CCMoveTo *treeBack = CCMoveTo::create(1, treeBackPoint2);
                    CCSequence *sq2 = CCSequence::create(delay, treeBack, NULL);
                    _tree2->runAction(sq2);
                    
                    CCMoveTo *lineBack = CCMoveTo::create(1, lineBackPoint);
                    CCScaleTo * scale = CCScaleTo::create(0, 0);
                    CCMoveTo *lineBack1 = CCMoveTo::create(0.1, _lineRoot);
                    CCRotateBy * rotate1 = CCRotateBy::create(0.1f, 270);
                    CCSequence *sq3 = CCSequence::create(delay, lineBack, scale,
                                                         lineBack1, rotate1, NULL);
                    _line->runAction(sq3);
                    _line->setPosition(_lineRoot);
                    
                    _tree1->setPosition(ccp((680 + _tree1->getContentSize().width / (b + 1)) * _SIZE_RATIO_X, 200 * _SIZE_RATIO_Y));
                    _tree1->setScaleX(1 - (b + 1) * 0.2);
                    CCDelayTime *delay2 = CCDelayTime::create(4);
                    do {
                        a = rand() % 680;
                    } while (a <= _tree1->getContentSize().width / (b +1) + 30);
                    CCMoveBy *moveBy = CCMoveBy::create(1, ccp(-a, 0));
                    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("level") == 4) {
                        CCCallFuncN *stealth = CCCallFuncN::create(this,callfuncN_selector(GameLayer::stealthCallBack));
                        CCSequence *sq4 = CCSequence::create(delay2, moveBy, endtouch, stealth, NULL);
                        _tree1->runAction(sq4);
                    } else {
                        CCSequence *sq4 = CCSequence::create(delay2, moveBy, endtouch, NULL);
                        _tree1->runAction(sq4);
                    }
                }
            } else {
                CCCallFuncN *endGame = CCCallFuncN::create(this,callfuncN_selector(GameLayer::setEndGame));
                CCPoint tagetdow = ccp(_mario->getPositionX() + withLine + 10, 0);
                CCMoveTo *movedown = CCMoveTo::create(3, tagetdow);
                CCSequence *sq = CCSequence::create(move, movedown, endGame, NULL);
                _mario->runAction(sq);
                CCDelayTime * delay = CCDelayTime::create(3);
                CCSequence * sq2 = CCSequence::create(delay, rotate, NULL);
                _line->runAction(sq2);
            }
        }
    }
}
void GameLayer::endTouch(CCNode *node) {
    this->_isContinue = true;
}

void GameLayer::setEndGame(CCNode *node) {
    _endLayer->setVisible(true);
}
void GameLayer::closeCallback(CCObject* pSender)
{
    if (_isContinue) {
        _pauseLayer->setVisible(true);
        _isContinue = false;
    }
}

void GameLayer::onContinue(CCObject * pSender) {
    _pauseLayer->setVisible(false);
    _isContinue = true;
}

void GameLayer::onRestart(CCObject * pSender) {
    CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

void GameLayer::onQuit(CCObject * pSender) {
    CCDirector::sharedDirector()->replaceScene(StartGame::scene());
}

void GameLayer::updateScore(float dt) {
    char scoreBuf[20] = {0};
    if (_score < 10) sprintf(scoreBuf, "0%d", _score);
    else sprintf(scoreBuf, "%d", _score);
    _scoreLabel->setString(scoreBuf);
    _endScore->setString(scoreBuf);
}

void GameLayer::sensitiveCallBack(CCNode *node) {
    _line->setScaleY(_dt);
    _line->setScaleX(1);
}

void GameLayer::stealthCallBack(CCNode * node) {
    _tree1->setVisible(false);
}

void GameLayer::stealthCallBack2(CCNode * node) {
    _tree2->setVisible(false);
}