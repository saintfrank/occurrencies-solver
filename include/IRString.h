/*
 * IRString.h
 *
 *  Created on: Nov 7, 2011
 *      Author: showandtell
 */

#ifndef IRSTRING_H_
#define IRSTRING_H_

#include <iostream>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class IRString{

	public :
    
		/** Retrieves the extracted string
		  * @return The extracted string
		  */
		virtual	std::string & getExtracted() = 0 ;

		/** Request of string extraction, RoundRobin politic
		 *
		 * @return true in case of success, false a the end of array
		 */
		virtual bool extractNextRR() = 0;
    
        /** Forces the next extracted to the index index
         * @param index Index of strign to exteract
         * @return true in case of success, false otherwise
         */
        virtual bool extractThis(int index) = 0;

    
        /** Retrieves the extracted string
         * @return The extracted string
         */
        virtual	const std::string & getElement() = 0;
    

        /** Retrieves the extracted string
         * @return The extracted string
         */
        virtual	std::vector<std::string> & getElements() = 0;
    

		/** Adds a string to the lost vector
		 * @param newString The string to add
		 */
		virtual void addString(const std::string & newString) = 0;

    
        /** Trivial
         *
         */
        virtual bool isConstant() = 0;
    
        /** Trivial
         *
         */
        virtual int getSize() = 0;
    
      
        /** Trivial
        */
        virtual void print() = 0;
    

		typedef boost::shared_ptr<IRString> Ptr;				/** A typedef for a smart pointer to this object (will be automatically destroyed when ownership block will end)*/


};


#endif /* IRSTRING_H_ */
