//
//  Body.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/18/16.
//
//

#include "Body.hpp"

void Body::setup()
{
    mouthBase.setup("imgs/body/mouth/1");
    drawingHBase.setup("imgs/body/hand/drawing");
    fetchingHBase.setup("imgs/body/hand/fetching");
    puttingHBase.setup("imgs/body/hand/putting");
    swipingHBase.setup("imgs/body/hand/swiping");
    
    ofAddListener(Global::eatEvent, this, &Body::onEatEvent);
    ofAddListener(Global::drawEvent, this, &Body::onDrawEvent);
    ofAddListener(Global::fetchEvent, this, &Body::onFetchEvent);
    ofAddListener(Global::putEvent, this, &Body::onPutEvent);
    ofAddListener(Global::swipeEvent, this, &Body::onSwipeEvent);
}

void Body::update()
{
    if (!mouths.empty())
    {
        if (mouths.front().isDone())
        {
            mouths.pop_front();
        }
    }
    if (!drawingHands.empty())
    {
        if (drawingHands.front().isDone())
        {
            drawingHands.pop_front();
        }
    }
    if (!fetchingHands.empty())
    {
        if (fetchingHands.front().isDone())
        {
            fetchingHands.pop_front();
        }
    }
    if (!puttingHands.empty())
    {
        if (puttingHands.front().isDone())
        {
            puttingHands.pop_front();
        }
    }
    if (!swipingHands.empty())
    {
        if (swipingHands.front().isDone())
        {
            swipingHands.pop_front();
        }
    }
}

void Body::draw()
{
    for (auto b : mouths)
        b.draw();
    for (auto b : drawingHands)
        b.draw();
    for (auto b : fetchingHands)
        b.draw();
    for (auto b : puttingHands)
        b.draw();
    for (auto b : swipingHands)
        b.draw();
}

void Body::onEatEvent()
{
    Mouth m;
    mouths.push_back(m);
    mouths.back().setup(&mouthBase);
    mouths.back().onEatEvent();
}

void Body::onDrawEvent(ofPoint& dest)
{
    DrawingHand d;
    drawingHands.push_back(d);
    drawingHands.back().setup(&drawingHBase);
    drawingHands.back().onDrawEvent(dest);
}

void Body::onFetchEvent()
{
    FetchingHand f;
    fetchingHands.push_back(f);
    fetchingHands.back().setup(&fetchingHBase);
    fetchingHands.back().onFetchEvent();
}

void Body::onPutEvent(ofPoint& dest)
{
    PuttingHand p;
    puttingHands.push_back(p);
    puttingHands.back().setup(&puttingHBase);
    puttingHands.back().onPutEvent(dest);
}

void Body::onSwipeEvent()
{
    SwipingHand s;
    swipingHands.push_back(s);
    swipingHands.back().setup(&swipingHBase);
    swipingHands.back().onSwipeEvent();
}
