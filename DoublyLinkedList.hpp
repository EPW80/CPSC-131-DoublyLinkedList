#ifndef MY_DOUBLY_LINKED_LIST_HPP
#define MY_DOUBLY_LINKED_LIST_HPP

/**
 * TODO: Implement DoublyLinkedList, its Node, and its Iterator!
 *
 * I've left some methods filled out for you,
 * 	and stubbed out some structure, to reduce difficulty.
 *
 * You may add or remove methods as you see fit,
 * 	as long as you can still pass all unit tests.
 * Although, it may be more difficult to do so. Your choice!
 *
 * Notice we're inside a namespace here.
 * The DLL is inside a namespace called DoublyLinkedList,
 * 	which is itself inside a namespace called CPSC131
 * This means, if you'd like to play around with your class later,
 * 	you'll need to access it like so:
 * ::CPSC131::DoublyLinkedList::DoublyLinkedList<int> list;
 *
 * Look into main.cpp and CPP_Tests.cpp for examples of using
 * 	the DLL and your BookStore. But don't worry too much, as you
 * 	only need to implement these classes
 * (main and tests are already done for you)
 */

//
#include <iostream>
#include <stdlib.h>
#include <stdexcept>

/**
 * Namespace for our classroom !
 */
namespace CPSC131
{
    /*** Namespace to hold all things related to our DLL*/
    namespace DoublyLinkedList
    {
        /**
         * Node class, which our DLL will use
         *
         * The Professor realizes he could have made this an inline class (like the Iterator),
         * but he is lazy.
         */
        template <class T>
        class Node
        {
        public:
            /// CTORS
            Node() : prev_(nullptr), next_(nullptr) {}

            Node(T element) : element_(element), prev_(nullptr), next_(nullptr) {}

            Node(T element, Node *prev, Node *next) : element_(element), prev_(prev), next_(next) {}

            /// Set the pointer to the previous element
            void setPrevious(Node *prev) { prev_ = prev; }

            /// Set the pointer to the previous element
            void setPrev(Node *prev) { prev_ = prev; }

            /// Get a pointer to the previous element
            Node *getPrevious() { return prev_; }

            /// Get a pointer to the previous element
            Node *getPrev() { return prev_; }

            /// Set the pointer to the next node
            void setNext(Node *next) { next_ = next; }

            /// Get a pointer to the next node
            Node *getNext() { return next_; }

            /// Set the element this node holds
            void setElement(T element) { element_ = element; }

            /// Get the element this node holds
            T &getElement() { return element_; }

            /// Return a reference to the element
            T &operator*() { return element_; }

        private:
            T element_;
            Node *prev_;
            Node *next_;
        };

        /**
         * Implement our DoublyLinkedList class !
         */
        template <class T>
        class DoublyLinkedList
        {
        public:
            /*** Nested Iterator class.
             * This allows user code to refer to the Iterators type as:
             *
             * CPSC131::DoublyLinkedList::DoublyLinkedList<int>::Iterator
             *
             * (as opposed to specifying the template argument two times)
             */
            class Iterator
            {
            public:
                ///	Constructor taking a head and tail pointer; YOU'RE WELCOME
                Iterator(Node<T> *head, Node<T> *tail) : head_(head), tail_(tail)
                {
                    cursor_ = end();
                }

                ///	Constructor taking a head, tail, and cursor pointer; YOU'RE WELCOME
                Iterator(Node<T> *head, Node<T> *tail, Node<T> *cursor) : head_(head), tail_(tail), cursor_(cursor) {}

                ///	Get a pointer to the head node, or end() if this list is empty
                Node<T> *begin() { return head_; }

                ///	Get a node pointer representing "end" (aka "depleted"). Probably want to just use nullptr.
                Node<T> *end() { return nullptr; }

                ///	Get the node to which this iterator is currently pointing
                Node<T> *getCursor() { return cursor_; }

                /**
                 * Assignment operator
                 * Return a copy of this Iterator, after modification
                 */
                Iterator &operator=(const Iterator &other)
                {
                    head_ = other.head_;
                    tail_ = other.tail_;
                    cursor_ = other.cursor_;
                    return *this;
                }

                /**
                 * Comparison operator
                 * Returns true if this iterator is equal to the other iterator, false otherwise
                 */
                bool operator==(const Iterator &other)
                {
                    return cursor_ == other.cursor_;
                }

