//
//  RenderingTest.cpp
//  Rendering_Sprite
//
//  Created by 郭 一鸣 on 14-1-22.
//
//

#include "RenderingTest.h"
USING_NS_CC;

enum {
    kMaxNodes = 10000,
    kNodesIncrease = 250
};

enum {
    kTagInfoLayer = 1
};

bool Rendering_Sprite::init()
{
    if (! Layer::init()) {
        return false;
    }
    std::cout << "Rendering_Sprite called!" << std::endl;
    
    auto size = Director::getInstance()->getWinSize();
    
    int nodes = 250;
    rendered_num = 0;
    nodes_num = 0;
    batchNode = NULL;
    parent = this;
    
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
    batchNode = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 100);
    parent->addChild(batchNode, 0);
    
    if (batchNode) {
        batchNode->retain();
    }
    
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    
    MenuItemFont::setFontSize(100);
    auto decrease = MenuItemFont::create(" - ", CC_CALLBACK_1(Rendering_Sprite::onDecrease, this));
    decrease->setColor(Color3B(0, 200, 20));
    auto increase = MenuItemFont::create(" + ", CC_CALLBACK_1(Rendering_Sprite::onIncrease, this));
    increase->setColor(Color3B(0, 200, 20));
    
    auto menu = Menu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(Point(size.width / 2, size.height - 100));
    addChild(menu, 1);
    
    auto label = LabelTTF::create("Actions", "Arial", 40);
    label->setPosition(Point(size.width / 2, size.height - 32));
    label->setColor(Color3B(255, 255, 40));
    addChild(label, 1);
    
    auto infoLabel = LabelTTF::create("0 nodes", "Marker Felt", 40);
    infoLabel->setColor(Color3B(0, 200, 20));
    infoLabel->setPosition(Point(size.width / 2, size.height - 150));
    addChild(infoLabel, 1, kTagInfoLayer);
    
    while (nodes_num < nodes) {
        onIncrease(this);
    }
    
    return true;
}

void Rendering_Sprite::onDecrease(Object* pSender)
{
    if (nodes_num <= 0) {
        return;
    }
    
    for (int i = 0; i < kNodesIncrease; ++i) {
        nodes_num--;
        this->removeSpriteWithTag(nodes_num);
    }
    
    updateNodes();
}

void Rendering_Sprite::onIncrease(Object* pSender)
{
    if (nodes_num >= kMaxNodes) {
        return;
    }
    
    for (int i = 0; i < kNodesIncrease; ++i) {
        auto sprite = createSpriteWithTag(nodes_num);
        performanceActions(sprite);
        ++nodes_num;
    }
    
    updateNodes();
}

Sprite* Rendering_Sprite::createSpriteWithTag(int tag)
{
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
    Sprite* sprite = NULL;
    
    int x, y;
    int r = (CCRANDOM_0_1() * 1400 / 100);
    
    y = r / 5;
    x = r % 5;
    
    x *= 85;
    y *= 121;
    
    sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(x, y, 85, 121));
    batchNode->addChild(sprite, 0, tag + 100);
    
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    return sprite;
}

void Rendering_Sprite::updateNodes()
{
    if (nodes_num != rendered_num) {
        auto inforLabel = (LabelTTF *)getChildByTag(kTagInfoLayer);
        char str[16] = {0};
        sprintf(str, "%u nodes", nodes_num);
        inforLabel->setString(str);
        
        rendered_num = nodes_num;
    }
}

void Rendering_Sprite::removeSpriteWithTag(int tag)
{
    batchNode->removeChildAtIndex(tag, true);
}

void Rendering_Sprite::performanceActions(Sprite* sprite)
{
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Point((rand() % (int)size.width), (rand() % (int)size.height)));
    
    float peroid = 0.5f + (rand() % 1000) / 500.0f;
    auto rot = RotateBy::create(peroid, 360.0f * CCRANDOM_0_1());
    auto rot_back = rot->reverse();
    auto permanentRot = RepeatForever::create(Sequence::create(rot, rot_back, NULL));
    sprite->runAction(permanentRot);
    
    float growDuration = 0.5f + (rand() % 1000) / 500.0f;
    auto grow = ScaleBy::create(growDuration, 0.5f, 0.5f);
    auto permanentScale = RepeatForever::create(Sequence::create(grow, grow->reverse(), NULL));
    sprite->runAction(permanentScale);
}