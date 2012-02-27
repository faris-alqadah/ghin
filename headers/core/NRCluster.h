//! Author: Faris Alqadah
/*!Class for representing a set or vector of RSets. This can be used to represent, bi-clusters
    and n-clusters.
 \sa Rset
 */

#ifndef NRCLUSTER_H
#define	NRCLUSTER_H

#include "RSet.h"


using namespace std;

class NRCluster {
public:
    //! Default constructor
    NRCluster();
    //! Alternate constructor
    /*!
     Allocates n sets and sets size to n
        \param n number of sets to allocate
     */
    NRCluster(unsigned int n);
    //! Alternate constructor
    /*!
     Makes the n-cluster of size n, but does not allocate the memory
        \param n size of the n-cluster
        \param allocate this value does not matter, if its true or false, its just to inidcate that no memory should be allocated

     */
    NRCluster(unsigned int n, bool allocate);
    //! Alternate constructor
    /*!
     Constructor n-cluster of size n and assigin a deep copy of the RSets from the vector aa to the n-cluster
        \params n size of the n-cluster
        \params aa a vector of RSets that will be used to initialize the sets of self by making a deep copy
     */
    NRCluster(unsigned int n, vector<RSet*> &aa);
    //! Copy constructor
    NRCluster(NRCluster &);
    //! Destructor
    ~NRCluster();
    //! Makes a deep copy of the n-cluster
    void DeepCopy(NRCluster&);
    //! Prints each RSet on a seperate line preceded by the Id of each RSet to stdout
    void Output();
    //! Prints each RSet on a seperate line preceded by the Id of each RSet to ofstream
    void Output(ofstream&);
    //! Prints each RSet on a seperate line preceded by the Id of each RSet to ofstream
    /*!
     Attempts to match the id of one of the name maps to the id of the sets of self. If
     the ids match, then then RSet is output using the name map, otherwise normal printing
     is performed.
     */
    void Output(ofstream&, vector<NameMap *>&nm);
    //! Resurns n, the number of sets in the n-cluster
    int GetN();
    //! Returns a pointer to the ith set
    RSet * GetSet(int);
    //! Returns a pointer to the set with id, if it exists, assertion is checked
    RSet * GetSetById(int id);
    //! Adds the set a to the end of the n-cluster
    void AddSet(RSet* a);
    //! Assigns a to the ith, deleting the previously defined ith set in the process
    void AssignSet(int i, RSet *a);
    //! Assigns a to the set with id, if it exists, previoulsy defined set with id is destroyed in the process
    void AssignSetById(int id, RSet *a );
    //! Returns the quality attribute
    double GetQuality();
    //! Set the quality attribute
    void SetQuality(double);
    //! Returns the id attribute
    int GetId();
    //! Set the id attribute
    void SetId(int);
    //! Return the marked attribute
    bool GetMarked();
    //! Set the marked attribute
    void SetMarked(bool m);
    //! Returns true if an RSet with id=id exists in self, false otherwsie
    bool ContainsRSetId(int id);
    //! Returns the value of the largest element in all sets of self
    pair<int,double> GetMaxElement();
    //! Returns the largest index of all RSets in self
    int GetMaxIdx();

protected:
    //! degree of the cluster
    unsigned int n;
    //! the actual data or sets
    vector<RSet*> sets;
    //! quality of the n-cluster
    double quality;
    //! id of the n-cluster
    int id;
    //! has this n-cluster been marked or flagged for whatever reason??
    bool marked; //is the ncluster marked or flagged

};

//! Returns true if a->GetQuality() > b->GetQuality(), use this function with std:sort()
bool Compare_Quality(NRCluster *a, NRCluster *b);


#endif	