                /**
                 * Inequality comparison operator
                 * Returns true if this iterator is not equal to the other iterator, false otherwise
                 */
                bool operator!=(const Iterator &other)
                {
                    return !(*this == other);
                }
                /**
                 * Prefix increment operator
                 * Return a copy of this Iterator, after modification
                 */
                Iterator &operator++()
                {
                    cursor_ = cursor_->getNext();
                    return *this;
                }
                /*** Postfix increment
                 * Return a copy of this Iterator, BEFORE it was modified
                 */
                Iterator operator++(int)
                {
                    Iterator copy(*this);
                    ++(*this);
                    return copy;
                }
                /*** Prefix decrement operator
                 * Return a copy of this Iterator, after modification
                 */
                Iterator &operator--()
                {
                    cursor_ = cursor_->getPrev();
                    return *this;
                }
                /**
                 * Postfix decrement operator
                 * Return a copy of this Iterator BEFORE it was modified
                 */
                Iterator operator--(int)
                {
                    Iterator copy = *this;
                    --(*this);
                    return copy;
                }
                /**
                 * AdditionAssignment operator
                 * Return a copy of the current iterator, after modification
                 */
                Iterator operator+=(size_t add)
                {
                    for (size_t i = 0; i < add && cursor_ != nullptr; ++i)
                    {
                        cursor_ = cursor_->getNext();
                    }
                    return *this;
                }
                /**
                 * SubtractionAssignment operator
                 * Return a copy of the current iterator, after modification
                 */
                Iterator operator-=(size_t sub)
                {
                    for (size_t i = 0; i < sub && cursor_ != nullptr; ++i)
                    {
                        cursor_ = cursor_->getPrev();
                    }
                    return *this;
                }
                /**
                 * AdditionAssignment operator, supporting positive or negative ints
                 */
                Iterator operator+=(int add)
                {
                    if (add > 0)
                    {
                        for (int i = 0; i < add && cursor_ != nullptr; ++i)
                        {
                            cursor_ = cursor_->getNext();
                        }
                    }
                    else
                    {
                        for (int i = 0; i > add && cursor_->getPrev() != nullptr; --i)
                        {
                            cursor_ = cursor_->getPrev();
                        }
                    }
                    return *this;
                }
                /**
                 * SubtractionAssignment operator, supporting positive or negative ints
                 */
                Iterator operator-=(int subtract)
                {
                    // This function adds an integer to the current iterators position in the list,
                    if (subtract > 0)
                    {
                        for (int i = 0; i < subtract && cursor_->getPrev() != nullptr; ++i)
                        {
                            cursor_ = cursor_->getPrev();
                        }
                    }
                    else
                    {
                        for (int i = 0; i > subtract && cursor_ != nullptr; --i)
                        {
                            cursor_ = cursor_->getPrev();
                        }
                    }
                    return *this;
                }

                /**
                 * Dereference operator returns a reference to the ELEMENT contained with the current node
                 */
                T &operator*()
                {
                    return *cursor_->getElement();
                }

            private:
                /// Pointer to the head node
                Node<T> *head_ = nullptr;
                /// Pointer to the tail node
                Node<T> *tail_ = nullptr;
                /**
                 * Pointer to the cursor node.
                 * This is only one way of letting the iterator traverse the linked list.
                 * You can change to a different method if you wish (and can still pass unit tests)
                 */
                Node<T> *cursor_ = nullptr;

                friend class DoublyLinkedList;
            };
            /// Constructor
            DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

            ///	Copy Constructor
            DoublyLinkedList(DoublyLinkedList &other) : DoublyLinkedList()
            {
                for (auto it = other.begin(); it != other.end(); ++it)
                {
                    push_back(*it);
                }
            }

            /// Destructor
            ~DoublyLinkedList()
            {
                clear();
            }

            /**
             * Clear the list and assign the same value, count times.
             * If count was 5, T was int, and value was 3,
             * 	we'd end up with a list like {3, 3, 3, 3, 3}
             */
            void assign(size_t count, const T &value)
            {
                clear();
                for (size_t i = 0; i < count; i++)
                {
                    push_back(value);
                }
            }

            /**
             * Clear the list and assign values from another list.
             * The 'first' iterator points to the first item copied from the other list.
             * The 'last' iterator points to the last item copied from the other list.
             *
             * Example:
             * 	Suppose we have a source list like {8, 4, 3, 2, 7, 1}
             * 	Suppose first points to the 4
             *	Suppose last points to the 7
             * 	We should end up with our list becoming: {4, 3, 2, 7}
             *
             * If the user code sends out-of-order iterators,
             * 	just copy from 'first' to the end of the source list
             * Example: first=7, last=4 from the list above would give us:
             * 	{7, 1}
             */
            void assign(Iterator first, Iterator last)
            {
                clear();
                for (; first != last && first.cursor != nullptr; ++first)
                {
                    push_back(*first);
                }
            }

            /// Return a pointer to the head node, if any
            Node<T> *head() const { return head_; }

            /// Return a pointer to the tail node, if any
            Node<T> *tail() const { return tail_; }

            /**
             * Return an iterator that points to the head of our list
             */
            Iterator begin()
            {
                return Iterator(head_, head_, tail_);
            }

