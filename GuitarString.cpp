//
//  GuitarString.cpp
//  ps5b
//
//  Created by Jingxian Shi on 3/26/18.
//  Copyright © 2018 Jingxian Shi. All rights reserved.
//
#include <stdint.h>
#include <cmath>
#include <vector>
#include "GuitarString.hpp"

GuitarString::GuitarString(double frequency) {
    int size = ceil(44100.0/frequency);
    _rb = new RingBuffer(size);
    _time = 0;
    pluck();
}

GuitarString::GuitarString(std::vector<sf::Int16> init) {
    _rb = new RingBuffer(static_cast<int>(init.size()));
    for (int i = 0; i < init.size(); i++) {
        _rb->enqueue(init[i]);
    }
    _time = 0;
}

GuitarString::~GuitarString() {
    delete _rb;
}

void GuitarString::pluck() {
    _rb->empty();
    while (!_rb->isFull()) {
        _rb->enqueue((sf::Int16)rand() & 0xffff);
    }
}

void GuitarString::tic() {
    sf::Int16 sample1 = _rb->dequeue();
    sf::Int16 sample2 = _rb->peek();
    double newUpdate = 0.996 * ((sample1 + sample2)/2.0);
    _rb->enqueue(newUpdate);
    _time++;
}

double GuitarString::sample() {
    return _rb->peek();
}

int GuitarString::time() {
    return _time;
}
