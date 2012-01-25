/*!
 Author: Faris Alqadah
 Johns Hopkins University
 Library of core data structures and operations for use in several data mining algorithms.

 */


#include<string>
#include<iostream>
#include <map>
#include <set>
#include <algorithm>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include <queue>
#include <math.h>
#include <iomanip>
#include<sstream>
#include <utility>
#include <numeric>
#include <assert.h>
#include<time.h>
#include <sys/times.h>
#include <unistd.h>


#ifndef _CORE_H
#define	_CORE_H

using namespace std;
/*!Class used to map integer ids to names in an IOSet.
 Names are mapped to integer ids by reading in a file in which the line number -1 maps
 to the string found on that line. In addition each name map has an id field to indicate which
 IOSet or domain it corresponds to.
 \sa IOset
 */

class NameMap {
public:

    //! Default constructor. No actual map is constructed, since no file is read.
    NameMap();
    //! Alternate constructor that passes in the file name and constructs the actual name map
    NameMap(string &file);
    //! Alternate constructor that passes in the file name and constructs the actual name map but only upto the nth entry
    NameMap(string, unsigned int n);
    //! Returns the file name from which the name map was constructed
    string GetFileName();
    //! returns the string mapped to i
    string GetName(unsigned int i);
    //! returns the id of name if it exists
    int NameToId(string &n);
    //! Returns the number of entries in the map
    int GetNumEntries();
    //! Set the id attribute of the name map
    void SetId(int);
    //! Returns the id attribue of the name map
    int GetId();
private:
    //! the actual map, maps the index in the vector to the string
    vector<string> mapping;
    //! number of entries
    int numEntries;
    //! name of the file from which the map was constructed
    string fileName;
    //id attribute to match to domains or IOSets
    int id;
    //! reverse mapping of strings to ids
    map<string,int> revMap;

};

/*!Class for representing an object-set or item-set as descibed in several
 data mining papers. Essentially an IOSet comprises an integer vector
 with some additional properties such as an id. It is generally assumed that
 algorithms will keep IOSets in sorted order to facilate operations such
 as set intersections, unions, difference etc.
 */
class IOSet {
public:

   //! Default constructor
    IOSet();
       //! Constructor that pre-allocates the size of the IOSet
    IOSet(int sz);
    //! Copy constructor
    IOSet(IOSet *a);
       //! Destructor
    ~IOSet();
    //! Returns the size or number of elements in the IOSet
    int Size();
    //! Returns the id of the IOSet
    int Id();
     //! Set the id of the IOSet
    void SetId(int id);
    //! Prints contents of the IOSet as space sperated intergers to stdout
    void Output();
    //! Prints contents of the IOSet as space sperated intergers to ofstream
    void Output(ofstream& f);
      //! Prints contents of the IOSet as space sperated names to std stream using namemap to map the integers to names
    void Output(NameMap *n);
    //! Prints contents of the IOSet as space sperated names to ofstream using namemap to map the integers to names
    void Output(ofstream &f, NameMap *n);
   //! Adds integer x to the end of the IOSet, increasing the size of the IOSet
    void Add(int x);
    //! Assigns the private size variable of the IOSet without actually re-allocationg memory
    /*!
     This operation should mainly be used by set operation algorithms where size of the
     IOSet may not be known a-priori.
     */
    void SetSize(int x);

