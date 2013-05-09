#ifndef TRANSLATION_H
#define TRANSLATION_H 

#include "Transformation.h"
#include "sgct.h"

class Translation : public Transformation{

public:
	Translation(float x, float y, float z);
	virtual ~Translation();

	void setTranslation(float x, float y, float z);


};

#endif

