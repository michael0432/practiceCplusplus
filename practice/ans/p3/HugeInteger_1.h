// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "Vector.h" // include definition of class vector 

template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger );
public:
   HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with size n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger< T > &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger< T >& operator=( const HugeInteger< T > &right ); // assignment operator

   bool operator==( const HugeInteger< T > &right ) const; // less than or equal to

   bool operator<( const HugeInteger< T > &right ) const;  // less than

   bool operator<=( const HugeInteger< T > &right ) const; // less than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger< T > operator+( HugeInteger< T > &op2 );

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger< T > operator-( HugeInteger< T > &op2 );

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger< T > operator*( HugeInteger< T > &op2 );

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger< T > operator/( HugeInteger< T > &op2 );

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger< T > operator%( HugeInteger< T > &op2 );

   HugeInteger< T >& operator++(); // prefix increment operator

   HugeInteger< T > operator++( int ); // postfix increment operator

   HugeInteger< T >& operator--(); // prefix decrement operator

   HugeInteger< T > operator--( int ); // postfix decrement operator

   void convert( vector< T > &v ); // convert a vector of decimal digits into a HugeInteger
   bool isZero() const;           // return true if and only if all digits are zero
private:
   vector< T > integer;

   void divideByTen();            // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1
   void helpDecrement();          // decrements a HugeInteger by 1
}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger< T > &integerToCopy )
   : integer( integerToCopy.integer )
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( const HugeInteger< T > &right ) const
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<( const HugeInteger< T > &right ) const
{
   if(*this == right)
      return false;
   if(integer.size() > right.integer.size())
      return false;
   else if(integer.size() < right.integer.size())
      return true;
   else{
      for(int i=integer.size()-1; i>=0; i--){
         T v1 = *(integer.begin()+i);
         T v2 = *(right.integer.begin()+i);
         if(v1 < v2) return true;
         else if(v1 > v2) return false;
      }
   }
   return false;
} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( const HugeInteger< T > &right ) const
{
   return ( *this == right || *this < right );
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( HugeInteger< T > &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger< T > sum( sumSize );

   typename vector< T >::iterator it1 = integer.begin();
   typename vector< T >::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   typename vector< T >::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         *it3 -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-( HugeInteger< T > &op2 )
{
   HugeInteger< T > zero;

   if( *this == op2 )
      return zero;

   HugeInteger< T > difference( *this );
   typename vector< T >::iterator it1 = difference.integer.begin();
   typename vector< T >::iterator it2 = op2.integer.begin();
   int borrow = 0;
   for(; it1 != difference.integer.end(); it1++){
      int sub;
      if(it2 == op2.integer.end()){
         sub = 0;
      }
      else{
         sub = *it2;
      }
      int tmp = (*it1)-sub-borrow;
      if(tmp < 0){
         *it1 = tmp + 10;
         borrow = 1;
      }
      else{
         *it1 = tmp;
         borrow = 0;
      }
      if(it2 != op2.integer.end()){
         it2++;
      }
   }
   while(difference.integer.back() == 0 && !difference.isZero()){
      difference.integer.pop_back();
   }

   return difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*( HugeInteger< T > &op2 )
{
   HugeInteger< T > zero;
   if( isZero() || op2.isZero() )
      return zero;

	HugeInteger< T > product( integer.size() + op2.integer.size() );
   HugeInteger< T > my(*this);
   HugeInteger< T > other(op2);
   int cnt = 0;
   typename vector< T >::iterator it1 = my.integer.begin();
   typename vector< T >::iterator it2 = other.integer.begin();
   typename vector< T >::iterator it3 = product.integer.begin();

   int shift1 = 0, shift2 = 0;
   for(; it2 != other.integer.end(); it2++, shift2++){
      int carry = 0, shift1 = 0;
      int place;
      for(it1 = my.integer.begin(); it1 != my.integer.end(); it1++, shift1++){
         place = shift1 + shift2;
         int p = (*it1) * (*it2) + carry;
         if(p >= 10){
            it3 = product.integer.begin() + place;
            *it3 += p % 10;
            carry = p / 10;
         }
         else{
            it3 = product.integer.begin() + place;
            *it3 += p;
            carry = 0;
         }
      }
      if(carry != 0){
         it3 = product.integer.begin() + place + 1;
         *it3 += carry;
      }
      int c2 = 0;
      for(it3 = product.integer.begin(); it3 != product.integer.end(); it3++){
         int num = (*it3) + c2;
         if(num >= 10){
            c2 = num / 10;
            *it3 = num % 10;
         }
         else{
            *it3 = num;
            c2 = 0;
         }
      }
   }
   while(product.integer.back() == 0 && !product.isZero()){
      product.integer.pop_back();
   }
   return product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/( HugeInteger< T > &op2 )
{
   HugeInteger< T > zero;
   if( *this < op2 )
      return zero;

   HugeInteger< T > quotient( integer.size() + op2.integer.size() );
   
   int myDigit = integer.size();
   int otherDigit = op2.integer.size();
   int stepDigit = myDigit-otherDigit+1;
   HugeInteger< T > my(*this);
   HugeInteger< T > tmp(op2);
   HugeInteger< T > step(stepDigit);
   vector<T> v;
   for(int i=0; i<stepDigit; i++){
      if(i == 0)
         v.push_back(1);
      else
         v.push_back(0);
   }
   step.convert(v);
   while(stepDigit > 0 && !my.isZero()){
      //HugeInteger step(stepDigit);
      HugeInteger< T > thisStep = step*op2;
      if(thisStep<=my){
         HugeInteger< T > tmp_my = my-thisStep;
         HugeInteger< T > tmp_quotient = quotient+step;
         for(int i=0; i<my.integer.size(); i++){
            *(my.integer.begin()+i) = *(tmp_my.integer.begin()+i);
         }
         for(int i=0; i<quotient.integer.size(); i++){
            *(quotient.integer.begin()+i) = *(tmp_quotient.integer.begin()+i);
         }
         while(my.integer.back() == 0 && !my.isZero()){
            my.integer.pop_back();
         }
      }
      else{
         stepDigit -= 1;
         step.divideByTen();
      }
   }
   while(quotient.integer.back() == 0 && !quotient.isZero()){
      quotient.integer.pop_back();
   }
   
   return quotient;
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%( HugeInteger< T > &op2 )
{
   HugeInteger< T > quotient = ( *this ) / op2;
   HugeInteger< T > product = quotient * op2;
   HugeInteger< T > remainder = ( *this ) - product;
   return remainder;
}

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator++()
{
   helpIncrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++( int )
{
   HugeInteger< T > temp = *this; // hold current state of object
   helpIncrement();

   // return unincremented, saved, temporary object
   return temp; // value return; not a reference return
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator--()
{
   helpDecrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--( int )
{
   HugeInteger< T > temp = *this; // hold current state of object
   helpDecrement();

   // return unincremented, saved, temporary object
   return temp; // value return; not a reference return
}

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert( vector< T > &v )
{
   integer.resize( v.size() );
   typename vector< T >::iterator it1 = integer.end() - 1;
   typename vector< T >::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
   typename vector< T >::const_iterator it = integer.begin();
   for( ; it != integer.end(); ++it )
      if( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   typename vector< T >::iterator it = integer.begin() + 1;
   for( ; it != integer.end(); ++it )
      *( it - 1 ) = *it;
   integer.pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
   typename vector< T >::iterator it = integer.begin();
   ( *it )++;
   typename vector< T >::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      if( *it == 10 )
      {
         *it = 0;
         ( *it2 )++;
      }

   if( ( *it ) == 10 )
   {
      *( it ) = 0;
      integer.resize( integer.size() + 1 );
      it = integer.end();
      --it;
      *it = 1;
   }
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
   typename vector< T >::iterator it = integer.begin();
   for( ; *it == 0; ++it )
      *it = 9;

   ( *it )--;
}

// overloaded output operator for class HugeInteger
template< typename U >
ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger )
{
   typename vector< U >::iterator it = hugeInteger.integer.end() - 1;
   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}

#endif