//! Author: Faris Alqadah
//!Class for representing a context as described in Formal Concept Analysis

/*!
  Represent a context from Formal Concept Analysis as two n-clusters in FIMI form.
  The two sets in the relationship
  are denoted by domain ids. By default set 1 domain id = 0 and set 2 domain id = 1.

 */

#ifndef _CONTEXT_H
#define	_CONTEXT_H

#include "NCluster.h"
#include "Ops.h"
#include "NameMap.h"

class Context {
public:
    //! Default constructor that sets the number of objects in the first and second domain
    /*!
      \param  num1 the number of objects in the first domain
      \param num2 the number of objects in the second domain

     */
    Context(int num1, int num2);
    //! Copy constructor
    /*!
        \param a another context to be deep copied
     */
    Context(Context &a);

    //! Constructor that takes in the actual full domains
    /*!
        \param d1 n-cluster representing the "rows" or domain1 in FIMI form
        \param d2 n-cluster representing the "columns" or domain2 in FIMI form
     */

    Context(NCluster *d1, NCluster *d2);
    //! Descturor
    ~Context();

    //! Returns an object-set from the context
    /*!
        \param domain the id of the domain from which the object-set will be returned
     *  \param setNum the object number in domain for which the object-set or prime will be returned
     */
    IOSet * GetSet(int domain, int setNum);

    //! Returns an IOSet with all the labels or object-ids of the specifed domain
    /*!
        \param domain the id of the domain from which the  object-ids will be returned
 
     */
    IOSet *GetLabels(int domain);

    //! Return the id of the context
    int GetId();
    //! Returns an interger pair corresponding to the ids of the domains
    pair<int, int> GetDomainIds();


    //! Assign a name map to one of the domains
    /*!
        \param dId the id of the domain to assign the name map to
        \param nm pointer to the name map to be assigned to the domain

     */
    void SetNameMap(int dId, NameMap *nm);
    //! Returns a pointer to the name map associated with one of the domains
    /*!
        \param dId the id of the domain for which the name map will be returned

     */
    NameMap * GetNameMap(int dId);

    //! Set the id of the context

    void SetId(int);
    //! Return the name of the context
    string GetName();

    //! Set the name of the context
    void SetName(string &);
    //! Set the domain id of either set1 or set2
    /*!
        \param setNum the set to which the id will be assigned, this should be eithier 0 or 1
        \param id will be assigned to be the domainId of the selected set
     */
    void SetDomainId(int setNum, int id);

    //! Returns the id of the selected set, (eithier 0 or 1)
    int GetDomainId(int setNum);
    //! Print the context to stdout as a binary matrix
    void PrintAsMatrix();
    //! Print the context to ofstream as a binary matrix
    void PrintAsMatrix(ofstream&);

    //! Resturns a sub-context of the original context
    /*!
     Constructs a sub context based on the objects in the paramaters a and b
     \param a set of objects from domain1 that will form the "rows" or first domain of the sub-context
     \param b set of objects from domain2 that will form the "columns" or second domain of the sub-context
     */
    Context * GetSubContext(IOSet *a, IOSet *b);

    //! Print the context in FIMI style to stdout
    void PrintAsFIMI();
  //! Print the context in FIMI style to ofstream
    void PrintAsFIMI(ofstream &);
    //! Return the number of objects for the specifed domain
    int GetNumSets(int domainId);
    //! Return the number of ones or relations between objects in domain1 and domain2
    int GetNumOnes();
    //! Return the number of ones / |domain1|*|domain2|
    double GetDensity();

    //! Return the longest set associated with any single object
    int GetLongestSet();

 
private:
     //!represent first domain
    NCluster *domain1;
    //!represent second domain
    NCluster *domain2;
    //!id of the context
    int id;
    //! name of the context
    string name;
    //! name map associated with domain 1
    NameMap *nameMap1;
    //! name map associated with domain 2
    NameMap *nameMap2; 
};


#endif	/* _CONTEXT_H */

