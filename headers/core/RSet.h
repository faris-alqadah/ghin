//! Author: Faris Alqadah
/*!Class for representing an real-valued object-sets such as tf-idf word sets
 along with their tf-idf value. Since these sets can be sparse (or more accuratley they
 are derived form sparse matrices) an index is maintained. Essentially is an IOSet
 with an added real-valued vector.
 */
#ifndef RSET_H
#define	RSET_H

#include "IOSet.h"
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

//! Compartor function used for IOSets, returns true if the a->GetSize() > b->GetSize()
bool RSet_Compare_Sup(IOSet *a, IOSet *b);

//! Compartor function used for IOSets, returns true if the a->GetId() > b->GetId()
bool RSet_Compare_Id(IOSet *a, IOSet *b);


#endif	/* RSET_H */

