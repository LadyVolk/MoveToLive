#include "Intersection.h"
#include <SFML/Graphics.hpp>

//ended up not using it
bool rectWithPoint(sf::Rect <float> rect, sf::Vector2f point) {
	if (point.x >= rect.left && point.x <= rect.left + rect.width && 
		point.y >= rect.top && point.y <= rect.top + rect.height) {
		return true;
	}
	else {
		return false;
	}
}
bool rectWithRect(sf::Rect <float> rect1, sf::Rect <float> rect2) {
	if (rect1.left + rect1.width < rect2.left ||  //rect1 is to the left of rect2
		rect2.left + rect2.width < rect1.left ||  //rect1 is to  the right of rect2
		rect1.top + rect1.height < rect2.top || //rect1 is above rect2
		rect2.top + rect2.height < rect1.top    //rect1 is below rect2
		)

	{
		return false;
	}
	else {
		return true;
	}
}