    //! Resize the IOSet to x, this will physically re-allocate and de-allocate memory unlike SetSize()
    void Resize(int x);
    //! Returns true if both IOSets have the same size and the exact contenets in the exact order and false otherwise
    bool Equal(IOSet&);
    //! Returns true if the IOSet contains the integer specified
    bool Contains(int);
    //! Make a deep copy of the input IOSet and assign it to self
    void DeepCopy(IOSet*);
    //! Remove the element at the specified index
    void Remove(int);
    //! Find and remove the specified element if it exists
    void FindRemove(int);
    //!Return the index of the specified element and -1 if element does not exist
    int GetIndex(int);
    //! Sort the elements of the IOSet in asscending order
    void Sort();
    //! Return the ith element
    int At(int i);
    //! Remove all elements from the IOSet
    void Clear();
    //! Return an iterator to the start of the IOSet
    vector<unsigned int>::iterator GetBegin();
    //! Return an iterator the end of the IOSet
    vector<unsigned int>::iterator GetEnd();
    //! Set the marked flag
    void SetMarked(bool);
    //! Returns the value of the marked flag
    bool GetMarked();
    //! Returns the largest element in the IOSet
    int GetMaxElement();
    //! Returns the quality
    double GetQuality();
    //! Set the qualuty
    void SetQuality(double);

private:
    //! size of the ioset
    int size;
    //! id of the ioset
    int id;
    //! vector to hold the data
    vector<unsigned int> d;
    //! has this ioset been marked for whatever reason??
    bool marked;
    //! the quality of the ioset
    double quality;

};



/*!Class for representing a sub-space or set of object-sets. Essentially an ncluster comprises vector of IOSets.
 \sa IOset
 */
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

/*!
  Represent a context from Formal Concept Analysis as two n-clusters in FIMI form.
  The two sets in the relationship
  are denoted by domain ids. By default set 1 domain id = 0 and set 2 domain id = 1.

 */
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


/*!
  Represent a Heterogenous Information Network (HIN) as described in data mining literature
 All edges in the network represent a context, and each node is a domain. The contexts are represented
 by the context class

 \sa Context

 */
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

/*!Class for representing an real-valued object-sets such as tf-idf word sets
 along with their tf-idf value. Since these sets can be sparse (or more accuratley they
 are derived form sparse matrices) an index is maintained. Essentially is an IOSet
 with an added real-valued vector.
 */

class RSet {
public:

   //! Default constructor
    RSet();
    //! Copy constructor
    RSet(RSet *a);
       //! Destructor
    ~RSet();
    //! Returns the size or number of elements in the RSet
    int Size();
    //! Returns the id of the RSet
    int Id();
     //! Set the id of the IOSet
    void SetId(int id);
    //! Prints contents of the RSet as space sperated pairs of real,intergers to stdout
    void Output();
    //! Prints contents of the RSet as space sperated pairs to ofstream
    void Output(ofstream& f);
    //! Prints contents of the RSet as space sperated pairs of names and values to ofstream using namemap to map the integers to names
    void Output(ofstream &f, NameMap *n);
   //! Adds pair to the end of the RSet, increasing the size of the RSet
    void Add(pair<int,double>);
    //! Make a deep copy of the input RSet and assign it to self
    void DeepCopy(RSet*);
    //! Return the  element indexed by i
    //! if not in the rset then return value is -1,-1
    pair<int,double> At(int i);
    //! Return an IOSet of all indexes that have values associated with them
    IOSet *GetIdxs();
    //!Returns a subspace of self as indicated by the idxs, assumes idxs is sorted for log linear time perfomance
    RSet* GetSubspace(IOSet *idxs);
    //! Returns index pointers (i.e. actual index not id) to the minimum and maximum element in the subspace specified by idxs, assumes idxs is sorted for linear time performance
    //! If subspace indicated by idxs does not exist, then -1,-1 is returned
    pair<int,int> GetMinMaxSubspaceIdxs(IOSet *idxs);
    //! Remove all elements from the RSet
    void Clear();
    //! Set the marked flag
    void SetMarked(bool);
    //! Returns the value of the marked flag
    bool GetMarked();
    //! Returns the largest element in the RSet (largest in terms of value)
    pair<int,double> GetMaxElement();
    //! Returns the smalles element in the RSet (smallets in terms of value)
    pair<int,double> GetMinElement();
    //! Returns the largest index in self
    int GetMaxIdx();
    //! Get sum of all values
    double Sum();
    //! Returns the variance of this RSet
    double Variance();
    //! Returns the standard deviation of self
    double Std_Dev();
    //! Returns the mean of self
    double Mean();
    //! Set the quality
    void SetQuality(double);
    //!Returns the quality
    double GetQuality();
    //! Return the range of self
    double Range();
private:
    //! size of the RSet
    int size;
    //! id of the RSet
    int id;
    //! vector to hold the values
    map<int,double>  vals;
    //! second copy of idxs, in sorted order to facilitate idx intersection
    IOSet idxs;
    //! iterator to be used for iterating in data structure
    map<int,double>::iterator it;
    //! has this RSet been marked for whatever reason??
    bool marked;
    //! the quality of this RSet
    double quality;

};