            /**
             * Return an iterator that points to the last element (tail) of our list
             */
            Iterator last()
            {
                if (empty())
                {
                    return Iterator(nullptr, nullptr, nullptr);
                }
                else
                {
                    return Iterator(tail_, nullptr, nullptr);
                }
            }

            /**
             * Should return an iterator that represents being past the end of our nodes,
             * or just that we are finished.
             * You can make this a nullptr or use some other scheme of your choosing,
             * 	as long as it works with the logic of the rest of your implementations.
             */
            Iterator end() { return nullptr; }

            /**
             * Returns true if our list is empty
             */
            bool empty() const { return size_ == 0; }

            /**
             * Returns the current size of the list
             * Should finish in constant time!
             * (keep track of the size elsewhere)
             */
            size_t size() const { return size_; }

            /**
             * Clears our entire list, making it empty
             * Remember: All removal operations should be memory-leak free.
             */
            void clear()
            {
                // Set a pointer to the head of the list
                Node<T> *current = head_;

                // Loop through each node in the list
                while (current != nullptr)
                {
                    Node<T> *next = current->next_;
                    delete current;
                    current = next;
                }
                // Set head and tail pointers to null and reset the size of the list
                head_ = nullptr;
                tail_ = nullptr;
                size_ = 0;
            }

            /**
             * Insert an element after the node pointed to by the pos Iterator
             *
             * If the list is currently empty,
             * 	ignore the iterator and just make the new node at the head/tail (list of length 1).
             *
             * If the incoming iterator is this->end(), insert the element at the tail
             *
             * Should return an iterator that points to the newly added node
             *
             * To avoid repeated code, it might be a good idea to have other methods
             * 	rely on this one.
             */
            Iterator insert_after(Iterator pos, const T &value)
            {
                Node<T> *new_node = new Node<T>(value);
                if (pos == end() || empty())
                {
                    if (empty())
                    {
                        head_ = new_node;
                    }
                    else
                    {
                        tail_->next_ = new_node;
                    }
                    tail_ = new_node;
                }
                else
                {
                    new_node->next_ = pos->next_;
                    pos->next_ = new_node;
                }
                return Iterator(new_node, head_, tail_);
            }

            /**
             * Insert a new element after the index pos.
             * Should work with an empty list.
             *
             * Should return an iterator pointing to the newly created node
             *
             * To reduce repeated code, you may want to simply find
             * an iterator to the node at the pos index, then
             * send it to the other overload of this method.
             */
            Iterator insert_after(size_t pos, const T &value)
            {
                Iterator it = begin();
                for (size_t i = 0; i < pos && it != end(); i++)
                {
                    ++it;
                }
                return insert_after(it, value);
            }

            /**
             * Erase the node pointed to by the Iterators cursor.
             *
             * If the 'pos' iterator does not point to a valid node,
             * 	throw an std::range_error
             *
             * Return an iterator to the node AFTER the one we erased,
             * 	or this->end() if we just erased the tail
             */
            Iterator erase(Iterator pos)
            {
                Node<T> *node = pos.node_;
                if (node == nullptr || node == head_ || node == tail_)
                {
                    throw std::range_error("Invalid iterator");
                }
                Node<T> *prevNode = node->prev_;
                Node<T> *nextNode = node->next_;

                // Updates the next_ pointer of the previous node to point to the next node or updates the head_ pointer
                if (prevNode != nullptr)
                {
                    prevNode->next_ = nextNode;
                }
                else
                {
                    head_ = nextNode;
                }
                if (nextNode != nullptr)
                {
                    nextNode->prev_ = prevNode;
                }
                else
                {
                    tail_ = prevNode;
                }
                Iterator nextIt(nextNode, head_, tail_);
                delete node;
                return nextIt;
            }
            /**
             * Add an element just after the one pointed to by the 'pos' iterator
             *
             * Should return an iterator pointing to the newly created node
             */
            Iterator push_after(Iterator pos, const T &value)
            {
                Node<T> *node = pos.node_;
                if (node == nullptr)
                {
                    throw std::range_error("Invalid iterator");
                }

                Node<T> *nextNode = node->next_;
                Node<T> *newNode = new Node(value, node, nextNode);
                node->next_ = newNode;
                if (nextNode != nullptr)
                {
                    nextNode->prev_ = newNode;
                }
                else
                {
                    tail_ = newNode;
                }
                return Iterator(newNode, head_, tail_);
            }

            /**
             * Add a new element to the front of our list.
             */
            void push_front(const T &value)
            {
                Node<T> *new_node = new Node<T>(value, nullptr, head_);
                if (head_ == nullptr)
                {
                    tail_ = new_node;
                }
                else
                {
                    head_->prev_ = new_node;
                }
                head_ = new_node;
                ++size_;
            }

