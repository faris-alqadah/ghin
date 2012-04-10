//! Author: Faris Alqadah
//!Class for representing a real valued matrix, (most likely sparse) as pairs of indexed values

/*!
  Essentially an extension of  a RContext from Formal Concept Analysis as two n-r-clusters in sparse pair format.
  The two sets in the relationship
  are denoted by domain ids. By default set 1 domain id = 0 and set 2 domain id = 1.

 */

#ifndef _RContext_H
#define	_RContext_H

#include "NRCluster.h"
#include "Ops.h"
#include "NameMap.h"

class RContext {
public:
    //! Default constructor that sets the number of objects in the first and second domain
    /*!
      \param  num1 the number of objects in the first domain
      \param num2 the number of objects in the second domain

     */
    RContext(int num1, int num2);
    //! Copy constructor
    /*!
        \param a another RContext to be deep copied
     */
    RContext(RContext &a);

    //! Constructor that takes in the actual full domains
    /*!
        \param d1 nr-cluster representing the "rows" or domain1 in sparse pair form
        \param d2 nr-cluster representing the "columns" or domain2 in sparse pair form
     */

    RContext(NRCluster *d1, NRCluster *d2);
    //! Descturor
    ~RContext();

    //! Returns an object-set from the RContext
    /*!
        \param domain the id of the domain from which the object-set will be returned
     *  \param setNum the object number in domain for which the object-set or prime will be returned
     */
    RSet * GetSet(int domain, int setNum);

    //! Returns an IOSet with all the labels (indicies) of the specifed domain
    /*!
        \param domain the id of the domain from which the  object-ids will be returned

     */
    IOSet *GetLabels(int domain);

    //! Return the id of the RContext
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

    //! Set the id of the RContext

    void SetId(int);
    //! Return the name of the RContext
    string GetName();

    //! Set the name of the RContext
    void SetName(string &);
    //! Set the domain id of either set1 or set2
    /*!
        \param setNum the set to which the id will be assigned, this should be eithier 0 or 1
        \param id will be assigned to be the domainId of the selected set
     */
    void SetDomainId(int setNum, int id);

    //! Returns the id of the selected set, (eithier 0 or 1)
    int GetDomainId(int setNum);
    //! Print the RContext to stdout as a binary matrix
    void PrintAsMatrix();
    //! Print the RContext to ofstream as a binary matrix
    void PrintAsMatrix(ofstream&);

       //!Prints  a sub-RContext of the original RContext
    /*!
     Constructs a sub RContext based on the objects in the paramaters a and b,
     \param a set of objects from domain1 that will form the "rows" or first domain of the sub-RContext
     \param b set of objects from domain2 that will form the "columns" or second domain of the sub-RContext
     \param dId1 id of the domain from whcih objects in a are derived
     \param dId2 id of the domain from which objects in b are derived
     */
    RContext *PrintSubSpace(IOSet *a, IOSet *b, int dId1, int dId2);


    //! Resturns a sub-RContext of the original RContext
    /*!
     Constructs a sub RContext based on the objects in the paramaters a and b
     \param a set of objects from domain1 that will form the "rows" or first domain of the sub-RContext
     \param b set of objects from domain2 that will form the "columns" or second domain of the sub-RContext
     */
    RContext * GetSubRContext(IOSet *a, IOSet *b);
    //! Compute the standard deviations of each row and column and store them
    void ComputeStdDevs();

    //!Compute ranges of each row and column and store them
    void ComputeRanges();

    //! Returns an standard deviation of a row / column or object set
    /*!
        \param domain the id of the domain from which the standard deviation will be looked up
     *  \param setNum the object number in domain for which the standard deviation will be looked up
     */
    double GetStdDev(int domain, int setNum);

    //! Returns range a row / column or object set
    /*!
        \param domain the id of the domain from which the range will be looked up
     *  \param setNum the object number in domain for which the range will be looked up
     */
    double GetRange(int domain, int setNum);


    //! Print the RContext in sparse pair style to stdout
    void PrintAsSparse();
  //! Print the RContext in sparse pair style to ofstream
    void PrintAsSparse(ofstream &);
    //! Return the number of objects for the specifed domain
    int GetNumSets(int domainId);
    //! Return the number of cells that are non-zeor or defined
    int GetNumCells();
    //! Return the number of cells that are none zero or defined / |domain1|*|domain2|
    double GetDensity();
    //!Prints some basic stats about the context such as density and number of elements in each domain
    void PrintBasicStats();
    //!Print the standard deviations
    void PrintStdDevs();


private:
     //!represent first domain
    NRCluster *domain1;
    //!represent second domain
    NRCluster *domain2;
    //!id of the RContext
    int id;
    //! name of the RContext
    string name;
    //! name map associated with domain 1
    NameMap *nameMap1;
    //! name map associated with domain 2
    NameMap *nameMap2;
    //! stanard deviations of domain 1 (if computed)
    RSet* stdDev1;
    //! stanard deviations of domain 2 (if computed)
    RSet* stdDev2;
    //! ranges of domain 1 (if computed)
    RSet *range1;
    //! ranges of domain 2 (if computed)
    RSet *range2;

};


#endif	/* _RContext_H */

