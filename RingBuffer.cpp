//
//  RingBuffer.cpp
//  ps5a
//
//  Created by Jingxian Shi on 3/19/18.
//  Copyright © 2018 Jingxian Shi. All rights reserved.
//

#include "RingBuffer.hpp"
#include <exception>
#include <stdexcept>
#include <vector>
#include <string>

RingBuffer::RingBuffer(int capacity) {
    if ( capacity < 1 )
        throw std::invalid_argument("Capacity must be greater than zero");
    _queue.resize(capacity);
    _capacity = capacity;
    _size = 0;
    _front = 0;
    _end = 0;
}

void RingBuffer::enqueue(int16_t x) {
    if ( isFull() ) {
        throw std::runtime_error("Can't enqueue to a full ring");
    }
    _queue[_end] = x;
    if (_end == (_capacity-1)) {
        _end = 0;
        _size++;
        return;
    }
    _end++;
    _size++;
    return;
}

int16_t RingBuffer::dequeue() {
    if ( isEmpty() ) {
        throw std::runtime_error("Can't dequeue to an empty RingBuffer");
    }
    int16_t item = _queue[_front];
    if ( _front == (_capacity-1) ) {
        _front = 0;
        _size--;
        return item;
    }
    _size--;
    _front++;
    return item;
}

int16_t RingBuffer::peek() {
    if ( isEmpty() ) {
        throw std::runtime_error("Can't peek an empty RingBuffer");
    }
    return _queue[_front];
}

void RingBuffer::empty() {
    _front = 0;
    _end = 0;
    _size = 0;
}
