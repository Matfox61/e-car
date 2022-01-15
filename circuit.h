#ifndef CIRCUIT_H_INCLUDED
#define CIRCUIT_H_INCLUDED
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <vector>

class Circuit{

    sf::Texture _circuitTexture;
    sf::Sprite _circuit ;//pour afficher le circuit
    sf::Image _circuitCollision ;

    sf::Texture _startLineTexture;
    sf::Sprite _startline ;//pour afficher la ligne de d�part : c'est ce circuit qu'on voit sur l'�cran
    sf::Image _startLineCircuit;

  	public :
    Circuit();
    ~Circuit();

    //selectionner le circuit qu'on souhaite afficher
    void setCircuitTexture(std::string);

    //selectionner le circuit avec la ligne de depart (comme les collisions sont g�r�es uniquement avec la couleur de la piste,
    //on dissocie le circuit de la ligne de d�part pour pas avoir de soucis car cette derni�re est blanche (diff�rente de la couleur de la route donc)
    void setStartLine(std::string);

    //retourne le circuit pour les collisions entre le circuit (la piste) et la voiture : ces collisions sont g�r�s dans  la classe collision
    sf::Image getCircuitCollision() const ;

    //retourne le circuit pour les collisions entre le la ligne de d�part (en blanc) et la voiture : ces collisions sont g�r�s dans le main par manque de temps
    sf::Image getStartlineCircuit() const ;

    //affiche le circuit _startLineCircuit
    void drawCircuit(sf::RenderWindow&);
};

#endif // CIRCUIT_H_INCLUDED
