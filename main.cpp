/*
Prject 4: Part 8 / 9
 video: Chapter 5 Part 6 Task 

Create a branch named Part8

 R-Values L-Values Move Semantics.

 This Task is going to demonstrate R-Values and writing Generic Code

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 
 
 Edit your Chapter 5 Part 4 Task and replace its instructions with these instructions
 
 Your job is to replace the owned type (the primitive specified by your template argument) from the 
     Templated Class you created in Ch5 p04 with a struct named Temporary that can behave ENTIRELY as a temporary object.
 
 That means you must use conversion functions to interact with what it owns.
 
 You need to figure out how to use conversion functions to be able to GET and SET the 'value' member variable.
    hint: conversion functions can return by value and also by ___...
  
 1) Here is a starting point for how to implement your Temporary struct.
 */

#include <typeinfo>
template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    /*
     revise these conversion functions to read/write to 'v' here
     hint: what qualifier do read-only functions usually have?
     */
    const operator NumericType() { /* read-only function */ return v; }
    operator NumericType&() { /* read/write function */ return v; }
private:
    static int counter;
    NumericType v;
};

/*
 2) add the definition of Temporary::counter here, which is a static variable and must be defined outside of the class.
    Remember the rules about how to define a Template member variable/function outside of the class.
*/

template<typename NumericType>
int Temporary::<NumericType>::counter = 0;

/*
 3) You'll need to template your overloaded math operator functions in your Templated Class from Ch5 p04
    use static_cast to convert whatever type is passed in to your template's NumericType before performing the +=, -=, etc.  here's an example implementation:
 */
namespace example
{
template<typename NumericType>
struct Numeric
{
    //snip
    template<typename OtherType>
    Numeric& operator-=(const OtherType& o) 
    { 
        *value -= static_cast<NumericType>(o); 
        return *this; 
    }
    //snip
};
}
// COMPLETE
/*
 4) remove your specialized <double> template of your Numeric<T> class from the previous task (ch5 p04)
    replace the 2 apply() functions in your Numeric<T> with the single templated apply() function from the specialized <double> template.
 */
// COMPLETE
/*
 5) Template your pow() function the same way you templated the overloaded math operators
    Remove the call to powInternal() and just call std::pow() directly.
    you'll need to static_cast<> the pow() argument the same way you did in the overloaded math operators, when you pass it to std::pow()
 */
/*
 
 6) Finally, your conversion function in your templated class is going to be returning this Temporary, 
        so you should probably NOT return by copy if you want your templated class's owned object to be modified by any math operation.
    See the previous hint for implementing the conversion functions for the Temporary if you want to get the held value
*/


/*
 7)   replace main() with the main below

 If you did everything correctly, this is the output you should get:
 
I'm a Temporary<f> object, #0
I'm a Temporary<i> object, #0
I'm a Temporary<d> object, #0
f: -1.89
d: -3.024
i: -9
Point { x: -1.89, y: -9 }
d: 3.024
I'm a Temporary<d> object, #1
I'm a Temporary<d> object, #2
d: 1.49519e+08
Point { x: -2.82591e+08, y: -1.34567e+09 }
I'm a Temporary<f> object, #1
I'm a Temporary<i> object, #1
I'm a Temporary<i> object, #2
I'm a Temporary<i> object, #3
intNum: 5
I'm a Temporary<f> object, #2
f squared: 3.5721
I'm a Temporary<f> object, #3
f cubed: 45.5796
I'm a Temporary<d> object, #3
d squared: 2.2356e+16
I'm a Temporary<d> object, #4
d cubed: 1.11733e+49
I'm a Temporary<i> object, #4
i squared: 81
I'm a Temporary<i> object, #5
i cubed: 531441

Use a service like https://www.diffchecker.com/diff to compare your output. 
*/

#include <iostream>
#include <cmath>
#include <functional>
#include <memory>
#include <limits>
#include <typeinfo>


template <typename T>
struct Numeric
{
    using Primitive = T;

    Numeric( Primitive varA ) : a( new Primitive(varA) ) {}

    operator Primitive() const { return *a; }

    template<typename FuncPtr>
    Numeric& apply( FuncPtr func )
    {
        func( *a );
        return *this;
    }

    template<typename OtherType>
    Numeric& pow( const OtherType& rhs )
    {
        if( a != nullptr )
            *a = static_cast<Primitive>( std::pow( *a, rhs ) );
        return *this;
    }

    template<typename OtherType>
    Numeric& operator+=( const OtherType& rhs )
    {
        *a += static_cast<Primitive>(rhs);
        return *this;
    }
    
