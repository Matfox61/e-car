#include "collision.h"


///Collision1
Collision::Collision() {}
Collision::~Collision() {}

void Collision::updateCoord (const Car& c)  {

        //On met à jour les coordonnées en dessous de chaque roue de la voiture
        _topleft.x = c.getBody().getTransform().transformPoint(c.getBody().getPoint(1)).x; //Avant gauche
        _topleft.y = c.getBody().getTransform().transformPoint(c.getBody().getPoint(1)).y;

        _topright.x = c.getBody().getTransform().transformPoint(c.getBody().getPoint(2)).x; //Avant droite
        _topright.y = c.getBody().getTransform().transformPoint(c.getBody().getPoint(2)).y;

        _botleft.x = c.getBody().getTransform().transformPoint(c.getBody().getPoint(0)).x;//Arrière gauche
        _botleft.y = c.getBody().getTransform().transformPoint(c.getBody().getPoint(0)).y;

        _botright.x = c.getBody().getTransform().transformPoint(c.getBody().getPoint(3)).x;//Arrière droite
        _botright.y = c.getBody().getTransform().transformPoint(c.getBody().getPoint(3)).y;

}

sf::Vector2f Collision::getTopleft () const {
    return _topleft ;
}
sf::Vector2f Collision::getTopright () const {
    return _topright;
}
sf::Vector2f Collision::getBotleft() const {
    return _botleft;
}
sf::Vector2f Collision::getBotright () const {
    return _botright ;
}

void Collision::setCircuit ( const Circuit& circuit) {
    _circuit = circuit;
    _circuitCollision = circuit.getCircuitCollision();
    _startlineCircuit = circuit.getStartlineCircuit();
}

//on met à jour en temps réel la couleur du pixel sous les roues de la voiture afin de pouvoir detecter les collisions après
void Collision::updatePixelColor(const Circuit&) {
    _colorUnderTopLeftWheel = _circuitCollision.getPixel(_topleft.x, _topleft.y);
    _colorUnderTopRightWheel = _circuitCollision.getPixel(_topright.x, _topright.y);
  	_colorUnderBotLeftWheel = _circuitCollision.getPixel(_botleft.x, _botleft.y);
  	_colorUnderBotRightWheel = _circuitCollision.getPixel(_botright.x, _botright.y);
  	//gérer la collision avec la ligne de départ avec le coin gauche
  	_colorTLWheelStartLine = _startlineCircuit.getPixel(_topleft.x, _topleft.y);
}

//on vérifie si la couleur du pixel est différente de la couleur de la piste, si c'est le cas, il y a collision
void Collision::collisionCircuit(Car& c) {

    if ((_colorUnderTopLeftWheel != roadColor && _colorUnderTopLeftWheel != start)
        ||(_colorUnderTopRightWheel != roadColor &&_colorUnderTopRightWheel != roadColor)
        ||(_colorUnderBotLeftWheel != roadColor && _colorUnderBotLeftWheel != roadColor)
        ||(_colorUnderBotRightWheel != roadColor && _colorUnderBotRightWheel != roadColor) ) {

             c.setPositionC();
        }



}

bool Collision::collisionStartLine() {
    return (_colorTLWheelStartLine== start) ;

}





