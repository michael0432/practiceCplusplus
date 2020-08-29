#include <cstddef>
#include <iostream>
#include <memory.h>
#include "Vector.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
{
   myFirst = myLast = myEnd = nullptr;
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector( const size_type count )
{
   myFirst = new value_type[count]();
   memset(myFirst, 0, 5 * sizeof(value_type));
   myLast = myFirst + count;
   myEnd = myFirst + count;
   
}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector( const vector &right )
{
   int c = right.myEnd - right.myFirst;
   int s = right.myLast - right.myFirst;
   myFirst = new value_type[c]();
   for(int i=0; i<c; i++){
      myFirst[i] = right.myFirst[i];
   }
   myLast = myFirst + s;
   myEnd = myFirst + s;
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

// Adds a new element at the end of the vector, after its current last element.
// The content of val is copied to the new element.
// This effectively increases the vector size by one,
// which causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
void vector::push_back( const value_type &val )
{
   size_type originalSize = size();
   resize( originalSize + 1 );
   myFirst[ originalSize ] = val;
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign( const vector &right )
{
   if( this != &right ) // avoid self-assignment
   {
      size_type newSize = right.myLast - right.myFirst;
      //resize(newSize);
      if(newSize > capacity()){
         myFirst = new value_type[newSize];
         for(int i=0; i<newSize; i++){
            myFirst[i] = right.myFirst[i];
         }
         myLast = myFirst + newSize;
         myEnd = myLast;
      }
      else{
         for(int i=0; i<newSize; i++){
            myFirst[i] = right.myFirst[i];
         }
         myLast = myFirst + newSize;
      }
      
      //myEnd = myFirst + (right.myEnd - right.myFirst);
   }

   return *this; // enables x = y = z, for example
}

// Resizes the vector so that it contains newSize elements.
// If newSize is smaller than the current vector size,
// the content is reduced to its first newSize elements, removing those beyond.
// If newSize is greater than the current vector size,
// the content is expanded by inserting at the end
// as many elements as needed to reach a size of newSize.
// The new elements are initialized as 0.
// If newSize is also greater than the current vector capacity,
// an automatic reallocation of the allocated storage space takes place.
void vector::resize( const size_type newSize )
{
   size_type s = size();
   if(newSize < s){
      myLast = myFirst + newSize;
   }
   else if(newSize > s){
      if(newSize > capacity()){

         size_type now_c = capacity();
         int new_c = now_c;
         new_c = newSize;
         if(s * 2 < newSize) new_c = newSize;
         else new_c = s * 2;
         pointer newFirst;
         newFirst = new value_type[new_c]();
         for(int i=0; i<s; i++){
            newFirst[i] = myFirst[i];
         }
         myFirst = newFirst;
         myLast = myFirst + newSize;
         myEnd = myFirst + new_c;
      }
      else{
         for(int i=s; i<newSize; i++){
            myFirst[i] = 0;
         }
      }
      myLast = myFirst + newSize;
      //myEnd = myFirst + newSize;
   }
}

// Removes the last element in the vector,
// effectively reducing the container size by one.
void vector::pop_back()
{
   if( size() > 0 )
      --myLast;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear()
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::pointer vector::begin()
{
   return myFirst;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size()
{
   return ( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity()
{
   return ( myEnd - myFirst );
}

// Returns a reference to the element at position "pos" in the vector container.
vector::value_type& vector::element( const size_type pos )
{
   return myFirst[ pos ];
}