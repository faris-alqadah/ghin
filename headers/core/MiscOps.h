/**
 *
 * Misc functions needed by many applications and data mining algorithms.
 *
 * Includes:
 *   -Sorting hashmap by value 
 *
 *
 *
 *
 */


#ifndef MISCOPS_H
#define	MISCOPS_H

using namespace std;

#include<map>
#include<vector>
#include <algorithm>




/**
 * 
 * Populate a a pairs vector by ordering the <key,value> pairs of the map by value. Assumes 
 * ordering exists for value types
 * 
 * 
 * @param theMap the map to be sorted by value
 * @return pointer to populated vector
 */
vector< pair<int,double> > * Sort_Map_By_Value( map<int,double> &theMap);
#endif	/* MISCOPS_H */

