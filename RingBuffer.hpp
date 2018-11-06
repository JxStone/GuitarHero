//
//  RingBuffer.hpp
//  ps5a
//
//  Created by Jingxian Shi on 3/19/18.
//  Copyright © 2018 Jingxian Shi. All rights reserved.
//

#ifndef RingBuffer_hpp
#define RingBuffer_hpp

#include <stdio.h>
#include <stdint.h>
#include <vector>

class RingBuffer {
 public:
    explicit RingBuffer(int capacity);
    int size() {return _size;}
    bool isEmpty() {return (_size == 0);}
    bool isFull() {return (_size == _capacity); }
    void enqueue(int16_t x);
    int16_t dequeue();
    int16_t peek();
    void empty();
 private:
    std::vector<int16_t> _queue;
    int _size;
    int _capacity;
    int _front;
    int _end;
};


#endif /* RingBuffer_hpp */

