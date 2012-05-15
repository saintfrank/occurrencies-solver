/*
 * IFileLoader.h
 *
 *  Created on: Nov 6, 2011
 *      Author: Francesco Cervigni
 */

#ifndef IFILELOADER_H_
#define IFILELOADER_H_

// System Library Includes
#include <iostream>

// Project Includes
#include <Problem.h>

class IFileLoader {

	public :

	/** This is the main interface for the loaders, opening a file and filling a Problem instance
	 *
	 */
	virtual bool loadFile( std::string & fileName, Problem & problemInstance ) = 0;


};


#endif /* IFILELOADER_H_ */
