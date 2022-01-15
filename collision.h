#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
#include "car.h"
#include "circuit.h"
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <vector>

const int WIDTH = 1650, HEIGHT = 1050 ;
const sf::Color roadColor = sf::Color(255,217,36);//Si pas cette couleur en dessous de la voiture : collision ==> c'est la couleur de la route pour l'instant
const sf::Color start = sf::Color(255,255,255);
using namespace std ;


class Collision{ ///j'ai pas encore créé de fichiers pour les collisions
    //les quatres roues de la voiture
    sf::Vector2f _topleft ;
    sf::Vector2f _topright ;
    sf::Vector2f _botleft;
  	sf::Vector2f _botright ;

  	//On récupère dans ces variables les couleurs des pixels situés sous les roues/coins de la voiture en fonction du circuit sans la ligne de départ
  	sf::Color _colorUnderTopLeftWheel;
  	sf::Color _colorUnderTopRightWheel;
  	sf::Color _colorUnderBotLeftWheel ;
  	sf::Color _colorUnderBotRightWheel;

  	sf::Color _colorTLWheelStartLine;

  	Circuit _circuit ;
    sf::Image _circuitCollision;//on gère les collisions avec ce circuit
    sf::Image _startlineCircuit;//On gère le timer avec ce circuit

  	public :
        Collision();
        ~Collision();
        void updateCoord (const Car&)  ; //pour mettre à jour les coord des sommets
        sf::Vector2f getTopleft () const ; //roue avant gauche
        sf::Vector2f getTopright () const ;//roue avant droite
        sf::Vector2f getBotleft() const ;//roue arrière gauche
        sf::Vector2f getBotright () const ;//roue arrière droite

        //on met à jour en temps réel la couleur du pixel sous les roues de la voiture afin de pouvoir detecter les collisions après
        void updatePixelColor(const Circuit&) ;

        //on récupère le circuit pour faire les collisions
        void setCircuit (const Circuit& circuit);

        //on gère les collisions : si la couleur du pixel sous une des roues de la voiture est différente de celle de la piste = collision
        void collisionCircuit(Car& c);

        //retourne vrai si on rentre en collision avec la ligne de départ
        bool collisionStartLine();


};

#endif // COLLISION_H_INCLUDED
