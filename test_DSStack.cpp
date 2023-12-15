#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "DSStack.cpp"
#include "DSList.cpp"

TEST_CASE("Check that DSStackArray works", "[DSStackArray]")
{
    // Test default constructor
    DSStackArray<int> stack1;
    REQUIRE(stack1.pop() == -1); // Expect pop to return -1 because stack is empty
    
    // Test push and pop
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    REQUIRE(stack1.pop() == 3);
    REQUIRE(stack1.pop() == 2);
    REQUIRE(stack1.pop() == 1);
    REQUIRE(stack1.pop() == -1); // Expect pop to return -1 because stack is empty
    
    // Test copy constructor
    DSStackArray<int> stack2;
    stack2.push(4);
    stack2.push(5);
    stack2.push(6);
    DSStackArray<int> stack3(stack2);
    REQUIRE(stack3.pop() == 6);
    REQUIRE(stack3.pop() == 5);
    REQUIRE(stack3.pop() == 4);
    REQUIRE(stack3.pop() == -1); // Expect pop to return -1 because stack is empty
    
    // Test assignment operator
    stack1 = stack2;
    REQUIRE(stack1.pop() == 6);
    REQUIRE(stack1.pop() == 5);
    REQUIRE(stack1.pop() == 4);
    REQUIRE(stack1.pop() == -1); // Expect pop to return -1 because stack is empty
    
    // Test capacity
    DSStackArray<int> stack4;
    for (int i = 0; i < 100; i++) 
    {
        stack4.push(i);
    }
    REQUIRE(stack4.pop() == 99);
    REQUIRE(stack4.pop() == 98);
    REQUIRE(stack4.pop() == 97);
    REQUIRE(stack4.pop() == 96);
}

TEST_CASE("Check that DSStackList works", "[DSStackList]")
{
    DSStackList<int> stack;

    SECTION("Push and pop elements")
    {
        stack.push(1);
        stack.push(2);
        stack.push(3);

        REQUIRE(stack.pop() == 3);
        REQUIRE(stack.pop() == 2);
        REQUIRE(stack.pop() == 1);
        REQUIRE(stack.pop() == -1);
    }

    SECTION("Copy constructor and assignment operator")
    {
        DSStackList<int> stackCopy = stack;
        stack.push(1);
        stackCopy.push(2);

        REQUIRE(stack.pop() == 1);
        REQUIRE(stackCopy.pop() == 2);

        DSStackList<int> stackAssign;
        stackAssign = stackCopy;
        stackCopy.push(3);
        stackAssign.push(4);

        REQUIRE(stackCopy.pop() == 3);
        REQUIRE(stackAssign.pop() == 4);
    }
}
