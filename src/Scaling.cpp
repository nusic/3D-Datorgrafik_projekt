#include "Scaling.h"

Scaling::Scaling(float sx, float sy, float sz){
	setScaling(sx,sy,sz);
}

Scaling::~Scaling(){

}

void Scaling::setScaling(float sx, float sy, float sz){
	matrix[0][0] = sx;
	matrix[1][1] = sy;
	matrix[2][2] = sz;
}