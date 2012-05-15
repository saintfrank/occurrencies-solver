/*
 * StlFileLoader.h
 *
 *  Created on: Nov 6, 2011
 *      Author: showandtell
 */

#ifndef STLFILELOADER_H_
#define STLFILELOADER_H_

#include "IFileLoader.h"
#include "Problem.h"

#include <iostream>
#include <string>

class StlFileLoader : public IFileLoader {

	public:

		StlFileLoader();
		virtual ~StlFileLoader();


		/** This is the main interface for the loaders, opening a file and filling a Problem instance
		 *
		 * @param fileName The file name
		 * @param problemInstance A reference to an Problem instance owned by the main Logic
		 */
		virtual bool loadFile( std::string & fileName, Problem & problemInstance );


};

#endif /* STLFILELOADER_H_ */