            /**
             * Add an element to the end of this list.
             *
             * Should return an iterator pointing to the newly created node.
             */
            Iterator push_back(const T &value)
            {
                Node<T> *new_node = new Node<T>(value, nullptr, tail_);
                if (tail_ == nullptr)
                {
                    head_ = new_node;
                }
                else
                {
                    tail_ = new_node;
                }
                tail_ = new_node;
                ++size_;
                return Iterator(new_node, head_, tail_);
            }

            /**
             * Remove the node at the front of our list
             *
             * Should throw an exception if our list is empty
             */
            void pop_front()
            {
                if (head_ == nullptr)
                {
                    throw std::range_error("Empty list");
                }
                Node<T> *temp = head_;
                head_ = head->next_;
                delete temp;
            }

            /**
             * Remove the node at the end of our list
             *
             * Should throw an exception if our list is empty
             */
            void pop_back()
            {
                if (tail_ == nullptr)
                {
                    throw std::range_error("Empty list");
                }
                Node<T> *temp = tail_;
                tail_ = tail_->prev_;
                delete temp;
            }

            /**
             * Return a reference to the element at the front.
             *
             * Throw an exception if the list is empty
             */
            T &front()
            {
                if (head_ == nullptr)
                {
                    throw std::range_error("Empty list");
                }
                return head_->value_;
            }

            /**
             * Return a reference to the element at the back.
             *
             * Throw an exception if the list is empty
             */
            T &back()
            {
                if (tail_ == nullptr)
                {
                    throw std::range_error("Empty list");
                }
                return tail_->value_;
            }

            /**
             * Return the element at an index
             *
             * Should throw a range_error is out of bounds
             */
            T &at(size_t index)
            {
                if (index >= size_)
                {
                    throw std::range_error("Index out of bounds");
                }
                Node<T> *temp = head_;
                for (size_t i = 0; i < index; ++i)
                {
                    temp = temp->getNext();
                    if (temp == nullptr)
                    {
                        throw std::runtime_error("Invalid node");
                    }
                }
                return temp->getElement();
            }

            /**
             * Reverse the current list
             *
             * It might be easy to consider the following:
             * - Create a temp empty list
             * - Iterate through the current list
             * - For each item in the current list, push to the FRONT (not back)
             * - Assign the current list to the temp list
             * - Discard the temp list
             */
            void reverse()
            {
                Node<T> *current = head_;
                Node<T> *temp = nullptr;
                while (current != nullptr)
                {
                    temp = current->prev_;
                    current->prev_ = current->next_;
                    current->next_ = temp;
                    current = current->prev_;
                }
                temp = head_;
                head_ = tail_;
                tail_ = temp;
            }

            /**
             * I bet you're happy I'm not making you do this.
             * No tests will be run against this function,
             * 	but feel free to try it out, as a challenge!
             *
             * If I were doing this and didn't care too much for efficiency,
             * 	I would probably create an extra helper function to swap two
             * 	positions in the current list.
             * Then I would simply sweep through the list and perform
             *  the bubble-sort algorithm. Perhaps selection sort.
             *
             * If you want a huge challenge, try implementing quicksort.
             *
             * (but again, don't worry about this method; it will not be tested)
             */
            void sort()
            {
            }

            /**
             * Assignment operator
             *
             * Clear this list and fill it with the others' values
             * (by value, not by reference)
             *
             * Return a reference to this list
             */
            DoublyLinkedList<T> &operator=(DoublyLinkedList<T> &other)
            {
                if (this != &other)
                {
                    clear();
                    for (Node<T> *node = other.head_; node != nullptr; node = node->next_)
                    {
                        push_back(node->value_);
                    }
                }
                return *this;
            }

            /**
             * Return true if the lists are "equal"
             *
             * "Equal" here is defined as:
             * - Same size
             * - Elements at the same indexes would return true for their own comparison operators
             *
             * In other words: "They contain all the same values"
             * (no need to be references to each other)
             */
            bool operator==(DoublyLinkedList<T> &other)
            {
                if (size() != other.size())
                {
                    return false;
                }
                auto it1 = begin();
                auto it2 = other.begin();
                for (; it1 != end() && it2 != other.end(); ++it1, ++it2)
                {
                    if (*it1 != *it2)
                    {
                        return false;
                    }
                }
                return true;
            }

            /**
             * Return true if the lists are "not equal"
             *
             * See the operator== stub for definition of "equal"
             *
             * Probably want to avoid repeated code by relying on the other operator
             */
            bool operator!=(DoublyLinkedList<T> &other)
            {
                return !(*this == other);
            }

        private:
            Node<T> *head_ = nullptr;
            Node<T> *tail_ = nullptr;
            size_t size_ = 0;
        };
    }
}
#endif
