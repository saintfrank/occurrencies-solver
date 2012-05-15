/*
 * ConstantString.cpp
 *
 *  Created on: Nov 7, 2011
 *      Author: showandtell
 */

#include "ConstantString.h"

ConstantString::ConstantString( std::string & str) {

	m_constant_string = str ;
    m_vec.push_back(str);

}

std::string & ConstantString::getExtracted() {return m_constant_string;}

const std::string & ConstantString::getElement()  {return m_constant_string;}



