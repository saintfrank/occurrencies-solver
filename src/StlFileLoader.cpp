/*
 * StlFileLoader.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: Francesco
 */

#include "StlFileLoader.h"
#include "ConstantString.h"

#include "Set.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

using namespace boost;

StlFileLoader::StlFileLoader() {


}

StlFileLoader::~StlFileLoader() {

}

bool StlFileLoader::loadFile( std::string & fileName, Problem & problemInstance ){

	std::cout << "Parsing the file " << fileName << std::endl;

	std::ifstream    data(fileName.c_str());
	std::string      line;

	int t_num = 0 ;
    
	data >> t_num;
    
    #ifdef DEBUG_INPUT   
    std::cout << t_num << std::endl;
    #endif
	// Skipping to the end of the line
	data.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Retrieving the target
	std::string target;
	std::getline(data,target);
    #ifdef DEBUG_INPUT   
    std::cout << target << std::endl;
    #endif   
    
	problemInstance.m_target = target;

	std::vector<std::string> read_t_strings;

	// retireving the k_strings

	while(t_num-- > 0)
       if(std::getline(data,line))
       {
           read_t_strings.push_back(line);
           #ifdef DEBUG_INPUT   
           std::cout << line  << std::endl;
           #endif
       }
       else
       {
           throw "Not enough t strings !!!";
       }

	std::map<std::string, IRString::Ptr> sets_read;

	std::string tTemp;
	std::string set;
    
    int i = 0;
    int longest_set = 0;
    
	while ( (std::getline(data,tTemp,':') ) &&  (data >> set) )
	{
		
		Set::Ptr newSet( new Set(tTemp) ) ; 
		
		std::list<std::string> tokenList;
		split(tokenList, set, is_any_of(","));

        
		BOOST_FOREACH(std::string t, tokenList)
   		{
            // filtering the input or just the strings which are already substring
            if( target.find(t) != std::string::npos)
      			newSet->addString(t);
            else
                i++;
   		}
        
        sets_read.insert(std::pair<std::string, IRString::Ptr>(tTemp, newSet));
        data.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        #ifdef DEBUG_INPUT   
        std::cout << "Adding string" << tTemp << std::endl;
		std::cout << tTemp << " : " << set <<  std::endl;
        #endif
        
        if ( newSet->getSize() > longest_set) 
            longest_set = newSet->getSize();
        
	}
    
    /////////////////////// Provide the problem with the longest set size 
    ///////////////////////
    problemInstance.m_longest_set = longest_set;
    
    
    std::cout << "Filtered " << i << " Impossible inputs" << std::endl;
    

	// Now creating the problem instance depending on the capilat letter



	BOOST_FOREACH(std::string t, read_t_strings )
   	{

            std::vector<IRString::Ptr> my_t_string;

      		std::string::iterator it = t.begin();

	    	while ( it != t.end()  )
    		{

    			if( islower( *it ) )
    			{
    				// Adding the new Constant
    				std::string s ;
    				s.append(1,*it);

                    IRString::Ptr ptr(new ConstantString(s));
    				my_t_string.push_back( ptr );
    			}
    			else
    			{
    				std::string s ;
    				s.append(1,*it);

                    std::map<std::string, IRString::Ptr>::iterator retrieve_from_previous = sets_read.find(s);
    				
                    if( retrieve_from_previous == sets_read.end() )
                    {
                        std::stringstream ss ; ss << "The string " << t << " has a letter that has no set :" << s ; 
                        throw ss.str();
                    }
                    else
                    {
                        #ifdef DEBUG_INPUT   
                        std::cout << "Adding a Letter to t_string " << s << std::endl;
                        #endif
                        my_t_string.push_back(retrieve_from_previous->second);
                    }
    				
    			}

                
                it++;
			
            }
        
        problemInstance.m_t_strings.push_back( my_t_string );
        
	}
    
    //problemInstance.printStatus();
    


    return true;
}