/*!Class for representing a set or vector of RSets. This can be used to represent, bi-clusters
    and n-clusters.
 \sa Rset
 */


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

/*!
  Essentially an extension of  a RContext from Formal Concept Analysis as two n-r-clusters in sparse pair format.
  The two sets in the relationship
  are denoted by domain ids. By default set 1 domain id = 0 and set 2 domain id = 1.

 */

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

/*!
  Represent a Heterogenous Information Network (HIN) as described in data mining literature. This relation graph
 may include real-valued contexts.  All edges in the network represent a context, and each node is a domain. The contexts are represented
 by the context class

 \sa RelationGraph
 \sa RConcetxt
 \sa Context

 */

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

/*!
 Computes the mean of a hypergeometrically distributed random varaiable
    \param n see wiki entry of hypergeomtric distribution
    \param m see wiki entry of hypergeomtric distribution
    \param NN corresponds to N in wiki entry of hypergeomtric distribution
 */
double Hypgeo_Mean(int n, int m, int NN);

/*!
 Computes the standard devation of a hypergeometrically distributed random varaiable
    \param n see wiki entry of hypergeomtric distribution
    \param m see wiki entry of hypergeomtric distribution
    \param NN corresponds to N in wiki entry of hypergeomtric distribution
 */
double Hypgeo_Dev(int n, int m, int NN);


/*!
 Computes the mean of a beta-binomial distributed random varaiable
    \param n see wiki entry of beta-binomial distribution
    \param alpha see wiki entry of beta-binomial distribution
    \param beta see wiki entry of beta-binomial distribution
 */
double BetaBinomial_Mean(int n, int alpha, int beta);

/*!
 Computes the standard devation of a beta-binomial distributed random varaiable
    \param n see wiki entry of beta-binomial distribution
    \param alpha see wiki entry of beta-binomial distribution
    \param beta see wiki entry of beta-binomial distribution
 */
double BetaBinomial_Dev(int n, int alpha, int beta);



/*!
 Computes a z-score
    \param x the value compute z-score for
    \param mean the mean of the sample
    \parm std the standard deviation of the sample
 */
double Z_Score(double x, double mean, double std);

//!Class for representing a context as described in Formal Concept Analysis






//! Compartor function used for IOSets, returns true if the a->GetSize() > b->GetSize()
bool Compare_Sup(IOSet *a, IOSet *b);

//! Compartor function used for IOSets, returns true if the a->GetId() > b->GetId()
bool Compare_Id(IOSet *a, IOSet *b);

//! Compartor function used for IOSets, returns true if the a->GetQuality() > b->GetQuality()
bool Compare_Quality_IOSet(IOSet *a, IOSet *b);

/*!

 This class serves as the base function for Information Network Clustering algorithms that
 are based on Formal Concept Analysis and Concept lattices.

 All FCA-based algorithms should be formed as children classes of this class, as this
 class provides several generic class members that are utilized to indicate different modes
 of operation for each algorithm. For example, different modes of operation could be mining the clusters
 and outputing to a file, or maintaing in memory etc. Additionaly the class member variables indicate what
 quality functions should be used etc. Each derived class' documentation speficies what variables must be set
 in order to execute the underlying algorihtm correclty.

 */

