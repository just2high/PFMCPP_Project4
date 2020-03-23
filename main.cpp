/*
Project 4: Part 4 / 9
 Chapter 4 Part 7
 Function/Constructor Overloading

 Create a branch named Part4
 
 Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add pow() functions, and a powInternal() function to each of your UDTs
     a) your pow() functions should call powInternal()
     b) add a pow() whose argument type is the primitive your UDT owns.  the argument should be passed by copy.
     c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
         the argument should be passed as const ref
         i.e. if you had UDTs named IntType, FloatType, DoubleType
             in your IntType class, you'd have:
                 pow(const IntType&),
                 pow(const FloatType&),
                 pow(const DoubleType&),
                 and pow(int)
     d) be sure to remember the rules about what member functions can be called on const objects.
             (const objects can only call their const member functions)
     e) the pow() functions should be chainable.
 
 2) your powInternal() function should do something like this in its body:    *val = std::pow( *val, arg );
         where 'arg' is the passed-in type, converted to whatever type your object is holding.
             if your UDT owns an int, then arg would be an int.
             if your UDT owns a float, then arg would be a float.
         std::pow's documentation is found here: https://en.cppreference.com/w/cpp/numeric/math/pow so be sure to include
             the proper header file listed there.
         powInternal() should be chainable.
 
 3) modify the Point class below to have Constructors that accept your UDTs.
     a) make the Constructor's UDT arguments initialize the Point class's two member variables.
     b) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     c) add a toString() function to the Point class that prints out the x and y members via std::cout.
 
 4) Add to main()
     a) use your new pow() function in main for all of your types and print out the results.
     b) use the Point class in main and multiply some Point instances with your UDTs
     c) use the Point::toString() function to print out the results.
 
 
 5) make sure it compiles without errors.
 
 You will need to use Forward Declaration and out-of-class definitions to complete this.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

struct Point
{
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
private:
    float x{0}, y{0};
};



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
