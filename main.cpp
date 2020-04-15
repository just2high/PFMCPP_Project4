/*
Project 4 - Part 6 / 9
Video: Chapter 5 Part 3
 
Create a branch named Part6
 
 Lambdas
 
    Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add two member functions named "apply()" to each of your Heap-Allocated Numeric Type wrappers.
         both apply() functions should work with chaining
 
 2) One of the apply() functions should takes a std::function<> object as the function argument.
    the std::function<> object should return *this;
 
 3) the other apply() function should take a function pointer. 
    the function pointer should return void.
 
 4) Make both of the member functions's Callable Function Parameter use your owned object as it's single parameter.
         e.g. if you manage your owned object via std::unique_ptr<T>, you'd use this for your std::function argument:
             std::function< OwnedT&(std::unique_ptr<T>&)>
             
         if you managed your owned object via a raw pointer, you'd use this for your std::function argument:
             std::function<OwnedT&(T&)>    
 
 5) call that Callable Function Parameter in the apply() member function.
         be sure to practice safe std::function usage (make sure it's not a nullptr function being called)
 
 6) Using one instance of each of your Heap-Allocated Numeric Type wrappers: Call your apply() member function twice in main()
         a) once with a lambda as the argument
         b) once with a free function as the argument.
         c) there will be a total of 6 calls to apply() in main(), 2x per HeapType, IntType, DoubleType instance.
         If this confuses you, rewatch the video where I pass a free function in to a function that wants a function pointer
 
 8) Make your lambda & free function update the value of your held object
 
 9) use std::cout statements to print out the results of calling apply()
 
build/run to make sure you don't have any errors

Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 
 If you need to see an example, look at https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part6Example.cpp
 */






#include <iostream>
#include <cmath>
#include <functional>

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

    Point& operator*=( float m )
    {
        return multiply( m );
    }

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

    void apply( std::function<FloatType&( float )>add );
    void apply();

    FloatType& add( float rhs );
    FloatType& subtract( float rhs );
    FloatType& multiply( float rhs );
    FloatType& divide( float rhs );

    FloatType& pow( float rhs );
    FloatType& pow( const FloatType& rhs );
    FloatType& pow( const DoubleType& rhs );
    FloatType& pow( const IntType& rhs );

    FloatType& operator+=( float rhs )
    {
        *a += rhs;
        return *this;
    }

    FloatType& operator -=( float rhs )
    {
        *a -= rhs;
        return *this;
    }

    FloatType& operator *=( float rhs )
    {
        *a *= rhs;
        return *this;
    }

    FloatType& operator/=( float rhs )
    {
        *a /= rhs;
        return*this;
    } 

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

    DoubleType& operator+=( double rhs )
    {
        *a += rhs;
        return *this;
    }

    DoubleType& operator -=( double rhs )
    {
        *a -= rhs;
        return *this;
    }

    DoubleType& operator *=( double rhs )
    {
        *a *= rhs;
        return *this;
    }

    DoubleType& operator/=( double rhs )
    {
        *a /= rhs;
        return*this;
    } 


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

    IntType& operator+=( int rhs )
    {
        *a += rhs;
        return *this;
    }

    IntType& operator -=( int rhs )
    {
        *a -= rhs;
        return *this;
    }

    IntType& operator *=( int rhs )
    {
        *a *= rhs;
        return *this;
    }

    IntType& operator/=( int rhs )
    {
        if( rhs == 0 )
        {
            std::cout << "warning, trying to divide by 0\n";
            std::cout << "Current value of IntType: ";
            return *this;
        }
        *a /= rhs;
        return*this;
    } 

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
        *a = static_cast<int>( std::pow( *a, value ) );

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

    std::cout << "The starting value of FloatType 'ft' is: " << static_cast<float>(ft) << std::endl;
    std::cout << "The starting value of DoubleType 'dt' is: " << static_cast<double>(dt) << std::endl;
    std::cout << "The starting value of IntType 'it' is: " << static_cast<int>(it) << std::endl;

    divider();

    ft += 5.4f;
    ft *= 6;

    std::cout << "We can add (5.4) to 'ft' and multiply 'it' by (6) which equals: " << static_cast<float>(ft) << std::endl;
 
    dt /= 2.2;
    dt += 0.86;

    std::cout << "We can divde 'dt' by (2.2) and add (0.86) which equals: " << static_cast<double>(dt) << std::endl;

    it -= 10;
    it *= 12;
    it /= static_cast<int>(ft);

    std::cout << "We can subtract (10) from 'it' and multiply by (12) and divide by ft(" << static_cast<float>(ft) << ") which equals: " << static_cast<int>(it) << std::endl;
 
    divider();

    std::cout << "We will find that we cannot divide 'it' by a number less than 1:\n"; 
    std::cout << "it(" << static_cast<int>(it) << ") divided by 0.2 throws an error:\n";
    std::cout << ( it /= static_cast<int>(0.2) ) << std::endl;

    divider();

    dt *= static_cast<double>(it);
    dt += static_cast<double>(ft);

    std::cout << "But we can use all types together.  The result of 'dt' times 'it' plus 'ft' is: " << static_cast<double>(dt) <<std::endl;

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

    pt *= static_cast<float>(ft);

    std::cout << "pt multiplied by ft is:\n";
    // pt.multiply(ft);
    pt.toString();

    pt *= static_cast<float>(it);


    std::cout << "then pt multiplied by it is:\n";
    // pt.multiply(it);
    pt.toString();

    DoubleType dtp( 5.67893 );
    Point pdt( dtp );

    divider();

    std::cout << "pdt initialized with a DoubleType has these points:\n";
    pdt.toString();
    std::cout << "And then multiplied by the initializing DoubleType moves the point:\n";
    // pdt.multiply(dtp);

    pdt *= static_cast<float>(dtp);

    pdt.toString();

    divider();

    std::cout << "good to go!" << std::endl;
}
