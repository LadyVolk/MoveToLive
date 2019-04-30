#include <SFML/System/Vector2.hpp>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

float Length(sf::Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f Normalize(sf::Vector2f v) {
	if (Length(v) == 0) {
		return v;
	}
	return sf::Vector2f(v.x / Length(v), v.y / Length(v));
}

sf::Vector2f RandomVectorN() {
	sf::Vector2f vector;
	vector.x = -1 + 2*(float)(rand()) / ((float)(RAND_MAX));
	vector.y = -1 + 2*(float)(rand()) / ((float)(RAND_MAX));
	return Normalize(vector);
}