/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */

struct A {};

struct HeapA
{
    A* a;

    HeapA() : a( new A ) {}
    ~HeapA()
    {
        delete a;
        a = nullptr;
    }
};

 /*
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers  
         IntType should own a heap-allocated int, for example.
 
 2) give it a constructor that takes the appropriate primitive
    this argument will initialize the owned primitive's value.
         i.e. if you're owning an int on the heap, your ctor argument will initialize that heap-allocated int's value.
 
 3) modify those add/subtract/divide/multiply member functions from chapter 2 on it
         a) make them modify the owned numeric type
         b) set them up so they can be chained together.
             i.e.
             DoubleType dt(3.5);
             dt.add(3.0).multiply(-2.5).divide(7.2); //an example of chaining
 
 4) write add/subtract/divide/multiply member functions for each type that take your 3 UDTs
        These are in addition to your member functions that take primitives
        for example, IntType::divide(const DoubleType& dt);
        These functions should return the result of calling the function that takes the primitive.
     
 
 5) print out the results with some creative couts 
    i.e.
         FloatType ft(0.1f);
         IntType it(3);
         std::cout << "adding 3 and subtracting 'it' from 'ft' results in the following value: " << *ft.add(2.f).subtract( it ).value << std::endl;  //note the dereference of the `value` member of `ft`
 
 6) Don't let your heap-allocated owned type leak!
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */


#include <iostream>

struct FloatType
{
    float* a;
    FloatType( float varA ) : a( new float(varA) ) {}
    ~FloatType()
    {
        delete a;
        a = nullptr;
    }
    
    //previous functions

    float add( float lhs, float rhs )
    {
        return lhs + rhs;
    }

    float subtract( float lhs, float rhs )
    {
        return lhs + rhs;
    }

    float multiply( float lhs, float rhs )
    {
        return lhs * rhs;
    }

    float divide( float lhs, float rhs )
    {
        if( rhs == 0.f )
        {
            std::cout << "warning, trying to divide by 0\n";
        }
        return lhs / rhs;
    }
};

struct DoubleType
{
    double* a;

    DoubleType ( double varA ) : a( new double(varA) ) {}
    ~DoubleType()
    {
        delete a;
        a = nullptr;
    }

    double add( double lhs, double rhs )
    {
        return lhs + rhs;
    }
    
    double subtract( double lhs, double rhs )
    {
        return lhs - rhs;
    }

    double multiply( double lhs, double rhs )
    {
        return lhs * rhs;
    }

    double divide( double lhs, double rhs )
    {
        if( rhs == 0 )
        {
            std::cout << "warning, trying to divide by 0\n";
        }
        return lhs / rhs;
    }
};

struct IntType
{
    int* a;

    IntType( int varA ) : a( new int(varA) ) {}
    ~IntType()
    {
        delete a;
        a = nullptr;
    }

    int add( int lhs, int rhs )
    {
        return lhs + rhs;
    }

    int subtract( int lhs, int rhs )
    {
        return lhs - rhs;
    }

    int multiply( int lhs, int rhs )
    {
        return lhs * rhs;
    }

    int divide( int lhs, int rhs )
    {
        if( rhs == 0 )
        {
            std::cout << "warning, trying to divide by 0\n";
            return 0;
        }
        return lhs / rhs;
    }
};


int main()
{
    FloatType ft;
    
    std::cout << "result of ft.add(): " << ft.add( 4.3f, 3.9f ) << std::endl;
    std::cout << "result of ft.subtract(): " << ft.subtract( 22.3f, 11.2f ) << std::endl;
    std::cout << "result of ft.multiply(): " << ft.multiply ( 1.2f, 3.4f ) << std::endl;
    std::cout << "result of ft.divide(): " << ft.divide ( 4.6f, 0.9f ) << std::endl;

    std::cout << "\n";

    DoubleType dt;

    std::cout << "result of dt.add(): " << dt.add( 0.23154, 0.3425 ) << std::endl;
    std::cout << "result of dt.subtract(): " << dt.subtract( 203.47392, 1000.9372 ) << std::endl;
    std::cout << "result of dt.multiply(): " << dt.multiply ( 4.5677, 3.0987 ) << std::endl;
    std::cout << "result of dt.divide(): " << dt.divide ( 5.678, 0 ) << std::endl;

    std::cout << "\n";

    IntType it;

    std::cout << "result of it.add(): " << it.add( 8293471, 8982347 ) << std::endl;
    std::cout << "result of it.subtract(): " << it.subtract( 32739523, 83294 ) << std::endl;
    std::cout << "result of it.multiply(): " << it.multiply ( 44, 3098 ) << std::endl;
    std::cout << "result of it.divide(): " << it.divide ( 99, 0 ) << std::endl;

    std::cout << "\n";

    std::cout << "good to go!" << std::endl;
}