class LatticeAlgos{


public:
//! Default constructor
   LatticeAlgos(){
    srchLvl =0; //default
    numConcepts=0; //default
    dispProgress=false; //default
    enumerationMode=1; //seting default
    qualityMode=1; //default
    ovlpMode=1;
    ovlpThresh=0.25;  //this is the overlap threshold...setting default
    topKK = 100;      //this is "K" for top k enumerations...setting default
    pruneMode=1; //defaults
}








//! keeps track of the search level in an enumeration algorithm
int srchLvl;
//! keeps track of the total number of concepts or clusters enumerated
int numConcepts;
//! flag to indicate if progress of the algorithm should output to the user (stdout)
bool dispProgress;

//Data structures and files
//! data structure to hold the enumerated clusters in memory during algorithm exectuion
vector<NCluster*> CONCEPTS;
 //! vector of name maps to be used to output clusters
vector<NameMap*> NAME_MAPS;
//! if ENUM_FILE or ENUM_TOPK_FILE is selected then this file is used to output the concepts
string OUTFILE;
//!ofstream used to output to OUTFILE.concepts
ofstream OUT1;
 //!ofsteram used to output to OUTFILE.concept.names
ofstream OUT2;


/////////////////////////////////Enumeation Modes///////////////////////////////
//! Enumeration mode that specifies to algorithms to mine and store clusters in memory
static const int ENUM_MEM=1;
//! Enumeration mode that specifies to algorithms to mine and output clusters to a file, this file is specified by OUTFILE
static const int ENUM_FILE=2;
//! Enumeration mode that specifies to algorithms to mine only the top K clusters and output to a file, this file is specified by OUTFILE
static const int ENUM_TOPK_FILE=3;
//! Enumeration mode that specifies to algorithms to mine only the top K clusters and store in memory
static const int ENUM_TOPK_MEM=4;
//! Users will set this variable to indicate the enumeration mode
int enumerationMode;

/////////////////////////////////Quality Modes///////////////////////////////
//! quality mode that indicates to use the area of a concept as its quality measure
static const int AREA=1;
//! quality mode that indicates to use the beta area of a concept as its quality measure (see "An effective algorithm for mining 3-clusters" by Alqadah et al.)
static const int BETA=2;
//! user will set this variable to indicate the desired qualityMode
int qualityMode;
//! function pointer to a quality measure, interface functions will set this acrroding to qualityMode
double(*qualityFunction)(NCluster*, vector<double> &);
 //! store the parameters for a quality function here, see the QualityMeasures.h documentation for specification of these parameters
 vector<double> params;





/////////////////////////////////Overlap Modes///////////////////////////////
 //! overlap mode that indicates to use the average jaccard coefficient across all sets of an n-cluster to compute overlapping
static const int AVG_JACCARD=1;
 //! user will set this variable to inidicate the desired qualityMode
int ovlpMode;
//! function pointer to an overlap function computer, interface function will set this according to ovlpMode
double(*ovlpFunction)(NCluster*,NCluster*);
//! a threshold value that indicates how much overlap two clusters may have before an algorithm keeps the higher quality cluster
double ovlpThresh;

/////////////////////////////////Top K Modes///////////////////////////////
 //! the number of clusters an algorithm should enumerate if user only wants the top k clusters
int topKK;

/////////////////////////////////Prune Modes///////////////////////////////
 //! prune mode that indicates pruning will be based on size (support pruning)
static const int PRUNE_SIZE=1;
 //! user will set this variable to indicate the the desired pruning mode
int pruneMode;

//! if PRUNE_SIZE mode is selected this vector should be initialized to the min support of each domain
/*!
 PRUNE_SIZE_VECTOR[domainId-1] should contain the minumum number of objects a domain with domainId should contian in order to
 be considered for enumeration. Users must set the values for this vector
 */
vector<int> PRUNE_SIZE_VECTOR;

};

//! Basic Lattice operations derived from formal concept anaylsis. These are extended  to heterogenous information networks (HINs)


