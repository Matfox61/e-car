#ifndef SOUNDS_H_INCLUDED
#define SOUNDS_H_INCLUDED
#include <SFML/Audio.hpp>
#include "car.h"
#include "collision.h"
#include "circuit.h"

class Sounds {
private :
    sf::Music _bgMusic;

public :
    Sounds();
    ~Sounds();
    void playBackgroundMusic();//jouer la musique de fond
};

#endif // SOUNDS_H_INCLUDED


