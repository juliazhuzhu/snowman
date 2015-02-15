#include "Star.h"

Star* Star::create(int color){
	Star* ret = new Star();
	if(ret && ret->initWithFile(ret->getImage(color))){
		ret->color = color;
		ret->selected = false;
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}


char* Star::getImage(int color){
	switch(color){
	case color::BLUE:
		return "leek.png";
	case color::GREEN:
		return "artichoke.png";
	case color::YELLOW:
		return "chilli.png";
	case color::RED:
		return "carrot.png";
	case color::PURPLE:
		return "tomato.png";
	}
}

bool Star::isSelected(){
	return selected;
}

int Star::getColor(){
	return color;
}

void Star::setColor(int _color){
    color = _color;
}

void Star::setDesPosition(const Point& p){
	desPosition = p;
}

void Star::updatePosition(){
	if(desPosition.y != getPositionY()){
		setPositionY(getPositionY() - MOVE_SPEED);
		if(getPositionY() < desPosition.y){
			setPositionY(desPosition.y);
		}
	}
	if(desPosition.x != getPositionX()){
		setPositionX(getPositionX() - MOVE_SPEED);
		if(getPositionX() < desPosition.x){
			setPositionX(desPosition.x);
		}
	}
}