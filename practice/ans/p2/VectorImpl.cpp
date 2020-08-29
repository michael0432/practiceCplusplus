#include "Vector.h" // include definition of class vector 
#include <cstddef>
#include <iostream>
#include <memory.h>
// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
   : myFirst(),
     myLast(),
     myEnd()
{
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector( const size_type count )
   : myFirst(),
     myLast(),
     myEnd()
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
   : myFirst(),
     myLast(),
     myEnd()
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
// The content of val is copied (or moved) to the new element.
// This effectively increases the container size by one,
// which causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
void vector::push_back( const value_type &val )
{
   size_type originalSize = size();
   resize( originalSize + 1 );
   myFirst[ originalSize ] = val;
}

// overloaded assignment operator
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
   }

   return *this; // enables x = y = z, for example
}

// Resizes the container so that it contains "newSize" elements.
// If "newSize" is smaller than the current container size,
// the content is reduced to its first "newSize" elements, removing those beyond.
// If "newSize" is greater than the current container size,
// the content is expanded by inserting at the end as many elements as needed
// to reach a size of "newSize".
// The new elements are initialized as 0.
// If "newSize" is also greater than the current container capacity,
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
void vector::clear() // erase all
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::iterator vector::begin()
{
   return myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::const_iterator vector::begin() const
{
   return const_iterator( myFirst );
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::iterator vector::end()
{
   return myLast;
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::const_iterator vector::end() const
{
   return const_iterator( myLast );
}

// Returns a const_iterator pointing to the first element in the container.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::const_iterator vector::cbegin() const
{
   return begin();
}

// Returns a const_iterator pointing to the past-the-end element in the container.
// If the container is empty, this function returns the same as vector::cbegin.
// The value returned shall not be dereferenced.
vector::const_iterator vector::cend() const
{
   return end();
}

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty() const
{
   return myFirst == myLast;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size() const
{
   return static_cast< size_type >( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity() const
{
   return static_cast< size_type >( myEnd - myFirst );
}

// Returns a reference to the first element in the vector.
// Calling this function on an empty container causes undefined behavior.
vector::value_type& vector::front()
{
   return *myFirst;
}

// Returns a reference to the first element in the vector.
// Calling this function on an empty container causes undefined behavior.
const vector::value_type& vector::front() const
{
   return *myFirst;
}

// Returns a reference to the last element in the vector.
// Calling this function on an empty container causes undefined behavior.
vector::value_type& vector::back()
{
   return myLast[ -1 ];
}

// Returns a reference to the last element in the vector.
// Calling this function on an empty container causes undefined behavior.
const vector::value_type& vector::back() const
{
   return myLast[ -1 ];
}