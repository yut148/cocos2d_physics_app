#ifndef __physicsAPP__GameLayer__
#define __physicsAPP__GameLayer__

#include "cocos2d.h"

class GameLayer : public cocos2d::Layer
{
protected:
    enum Tag
    {
        T_Background = 1,
        T_Enemy,
        T_Ball,
        T_Gum1,
        T_Gum2,
    };
    
    enum ZOrder
    {
        Z_Background = 1,
        Z_Enemy,
        Z_Launcher2,
        Z_Gum2,
        Z_Ball,
        Z_Gum1,
        Z_Launcher1,
    };
    
    void createBackground();
    void createGround();
    void createEnemy(cocos2d::Point positon);
    void createBall();
    cocos2d::Point caluculatePosition(cocos2d::Point touchPosition);
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameLayer);
    virtual void onEnter();
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif /* defined(__physicsAPP__GameLayer__) */
