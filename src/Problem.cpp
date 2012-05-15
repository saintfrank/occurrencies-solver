//
//  Problem.cpp
//  
//
//  Created by Francesco Cervigni on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Problem.h"
#include <iostream>

#include <boost/foreach.hpp>

using namespace boost;


/** A representation print. Mostly for debugging.
 *
 */
void Problem::printStatus(){

    std::cout << "\nProblem Representation\n\nTarget : " << m_target << "\n" << std::endl;
    
    std::cout << "Number of t strings: " << m_t_size << std::endl;
    std::cout << "Longest set: " << m_longest_set << std::endl;
    
    
    std::cout << "T strings: "<< std::endl;
    
    BOOST_FOREACH(std::vector<IRString::Ptr> t_str, m_t_strings )
   	{
        
        BOOST_FOREACH(IRString::Ptr t_str_letter, t_str )
        {
        
        std::cout << t_str_letter->getElement();
        
        }
        
        std::cout << std::endl;
    
    }
    
    BOOST_FOREACH(std::vector<IRString::Ptr> t_str, m_t_strings )
   	{
        
        BOOST_FOREACH(IRString::Ptr t_str_letter, t_str )
        {
            
            t_str_letter->print();
            
        }
        
        std::cout << std::endl;
        
    }
    
    

}

