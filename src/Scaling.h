#include "Transformation.h"

class Scaling : public Transformation {
public:
	Scaling(float sx, float sy, float sz);
	virtual ~Scaling();

	void setScaling(float sx, float sy, float sz);
};