#include <SFML/Audio.hpp>
#include "sounds.h"
#include "car.h"

Sounds::Sounds(){}
Sounds::~Sounds(){}

void Sounds::playBackgroundMusic() {
    if (!_bgMusic.openFromFile("bgmusic.wav")) {
        cout <<"Erreur chargement fichier bgmusic.ogg" << endl ;
    }
    _bgMusic.setVolume(5.f);
    _bgMusic.play();
    _bgMusic.setLoop(true);

}

