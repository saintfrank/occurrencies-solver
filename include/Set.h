/*
 * Set.h
 *
 *  Created on: Nov 7, 2011
 *      Author: showandtell
 */

#ifndef SET_H_
#define SET_H_

#include "IRString.h"

#include <iostream>
#include <vector>
#include <sstream>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

/**
 * @class This class represent the sets, the letter correspondent to the set is just here, so it will be encapsulated
 */
class Set : public IRString{

	public :

	Set ( std::string & name );
	virtual ~Set();							/** Empty, no pointer held by this class.*/

	/** Retrieves the extracted string
	 * @return The extracted string
	 */
	virtual std::string & getExtracted();

	/** Request of string extraction, RoundRobin politic
	 *
	 * @return true in case of success, false a the end of array
	 */
	virtual bool extractNextRR();

	/** Forces the next extracted to the index index
	 * @param index Index of strign to exteract
	 * @return true in case of success, false otherwise
	 */
	virtual bool extractThis(int index);

	/** Adds a string to the lost vector
	 * @param newString The string to add
	 */
	virtual void addString(const std::string & newString);

	/** Utility getter
	 * @param index The index
	 * @return the element at index index
	 */
	virtual const std::string & getElement();
    
    /** Trivial
     *
     */
    virtual int getSize() {return m_strings.size();}
    
    /** Retrieves the extracted string
     * @return The extracted string
     */
    virtual	std::vector<std::string> & getElements() {    return m_strings;   }
    

    
    /** Trivial
     *
     */
    virtual bool isConstant(){ return false;}
    
    
    /** Utility getter
	 * @param index The index
	 * @return the element at index index
	 */
	virtual const std::string & getStringAt(int index);
    
    /** Trivial
     */
    virtual void print(); 
    


	std::string m_element;					/**< The correspondent element of the Alphabet*/

	unsigned int m_extracted_index;					/**< The pointer to the next extracted element */

	std::string m_extracted;				/**< The extracted element */

	std::vector<std::string> m_strings ; 	/**< The correspondent set of strings*/

};



#endif /* SET_H_ */
