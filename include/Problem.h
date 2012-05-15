/*
 * Problem.h
 *
 *  Created on: Nov 6, 2011
 *      Author: Francesco Cervigni
 */

#ifndef PROBLEM_H_
#define PROBLEM_H_

#include <IRString.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>


/** This class is a representation of the problem. It contains all the input values.
 *
 */
class Problem{

	public :
    
        Problem():m_t_size(0),m_longest_set(0){}

		/** A representation print. Mostly for debugging.
		 *
		 */
		void printStatus();
    
		// Data Members

		std::string m_target; 						/**< The target string	*/

		std::vector< std::vector<IRString::Ptr> > m_t_strings;		/**< The t strings		*/
    
        int m_t_size; /**< The number of t, to don't call size every time 		*/

        int m_longest_set; /**< Size of the longest set, to generate random numbers	*/

};


#endif /* PROBLEM_H_ */
