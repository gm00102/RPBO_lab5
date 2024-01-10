#include <iostream>
#include <initializer_list>

using namespace std;

template<typename T>
class AbstractQueue {
public:
    virtual ~AbstractQueue() {};

    virtual unsigned GetSize() const = 0;
    virtual bool Push(const T& element) = 0;
    virtual bool Pop(T& element) = 0;
    virtual bool Peek(T& element) = 0;
    virtual bool IsEmpty() const = 0;
};

template<typename T>
class QueueBasedOnUnidirectionalLinkedList : public AbstractQueue<T> {
private:
    class Node {
    public:
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    unsigned size;

public:
    QueueBasedOnUnidirectionalLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    QueueBasedOnUnidirectionalLinkedList(const QueueBasedOnUnidirectionalLinkedList<T>& other) {
        head = nullptr;
        tail = nullptr;
        size = 0;

        Node* curr = other.head;
        while (curr != nullptr) {
            Push(curr->data);
            curr = curr->next;
        }
    }

    QueueBasedOnUnidirectionalLinkedList(QueueBasedOnUnidirectionalLinkedList<T>&& other) noexcept {
        head = other.head;
        tail = other.tail;
        size = other.size;

        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    QueueBasedOnUnidirectionalLinkedList(initializer_list<T> ilist) : head(nullptr), tail(nullptr), size(0) {
        for (const T& value : ilist) {
            Push(value);
        }
    }

    ~QueueBasedOnUnidirectionalLinkedList() {
        while (!IsEmpty()) {
            T element;
            Pop(element);
        }
    }

    QueueBasedOnUnidirectionalLinkedList& operator=(const QueueBasedOnUnidirectionalLinkedList<T>& other) {
        if (this != &other) {
            while (!IsEmpty()) {
                T element;
                Pop(element);
            }

            Node* curr = other.head;
            while (curr != nullptr) {
                Push(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    QueueBasedOnUnidirectionalLinkedList& operator=(QueueBasedOnUnidirectionalLinkedList<T>&& other) noexcept {
        if (this != &other) {
            while (!IsEmpty()) {
                T element;
                Pop(element);
            }

            head = other.head;
            tail = other.tail;
            size = other.size;

            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    unsigned GetSize() const override {
        return size;
    }

    bool Push(const T& element) override {
        Node* newNode = new Node(element);

        if (IsEmpty()) {
            head = newNode;
            tail = newNode;
            tail->next = head; // Make it cyclic
        }
        else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head; // Make it cyclic
        }

        size++;
        return true;
    }

    bool Pop(T& element) override {
        if (IsEmpty()) {
            return false;
        }

        element = head->data;

        if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else {
            Node* temp = head;
            head = head->next;
            tail->next = head; // Update cyclic link
            delete temp;
        }

        size--;
        return true;
    }

    bool Peek(T& element) override {
        if (IsEmpty()) {
            return false;
        }

        element = head->data;
        return true;
    }

    bool IsEmpty() const override {
        return size == 0;
    }
};

template<typename T>
void demonstrateAbstractQueue(AbstractQueue<T>& queue) {
    queue.Push(3121);
    queue.Push(312);
    queue.Push(323);
    queue.Push(4123);

    cout << "Size: " << queue.GetSize() << endl;
    cout << "Queue: ";
    T element;
    while (queue.Pop(element)) {
        cout << element << " ";
    }
    cout << endl;
}

template<typename T>
void demonstrateAbstractQueue(AbstractQueue<T>* queue) {
    queue->Push(31231);
    queue->Push(1231);
    queue->Push(312);
    queue->Push(4123);

    cout << "Size: " << queue->GetSize() << endl;
    cout << "Queue: ";
    T element;
    while (queue->Pop(element)) {
        cout << element << " ";
    }
    cout << endl;
}

int main() {
    QueueBasedOnUnidirectionalLinkedList<int> queue1;
    demonstrateAbstractQueue(queue1);

    QueueBasedOnUnidirectionalLinkedList<int> queue2;
    demonstrateAbstractQueue(&queue2);

    return 0;
}