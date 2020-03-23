/*
 Project 4 - Part 3 / 9
 Video: Chapter 4 Part 3 
 Casting

 Create a branch named Part3
 
 do not remove anything from main().  you'll be revising your main() to work with these new code changes.
 
    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.

 1) remove your functions that accepted a User-Defined Type
 
 2) remove any getValue() functions if you added them
 
 3) move all of your add/subtract/multiply/divide implementations out of the class.
  
 4) add user-defined conversion functions that convert to the numeric type your object holds.
        i.e. if your type holds an int, you'll need an operator int() function.
 
 5) make your member variable private.
         this conversion function should be the ONLY WAY to access the held value.
         use the proper casting technique to invoke this conversion function
 
 6) clean up any forward declaration that you might have.
 
 7) make sure it compiles & runs without errors.
 
 8) use your knowledge of casting to remove any conversion warnings. 
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */



#include <iostream>

struct FloatType
{
    FloatType( float varA ) : a( new float(varA) ) {}
    ~FloatType()
    {
        delete a;
        a = nullptr;
    }

    operator float() { return *a; }

    FloatType& add( float rhs );
    FloatType& subtract( float rhs );
    FloatType& multiply( float rhs );
    FloatType& divide( float rhs );

    private:
    float* a;
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

    operator double() { return *a; }

    DoubleType& add( double rhs );
    DoubleType& subtract( double rhs );
    DoubleType& multiply( double rhs );
    DoubleType& divide( double rhs );

    private:
    double* a;
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

    operator int() { return *a; }

    IntType& add( int rhs );
    IntType& subtract( int rhs );
    IntType& multiply( int rhs );
    IntType& divide( int rhs );

    private:
    int* a;
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

    std::cout << "good to go!" << std::endl;
}
