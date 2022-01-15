#include "circuit.h"

Circuit::~Circuit() {}

Circuit::Circuit() {}

void Circuit::setCircuitTexture(std::string nomFichier) {
    if (!_circuitTexture.loadFromFile(nomFichier)) {//chargement du circuit
        std::cout << "Marche pas" << std::endl;
    }
    _circuit.setTexture(_circuitTexture);
    _circuitCollision = _circuitTexture.copyToImage();
}

void Circuit::setStartLine(std::string nomFichier) {
    if (!_startLineTexture.loadFromFile(nomFichier)) {//chargement de la ligne de départ
        std::cout << "Marche pas" << std::endl;
    }
    _startline.setTexture(_startLineTexture);
    _startLineCircuit = _startLineTexture.copyToImage();
}

//retourne le circuit pour les collisions entre le circuit (la piste) et la voiture : ces collisions sont gérés dans  la classe collision
sf::Image Circuit::getCircuitCollision() const {
    return _circuitCollision;
}

//affichage du circuit avec la ligne de départ
void Circuit::drawCircuit(sf::RenderWindow& f) {
    f.draw(_startline);
}

//retourne le circuit pour les collisions entre le la ligne de départ (en blanc) et la voiture : ces collisions sont gérés dans le main par manque de temps
sf::Image Circuit::getStartlineCircuit() const {
    return _startLineCircuit;
}

