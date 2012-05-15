/*
 * Set.cpp
 *
 *  Created on: Nov 7, 2011
 *      Author: Francesco
 */

#include "Set.h"

Set::Set(std::string & name) {

	m_element = name ;
	m_extracted_index = 0;

}

Set::~Set() {}


std::string & 		Set::getExtracted()                     { return m_extracted;	}


const std::string & Set::getElement()                       { return m_element;     }

const std::string & Set::getStringAt(int index)     { return m_strings.at(index); 	}




bool Set::extractNextRR(){

	if ( (++m_extracted_index) == m_strings.size() )
	{
		// if the array is finished I reset
		m_extracted_index = 0 ;
		m_extracted = m_strings.at(0) ;

		return false;
	}
	else
	{
		// Extracting the next and updating the index (++m_extracted_index)
		m_extracted = m_strings.at(++m_extracted_index) ;

		return true;
	}

}

bool Set::extractThis(int index)
{
	// Trivial
	m_extracted_index = index % m_strings.size();
	m_extracted = m_strings.at(m_extracted_index);

	return true;
}


void Set::addString(const std::string & newString)	{ m_strings.push_back(newString); }


void Set::print() { 
    
    std::cout << m_element << " : " ; 
    
    BOOST_FOREACH(std::string t, m_strings )
    {
        std::cout << t << " ";
    }   
    
    std::cout << "\n" ;
    
}




