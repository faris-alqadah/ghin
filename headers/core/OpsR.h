//! Author: Faris Alqadah
/*! Basic operations for RSets which are essentially real-valued vectors.
 These include some basic matrix operations and statistical ops

 \sa RSet
 */




#ifndef _OPSR_H
#define _OPSR_H


#include"NRCluster.h"
#include <algorithm>
using namespace std;

//! Assumes a is the sparse representation of a sparse matrix, and transposes it
NRCluster *TransposeSparse(NRCluster *a,int sz1, int sz2);

//! Returns a the set of idxs that are common to both a and b
IOSet *Common_Idxs(RSet *a, RSet *b);

//! Return the intersection of the indices of a and elements of IOSet b
RSet *Intersect(RSet *a, IOSet *b);

//! Union two RSets by indicies, assumes that the RSets are sorted by index
RSet *Union(RSet *a, RSet *b);

/*!
 *
 * Computes the spearman rank correlation of the two specifed RSets
 * over the specified idxs. It is assumed that the two RSets both contain
 * the specified idxs
 * 
 * @params a first RSet
 * @params b second RSet
 * @params idxs the ids of the idxs to compute the rank correlation over
 */
double Spearman_Rank_Correlation(RSet *a, RSet *b,IOSet *idxs );




#endif


