#include <iostream>
#include <stack>

using namespace std;

class MyException : public std::exception {
    const char *what() const noexcept override {
        return "Provide more details to the exception";
    }
};

class QueueFrom2Stacks {
    stack<int> forward;
    stack<int> backward;
    int size;
    int capacity;

public:
    QueueFrom2Stacks(int cap);

    bool isEmpty();

    bool isFull();

    bool enqueue(int val);

    bool dequeue(int &ret);

    void clear();

    void printQueue();

private:
    void store_backward_to_forward();

    void store_forward_to_backward_leave1();

    void restore_backward();

    void restore_forward();
};

QueueFrom2Stacks::QueueFrom2Stacks(int cap) {
    // TODO: check cap range
    capacity = cap;
    size = 0;
}


bool QueueFrom2Stacks::isEmpty() {
    return size == 0;
}

bool QueueFrom2Stacks::isFull() {
    return size == capacity;
}

bool QueueFrom2Stacks::enqueue(int val) {
    if (size == capacity){
        MyException e;
        throw e;
    }
//        return false;

    forward.push(val);
    store_backward_to_forward();
    backward.push(val);
    restore_backward();
    size++;

    return true;
}

bool QueueFrom2Stacks::dequeue(int &ret) {
    if (size == 0){
        MyException e;
        throw e;
    }
//        return false;

//    int val;
    ret = backward.top();
    backward.pop();
    store_forward_to_backward_leave1();
    forward.pop();
    restore_forward();
    size--;

    return true;
}

void QueueFrom2Stacks::clear() {
    for (int i = size; i > 0; i--) {
        forward.pop();
        backward.pop();
    }
    size = 0;
}

void QueueFrom2Stacks::printQueue() {
    stack<int> tmpstack = forward;
    for (int i = 0; i < size; i++) {
        cout << tmpstack.top() << " ";
        tmpstack.pop();
    }
    cout << endl;
}

void QueueFrom2Stacks::store_backward_to_forward() {
    int val;
    for (int i = 0; i < size; i++) {
        val = backward.top();
        backward.pop();
        forward.push(val);
    }
}

void QueueFrom2Stacks::restore_backward() {
    int val;
    for (int i = 0; i < size; i++) {
        val = forward.top();
        forward.pop();
        backward.push(val);
    }
}

void QueueFrom2Stacks::store_forward_to_backward_leave1() {
    int val;
    for (int i = 0; i < size - 1; i++) {
        val = forward.top();
        forward.pop();
        backward.push(val);
    }
}

void QueueFrom2Stacks::restore_forward() {
    int val;
    for (int i = 0; i < size - 1; i++) {
        val = backward.top();
        backward.pop();
        forward.push(val);
    }
}

// Stack implementation in C++
int main() {
    QueueFrom2Stacks q(5);
    if (q.isEmpty())
        cout << "Stack Is Empty\n";
    else
        cout << "Stack Is Not Empty\n";

    try {
        q.enqueue(0);
        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);
        q.printQueue();

        int ret;
        q.dequeue(ret);
        q.printQueue();
        q.dequeue(ret);
        q.printQueue();
        q.dequeue(ret);
        q.printQueue();
        q.dequeue(ret);
        q.printQueue();
        q.dequeue(ret);
        q.printQueue();

        if (q.isEmpty())
            cout << "Stack Is Empty\n";
        else
            cout << "Stack Is Not Empty\n";
    }
    catch (exception &e) {
        std::cerr << "Exception caught : " << e.what() << std::endl;
    }


    return 0;
}