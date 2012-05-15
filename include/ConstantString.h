/*
 * ConstantString.h
 *
 *  Created on: Nov 7, 2011
 *      Author: showandtell
 */

#ifndef CONSTANTSTRING_H_
#define CONSTANTSTRING_H_


#include "IRString.h"

#include <iostream>
#include <string>

class ConstantString : public IRString {

    public:
		ConstantString(std::string & strParam );

        virtual ~ConstantString( ){}

		/** Retrieves the extracted string
		  * @return The extracted string
	      */
        virtual	std::string & getExtracted();
    
    
        /** Retrieves the extracted string
         * @return The extracted string
         */
        virtual	const std::string & getElement();
    
    
        /** Adds a string to the lost vector
         * @param newString The string to add
         */
        virtual void addString(const std::string & newString){}

        /** Forces the next extracted to the index index
         * @param index Index of strign to exteract
         * @return true in case of success, false otherwise
         */
        virtual bool extractThis(int index){ return true; }
    
        /** Trivial
         *
         */
    virtual bool isConstant() {return true;}
    
    /** Retrieves the extracted string
     * @return The extracted string
     */
    virtual std::vector<std::string> & getElements() { return m_vec;   }
    
    
        /** Trivial
         *
         */
    virtual int getSize() {return 1;}
    
    
		/** Request of string extraction, RoundRobin politic
		 *
		 * @return true in case of success, false a the end of array
		 */
        virtual bool extractNextRR() { return true;}   /** <----  I know, I am a Bad Person... */

    /** Trivial
     */
    virtual void print() { std::cout << m_constant_string << std::endl; }
    

	private :

		std::string m_constant_string;
        std::vector<std::string> m_vec;



};

#endif /* CONSTANTSTRING_H_ */
