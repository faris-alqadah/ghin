//! Author: Faris Alqadah
//!Class for representing a Heterogenous Information Network (HIN).

/*!
  Represent a Heterogenous Information Network (HIN) as described in data mining literature. This relation graph
 may include real-valued contexts.  All edges in the network represent a context, and each node is a domain. The contexts are represented
 by the context class

 \sa RelationGraph
 \sa RConcetxt
 \sa Context

 */

#ifndef _RELATIONGRAPHR_H
#define	_RELATIONGRAPHR_H

#include"RContext.h"
#include "Context.h"



class RelationGraphR{
public:
//! Default constructor
    RelationGraphR();

//! Destructor
    ~RelationGraphR();

//! Adds rcontext c to the network
/*!
  Add a context to the network. This method assumes the ids of the domains of the context
 are well defined, and will use these ids to construct the topplogy of the network.
 \param r the rcontext to add to the network,

 */
void AddRContext(RContext *r);


//! Returns the number of nodes (domains) in the network
int GetNumNodes();

//! Returns true if the ids are an edge in the network, false otherwise
/*!
 Returns true if there exists a context in the network that has domains
 with id1 and id2

 */
bool IsEdge(int id1,int id2);

//! Returns a vector of rcontexts that contain domain
    vector<RContext*> * GetContexts(int domain);
//! Compute standatd deviations in all contexts
    void ComputeStdDevs();
 //! Compute range in all contexts
    void ComputeRange();
//! Returns an IOSet of domain ids which correspond to the articulation nodes of the network
    IOSet *GetArtDomains();

//! Returns a pointer to the rcontext with the specified ctxId
    RContext * GetRContext(int ctxId);

//! Reutnrs an IOSet of doamins ids that share an edge with domain
    IOSet * GetNeighbors(int domain);

//! Reutnrs an IOSet of all the context ids
    IOSet * GetAllContextIds();

//! Reutnrs an IOSet of all the domain ids
    IOSet *GetAllDomainIds();

//! Reutnrs true if dId is a domain id in the network, false otherwise
    bool IsDomainId(int dId);
//! Reutnrs true if cId is a rcontext id in the network, false otherwise
    bool IsRContextId(int cId);

//! Prints the HIN
    void Print();

//! Returns the rcontext correspoding to the edge (s,t), that is context with domains s and t
    RContext* GetRContext(int s, int t);

 //! Returns a vector of name map pointers correspoding to each domain of the HIN
 /*!
  The name maps are not in any specfied order, use the id attribute of each name to figure
  out correspondce to domains!

   \sa NameMap

  */
    vector<NameMap*> * GetNameMaps();

private:
    //! maps domains to rcontexts
    NCluster domainContextMap;
    //! holds all the rcontexts
    vector<RContext*> contexts;
    //! adajcency list of the actual graph
    NCluster domainRelations;

};


#endif	/* _RELATIONGRAPH_H */
