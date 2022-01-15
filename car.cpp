#include"car.h"
#include<vector>
using namespace std;

Car::Car(const sf::Keyboard::Key controls[4]) {
	_body = sf::RectangleShape(_size);
	_body.setPosition(750.f, 300.f); //positionnement sur la piste
	_body.setOrigin(_size * .5f);
	_velocity = 0;
        //pour avoir des controles différents en fonction de la voiture
        _ctl_forward = controls[0];
        _ctl_backward = controls[1];
        _ctl_left = controls[2];
        _ctl_right = controls[3];

        loadTexture();
}

Car::~Car() {

}


void Car::update(sf::Time elapsed) {

        // on recupere les anciennes coordonnes de la voiture
        _oldPosX = _body.getPosition().x ; _oldPosY = _body.getPosition().y ;


	//on récupère le temps qui s'est écoulé depuis la dernière update et on l'exprime en seconde
	float dt = elapsed.asSeconds();

	// on récupère l'orientation du corps
	_rotation = _body.getRotation() * (M_PI/180); //conversion en radian pour fonctionner avec sin et cos de cmath
	// direction est le vecteur normalisé qui pointe dans la direction de la voiture
	sf::Vector2f direction(cos(_rotation), sin(_rotation));

	// on calcule la position théorique des roues avant et arrière pour calculer la trajectoire
	// on n'a besoin de simuler que deux roues : une a l'avant et une a l'arriere
	sf::Vector2f frontWheel = _body.getPosition() + direction * float(_base/2);
	sf::Vector2f backWheel = _body.getPosition() - direction * float(_base/2);

	// on verifie si on avance ou recule
	//  1 si on avance
	//  0 si rien
	// -1 si on recule
	float isforward = (sf::Keyboard::isKeyPressed(_ctl_forward) - sf::Keyboard::isKeyPressed(_ctl_backward));

	// on calcule la nouvelle vitesse en fonction de la vitesse actuelle de la voiture
	// il faut distinguer les combinaisons des cas suivants : on avance ou on recule / on veut avancer ou on veut reculer
	_velocity = (_velocity + dt * _acceleration * isforward) * isforward*isforward + (1 - isforward*isforward) * ( _velocity - _acceleration * dt * ((_velocity>0)-(_velocity<0)));

	// on limite la vélocité entre les bornes [-speed, speed]
	_velocity = min(_velocity, _speed);
	_velocity = max(_velocity, -_speed);

	// on fait bouger les roues en conséquence
	backWheel += _velocity * direction;
	// on calcule de combien tourne la roue avant
	float steering = calculateSteerAngle();
	frontWheel += _velocity * sf::Vector2f(cos(_rotation+steering) , sin(_rotation+steering));

	// on calcule la nouvelle position globale du corps en fonction des deux nouvelles positions des roues avant et arrières
	sf::Vector2f newpos = (frontWheel + backWheel) / 2.f;
	_body.setPosition(newpos);
	// on calcule la nouvelle orientation globale du véhicule en l'allignant sur la position des deux roues
	float newrot = atan2( frontWheel.y - backWheel.y , frontWheel.x - backWheel.x ) * (180/M_PI);
	_body.setRotation(newrot);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) _body.setPosition(400,300);
}

//en focntion des touches gauche ou droite calcule de combien la voiture tourne
float Car::calculateSteerAngle() {
	int turn = 0;
	if (sf::Keyboard::isKeyPressed(_ctl_left)) turn -= 1;
	if (sf::Keyboard::isKeyPressed(_ctl_right)) turn += 1;
	float steerAngle = turn * _steering;
	return steerAngle;
}

//affiche la voiture
void Car::draw(sf::RenderWindow& window) const {
        window.draw(_body);
}

float lerp(float a, float b, float t) {
	return (a+t*(b-a));
}

//retourne le _body de la voiture
sf::RectangleShape Car::getBody() const {
    return _body ;
}

float Car::getRotation() const {
    return _rotation ;
}


//actualisation de la position de la voiture avant un mouvement qui entraine une collision
void Car::setPositionC() {
    _body.setPosition(_oldPosX,_oldPosY);
}

//chargement de la texture
void Car::loadTexture(){
    _carTexture.loadFromFile("pixil-frame-0.png");
    _body.setTexture(&_carTexture);
}

//positionnement de la deuxième voiture sous la première
void Car::setPositionCar2() {
    _body.setPosition(750,330);
}


