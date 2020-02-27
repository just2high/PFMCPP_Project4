#include <iostream>
/*
 Project 4 - Part 1 / 9
 video: Chapter 2 Part 7
 Returning Values tasks 

 Create a branch named Part1
 
 1) write 3 UDTs named FloatType, DoubleType, IntType.

 2) give each UDT the following member functions:
        add( lhs, rhs );
        subtract( lhs, rhs );
        multiply( lhs, rhs );
        divide( lhs, rhs );
 3) implement the appropriate action in the member function. 
         Be aware that floating point division by 0 is legal, but integer division by 0 will crash your program.  
         Handle this possible input when you write your divide() functions.
 
 4) make them return the correct primitive type. e.g. if you're implementing the FloatType::add function, your implementation would start like this:
        float FloatType::add( float lhs, float rhs )
 
 5) declare a few instances of each class in main() and call the member functions with the appropriate arguments.
        FloatType ft;
        auto result = ft.add(3.2f, 23.f );
 
 6) print out those results using std::cout:
        std::cout "result of ft.add(): " << result << std::endl;
 
 7) After you finish defining each type/function, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */

 struct FloatType
 {
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
