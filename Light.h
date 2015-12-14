/* 
 * File:   Light.h
 * Author: kurtbradd
 *
 */

#ifndef LIGHT_D
#define LIGHT_D
#include "structs.h"
class Light {
	public:

		// Constructor
		Light(int glLight, Param pos, Param diff , Param spec, Param amb);
		
		// Operators
		void enable();
		void redrawLight();
		void increaseX(int val);
		void decreaseX(int val);
		void increaseY(int val);
		void decreaseY(int val);
		void increaseZ(int val);
		void decreaseZ(int val);

		// Members
		Param pos,amb,dif,spec;
		// float 
		int lightNum;
};

#endif /* CAMERA_H */
