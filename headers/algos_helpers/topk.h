//! Author: Faris Alqadah
//! Helper functions for keeping track of the top K clusters during an enumeration algorithm


#include "../core/RelationGraph.h"
#include "../core/Ops.h"
#include "basic.h"
//! Retains the top K clusters by checking for overlapping clusters then keeping the higher quality cluster if overlap occurs
/*!
    Attempts to add the cluster c to v, this can happen in three cases
     v.size() < k
        OR
      there does not exist any cluster x in v s.t Ovlp(c,x) > ovlpThresh && Quality(c) > min(Quality(x)) for any x in v
          OR
     there exists at least once cluster c s.t. ovlp(c,x) > ovlpThresh && Quality(c) > Quality(x) then c replaces x
     \param v the vector of current clusters enumerated by the algorithm
     \param c the current cluster enumerated
     \param Ovlp a function pointer to a function that computes overlap between clusters \sa Ops
     \param ovlpThresh the threshold for overlap
     \param k K

 */
void RetainTopK_Overlap(vector<NCluster*> &v, NCluster *c,double (*Ovlp)(NCluster*,NCluster*), double ovlpThresh, int k);




