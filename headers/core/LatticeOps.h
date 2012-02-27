//! Author: Faris Alqadah
//! Basic Lattice operations derived from formal concept anaylsis. These are extended  to heterogenous information networks (HINs)


#include "RelationGraph.h"





//! Returns the concept corresponds to the concept that contains all the objects from domain2, and any element in domain1 that contains all objects from doamin2 or the empty set
NCluster *GetTop(Context *c);
//! Returns  the bottom level concept from c, this concept corresponds to the concept that contains all the objects from domain1, and any element in domain2 that contains all objects from doamin1 or the empty set
NCluster *GetBottom(Context *c);
//! Computes the Prime (') (see any book on Formal Concept Anaylsis) for a given object-set
/*!
    The operation differs slighty from the strict FCA definition in that if a[s] is empty
    then the result is a NULL set. Moreover, this PrimeOperator is "min-aware" so that if at any time during the compution
     the results has cardinality <> min no more operations are perfomed and NULL is returned

    \param a the n-cluster that contains set s as a(s)
    \param g the relation graph in which (s,t) must be an edge (a context exists)
    \param s indicates the source domain id in a to serve as the input for the prime operator
    \param t indicates the target domain
    \param min indicates the minimum size the result prime should be, otherwise NULL is returned

 */
IOSet *Prime(NCluster *a, RelationGraph *g, int s, int t, int min);










