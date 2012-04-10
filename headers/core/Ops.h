//! Author: Faris Alqadah
/*! Basic operations for sets. Also included are some set similarity measures
 such as jaccard and Sorensen coefficent. Almost all operations defined here assume
 that the IOSets are sorted in order to achieve O(n) running time for common set ops.
 Please keep this in mind!

 External variables included to keep track of the number of times these
  basic operations are invoked

  Any template functions for set / vector operations should also be placed here
 \sa IOset
 */


 

#ifndef _OPS_H
#define _OPS_H


#include"NCluster.h"
#include <algorithm>
#include<list>


using namespace std;








template <class t>
//! Destroy a pointer to a vector with elements of class t
void DstryVector( vector<t*> *v){
    for(int i=0; i < v->size(); i++){
        if (v->at(i) != NULL){
            delete v->at(i);
            v->at(i) = NULL;
        }
    }
    delete v;
}
template <class t>
//! Destroy  a vector with elements of class t
void DstryVector( vector<t*> &v){
    for(int i=0; i < v.size(); i++){
        if (v.at(i) != NULL){
            delete v.at(i);
            v.at(i) = NULL;
        }
    }
}
template <class t>
//! Destroy  a list with pointer elements of class t
void DstryList( list<t*> &v){
    typename list<t*>::iterator it;
    it= v.begin();
    while(it != v.end()){
        if ( (*it) != NULL){
            delete (*it);
            (*it) = NULL;
        }
        it++;
    }
}
template <class t>
//! Remove element at the iterator position from list and re-allocate the memory, then returns iterator to next element in the list
typename list<t*>::iterator RemoveFromList( list<t*> &v, typename list<t*>::iterator it){
    return v.erase(it);
}



//! Set intersection
IOSet * Intersect( IOSet*, IOSet*);

//! Set difference a-b
IOSet * Difference( IOSet *a,  IOSet *b);

//! Symmetric set difference
IOSet *SymmDifference( IOSet*, IOSet*);

//! Set union
IOSet* Union( IOSet*,  IOSet*);



//! Returns true if b is a subet of a and false otherwise
bool Contains( IOSet *a,  IOSet *b );



//! Returns true if b is a proper subet of a and false otherwise
bool ProperSubSet(IOSet *a, IOSet*b);

//! Returns Jaccard Coefficient |a intersect b| / |  a union b|
double PercentOverlap( IOSet *a, IOSet *b );


//! Returns Sorensen Index or Dice coefficient 2*| a intersect b| / |a| + |b|
double PercentOverlap_Sorensen( IOSet *a, IOSet *b );


//! Assumes a.GetN == b.GetN, and returns(SUM_{i=0...GetN()-1} PercentOverlap(a[i],b[i]))/ GetN()
double AverageOverlap(NCluster *a, NCluster *b);

//! Returns 1 if the b[0] is of greater equal size 0 otherwise, this is used as an "overlap" function for query-based bi-clustering
double GreaterEqualSize(NCluster *a, NCluster *b);

//! Assumes a is the FIMI representation of a sparse matrix, and transposes it
NCluster *TransposeFimi(NCluster *a);

//! Assumes a is the FIMI representation of a sparse matrix, and transposes it
NCluster *TransposeFimi(NCluster *a,int sz1,int sz2);

//! Randomly select an element from a set given weights associated with each element in the set
int WeightedUniformDraw(vector<long double> &weights);

//! Randomly select an element from a set given weights associated with each element in the set
int WeightedUniformDraw(vector<double> &weights);

//! Randomly (uniformly) select a subset from IOSet
IOSet * UniformSubsetDraw(IOSet *t);

//! Select a subset from t, with probablity proportional to its size
IOSet * BinomialSubsetDraw(IOSet *t);


unsigned int NChooseK(unsigned int n, unsigned int k);

long double NChooseK(long double n, long double k);

/*!
 * Pairing function is a process to uniquely encode two natural numbers into a single natural number
 *
 *
 */
int CantorPairing(const unsigned int k1, const unsigned int k2);

/*!
 * Invert the cantor pairing function to recover the two integers that
 * were mapped to a pair
 *
 */
pair<int,int> InverseCantor(int cantor);


/*!
     EXTERNALS
Use these to keep count of the number of basic set operations used
within a particular algorithm
*/
//!number of intersections performed
extern int numIntersection;
//!number of subset checks performed
extern int numSubset;
//!number of set unions performed
extern int numUnion;
//!number of set differences performed
extern int numDifference;



#endif	/* _OPS_H */


