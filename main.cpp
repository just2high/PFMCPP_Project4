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

#include <iostream>
#include <cmath>

struct DoubleType;
struct IntType;
struct FloatType;

struct Point
{
    Point( float a, float b ) : x( a ), y( b ) {}
    Point( const FloatType& ft );
    Point( const DoubleType& dt );
    Point( const IntType& it );

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
    Point& multiply( const FloatType& ft );
    Point& multiply( const DoubleType& dt );
    Point& multiply( const IntType& it );

    void toString()
    {
        std::cout << "The x coordinate is: " << x << "\nThe y coordinate is: " << y << std::endl;
    }

private:
    float x{0}, y{0};
};

struct FloatType
{
    FloatType( float varA ) : a( new float(varA) ) {}
    ~FloatType()
    {
        delete a;
        a = nullptr;
    }

    operator float() const { return *a; }

    FloatType& add( float rhs );
    FloatType& subtract( float rhs );
    FloatType& multiply( float rhs );
    FloatType& divide( float rhs );

    FloatType& pow( float rhs );
    FloatType& pow( const FloatType& rhs );
    FloatType& pow( const DoubleType& rhs );
    FloatType& pow( const IntType& rhs );

    private:
    float* a;

    FloatType& powInternal( const float value );
};

FloatType& FloatType::add( float rhs )
{
    *a += rhs;
    return *this;
}

FloatType& FloatType::subtract( float rhs )
{
    *a -= rhs;
    return *this;
}

FloatType& FloatType::multiply( float rhs )
{
    *a *= rhs;
    return *this;
}

FloatType& FloatType::divide( float rhs )
{
    if( rhs == 0.f )
    {
        std::cout << "warning, trying to divide by 0\n";
    }
    *a /= rhs;
    return *this;
}

struct DoubleType
{
    DoubleType ( double varA ) : a( new double(varA) ) {}
    ~DoubleType()
    {
        delete a;
        a = nullptr;
    }

    operator double() const { return *a; }

    DoubleType& add( double rhs );
    DoubleType& subtract( double rhs );
    DoubleType& multiply( double rhs );
    DoubleType& divide( double rhs );

    DoubleType& pow( double rhs );
    DoubleType& pow( const FloatType& rhs );
    DoubleType& pow( const DoubleType& rhs );
    DoubleType& pow( const IntType& rhs );

    private:
    double* a;

    DoubleType& powInternal( const double value );
};

DoubleType& DoubleType:: add( double rhs )
{
    *a += rhs;
    return *this;
}

DoubleType& DoubleType::subtract( double rhs )
{
    *a -= rhs;
    return *this;
}

DoubleType& DoubleType::multiply( double rhs )
{
    *a *= rhs;
    return *this;
}

DoubleType& DoubleType::divide( double rhs )
{
    if( static_cast<int>(rhs) == 0 )
    {
        std::cout << "warning, trying to divide by 0\n";
    }
    *a /= rhs;
    
    return *this;
}

struct IntType
{
    IntType( int varA ) : a( new int(varA) ) {}
    ~IntType()
    {
        delete a;
        a = nullptr;
    }

    operator int() const { return *a; }

    IntType& add( int rhs );
    IntType& subtract( int rhs );
    IntType& multiply( int rhs );
    IntType& divide( int rhs );

    IntType& pow( int rhs );
    IntType& pow( const FloatType& rhs );
    IntType& pow( const DoubleType& rhs );
    IntType& pow( const IntType& rhs );

    private:
    int* a;
    
    IntType& powInternal( const int value );
};

IntType& IntType::add( int rhs )
{
    *a += rhs;
    return *this;
}

IntType& IntType::subtract( int rhs )
{
    *a -= rhs;
    return *this;
}

IntType& IntType::multiply( int rhs )
{
    *a *= rhs;
    return *this;
}

IntType& IntType::divide( int rhs )
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

/* Power Function Definitions */

FloatType& FloatType::powInternal( const float value )
{
    if ( a != nullptr )
        *a = std::pow( *a, value );

    return *this;
}

FloatType& FloatType::pow( float rhs )
{
    return powInternal( rhs );
}

FloatType& FloatType::pow( const FloatType& rhs )
{
    return powInternal( static_cast<float>(rhs) );
}

FloatType& FloatType::pow( const DoubleType& rhs )
{
    return powInternal( static_cast<float>(rhs) );
}

FloatType& FloatType::pow( const IntType& rhs )
{
    return powInternal( static_cast<float>(rhs) );
}

//===========================================//

DoubleType& DoubleType::powInternal( const double value )
{
    if ( a != nullptr )
        *a = std::pow( *a, value );

    return *this;
}

