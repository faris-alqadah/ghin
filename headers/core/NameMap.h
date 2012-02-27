//! Author: Faris Alqadah
/*!Class used to map integer ids to names in an IOSet.
 Names are mapped to integer ids by reading in a file in which the line number -1 maps
 to the string found on that line. In addition each name map has an id field to indicate which
 IOSet or domain it corresponds to.
 \sa IOset
 */

#ifndef _NAMEMAP_H
#define	_NAMEMAP_H

#include <iomanip>
#include<string>
#include<vector>
#include<sstream>
#include<iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
using namespace std;

class NameMap {
public:
    
    //! Default constructor. No actual map is constructed, since no file is read.
    NameMap();
    //! Alternate constructor that passes in the file name and constructs the actual name map
    NameMap(string &file);
    //! Alternate constructor that passes in the file name and constructs the actual name map but only upto the nth entry
    NameMap(string &, unsigned int n);
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

#endif	/* _NAMEMAP_H */

