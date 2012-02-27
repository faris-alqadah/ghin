//! Author: Faris Alqadah
/*!Class for representing a sub-space or set of object-sets. Essentially an ncluster comprises vector of IOSets.
 \sa IOset
 */

#ifndef _NCLUSTER_H
#define	_NCLUSTER_H

#include "IOSet.h"

using namespace std;

class NCluster {
public:
    //! Default constructor
    NCluster();
    //! Alternate constructor
    /*!
     Allocates n sets and sets size to n
        \param n number of sets to allocate
     */
    NCluster(unsigned int n);
    //! Alternate constructor
    /*!
     Makes the n-cluster of size n, but does not allocate the memory
        \param n size of the n-cluster
        \param allocate this value does not matter, if its true or false, its just to inidcate that no memory should be allocated

     */
    NCluster(unsigned int n, bool allocate);
    //! Alternate constructor
    /*!
     Constructor n-cluster of size n and assigin a deep copy of the IOsets from the vector aa to the n-cluster
        \params n size of the n-cluster
        \params aa a vector of IOSets that will be used to initialize the sets of self by making a deep copy
     */
    NCluster(unsigned int n, vector<IOSet*> &aa);
    //! Copy constructor
    NCluster(NCluster &);
    //! Destructor
    ~NCluster();
    //! Makes a deep copy of the n-cluster
    void DeepCopy(NCluster&);
    //! Prints each IOset on a seperate line preceded by the Id of each IOSet to stdout
    void Output();
    //! Prints each IOset on a seperate line preceded by the Id of each IOSet to ofstream
    void Output(ofstream&);
    //! Prints each IOset on a seperate line preceded by the Id of each IOSet to ofstream
    /*!
     Attempts to match the id of one of the name maps to the id of the sets of self. If
     the ids match, then then IOSet is output using the name map, otherwise normal printing
     is performed.
     */
    void Output(ofstream&, vector<NameMap *>&nm);

    //! Prints each IOset on a seperate line preceded by the Id of each IOSet to std stream
    /*!
     Attempts to match the id of one of the name maps to the id of the sets of self. If
     the ids match, then then IOSet is output using the name map, otherwise normal printing
     is performed.
     */
    void Output(vector<NameMap *>&nm);
    //! Resurns n, the number of sets in the n-cluster
    int GetN();
    //! Returns a pointer to the ith set
    IOSet * GetSet(int);
    //! Returns a pointer to the set with id, if it exists, assertion is checked
    IOSet * GetSetById(int id);
    //! Adds the set a to the end of the n-cluster
    void AddSet(IOSet* a);
    //! Assigns a to the ith, deleting the previously defined ith set in the process
    void AssignSet(int i, IOSet* a);
    //! Assigns a to the set with id, if it exists, previoulsy defined set with id is destroyed in the process
    void AssignSetById(int id, IOSet* a );
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
    //! Returns true if an IOSet with id=id exists in self, false otherwsie
    bool ContainsIOSetId(int id);
    //! Returns the value of the largest element in all sets of self
    int GetMaxElement();
    //! Remove the IOSet at index i
    void RemoveSet(int i);
    //!Sort the sets by the quality variables of each IOSet
    void SortSets();



protected:
    //! degree of the cluster
    unsigned int n;
    //! the actual data or sets
    vector<IOSet*> sets;
    //! quality of the n-cluster
    double quality;
    //! id of the n-cluster
    int id;
    //! has this n-cluster been marked or flagged for whatever reason??
    bool marked; //is the ncluster marked or flagged

};

//! Returns true if a->GetQuality() > b->GetQuality(), use this function with std:sort()
bool Compare_Quality_NCluster(NCluster *a, NCluster *b);



#endif

