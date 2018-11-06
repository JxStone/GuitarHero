//
//  GuitarString.hpp
//  ps5b
//
//  Created by Jingxian Shi on 3/26/18.
//  Copyright © 2018 Jingxian Shi. All rights reserved.
//

#ifndef GuitarString_hpp
#define GuitarString_hpp

#include <SFML/System.hpp>
#include <vector>
#include "RingBuffer.hpp"

class GuitarString {
 public:
    explicit GuitarString(double frequency);
    explicit GuitarString(std::vector<sf::Int16> init);
    ~GuitarString();
    void pluck();
    void tic();
    double sample();
    int time();
 private:
    RingBuffer* _rb;
    int _time;
};

#endif /* GuitarString_hpp */
