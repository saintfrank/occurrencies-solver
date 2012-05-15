/*
 * Engine.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: Francesco
 */

#include "Engine.h"
#include "Problem.h"
#include "StlFileLoader.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <cstdlib> 
#include <set>
#include <sstream>
#include <iostream>
#include <ostream>
#include <fstream>

#include <vector>

using namespace boost::filesystem;
using namespace std;


bool Engine::start(){

    // Initialization
    std::vector< std::vector<IRString::Ptr> > allTs = m_problem.m_t_strings;
    
    ///////////////////////// Filtering step
    /////////////////////////
    #ifdef DEBUG_ALGO
    std::cout << "Prima" << std::endl;
    m_problem.printStatus();
    #endif
    
    BOOST_FOREACH( std::vector<IRString::Ptr> tTemp, allTs )
   	{
        filter( tTemp, m_problem.m_target );
    }

    #ifdef DEBUG_ALGO
    std::cout << "Dopo" << std::endl;
    m_problem.printStatus();
    #endif
    //////////////////////////
    
    std::set<IRString::Ptr> Ts;
    
    BOOST_FOREACH( std::vector<IRString::Ptr> tTemp, m_problem.m_t_strings )
   	{
        BOOST_FOREACH( IRString::Ptr t, tTemp )
        {
            Ts.insert(t);
        }
    }
    
    bool result = false;
    
    
    for (int i = 0 ; i < (m_problem.m_longest_set*m_problem.m_longest_set*m_problem.m_longest_set*m_problem.m_longest_set*m_problem.m_longest_set); i++)
    {
        BOOST_FOREACH( IRString::Ptr s, Ts )
        {
            int random_integer = rand(); 
            s->extractThis(random_integer);
        }
        
        if( Check() == true )
        {
            result = true;
            break;
        }    
        
    }
    
        
    printResult(result);

    return true ;

}
    
bool Engine::Check(){
    
    
    BOOST_FOREACH( std::vector<IRString::Ptr> tTemp, m_problem.m_t_strings )
   	{
        std::stringstream ss;
        
        BOOST_FOREACH( IRString::Ptr t_s, tTemp )
        {
            ss << t_s->getExtracted() ; 
        }
        
        std::string guess = ss.str();
        
        #ifdef DEBUG_ALGO
        std::cout << "The guess  " << guess  << std::endl;
        #endif
        
        if( m_problem.m_target.find(guess,0) == std::string::npos )
            return false;
        
    }
    
    return true;


}

bool Engine::printResult(bool result){

    m_path.replace(m_path.size()-4,4,".SOL");
        
    ofstream myfile;
    myfile.open(m_path.c_str());
        
    if(result)
    {   
        std::vector< std::vector<IRString::Ptr> > allTs = m_problem.m_t_strings;
            
        std::set<IRString::Ptr> Ts;
    
        BOOST_FOREACH( std::vector<IRString::Ptr> tTemp, m_problem.m_t_strings )
        {
            BOOST_FOREACH( IRString::Ptr t, tTemp )
            {
                Ts.insert(t);
            }
        }
        
        
        BOOST_FOREACH( IRString::Ptr t, Ts )
        {
            myfile << t->getElement() << ":" << t->getExtracted();
        }
        
    }
    else
    {
        myfile << "NO SOLUTION FOUND.";
    }
    
    myfile.close();
    
    
    return true;
}

