/*
 * Engine.h
 *
 *  Created on: Nov 6, 2011
 *      Author: showandtell
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "Problem.h"



class Engine {

	public :

	Engine(Problem & p):m_problem(p){}
	virtual ~Engine(){}
        
    bool printResult(bool);
    
    bool hasOne(IRString::Ptr & t, std::string remaining);
    
    
    bool filter(std::vector<IRString::Ptr> vect, std::string s_initial);
                           

    std::vector<IRString::Ptr>  getBigger( std::vector< std::vector<IRString::Ptr> > & t_strings );
    
    bool Check();
    

	void loadProblem( Problem & p ){ m_problem = p; }

    bool start();

    std::string m_path;   
    
	Problem & m_problem;

};



#endif /* ENGINE_H_ */
