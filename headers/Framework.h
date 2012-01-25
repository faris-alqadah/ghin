//! Author: Faris Alqadah
/*!
 The Game Theortic Framework for HIN-clustering. LatticeAlgos and implements the framework
 described in the paper "A Game Theoritic Framework for HIN-cluster" by  Alqadah et al.
 Essentialy, HIN-clusters are considered Nash equalibrium points, based on a specified reward
 function.

 The current implenetaiton is quite naive as far as computaion, and can be vastly improved
 in terms of efficiency.

 \sa Helper.h
 \sa ghin.cpp

 */
#ifndef FRAMEWORK_H
#define	FRAMEWORK_H


#include "Z_Rewards.h"
#include "Count_Rewards.h"
#include "random_sample.h"

using namespace std;

class Ghin : public LatticeAlgos{
public:
Ghin():LatticeAlgos() {
    w=-1;
    tiredMode=false;
    rewardMode=-1;
    totalIters=0;
    totalCands=0;
    avgNashIters=0;
};


/*!
 Select the initial cluster (or party) that a deal will tried to be worked out with
 Typically this involves selecting a random domain (player) and selecting the prime
  in all neighbors, while in nodes that have similar color select nodes that share a
  more nodes than expected

  \param domain the domaain to seed for an initial candidate
  \param sampleSet the sample set from which to draw objects
  \param clustered objects that have already been clustered
 */
NCluster* SelectInit(int domain, NCluster *sampleSet, NCluster *clustered);


/*!
 Select the initial cluster (or party) that a deal will tried to be worked out with
 This method samples connected n-clusters across the hin by using random sampling of itemsets
 ~ to frequency or support
  \param sampleSet the sample set from which to draw objects

 */
NCluster* SelectInit_RandomFreq(NCluster *sampleSet);

/*!
  Iterate until a nash equalibrium is reached or return NULL
 */

NCluster* MakeDeal(NCluster*);

/*!
   Attempts to maximuze the reward of a single domain c while holding all other
   selections constant
   Reutnrs true if a change is made otherwise false
 */
bool MaximizeDomain(NCluster *, IOSet *c, int,bool);





/*!
  Update the set suitable for selection by removing all the elements of
  the input NCluster
 */

void UpdateSampleSet(NCluster*,NCluster*);


/*!
  The main algorithm:
    1. Mark domains in HIN tree as red and black
    2. Set slection_set = all objects in each domain
    3. Unil selection_set is empty DO:
           1. Select domain r at random
           2. Create initial cluster C starting with random object in r
           3. Attempt to make deal with C
           4. If deal is made with C update selection set


 Assumes RewardFunc variable has been set.
 */
void GHIN_Alg();



//! Pointer to reward function
//! the two integers specify the domains for which the reward function is computed
//! these are naive implementations of reward functions
double (*RewardFunc)(NCluster*,int,int,double,RelationGraph*);

//! weight value that is used in conjuction with different reward functions
double w;

/////////////////////////////////Reward function Modes///////////////////////////////
//! the id of the reward function
int rewardMode;
//! run with tiring party-goer mode?
bool tiredMode;
//! The simple weighted zeros reward function
static const int SIMPLE_WEIGHTED=1;
//! Expected satisfaction reward function using hyper-geomtric distribution
static const int EXPECTED_HYPGEO_SAT=2;
//! Expected satisfaction reward function using beta-binomial distibution
static const int EXPECTED_BETABINOMIAL_SAT=3;

///////////////////////Data Structs/////////////////////////////////////////////
//! pointer to a hin
RelationGraph *hin;
vector< vector<double> > tired;


//////////////////////////Some algorithm stats//////////////////////////////////
//! total number of iterations GHIN algorithms utilized
int totalIters;
//! total number of candidates generated to find Nash equalibrium
double totalCands;
//! avg number of iterations to find a nash equalibrium or fail...
double avgNashIters;


/////////////////////////REWARD FUNCTIONS///////////////////////////////////////

///*!
//    Given a reward function, computes a satasfaction score for the cluster, and assigns it to
// the .quality field of the ncluster.
// \params a the ncluster to compute score for, a->Quality() will be set to the score
// \param obj the object id to compute for
// \param doamin the domain id for which to compute the score with respect to
//
// */
//void Compute_Score(NCluster *a);





/*!
 Initialize the tiring vector
 */
void InitTiring();

/*!
  Update the tired vector when using the tired rewarad function

 */
void UpdateTired(NCluster *c);


/*!
 Returns the set of objects not currently in the cluster whose addition increases the reward function for the specified domain
    \param a the current cluster
    \param domain the domain for which possible addtions are computed
    \param RewardFunc pointer to the reward function to be used
 */

IOSet *AddSet_Reward(NCluster *a, int domain);

/*!
 Returns the set of objects in the current cluster and specifed domain whose removal increases the reward function
    \param a the current cluster
    \param domain the domain for which possible addtions are computed
    \param RewardFunc pointer to the reward function to be used
 */
IOSet *RemoveSet_Reward(NCluster *a, int domain);


////////////////////////////////////Helper functions////////////////////////////
/*!
 Randomly select a domain
 */
int SelectRandomDomain();

/*!
 Determine if the selection sets are empty
 */
bool SelectEmpty(NCluster*);
/*!
 Randomly select a and object from the set
 */
int SelectRandomObjectFromSet(IOSet*);

/*!
  Check if a cluster is a repeat of a previously enumerated cluster
 */
bool CheckRepeat(NCluster *);

/*!
  Make the first set of all objects that can be selected for initial state
*/
NCluster* MakeInitialSampleSet();

/*!
  Update the set suitable for selection by removing all the elements of
  the input NCluster
*/

void UpdateSampleSet(NCluster *selection, NCluster *currCluster, NCluster *clustered);
};
#endif	/* FRAMEWORK_H */

