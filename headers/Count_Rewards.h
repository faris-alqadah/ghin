//! Author: Faris Alqadah
/*!
 Reward functions for the GHIN framework (See Alqadah et al. KDD 2011)
 These reward functions rely on simple counting of the number of interactions

 \sa Helper.h
 \sa ghin.h

 */

#ifndef COUNT_REWARDS_H
#define	COUNT_REWARDS_H

#include "core.h"



/*!
 Computes the simple weighted score. See Alqadah et al. in KDD '11 for details
 \params a the ncluster to compute score for
 \param obj the object id to compute for
 \param doamin the domain id for which to compute the score with respect to
  \param w the weight paramater (see Alqadah et al. KDD 2011)
 \param hin the information network

 */
double Simple_Weighted_Score(NCluster *a, int obj, int domain, double w, RelationGraph *hin);




#endif	/* COUNT_REWARDS_H */

