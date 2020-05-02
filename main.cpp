/*
Project 4: Part 7 / 9
Video: Chapter 5 Part 4

Create a branch named Part7

Do not delete your previous main. you will be adding to it.

Templates and Containers

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 

#1) if you're not using std::unique_ptr to own your heap-allocated type as a member variable, 
    replace your manual memory management techniques with a private std::unique_ptr member variable.

#2) replace your Heap-Allocated Numeric Type-owning class with a templated class called Numeric.
        replace all of your previous instances of your separate classes with this templated class.

#3) add a 'using <some name> = <your class template parameter>;' 
        treat this type declaration via 'using' as a static member variable
        use this Type alias as the argument everywhere you previously used the template argument.
        this will make it very easy to change the type if needed.
            i.e. if you have 'std::unique_ptr<NumericType> value;' before
                you'd replace NumericType in that variable declaration with '<some name>'
        
#4) you'll need to pair it with decltype() to help the compiler figure out the type of the object 
    your class owns when you make your lambda and free function that takes your unique_ptr.  
    i.e. like this for determining the template parameter of the unique_ptr function argument to your class's apply() function
        std::unique_ptr< decltype( <instance of class> )::<some name> >
    
#5) template your free function for the apply() that takes a function pointer so it can be used with your Wrapper class's apply() function

#6) add an explicit template specialization for 'double' of your wrapper class
        this template specialization will have one apply() function instead of 2. 

#7) this apply() function will be templated, and expect a Callable object, not std::function<>. 
        the function should allow for chaining.  
        the callable object should return void, like the function pointer-based apply() function in the primary class template

#8) instantiate your explicit template specialization

#9) call the apply function twice, once with a lambda and once with the free function
        the free function is templated, so you might need to call it including the template arguments.
        
#10) in addition to using the lambda argument to modify the owned object:  (your previous task's lambdas did this same thing) 
        make the lambda use your explicit template instance (maybe via a std::cout), 

#11) now that your class is templated, you'll need to adjust your logic in your division function to handle if your input is a zero or not, based on your templated type.  
        - look up how to use std::is_same<>::value on cppreference to determine the type of your template parameter.
        
        - look up how to use std::numeric_limits<>::epsilon() to determine if you're dividing by a floating point 0
        
        - read about Knuth's algorithm here: https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/

        - in plain-english, you'll need to implement logic like this:
        if your template type is an int
                if your parameter's type is also an int
                        if your parameter is 0
                                don't do the division
                else if it's less than epsilon
                        dont do the divison
        else if it's less than epsilon
                warn about doing the division

        - to make these checks work during compilation, your if() statements will need to be 'constexpr':  if constexpr (expression)

compile/link/run to make sure you don't have any errors

Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.

If you need to view an example, see: https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part7Example.cpp
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

    Numeric& apply( std::function< Numeric&( Primitive& )> func )
    {
        if (func != nullptr )
            return func( *a );

        std::cout << "Warning, nullptr, can't apply.\n";
        return *this;
    }

    using FuncPtr = void(*)( Primitive& );
    Numeric& apply( FuncPtr func )
    {
        if ( func != nullptr )
            func( *a );
        return *this;
    }

    Numeric& pow( Primitive rhs )
    {
        return powInternal ( rhs );
    }

    Numeric& operator+=( Primitive rhs )
    {
        *a += rhs;
        return *this;
    }

    Numeric& operator-=( Primitive rhs )
    {
        *a -= rhs;
        return *this;
    }

    Numeric& operator*=( Primitive rhs )
    {
        *a *= rhs;
        return *this;
    }

    Numeric& operator/=( Primitive rhs )
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

        *a /= rhs;
        return *this;
    } 

private:
    std::unique_ptr<Primitive> a;

    Numeric& powInternal( const Primitive value )
    {
        if( a != nullptr )
            *a = static_cast<Primitive>( std::pow( *a, value ) ); // to avoid warning when converting into <int> type
        return *this;
    }
};

// DoubleType Templated Def
template <>
struct Numeric<double>
{
    using Primitive = double;

    Numeric( Primitive varA ) : a( new Primitive(varA) ) {}

    operator Primitive() const { return *a; }

    template<typename FuncPtr>
    Numeric& apply( FuncPtr func )
    {
        func( *a );
        return *this;
    }

    Numeric& pow( Primitive rhs )
    {
        return powInternal ( rhs );
    }

    Numeric& operator+=( Primitive rhs )
    {
        *a += rhs;
        return *this;
    }

    Numeric& operator -=( Primitive rhs )
    {
        *a -= rhs;
        return *this;
    }

    Numeric& operator *=( Primitive rhs )
    {
        *a *= rhs;
        return *this;
    }

    Numeric& operator/=( Primitive rhs )
    {
        *a /= rhs;
        return*this;
    } 

    private:
    std::unique_ptr<Primitive> a;

    Numeric& powInternal( const Primitive value )
    {
        if( a != nullptr )
            *a = std::pow( *a, value );
        return *this;
    }
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
    
    ftA.apply( [&ftA]( float &a ) -> FloatType&
    {
        a += a;
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
    
    itA.apply( [&itA]( int &a ) -> IntType&
    {
        a += a;
        return itA;    
    } );
    
    std::cout << "itA applied to itself by lambda is: " << static_cast<int>(itA) << std::endl;

    itA.apply( updateValue );

    std::cout << "itA applied to itself via function pointer is: " << static_cast<int>(itA) << std::endl;

    divider();

    std::cout << "good to go!" << std::endl;
}