//! Returns the concept corresponds to the concept that contains all the objects from domain2, and any element in domain1 that contains all objects from doamin2 or the empty set
NCluster *GetTop(Context *c);
//! Returns  the bottom level concept from c, this concept corresponds to the concept that contains all the objects from domain1, and any element in domain2 that contains all objects from doamin1 or the empty set
NCluster *GetBottom(Context *c);
//! Computes the Prime (') (see any book on Formal Concept Anaylsis) for a given object-set
/*!
    The operation differs slighty from the strict FCA definition in that if a[s] is empty
    then the result is a NULL set. Moreover, this PrimeOperator is "min-aware" so that if at any time during the compution
     the results has cardinality <> min no more operations are perfomed and NULL is returned

    \param a the n-cluster that contains set s as a(s)
    \param g the relation graph in which (s,t) must be an edge (a context exists)
    \param s indicates the source domain id in a to serve as the input for the prime operator
    \param t indicates the target domain
    \param min indicates the minimum size the result prime should be, otherwise NULL is returned

 */
IOSet *Prime(NCluster *a, RelationGraph *g, int s, int t, int min);



//! Returns true if a->GetQuality() > b->GetQuality(), use this function with std:sort()
bool Compare_Quality_NCluster(NCluster *a, NCluster *b);



//! Returns true if a->GetQuality() > b->GetQuality(), use this function with std:sort()
bool Compare_Quality(NRCluster *a, NRCluster *b);




/*! Basic operations for sets. Also included are some set similarity measures
 such as jaccard and Sorensen coefficent. Almost all operations defined here assume
 that the IOSets are sorted in order to achieve O(n) running time for common set ops.
 Please keep this in mind!

 External variables included to keep track of the number of times these
  basic operations are invoked

  Any template functions for set / vector operations should also be placed here
 \sa IOset
 */
template <class t>
//! Destroy a pointer to a vector with elements of class t
void DstryVector( vector<t*> *v){
    for(int i=0; i < v->size(); i++){
        if (v->at(i) != NULL){
            delete v->at(i);
            v->at(i) = NULL;
        }
    }
    delete v;
}
template <class t>
//! Destroy  a vector with elements of class t
void DstryVector( vector<t*> &v){
    for(int i=0; i < v.size(); i++){
        if (v.at(i) != NULL){
            delete v.at(i);
            v.at(i) = NULL;
        }
    }
}
template <class t>
//! Destroy  a list with pointer elements of class t
void DstryList( list<t*> &v){
    typename list<t*>::iterator it;
    it= v.begin();
    while(it != v.end()){
        if ( (*it) != NULL){
            delete (*it);
            (*it) = NULL;
        }
        it++;
    }
}
template <class t>
//! Remove element at the iterator position from list and re-allocate the memory, then returns iterator to next element in the list
typename list<t*>::iterator RemoveFromList( list<t*> &v, typename list<t*>::iterator it){
    return v.erase(it);
}



//! Set intersection
IOSet * Intersect( IOSet*, IOSet*);

//! Set difference a-b
IOSet * Difference( IOSet *a,  IOSet *b);

//! Symmetric set difference
IOSet *SymmDifference( IOSet*, IOSet*);

//! Set union
IOSet* Union( IOSet*,  IOSet*);



//! Returns true if b is a subet of a and false otherwise
bool Contains( IOSet *a,  IOSet *b );



//! Returns true if b is a proper subet of a and false otherwise
bool ProperSubSet(IOSet *a, IOSet*b);

//! Returns Jaccard Coefficient |a intersect b| / |  a union b|
double PercentOverlap( IOSet *a, IOSet *b );


//! Returns Sorensen Index or Dice coefficient 2*| a intersect b| / |a| + |b|
double PercentOverlap_Sorensen( IOSet *a, IOSet *b );


//! Assumes a.GetN == b.GetN, and returns(SUM_{i=0...GetN()-1} PercentOverlap(a[i],b[i]))/ GetN()
double AverageOverlap(NCluster *a, NCluster *b);