bool Engine::hasOne(IRString::Ptr & t, std::string remaining){
 
    bool result = false;
    
    if(t->isConstant())
    {
        int off = remaining.find(t->getExtracted());
        
        if (off == 0)
        {
            #ifdef DEBUG_ALGO
            std::cout << t->getElement()  << " HasOne : found constant ! " << std::endl;
            #endif
            return true; // if is prefix
        }    
    }
    else
    {
        // if is a set
        BOOST_FOREACH( std::string s, t->getElements() )
        {
            if ( remaining.find( s ) == 0 )
            {    
                result = true ; // if has found a possible one            
                #ifdef DEBUG_ALGO
                std::cout << t->getElement()  << " HasOne : found string ! " << s << std::endl;
                #endif
            }    
        }
        
    }
    
    return result;

}
    
    
bool Engine::filter(std::vector<IRString::Ptr> vect, std::string s_initial){
    
    unsigned int i = 0;
    
    #ifdef DEBUG_ALGO
    std::cout << "Filter 0" << std::endl;
    #endif
    
    
    BOOST_FOREACH(IRString::Ptr t, vect )
   	{
        // for every letter
        if( ! t->isConstant() )
        {
            #ifdef DEBUG_ALGO
            std::cout << "Filter 1" << std::endl;
            #endif
         
            if(i >= vect.size()-1) // if is the las t, then returns
            {
                return true;
            } 
            
            unsigned int j = 0;
            std::vector<int> toRemove;
            
            BOOST_FOREACH(std::string s, t->getElements() )
            {
                

                #ifdef DEBUG_ALGO
                std::cout << "Filter 2" << std::endl;
                #endif
                
                
                bool found = false;
                
                // for every string in the set
            
                // get the possible positions ///////
                vector<size_t> positions;
                size_t pos = s_initial.find(s, 0);
                
                while(pos != string::npos)
                {
                    positions.push_back(pos);
                    pos = s_initial.find(s,pos+1);
                }
                ///////////////////////////////////
                
                BOOST_FOREACH( int off, positions )
                {
                    std::cout << "Off: " << off;
                }
                std::cout << std::endl;
                
                // With this loop I guarantee that for every possible occurence of this string is checked whether it valuable
                
                BOOST_FOREACH( unsigned int off, positions )
                {
                    #ifdef DEBUG_ALGO 
                    std::cout << "Filter 3 : "<< t->getElement() << ":" << s << " searching if possible this next " << vect.at(i+1)->getElement() << " at " << off << s_initial.substr(off) << std::endl;
                    #endif
                    
                    if(off != s_initial.size()-1)
                      if( hasOne( vect.at(i+1), s_initial.substr(off+1) ) )
                    {
                        #ifdef DEBUG_ALGO
                        std::cout << "Filter 4 : found " << s << std::endl;
                        #endif
                        
                        found = true;
                        
                    }
                    else
                    {
                        #ifdef DEBUG_ALGO
                        std::cout << "Filter 4 : not found " << s << std::endl;
                        #endif
                    }
                }
            
                if( ! found )
                {
                    #ifdef DEBUG_ALGO
                    std::cout << "Filter 7 : removing "<< s << std::endl;
                    #endif
                    toRemove.push_back(j);
                }    
                j++;
                       
            }
            
            // removing the impossible strings
            BOOST_FOREACH(int rem, toRemove  )
            {
                #ifdef DEBUG_REM
                std::cout << "Filter 8" << std::endl;
                #endif
                t->getElements().erase(t->getElements().begin()+rem);
                
                #ifdef DEBUG_ALGO
                std::cout << "Filter 9" << std::endl;
                #endif
            }
            
        }
            
        i++;
    
    }
    
    #ifdef DEBUG_ALGO
    std::cout << "Filter 10" << std::endl;
    #endif
    
                       
    return true;
    
        
}

/** @warning not returning null
 */
std::vector<IRString::Ptr>  Engine::getBigger( std::vector< std::vector<IRString::Ptr> > & t_strings ){

    if(t_strings.empty())
        throw("Trying to get bigger from an empty vector !");
    
    std::vector<IRString::Ptr> bigger = t_strings.at(0);
    
    BOOST_FOREACH(std::vector<IRString::Ptr> t, t_strings )
   	{
        if(t.size() >  bigger.size())
            bigger = t ;        
    }
    
    return bigger;
    
}


/** The main functionalities, getting the folder name as mandatory parameter and a file name as Optional Parameter
 *
 */

bool loadParameters(int argc, char ** argv, std::string & path){

	switch (argc)
	{
	  case 2:
	     path = argv[1];
	     break;

	  default:
		 std::cerr << argc << "Usage: chp [folder_path] [file_path] " << std::endl;
		 return false;
	}

	return true;

}

int main(int argc, char *argv[]){


	try
	{

		std::string pathName 	= "";
		std::string path 		= "data/";

		if ( ! loadParameters(argc, argv, pathName) )
			return 1 ;

		IFileLoader * fileLoader = new StlFileLoader();
        
        if ( ! exists(pathName) )
        {
            std::cerr << "Error : File or Directory does not exist ! " << std::cerr ;
        }    
        
        
		if ( ! is_directory(pathName) )
		{
			// If there is just one Problem to solve
			Problem myProblem;

			if ( ! fileLoader->loadFile( pathName , myProblem ) )
			{
				std::cerr << "Error : Impossible to load file " << pathName << " " << "FileName" << std::endl;
			}

			Engine myEngine(myProblem);
            myEngine.m_path = pathName ;
            myEngine.start();

		}
		else
		{
			std::cout << pathName << " is a directory containing:\n";
			copy(directory_iterator(pathName), directory_iterator(), std::ostream_iterator<directory_entry>(std::cout, "\n"));			
		}
	}
    catch( std::string str )
	{
        cout << "Error : " << str << '\n';
    }    
	catch( char * str )
	{
	      cout << "Error : " << str << '\n';
	}
	catch (const filesystem_error& ex)
	{
		std::cout << ex.what() << std::endl;
	}
    catch (const std::exception & ex)
	{
		std::cout << ex.what() << std::endl;
	}


}