    template<typename OtherType>
    Numeric& operator-=( const OtherType& rhs )
    {
        *a -= static_cast<Primitive>(rhs);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator*=( const OtherType& rhs )
    {
        *a *= static_cast<Primitive>(rhs);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator/=( const OtherType& rhs )
    {   
        if constexpr ( std::is_same<Primitive, int>::value )
        {
            if constexpr ( std::is_same< decltype(rhs), int>::value )
            { 
                if ( rhs == 0 )
                {
                    std::cout << "Can't divide by 0.\n";
                    return *this;
                }
                else if ( rhs < std::numeric_limits<Primitive>::epsilon() )
                {
                    std::cout << "Can't divide by 0.\n";
                    return *this;
                }
            }
        }
        else if ( rhs < std::numeric_limits<Primitive>::epsilon() )
        {
            std::cout << "Warning, dividing by 0.\n";
        }

        *a /= static_cast<Primitive>(rhs);
        return *this;
    } 

private:
    std::unique_ptr<Primitive> a;
};

struct Point
{
    Point( float a, float b ) : x( a ), y( b ) {}

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

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

/*         Free Functions               */

template <typename T>
void updateValue( T& value)
{
    value += value;
}

void divider()
{
    std::cout << "\n\n===============================\n\n";
}

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

#include <iostream>
int main()
{
    Numeric<float> f(0.1f);
    Numeric<int> i(3);
    Numeric<double> d(4.2);
    
    f += 2.f;
    f -= i;
    f *= d;
    f /= 2.f;
    std::cout << "f: " << f << std::endl;
    
    d += 2.f;
    d -= i;
    d *= f;
    d /= 2.f;
    std::cout << "d: " << d << std::endl;
    
    i += 2.f; i -= f; i *= d; i /= 2.f;
    std::cout << "i: "<< i << std::endl;
    
    Point p(f, i);
    p.toString();
    
    d *= -1;
    std::cout << "d: " << d << std::endl;
    
    p.multiply(d.pow(f).pow(i));
    std::cout << "d: " << d << std::endl;
    
    p.toString();
    
    Numeric<float> floatNum(4.3f);
    Numeric<int> intNum(2);
    Numeric<int> intNum2(6);
    intNum = 2 + (intNum2 - 4) + static_cast<double>(floatNum) / 2.3;
    std::cout << "intNum: " << intNum << std::endl;
    
    {
        using Type = decltype(f)::Type;
        f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;
        
        f.apply( cube<Type> );
        std::cout << "f cubed: " << f << std::endl;
    }
    
    {
        using Type = decltype(d)::Type;
        d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;
        
        d.apply( cube<Type> );
        std::cout << "d cubed: " << d << std::endl;
    }
    
    {
        using Type = decltype(i)::Type;
        i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;
        
        i.apply( cube<Type> );
        std::cout << "i cubed: " << i << std::endl;
    }
}
/*
int main()
{ 
    divider();

    Numeric<float> ft(3.2f);
    Numeric<double> dt(8.473276);
    Numeric<int> it(19);

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

    pt.toString();

    pt *= static_cast<float>(it);


    std::cout << "then pt multiplied by it is:\n";

    pt.toString();

    Numeric<double> dtp( 5.67893 );
    Point pdt( static_cast<float>(dtp), static_cast<float>(dtp) );

    divider();

    std::cout << "pdt initialized with a DoubleType has these points:\n";
    pdt.toString();
    std::cout << "And then multiplied by the initializing DoubleType moves the point:\n";


    pdt *= static_cast<float>(dtp);

    pdt.toString();

    divider();

    std::cout << "The apply() function applies the current value of the current object to itself.\n\n";

    Numeric<float> ftA(4.5f);
    using FloatType = decltype(ftA);

    std::cout << "FtA is currently: " << static_cast<float>(ftA) << std::endl;
    
    ftA.apply( [&ftA]( std::unique_ptr<FloatType::Primitive> &a ) -> FloatType&
    {
        *a += *a;
        return ftA;    
    } );
    
    std::cout << "FtA applied to itself by lambda is: " << static_cast<float>(ftA) << std::endl;

    ftA.apply( updateValue );

    std::cout << "FtA applied to itself via function pointer is: " << static_cast<float>(ftA) << std::endl;

    divider();

    Numeric<double> dtA(7.894561);
    using DoubleType = decltype(dtA);

    std::cout << "dtA is currently: " << static_cast<double>(dtA) << std::endl;
    
    dtA.apply( [&dtA]( double &a ) -> DoubleType&
    {
        a += a;
        return dtA;    
    } );
    
    std::cout << "dtA applied to itself by lambda is: " << static_cast<double>(dtA) << std::endl;

    dtA.apply( updateValue<double> );

    std::cout << "dtA applied to itself via function pointer is: " << static_cast<double>(dtA) << std::endl;

    divider();

    Numeric<int> itA(495);
    using IntType = decltype(itA);

    std::cout << "itA is currently: " << static_cast<int>(itA) << std::endl;
    
    itA.apply( [&itA]( std::unique_ptr<IntType::Primitive> &a ) -> IntType&
    {
        *a += *a;
        return itA;    
    } );
    
    std::cout << "itA applied to itself by lambda is: " << static_cast<int>(itA) << std::endl;

    itA.apply( updateValue );

    std::cout << "itA applied to itself via function pointer is: " << static_cast<int>(itA) << std::endl;

    divider();

    std::cout << "good to go!" << std::endl;
}
*/