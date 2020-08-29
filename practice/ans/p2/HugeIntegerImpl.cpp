// Member-function definitions for class HugeInteger
#include <iostream>
#include <cstddef>
#include <memory.h>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
   : integer( 1 )
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1 )
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::assign( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer.assign( right.integer );

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::equal( const HugeInteger &right ) const
{
   if(right.integer.size() != integer.size()){
      return false;
   }
   else{
      for(int i=integer.size()-1; i>=0; i--){
         int v1 = *(integer.begin()+i);
         int v2 = *(right.integer.begin()+i);
         if(v1 != v2) return false;
      }
   }
   return true;
   
} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::less( const HugeInteger &right ) const
{
   if(equal(right)) return false;
   if(integer.size() > right.integer.size()){
      return false;
   }
   else if(integer.size() < right.integer.size()){
      return true;
   }
   else{
      for(int i=integer.size()-1; i>=0; i--){
         int v1 = *(integer.begin()+i);
         int v2 = *(right.integer.begin()+i);
         if(v1 < v2) return true;
         else if(v1 > v2) return false;
      }
   }
   return false;
} // end function less

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual( const HugeInteger &right ) const
{
   return ( less( right ) || equal( right ) );
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add( HugeInteger &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   vector::iterator it1 = integer.begin();
   vector::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   vector::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::subtract( HugeInteger &op2 )
{
   HugeInteger zero;

   if( equal( op2 ) )
      return zero;
   
   HugeInteger difference( *this );

   vector::iterator it1 = difference.integer.begin();
   vector::iterator it2 = op2.integer.begin();
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
} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::multiply( HugeInteger &op2 )
{
   HugeInteger zero;
   
   if( isZero() || op2.isZero() )
      return zero;

   unsigned int productSize = integer.size() + op2.integer.size();
   HugeInteger product( productSize );
   HugeInteger my(*this);
   HugeInteger other(op2);
   int cnt = 0;
   vector::iterator it1 = my.integer.begin();
   vector::iterator it2 = other.integer.begin();
   vector::iterator it3 = product.integer.begin();

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
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::divide( HugeInteger &op2 )
{
   HugeInteger zero;
   if( less( op2 ) )
      return zero;
   HugeInteger my(*this);
   HugeInteger tmp(op2);
   int myDigit = integer.size();
   int otherDigit = op2.integer.size();
   int stepDigit = myDigit-otherDigit+1;
   HugeInteger quotient(this->integer.size()), step(stepDigit);
   vector v;
   for(int i=0; i<stepDigit; i++){
      if(i == 0)
         v.push_back(1);
      else
         v.push_back(0);
   }
   step.convert(v);
   while(stepDigit > 0 && !my.isZero()){
      //HugeInteger step(stepDigit);
      HugeInteger thisStep = step.multiply(op2);
      if(thisStep.lessEqual(my)){
         HugeInteger tmp_my = my.subtract(thisStep);
         HugeInteger tmp_quotient = quotient.add(step);
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
} // end function divide

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::modulus( HugeInteger &op2 )
{
   HugeInteger quotient = divide( op2 );
   HugeInteger product = quotient.multiply( op2 );
   HugeInteger remainder = subtract( product );
   return remainder;
}

// convert a vector of decimal digits into a HugeInteger
void HugeInteger::convert( vector &v )
{
   integer.resize( v.size() );
   vector::iterator it1 = integer.end() - 1;
   vector::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
   for( vector::iterator it = integer.begin(); it != integer.end(); ++it )
      if ( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   vector::iterator it = integer.begin();
   vector::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.pop_back();
}

// overloaded output operator
void HugeInteger::output( ostream &outFile )
{
   vector::iterator it = integer.end() - 1;
   for( ; it != integer.begin() - 1; --it )
      if( *it < 10 )
         outFile << *it;
   outFile << endl;
} // end function output