DoubleType& DoubleType::pow( double rhs )
{
    return powInternal( rhs );
}

DoubleType& DoubleType::pow( const FloatType& rhs )
{
    return powInternal( static_cast<double>(rhs) );
}

DoubleType& DoubleType::pow( const DoubleType& rhs )
{
    return powInternal( static_cast<double>(rhs) );
}

DoubleType& DoubleType::pow( const IntType& rhs )
{
    return powInternal( static_cast<double>(rhs) );
}

//===========================================//

IntType& IntType::powInternal( const int value )
{
    if ( a != nullptr )
        *a = std::pow( *a, value );

    return *this;
}

IntType& IntType::pow( int rhs )
{
    return powInternal( rhs );
}

IntType& IntType::pow( const FloatType& rhs )
{
    return powInternal( static_cast<int>(rhs) );
}

IntType& IntType::pow( const DoubleType& rhs )
{
    return powInternal( static_cast<int>(rhs) );
}

IntType& IntType::pow( const IntType& rhs )
{
    return powInternal( static_cast<int>(rhs) );
}

/* Point UDT Implementation */

Point::Point( const FloatType& ft ) : Point( ft, ft) {}

Point::Point( const DoubleType& dt ) : Point ( static_cast<float>(dt), static_cast<float>(dt) ) {}

Point::Point( const IntType& it ) : Point ( static_cast<int>(it), static_cast<int>(it) ) {}

Point& Point::multiply( const FloatType& ft )
{
    return multiply( static_cast<float>(ft) );
}

Point& Point::multiply( const DoubleType& dt )
{
    return multiply( static_cast<float>(dt) );
}

Point& Point::multiply( const IntType& it )
{
    return multiply( static_cast<float>(it) );
}

void divider()
{
    std::cout << "\n\n===============================\n\n";
}

int main()
{ 
    divider();

    FloatType ft(3.2f);
    DoubleType dt(8.473276);
    IntType it(19);

    std::cout << "The starting value of FloatType ft is: " << static_cast<float>(ft) << std::endl;
    std::cout << "The starting value of DoubleType dt is: " << static_cast<double>(dt) << std::endl;
    std::cout << "The starting value of IntType it is: " << static_cast<int>(it) << std::endl;

    divider();

    std::cout << "We can add (5.4) to ft and multiply it by (6) which equals: " << static_cast<float>( ft.add(5.4f).multiply(6) ) << std::endl;

    std::cout << "We can divde dt by (2.2) and add (0.86) which equals: " << static_cast<double>(dt.divide(2.2).add(0.86) ) << std::endl;

    std::cout << "We can subtract (10) from it and multiply by (12) and divide by ft(" << static_cast<float>(ft) << ") which equals: " << static_cast<int>( it.subtract(10).multiply(102).divide( static_cast<int>(ft) ) ) << std::endl;

    divider();

    std::cout << "We will find that we cannot divide it by a number less than 1:\n"; 
    std::cout << "it(" << static_cast<int>(it) << ") divided by 0.2 throws an error:\n";
    std::cout << it.divide(static_cast<int>(0.2)) << std::endl;

    divider();

    std::cout << "But we can use all types together.  The result of 'dt' time 'it' plus 'ft' is: " << static_cast<double>( dt.multiply( static_cast<int>(it) ).add( static_cast<double>(ft) ) ) <<std::endl;

    divider();

    std::cout << "Ft is currently: " << static_cast<float>(ft) << std::endl;
    std::cout << "ft pow of 3: " << ft.pow( 3 ) << std::endl;
    std::cout << "it is currently: " << static_cast<int>(it) << std::endl;
    std::cout << "it pow of 2: " << it.pow( 2 ) << std::endl;
    std::cout << "dt is currently: " << static_cast<double>(dt) << std::endl;
    std::cout << "dt pow of 1.2: " << dt.pow( 1.2 ) << std::endl;

    std::cout << "Chaining makes ridiculous numbers: " << ft.pow(it).pow(3) << std::endl;

    divider();

    Point pt( 2.f, 3.f );

    std::cout << "pt's initial points are:\n";
    pt.toString();

    std::cout << "pt multiplied by ft is:\n";
    pt.multiply(ft);
    pt.toString();

    std::cout << "then pt multiplied by it is:\n";
    pt.multiply(it);
    pt.toString();

    DoubleType dtp( 5.67893 );
    Point pdt( dtp );

    divider();

    std::cout << "pdt initialized with a DoubleType has these points:\n";
    pdt.toString();
    std::cout << "And then multiplied by the initializing DoubleType moves the point:\n";
    pdt.multiply(dtp);
    pdt.toString();

    divider();

    std::cout << "good to go!" << std::endl;
}
