//
//  RenderingTest.h
//  Rendering_Sprite
//
//  Created by 郭 一鸣 on 14-1-22.
//
//

#ifndef __Rendering_Sprite__RenderingTest__
#define __Rendering_Sprite__RenderingTest__

#include <iostream>
#include "cocos2d.h"

class Rendering_Sprite : public cocos2d::Layer
{
public:
    Rendering_Sprite(){}
    ~Rendering_Sprite()
    {
        if(batchNode)
        {
            batchNode->release();
            batchNode = NULL;
        }
    }
    virtual bool init() override;
    
    cocos2d::Sprite* createSpriteWithTag(int tag);
    void removeSpriteWithTag(int tag);
    void performanceActions(cocos2d::Sprite* sprite);
    
    void onIncrease(Object* pSender);
    void onDecrease(Object* pSender);
    
    void updateNodes();
    
    CREATE_FUNC(Rendering_Sprite);
protected:
    int rendered_num;
    int nodes_num;
    cocos2d::SpriteBatchNode* batchNode;
    cocos2d::Node* parent;
};

#endif /* defined(__Rendering_Sprite__RenderingTest__) */