//! Returns 1 if the b[0] is of greater equal size 0 otherwise, this is used as an "overlap" function for query-based bi-clustering
double GreaterEqualSize(NCluster *a, NCluster *b);

//! Assumes a is the FIMI representation of a sparse matrix, and transposes it
NCluster *TransposeFimi(NCluster *a);

//! Assumes a is the FIMI representation of a sparse matrix, and transposes it
NCluster *TransposeFimi(NCluster *a,int sz1,int sz2);

//! Randomly select an element from a set given weights associated with each element in the set
int WeightedUniformDraw(vector<long double> &weights);

//! Randomly select an element from a set given weights associated with each element in the set
int WeightedUniformDraw(vector<double> &weights);

//! Randomly (uniformly) select a subset from IOSet
IOSet * UniformSubsetDraw(IOSet *t);

//! Select a subset from t, with probablity proportional to its size
IOSet * BinomialSubsetDraw(IOSet *t);


unsigned int NChooseK(unsigned int n, unsigned int k);

long double NChooseK(long double n, long double k);
/*!
     EXTERNALS
Use these to keep count of the number of basic set operations used
within a particular algorithm
*/
//!number of intersections performed
extern int numIntersection;
//!number of subset checks performed
extern int numSubset;
//!number of set unions performed
extern int numUnion;
//!number of set differences performed
extern int numDifference;


/*! Basic operations for RSets which are essentially real-valued vectors.
 These include some basic matrix operations and statistical ops

 \sa RSet
 */

//! Assumes a is the sparse representation of a sparse matrix, and transposes it
NRCluster *TransposeSparse(NRCluster *a);

//! Returns a the set of idxs that are common to both a and b
IOSet *Common_Idxs(RSet *a, RSet *b);

//! Return the intersection of the indices of a and elements of IOSet b
RSet *Intersect(RSet *a, IOSet *b);

//! Union two RSets by indicies, assumes that the RSets are sorted by index
RSet *Union(RSet *a, RSet *b);

/*!
 Pre-processing for the hin-core. Mainly reads in an input file, and context files
  to create a relation graph that is maintained in memory

 \sa RelationGraph
 */
//! Reads an input file that specifies a full relation graph and creates the relation graph store in memory as RelationGraph object
/*!
 See the README file for the format of the input file.
 \param inputFile the path to the input file
 \sa RelationGraph
 */
RelationGraph * MakeRelationGraph(string &inputFile);

//! Reads an input file that specifies a full relation graph and creates the relation graph store in memory as RelationGraphR object
/*!
 See the README file for the format of the input file.
 \param inputFile the path to the input file
 \sa RelationGraphR
 */
RelationGraphR * MakeRelationGraphR(string &inputFile);

//! Reads an input file that only specifies a single real-valued context and stores it in memory as RContext object
/*!
 See the README file for the format of the input file.
 \param inputFile the path to the input file
 \sa RContext, MakeRContext
 */
RContext * MakeSingleRContext( string & inputFile);

//! Returns a context object initialized to all the input variables
/*!
    \param inputFile the path to the input file
    \param dId1 id of domain1
    \param dId2 id of domain2
    \param name the name of the context
    \param ctxId id of the context
    \param nm1 pointer to the name map associated with domain1
    \param nm2 pointer to the name map associated with domain2
    \param sz1 number of elements in domain 1
    \param sz2 number of elements in domain 2

 */
Context * MakeContext(string &inputFile,int dId1, int dId2, string &name, int ctxId, NameMap *nm1, NameMap *nm2,int sz1,int sz2);


//! Returns a RContext object initialized to all the input variables
/*!
    \param inputFile the path to the input file
    \param dId1 id of domain1
    \param dId2 id of domain2
    \param name the name of the context
    \param ctxId id of the context
    \param nm1 pointer to the name map associated with domain1
    \param nm2 pointer to the name map associated with domain2

 */

