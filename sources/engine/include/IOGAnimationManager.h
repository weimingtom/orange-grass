/*
 * IOGAabb.h
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
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
