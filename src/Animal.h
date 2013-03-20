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
