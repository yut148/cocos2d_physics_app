#include "GameLayer.h"

#define WINSIZE Director::getInstance()->getWinSize()
#define BALL_INIT_POS Point(100, 150)
#define BALL_STRETCH_LENGTH 50
#define LAUNCHER_POS1 Point(80, 135)
#define LAUNCHER_POS2 Point(125, 140)

USING_NS_CC;

Scene* GameLayer::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = GameLayer::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void GameLayer::onEnter()
{
    Layer::onEnter();
    
    auto v = Vect(0,-98);
    auto scene = dynamic_cast<Scene*>(this->getParent());
    scene->getPhysicsWorld()->setGravity(v);
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    createBackground();
    createGround();
    createBall();
}

void GameLayer::createBackground()
{
    auto background = Sprite::create("background.png");
    background->setAnchorPoint(Point(0, 0.5));
    background->setPosition(Point(0, WINSIZE.height / 2));
    addChild(background, Z_Background, T_Background);
}

void GameLayer::createGround()
{
    auto background = getChildByTag(T_Background);
    
    PhysicsMaterial material;
    material.density = 0.5;//密度
    material.restitution = 0.5;//反発係数
    material.friction = 0.8;//摩擦係数
    
    auto body = PhysicsBody::createBox(Size(background->getContentSize().width,50) ,material);
    body->setDynamic(false);
    
    auto node = Node::create();
    node->setAnchorPoint(Point::ANCHOR_MIDDLE);
    node->setPhysicsBody(body);
    node->setPosition(Point(background->getContentSize().width / 2, 25));
    addChild(node);
}

void GameLayer::createEnemy(cocos2d::Point position)
{
    auto enemy = Sprite::create("enemy1.png");
    enemy->setPosition(position);
    enemy->setTag(T_Enemy);
    
    auto animation = Animation::create();
    animation->addSpriteFrameWithFile("enemy2.png");
    animation->addSpriteFrameWithFile("enemy1.png");
    animation->setDelayPerUnit(1);
    
    auto repeat = RepeatForever::create(Animate::create(animation));
    enemy->runAction(repeat);
    
    PhysicsMaterial material;
    material.density = 0.5;
    material.restitution = 0.5;
    material.friction = 0.3;
    
    auto body = PhysicsBody::createCircle(enemy->getContentSize().width * 0.47, material);
    body->setDynamic(true);
    enemy->setPhysicsBody(body);
    
    addChild(enemy, Z_Enemy);
}

bool GameLayer::onTouchBegan(Touch* touch, Event* unused_evetnt)
{
    bool ret = false;
    
    auto ball = getChildByTag(T_Ball);
    if (ball && ball->getBoundingBox().containsPoint(touch->getLocation())) {
        
        ball->setPosition(caluculatePosition(touch->getLocation()));
        ret = true;
    }
    
    return ret;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
    auto ball = getChildByTag(T_Ball);
    
    if (ball) {
        
        ball->setPosition(caluculatePosition(touch->getLocation()));
        
        auto angle = ((BALL_INIT_POS - ball->getPosition()).getAngle());
        auto pos = ball->getPosition() + Point(-25, 0).rotate(Point::forAngle(angle));
    }
    
    auto gum1 = getChildByTag(T_Gum1);
    
    if (!gum1) {
        
        gum1 = Sprite::create("brown.png");
        addChild(gum1, Z_Gum1, T_Gum1);
        
    }
    
    //gum1->setPosition(Lau)
    
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event)
{

}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event)
{

}






