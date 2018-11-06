/*
 Copyright 2015 Fred Martin, fredm@cs.uml.edu
 Mon Mar 30 08:58:49 2015
 
 based on Princeton's GuitarHeroLite.java
 www.cs.princeton.edu/courses/archive/fall13/cos126/assignments/guitar.html
 
 build with
 g++ -Wall -c GuitarHeroLite.cpp -lsfml-system \
 -lsfml-audio -lsfml-graphics -lsfml-window
 g++ -Wall GuitarHeroLite.o RingBuffer.o GuitarString.o \
 -o GuitarHeroLite -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window
 */

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <math.h>
#include <limits.h>

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>

#include "RingBuffer.hpp"
#include "GuitarString.hpp"

#define CONCERT_A 440.0
#define SAMPLES_PER_SEC 44100
using namespace std;

vector<sf::Int16> makeSamplesFromString(GuitarString& gs) {
    std::vector<sf::Int16> samples;
    
    gs.pluck();
    int duration = 8;  // seconds
    int i;
    for (i= 0; i < SAMPLES_PER_SEC * duration; i++) {
        gs.tic();
        samples.push_back(gs.sample());
    }
    
    return samples;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 200), "SFML Guitar Hero Lite");
    sf::Event event;
    double freq;
    unsigned key_index;
    string keyboard = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";
    vector < std::vector<sf::Int16> >samples(keyboard.length());
    vector<sf::SoundBuffer> buffer(keyboard.length());
    vector<sf::Sound> sound(keyboard.length());
    
    for (int i = 0; i < keyboard.length(); i++) {
        freq = CONCERT_A * pow(2, (i-24) / 12.0);
        GuitarString gs = GuitarString(freq);
        samples[i] = makeSamplesFromString(gs);
        if(!buffer[i].loadFromSamples(&samples[i][0], samples[i].size(), 2, SAMPLES_PER_SEC))
            throw runtime_error("sf::SoundBuffer: failed to load from samples.");
        sound[i].setBuffer(buffer[i]);
    }
    
    // we're reusing the freq and samples vars, but
    // there are separate copies of GuitarString, SoundBuffer, and Sound
    //   for each note
    //
    // GuitarString is based on freq
    // samples are generated from GuitarString
    // SoundBuffer is loaded from samples
    // Sound is set to SoundBuffer
    
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                case sf::Event::TextEntered:
                    key_index = keyboard.find(event.text.unicode);
                    sound[key_index].play();
                    break;
                    
                default:
                    break;
            }
            
            window.clear();
            window.display();
        }
    }
    return 0;
}
