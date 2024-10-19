#include <iostream>
using namespace std;
#define MAX 1000

class Stack
{
    int top;

public:
    int array[MAX];
    Stack()
    {
        top = -1;
    }
    bool push(int x)
    {
        if (top >= (MAX - 1))
        {
            cout << "Stack Overflow";
            return false;
        }
        else
        {
            array[++top] = x;
            cout << x << " pushed into stack\n";
            return true;
        }
    }
    int pop()
    {
        if (top < 0)
        {
            cout << "Stack Underflow";
            return 0;
        }
        else
        {
            int x = array[top--];
            return x;
        }
    }
    friend int peek()
    {
        if (top < 0)
        {
            cout << "Stack is Empty";
            return 0;
        }
        else
        {
            int x = array[top];
            return x;
        }
    }
    bool isEmpty()
    {
        return (top < 0);
    }
};

int main()
{
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(50);
    s.push(-1);
    s.pop();
    s.pop();
    cout << "Top element is: " << s.peek() << endl;

    s.peek();
    while (!s.isEmpty())
    {
        cout << s.peek() << " ";
        s.pop();
    }
    return 0;
}
