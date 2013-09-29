/*
 *  IOGAnimationManager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGANIMATIONMANAGER_H_
#define IOGANIMATIONMANAGER_H_

#include <IOGAnimation.h>


class IOGAnimationManager
{
public:
    virtual ~IOGAnimationManager() {}

    // create animation.
    virtual IOGAnimation* CreateAnimation (const std::string& _Alias) = 0;

    // get animation by alias.
    virtual IOGAnimation* GetAnimation (const std::string& _Alias) = 0;
};

#endif
