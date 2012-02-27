//! Author: Faris Alqadah
/*!Class for representing an object-set or item-set as descibed in several
 data mining papers. Essentially an IOSet comprises an integer vector
 with some additional properties such as an id. It is generally assumed that
 algorithms will keep IOSets in sorted order to facilate operations such
 as set intersections, unions, difference etc.
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

#include "NameMap.h"
using namespace std;


#ifndef _IOSET_H
#define	_IOSET_H

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

//! Compartor function used for IOSets, returns true if the a->GetSize() > b->GetSize()
bool Compare_Sup(IOSet *a, IOSet *b);

//! Compartor function used for IOSets, returns true if the a->GetId() > b->GetId()
bool Compare_Id(IOSet *a, IOSet *b);

//! Compartor function used for IOSets, returns true if the a->GetQuality() > b->GetQuality()
bool Compare_Quality_IOSet(IOSet *a, IOSet *b);








#endif	/* _IOSET_H */

