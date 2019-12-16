#include <iostream>
#include <stack>

using namespace std;


class QueueFrom2Stacks {
    stack<int> forward;
    stack<int> backward;
    int size;
    int capacity;

public:
    QueueFrom2Stacks(int cap);

    bool isEmpty();

    bool isFull();

    void enqueue(int val);

    int dequeue();

    void clear();

    void printQueue();

private:
    void store_backward_to_forward();

    void store_forward_to_backward_leave1();

    void restore_backward();

    void restore_forward();
};

QueueFrom2Stacks::QueueFrom2Stacks(int cap) {
    capacity = cap;
    size = 0;
}


bool QueueFrom2Stacks::isEmpty() {
    return size == 0;
}

bool QueueFrom2Stacks::isFull() {
    return size == capacity;
}

void QueueFrom2Stacks::enqueue(int val) {
    forward.push(val);
    store_backward_to_forward();
    backward.push(val);
    restore_backward();
    size++;
}

int QueueFrom2Stacks::dequeue() {
    int val;
    val = backward.top();
    backward.pop();
    store_forward_to_backward_leave1();
    forward.pop();
    restore_forward();
    size--;

    return val;
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

        q.dequeue();
        q.printQueue();
        q.dequeue();
        q.printQueue();
        q.dequeue();
        q.printQueue();
        q.dequeue();
        q.printQueue();
        q.dequeue();
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