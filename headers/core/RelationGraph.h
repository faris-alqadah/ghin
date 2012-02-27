//! Author: Faris Alqadah
//!Class for representing a Heterogenous Information Network (HIN).

/*!
  Represent a Heterogenous Information Network (HIN) as described in data mining literature
 All edges in the network represent a context, and each node is a domain. The contexts are represented
 by the context class

 \sa Context

 */

#ifndef _RELATIONGRAPH_H
#define	_RELATIONGRAPH_H

#include"Context.h"




class RelationGraph{
public:
//! Default constructor
    RelationGraph();

//! Destructor 
    ~RelationGraph();

//! Adds context c to the network
/*!
  Add a context to the network. This method assumes the ids of the domains of the context
 are well defined, and will use these ids to construct the topplogy of the network.
 \param c the context to add to the network,

 */
void AddContext(Context *c);


//! Returns the number of nodes (domains) in the network
int GetNumNodes();



/*! Return the number of elements in this domain*/
int NumObjsInDomain(int dId);

//! Return an IOSet of all objects in the specifed domain
IOSet *GetLabels(int dId);
//! Returns true if the ids are an edge in the network, false otherwise
/*!
 Returns true if there exists a context in the network that has domains
 with id1 and id2

 */
bool IsEdge(int id1,int id2);

//! Returns a vector of contexts that contain domain
    vector<Context*> * GetContexts(int domain);
//! Returns an IOSet of domain ids which correspond to the articulation nodes of the network
    IOSet *GetArtDomains();

//! Returns a pointer to the context with the specified ctxId
    Context * GetContext(int ctxId);

//! Reutnrs an IOSet of doamins ids that share an edge with domain
    IOSet * GetNeighbors(int domain);

//! Reutnrs an IOSet of all the context ids
    IOSet * GetAllContextIds();

//! Reutnrs an IOSet of all the domain ids
    IOSet *GetAllDomainIds();

//! Reutnrs true if dId is a domain id in the network, false otherwise
    bool IsDomainId(int dId);
//! Reutnrs true if cId is a context id in the network, false otherwise
    bool IsContextId(int cId);

    //! Reutnrs true if dId is an articulation node in the network, false otherwise
    bool IsArtNodeId(int dId);

//! Prints the HIN
    void Print();

 //! Returns set of objects in articulation node s that have suport >= 1 in all contexts
    IOSet * GetCommonObjectsArtNode(int aNode);

//! Returns the context correspoding to the edge (s,t), that is context with domains s and t
    Context* GetContext(int s, int t);

//! Returns ioset of objects in domain dId
    IOSet *GetDomainObjs(int dId);

//! Return the total number of nodes in the relation graph (i.e. sum of cardinality of all domains)
    int GetTotalNumObjs();
 //! Returns a vector of name map pointers correspoding to each domain of the HIN
 /*!
  The name maps are not in any specfied order, use the id attribute of each name to figure
  out correspondce to domains!

   \sa NameMap

  */
    vector<NameMap*> * GetNameMaps();

private:
    //! maps domains to contexts
    NCluster domainContextMap;
    //! holds all the contexts
    vector<Context*> contexts;
    //! adajcency list of the actual graph
    NCluster domainRelations; 

};


#endif	/* _RELATIONGRAPH_H */

