#ifndef NAME_H
#define NAME_H
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#define M_PI 3.14159265358979323846 ///j'avais des problèmes avec les constantes de cmath
#include <vector>
using namespace std;

class Car {

    sf::Keyboard::Key _ctl_forward;
    sf::Keyboard::Key _ctl_backward;
    sf::Keyboard::Key _ctl_left;
    sf::Keyboard::Key _ctl_right;

	sf::RectangleShape _body; //le corps de la voiture

	//variables aidant aux calculs de physique
	float _rotation;
	float _velocity;

	//carcteritiques de la voiture à modifier dans ce fichier
	const float _steering = 30 * (M_PI/180); // on prend en compte la transformation en radians
	const float _speed = 0.1;
	const float _acceleration = 200;
	const float _base = 60; // longueur : distance entre les roues permettant de calculer les virages
	const float _larg = 25; // largeur
	const sf::Vector2f _size = sf::Vector2f(_base, _larg);



	//Collision pour le moment mais à revoir
	float _oldPosX; //position x avant mouvement
	float _oldPosY; //position y avant mouvement
	sf::Vector2f _position = sf::Vector2f(_oldPosX,_oldPosY);

    //chargement de la texture d'une voiture
	sf::Texture _carTexture ;


	public :
		Car(const sf::Keyboard::Key controls[4]);
		~Car();
		void update(sf::Time);
		void draw(sf::RenderWindow&) const;
		float calculateSteerAngle();
		float getRotation() const;
		sf::RectangleShape getBody() const;
        ///voir comment gérer une deuxième couleur de texture
        void loadTexture();//charger la texture de la voiture

        void setPositionC()  ;//mettre à jour la position de la voiture
        void setPositionCar2();
};

float lerp(float a, float b, float t);


#endif
