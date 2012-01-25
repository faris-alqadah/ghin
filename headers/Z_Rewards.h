//! Author: Faris Alqadah
/*!
 Reward functions for the GHIN framework (See Alqadah et al. KDD 2011)
 These reward functions are "z-score"-like reward functions where the
 the number of interactions are compared against the expected number

 \sa Helper.h
 \sa ghin.h

 */

#ifndef Z_REWARDS_H
#define	Z_REWARDS_H

#include "core.h"



/*!
  Computes the expected satasfaction score using hypogemoteric distribution. \
  See Alqadah et al. in KDD '11 for details
 \params a the ncluster to compute score for
 \param obj the object id to compute for
 \param doamin the domain id for which to compute the score with respect to
 \param w the weight paramater (see Alqadah et al. KDD 2011)
 \param hin the information network
 */
double Exp_Sat_HypGeo_Score(NCluster *a, int obj, int domain, double w, RelationGraph *hin);



/*!
  Computes the expected satasfaction score using the beta-binomial distribution
 \params a the ncluster to compute score for
 \param obj the object id to compute for
 \param doamin the domain id for which to compute the score with respect to
 \param w the weight paramater
 \param hin the information network
 */
double Exp_Sat_BetaBinomail_Score(NCluster *a, int obj, int domain, double w, RelationGraph *hin);



#endif	/* Z_REWARDS_H */

