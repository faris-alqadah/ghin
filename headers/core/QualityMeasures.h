//! Author: Faris Alqadah
/*!
 Quality functions of n-clusters. All functions should have standard input signature
 so that they may be used generically with Lattice Algorithms

 \sa LatticeAlgos
 */


#include "RelationGraph.h"
#include "Ops.h"
#include <cmath>

//! Returns the area of an n-cluster, assuming it is star-shaped
/*!
 Area is compute as |a[artId]|* sum_{all other nodes i} |a[i]|
    \sa a the n-cluster to compute area for
    \sa params params[0] should contain the id of the articulation node
 */
double Area(NCluster *a, vector<double> &params);

//! Returns the beta-balanced area of an n-cluster, assuming it is star-shaped
/*!
 See "An efficient algorithm for mining 3-clusters" by Alqadah et al.
 Area is compute as |a[artId]|* (1/Beta)^sum_{all other nodes i} |a[i]| where 0 < Beta < 1
    \sa a the n-cluster to compute area for
    \sa params params[0] should contain the id of the articulation node, params[1] = beta
 */
double Beta(NCluster *a, vector<double> &params);


