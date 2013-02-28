//
//  Animal.h
//  openNiSample007
//
//  Created by Yuan Li on 2/25/13.
//  Copyright 2013 nyu. All rights reserved.
//

#ifndef ANIMAL_H_
#define ANIMAL_H_

#pragma once

namespace Jungle {
    class Animal
    {
    public:
        Animal(void);
        virtual ~Animal(void);
        
        virtual void Update(){};
        virtual void Draw(){};
    };
}


#endif
