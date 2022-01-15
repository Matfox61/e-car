#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <vector>
#include "car.h"
#include "collision.h"
#include "circuit.h"
#include "sounds.h"
using namespace std;

// controles du joueur 1 a appeler dans le constructeur de voiture
const sf::Keyboard::Key ctl_J1[4] = {sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right };

// controles du joueur 2 a appeler dans le constructeur de voiture
const sf::Keyboard::Key ctl_J2[4] = {sf::Keyboard::Z, sf::Keyboard::S, sf::Keyboard::Q, sf::Keyboard::D };

int main()
{


    // création de la fen�tre
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "e-car");

	sf::Clock game_clock;
	//chargement circuit
    Circuit circ ;
    circ.setCircuitTexture("race.png");//chargement du circuit pour les collisions des voitures avec les rebords du circuit
    circ.setStartLine("raceStartline.png");//chargement du circuit pour les collisions avec la ligne de d�part : c'est ce circuit qui est visible � l'�cran


	//utilisation de la classe "car"
	Car car(ctl_J1), car2(ctl_J2);
	car2.setPositionCar2(); //on place la voiture 2 en dessous de la voiture 1

    //collision pour les voitures
    Collision collV1,collV2 ;
    collV1.setCircuit(circ);
    collV2.setCircuit(circ);

    //chargement des textures des voitures
    car.loadTexture();
    car2.loadTexture();//meme couleur pour le moment car la m�thode charge son fichier directement avant, sans attribut sf::Texture


    ///Gestion du chrono des voitures
    //Voiture 1
    sf::Font police;
    police.loadFromFile("arial_narrow_7/arial_narrow_7.ttf");

    sf::Text affichage;
    affichage.setFont(police);
    affichage.setCharacterSize(24);
    affichage.setPosition(20, 20);

    sf::Text affichInterm;
    affichInterm.setFont(police);
    affichInterm.setCharacterSize(24);
    affichInterm.setPosition(20, 70);


    //voiture 2
    sf::Text affichage2;
    affichage2.setFont(police);
    affichage2.setCharacterSize(24);
    affichage2.setPosition(1500, 20);

    sf::Text affichInterm2;
    affichInterm2.setFont(police);
    affichInterm2.setCharacterSize(24);
    affichInterm2.setPosition(1500, 70);


    sf::Clock chrono;
    chrono.restart();

    //on joue la musique de fond
    Sounds son ;
    son.playBackgroundMusic();

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;

        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed) window.close();
        }

		game_clock.restart();
		sf::Time elapsed = game_clock.getElapsedTime();


///Gestion du chrono avec la ligne de départ. N.B : Désolé pour cette partie qui n'est pas mise dans une classe
        if (collV1.collisionStartLine()){

            sf::Time interm = chrono.getElapsedTime();
            float temps1 = interm.asSeconds();
            sf::String textTemps1 = std::to_string(temps1);
            affichInterm.setString(textTemps1);

        }

        sf::Time tempsChrono = chrono.getElapsedTime();
        float timer = tempsChrono.asSeconds();
        sf::String textTimer = std::to_string(timer);
        affichage.setString(textTimer);

        if (collV2.collisionStartLine()){

            sf::Time interm2 = chrono.getElapsedTime();
            float temps2 = interm2.asSeconds();
            sf::String textTemps2 = std::to_string(temps2);
            affichInterm2.setString(textTemps2);
        }
        sf::String textTimer2 = std::to_string(timer);
        affichage2.setString(textTimer2);

///Fin gestion du chrono


        //mise à jour des coordonnées des roues de la voiture
        collV1.updateCoord(car);
        collV2.updateCoord(car2);

        //mise à jour de la couleur des pixels sous les roues des voitures
        collV1.updatePixelColor(circ);
        collV2.updatePixelColor(circ);

        //gestion des collisions pour chaque voiture
        collV1.collisionCircuit(car);
        collV2.collisionCircuit(car2);

		//utlisation de la classe car
		car.update(elapsed);
        car2.update(elapsed);

        // effacement de la fenêtre en noir
        window.clear(sf::Color::Black);

        //affichage du circuit
        circ.drawCircuit(window);

        //utilisation de la classe car
		car.draw(window);
        car2.draw(window);

        //affichage des chronos
        //voiture1
        window.draw(affichage);
        window.draw(affichInterm);
        //voiture2
        window.draw(affichage2);
        window.draw(affichInterm2);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();


    }

    return 0;
}

