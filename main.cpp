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

struct DoubleType;
struct IntType;
struct FloatType
{
    float* a;
    FloatType( float varA ) : a( new float(varA) ) {}
    ~FloatType()
    {
        delete a;
        a = nullptr;
    }

    //taking FloatType as argument
    FloatType& add( const FloatType& rhs );
    FloatType& subtract( const FloatType& rhs );
    FloatType& multiply( const FloatType& rhs );
    FloatType& divide (const FloatType& rhs );

    //taking DoubleType as argument
    FloatType& add( const DoubleType& rhs );
    FloatType& subtract( const DoubleType& rhs );
    FloatType& multiply( const DoubleType& rhs );
    FloatType& divide (const DoubleType& rhs );

    //taking IntType as argument
    FloatType& add( const IntType& rhs );
    FloatType& subtract( const IntType& rhs );
    FloatType& multiply( const IntType& rhs );
    FloatType& divide (const IntType& rhs );
    
    //previous functions

    FloatType& add( float rhs )
    {
        *a += rhs;
        return *this;
    }

    FloatType& subtract( float rhs )
    {
        *a -= rhs;
        return *this;
    }

    FloatType& multiply( float rhs )
    {
        *a *= rhs;
        return *this;
    }

    FloatType& divide( float rhs )
    {
        if( rhs == 0.f )
        {
            std::cout << "warning, trying to divide by 0\n";
        }
        *a /= rhs;
        return *this;
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

    //taking FloatType as argument
    DoubleType& add( const FloatType& rhs );
    DoubleType& subtract( const FloatType& rhs );
    DoubleType& multiply( const FloatType& rhs );
    DoubleType& divide (const FloatType& rhs );

    //taking DoubleType as argument
    DoubleType& add( const DoubleType& rhs );
    DoubleType& subtract( const DoubleType& rhs );
    DoubleType& multiply( const DoubleType& rhs );
    DoubleType& divide (const DoubleType& rhs );

    //taking IntType as argument
    DoubleType& add( const IntType& rhs );
    DoubleType& subtract( const IntType& rhs );
    DoubleType& multiply( const IntType& rhs );
    DoubleType& divide (const IntType& rhs );

    //previous functions
    DoubleType& add( double rhs )
    {
        *a += rhs;
        return *this;
    }
    
    DoubleType& subtract( double rhs )
    {
        *a -= rhs;
        return *this;
    }

    DoubleType& multiply( double rhs )
    {
        *a *= rhs;
        return *this;
    }

    DoubleType& divide( double rhs )
    {
        if( rhs == 0 )
        {
            std::cout << "warning, trying to divide by 0\n";
        }
        *a /= rhs;
        
        return *this;
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

    //taking FloatType as argument
    IntType& add( const FloatType& rhs );
    IntType& subtract( const FloatType& rhs );
    IntType& multiply( const FloatType& rhs );
    IntType& divide (const FloatType& rhs );

    //taking DoubleType as argument
    IntType& add( const DoubleType& rhs );
    IntType& subtract( const DoubleType& rhs );
    IntType& multiply( const DoubleType& rhs );
    IntType& divide (const DoubleType& rhs );

    //taking IntType as argument
    IntType& add( const IntType& rhs );
    IntType& subtract( const IntType& rhs );
    IntType& multiply( const IntType& rhs );
    IntType& divide (const IntType& rhs );

    //previous functions
    IntType& add( int rhs )
    {
        *a += rhs;
        return *this;
    }

    IntType& subtract( int rhs )
    {
        *a -= rhs;
        return *this;
    }

    IntType& multiply( int rhs )
    {
        *a *= rhs;
        return *this;
    }

    IntType& divide( int rhs )
    {
        if( rhs == 0 )
        {
            std::cout << "warning, trying to divide by 0\n";
            std::cout << "Current value of IntType: ";
            return *this;
        }
        *a /= rhs;
        return *this;
    }
};

// FUNCTION DEFINITIONS //

//FloatType
//taking FloatType as argument
FloatType& FloatType::add( const FloatType& rhs )
{
    return add( *rhs.a );
}

FloatType& FloatType::subtract( const FloatType& rhs )
{
    return subtract( *rhs.a );
}

FloatType& FloatType::multiply( const FloatType& rhs )
{
    return multiply( *rhs.a );
}

FloatType& FloatType::divide (const FloatType& rhs )
{
    return divide( *rhs.a );
}

//taking DoubleType as argument
FloatType& FloatType::add( const DoubleType& rhs )    
{
    return add( *rhs.a );
}

FloatType& FloatType::subtract( const DoubleType& rhs )    
{
    return subtract( *rhs.a );
}

FloatType& FloatType::multiply( const DoubleType& rhs )    
{
    return multiply( *rhs.a );
}

FloatType& FloatType::divide (const DoubleType& rhs )    
{
    return divide( *rhs.a );
}

//taking IntType as argument
FloatType& FloatType::add( const IntType& rhs )    
{
    return add( *rhs.a );
}

FloatType& FloatType::subtract( const IntType& rhs )    
{
    return subtract( *rhs.a );
}

FloatType& FloatType::multiply( const IntType& rhs )    
{
    return multiply( *rhs.a );
}

FloatType& FloatType::divide (const IntType& rhs )    
{
    return divide( *rhs.a );
}

//DoubleType
//taking FloatType as argument
DoubleType& DoubleType::add( const FloatType& rhs )
{
    return add( *rhs.a );
}

DoubleType& DoubleType::subtract( const FloatType& rhs )
{
    return subtract( *rhs.a );
}

DoubleType& DoubleType::multiply( const FloatType& rhs )
{
    return multiply( *rhs.a );
}

DoubleType& DoubleType::divide (const FloatType& rhs )
{
    return divide( *rhs.a );
}

//taking DoubleType as argument
DoubleType& DoubleType::add( const DoubleType& rhs )    
{
    return add( *rhs.a );
}

DoubleType& DoubleType::subtract( const DoubleType& rhs )    
{
    return subtract( *rhs.a );
}

DoubleType& DoubleType::multiply( const DoubleType& rhs )    
{
    return multiply( *rhs.a );
}

DoubleType& DoubleType::divide (const DoubleType& rhs )    
{
    return divide( *rhs.a );
}

//taking IntType as argument
DoubleType& DoubleType::add( const IntType& rhs )    
{
    return add( *rhs.a );
}

DoubleType& DoubleType::subtract( const IntType& rhs )    
{
    return subtract( *rhs.a );
}

DoubleType& DoubleType::multiply( const IntType& rhs )    
{
    return multiply( *rhs.a );
}

DoubleType& DoubleType::divide (const IntType& rhs )    
{
    return divide( *rhs.a );
}

//IntType
//taking FloatType as argument
IntType& IntType::add( const FloatType& rhs )
{
    return add( *rhs.a );
}

IntType& IntType::subtract( const FloatType& rhs )
{
    return subtract( *rhs.a );
}

IntType& IntType::multiply( const FloatType& rhs )
{
    return multiply( *rhs.a );
}

IntType& IntType::divide (const FloatType& rhs )
{
    return divide( *rhs.a );
}

//taking DoubleType as argument
IntType& IntType::add( const DoubleType& rhs )    
{
    return add( *rhs.a );
}

IntType& IntType::subtract( const DoubleType& rhs )    
{
    return subtract( *rhs.a );
}

IntType& IntType::multiply( const DoubleType& rhs )    
{
    return multiply( *rhs.a );
}

IntType& IntType::divide (const DoubleType& rhs )    
{
    return divide( *rhs.a );
}

//taking IntType as argument
IntType& IntType::add( const IntType& rhs )    
{
    return add( *rhs.a );
}

IntType& IntType::subtract( const IntType& rhs )    
{
    return subtract( *rhs.a );
}

IntType& IntType::multiply( const IntType& rhs )    
{
    return multiply( *rhs.a );
}

IntType& IntType::divide (const IntType& rhs )    
{
    return divide( *rhs.a );
}

void divider()
{
    std::cout << "\n\n===============================\n\n";
}

int main()
{ 
    divider();

    FloatType ft(3.2);
    DoubleType dt(8.473276);
    IntType it(19);

    std::cout << "The starting value of FloatType ft is: " << *ft.a << std::endl;
    std::cout << "The starting value of DoubleType dt is: " << *dt.a << std::endl;
    std::cout << "The starting value of IntType it is: " << *it.a << std::endl;

    divider();

    std::cout << "We can add (5.4) to ft and multiply it by (6) which equals: " << *ft.add(5.4).multiply(6).a << std::endl;

    std::cout << "We can divde dt by (2.2) and add (0.86) which equals: " << *dt.divide(2.2).add(0.86).a << std::endl;

    std::cout << "We can subtract (10) from it and multiply by (12) and divide by ft(" << *ft.a << ") which equals: " << *it.subtract(10).multiply(102).divide(ft).a << std::endl;

    divider();

    std::cout << "We will find that we cannot divide it by a number less than 1:\n"; 
    std::cout << "it(" << *it.a << ") divided by 0.2 throws an error:\n";
    std::cout << *it.divide(0.2).a << std::endl;

    divider();

    std::cout << "But we can use all types together.  The result of 'dt' time 'it' plus 'ft' is: " << *dt.multiply(it).add(ft).a <<std::endl;

    divider();

    std::cout << "good to go!" << std::endl;
}