RContext * MakeRContext(string &inputFile,int dId1, int dId2, string &name, int ctxId, NameMap *nm1, NameMap *nm2);

//! Returns an Ncluster representing the FIMI file in inputFile
NCluster *MakeNClusterFromFimi(string &inputFile);

//! Reutrns an NRCluster from a file in spare matrix format
NRCluster *MakeNRClusterFromSparseFile(string &inputFile);


//! Tokenizes the string into a vector of string based on token
/*!
        \param str the string to be tokenized
        \param tokens emptry string vector that will be filled with tokens after function is called
        \param delim the character or string that is the delimiter to create tokens

 */
void Tokenize(const string& str, vector<string> &tokens , const string &delim);

//! Output an error message and exit the program
void Error(string &message);
/*!
 Quality functions of n-clusters. All functions should have standard input signature
 so that they may be used generically with Lattice Algorithms

 \sa LatticeAlgos
 */
//! Returns the area of an n-cluster, assuming it is star-shaped
/*!
 Area is compute as |a[artId]|* sum_{all other nodes i} |a[i]|
    \sa a the n-cluster to compute area for
    \sa params params[0] should contain the id of the articulation node
 */
double Area(NCluster *a, vector<double> &params);

//! Returns the beta-balanced area of an n-cluster, assuming it is star-shaped
/*!
 See "An efficient algorithm for mining 3-clusters" by Alqadah et al.
 Area is compute as |a[artId]|* (1/Beta)^sum_{all other nodes i} |a[i]| where 0 < Beta < 1
    \sa a the n-cluster to compute area for
    \sa params params[0] should contain the id of the articulation node, params[1] = beta
 */
double Beta(NCluster *a, vector<double> &params);





//! Compartor function used for IOSets, returns true if the a->GetSize() > b->GetSize()
bool RSet_Compare_Sup(IOSet *a, IOSet *b);

//! Compartor function used for IOSets, returns true if the a->GetId() > b->GetId()
bool RSet_Compare_Id(IOSet *a, IOSet *b);





//!Uitlity for timing algorithms

//! when timing starts
extern struct tms startTime;
//! when timing has ended
extern struct tms endTime; //when timiing ended
//! the time units
extern float clockTicksPerSecond;
//! start time converted to seconds
extern float startTimeSeconds;
//! end time converted to seconds
extern float endTimeSeconds;

//! Call this to Start timing
 void StartTiming();

//! Call this to End timing
 void EndTiming();

//! Call this after StartTiming and EndTiming have been called to compute total CPU time
 /*!
  \sa StartTiming
  \sa EndTiming

  */
 float ComputeTime();

 //! Helper functions for keeping track of the top K clusters during an enumeration algorithm

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


//! adds a new copy of to v
void StoreCluster(vector<NCluster*> &v, NCluster *c);


//! swaps out the ith pointer in v for a new copy of c
void SwapDelete(vector<NCluster*> &v, NCluster *c, int i);




//! Sets the quality of c by calling the Quality(c,params) function
/*!
 Every Quality function should have a specification for what it expects in params vector.
  \sa QualityMeasures
    \param c the ncluster for which the quality should be computed
    \param params a vector of paramaters that will be used to compute the quality
    \param Quality a valid pointer to a function for whcih quality will be computed. The functions
 should be derived from QualityMeasures.h

 @see QualityMeasures
 */
void SetQuality(NCluster *c,vector<double> &params, double (*Quality)(NCluster*,vector<double> &) );

//! Displays progress to stdout as ctr / total
void DispProgress(int ctr,int total);

//! Writes c to the file pointed to by out and flushes the buffer for instant writing
void OutputCluster(NCluster *c, ofstream &out);
//! Writes c to the file pointed to by out using the namemap vectors and flushes the buffer for instant writing
void OutputCluster(NCluster *c, ofstream &out, vector<NameMap*> &);


#endif	/* _CORE_H */

