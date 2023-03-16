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
	/**
	 * Namespace to hold all things related to our DLL
	 */
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
			/**
			 * Nested Iterator class.
			 * This allows user code to refer to the Iterator's type as:
			 *
			 * CPSC131::DoublyLinkedList::DoublyLinkedList<int>::Iterator
			 *
			 * (as opposed to specifying the template argument two times)
			 */
			class Iterator
			{
			public:
				///	Constructor taking a head and tail pointer; YOUR WELCOME
				Iterator(Node<T> *head, Node<T> *tail) : head_(head), tail_(tail) { this->cursor_ = this->end(); }
				// Iterator(Node<T>* head, Node<T>* tail) : head_(head), tail_(tail) { this->cursor_ = this->head_; }

				///	Constructor taking a head, tail, and cursor pointer; YOUR WELCOME
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
					this->head_ = other.head_;
					this->tail_ = other.tail_;
					this->cursor_ = other.cursor_;
					return *this;
				}

				///	Comparison operator
				bool operator==(const Iterator &other)
				{
					return (this->cursor_ == other.cursor_);
				}
				///	Inequality comparison operator
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
					if (cursor_)
					{
						cursor_ = cursor_->getNext();
					}
					return *this;
				}

				/**
				 * Postfix increment
				 * Return a copy of this Iterator, BEFORE it was modified
				 */
				Iterator operator++(int)
				{
					Iterator copy(*this);
					++(*this);
					return copy;
				}

				/**
				 * Prefix decrement operator
				 * Return a copy of this Iterator, after modification
				 */
				Iterator &operator--()
				{
					if (cursor_ == nullptr)
					{
						cursor_ = tail_;
					}
					else
					{
						cursor_ = cursor_->getPrevious();
					}
					return *this;
				}

				/**
				 * Postfix decrement operator
				 * Return a copy of this Iterator BEFORE it was modified
				 */
				Iterator operator--(int)
				{
					Iterator copy(*this);
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
				Iterator operator-=(size_t add)
				{
					for (size_t i = 0; i < add && cursor_ != nullptr; ++i)
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
					if (add >= 0)
					{
						for (int i = 0; i < add && cursor_ != nullptr; ++i)
						{
							++(*this);
						}
					}
					else
					{
						for (int i = 0; i > add && cursor_ != nullptr; --i)
						{
							--(*this);
						}
					}
					return *this;
				}

				/**
				 * SubtractionAssignment operator, supporting positive or negative ints
				 */
				Iterator operator-=(int subtract)
				{
					if (subtract >= 0)
					{
						for (int i = 0; i < subtract && cursor_ != nullptr; ++i)
						{
							--(*this);
						}
					}
					else
					{
						for (int i = 0; i > subtract && cursor_ != nullptr; --i)
						{
							++(*this);
						}
					}
					return *this;
				}

				/**
				 * Dereference operator returns a reference to the ELEMENT contained with the current node
				 */
				T &operator*()
				{
					return cursor_->getElement();
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

			/// Your welcome
			DoublyLinkedList()
			{
				this->head_ = nullptr;
				this->tail_ = nullptr;
				this->size_ = 0;
			}

			///	Copy Constructor
			DoublyLinkedList(DoublyLinkedList &other)
			{
				for (auto it = other.begin(); it != other.end(); ++it)
				{
					this->push_back(*it);
				}
			}

			/// DTOR: Your welcome
			~DoublyLinkedList()
			{
				this->clear();
			}

			/**
			 * Clear the list and assign the same value, count times.
			 * If count was 5, T was int, and value was 3,
			 * 	we'd end up with a list like {3, 3, 3, 3, 3}
			 */
			void assign(size_t count, const T &value)
			{
				this->clear();
				for (size_t i = 0; i < count; ++i)
				{
					this->push_back(value);
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
				this->clear();
				while (first != last)
				{
					this->push_back(*first);
					++first;
				}
			}

			/// Return a pointer to the head node, if any
			Node<T> *head() { return head_; }

			/// Return a pointer to the tail node, if any
			Node<T> *tail() { return tail_; }

			/**
			 * Return an iterator that points to the head of our list
			 */
			Iterator begin()
			{
				return Iterator(head_, tail_, head_);
			}

			/**
			 * Return an iterator that points to the last element (tail) of our list
			 */
			Iterator last()
			{
				return Iterator(head_, tail_, tail_);
			}

			/**
			 * Should return an iterator that represents being past the end of our nodes,
			 * or just that we are finished.
			 * You can make this a nullptr or use some other scheme of your choosing,
			 * 	as long as it works with the logic of the rest of your implementations.
			 */
			Iterator end()
			{

				return Iterator(head_, tail_, nullptr);
			}

			/**
			 * Returns true if our list is empty
			 */
			bool empty() const
			{
				return size_ == 0;
			}

			/**
			 * Returns the current size of the list
			 * Should finish in constant time!
			 * (keep track of the size elsewhere)
			 */
			size_t size() const
			{
				return size_;
			}

			/**
			 * Clears our entire list, making it empty
			 * Remember: All removal operations should be memory-leak free.
			 */
			void clear()
			{
				size_ = 0;
				Node<T> *node = this->head_;
				while (node != nullptr)
				{
					Node<T> *next = node->getNext();
					;
					delete node;
					node = next;
				}
				this->head_ = nullptr;
				this->tail_ = nullptr;
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
				Node<T> *current_node = pos.getCursor();
				;
				if (size_ == 0)
				{

					head_ = new Node<T>(value);
					tail_ = head_;
					size_++;
					return Iterator(head_, head_, tail_);
				}
				else if (current_node == nullptr)
				{
					tail_->setNext(new Node<T>(value));
					tail_->getNext()->setPrev(tail_);
					tail_ = tail_->getNext();
					size_++;
					return Iterator(tail_, head_, tail_);
				}
				else
				{
					Node<T> *newNode = new Node<T>(value);
					newNode->setNext(current_node->getNext());
					newNode->setPrev(current_node);
					current_node->setNext(newNode);
					if (newNode->getNext() != nullptr)
					{
						newNode->getNext()->setPrev(newNode);
					}
					else
					{
						tail_ = newNode;
					}
					size_++;
					return Iterator(newNode, head_, tail_);
				}
			}

			/**
			* Insert a new element after the index pos.
			* Should work with an empty list.
			*
			 Should return an iterator pointing to the newly created node
			*
			 To reduce repeated code, you may want to simply find
			* 	an iterator to the node at the pos index, then
			* 	send it to the other overload of this method.
			*/
			Iterator insert_after(size_t pos, const T &value)
			{
				if (pos > size())
				{
					throw std::range_error("Invalid index");
				}
				Iterator it = begin();
				for (size_t i = 0; i < pos; i++)
				{
					it++;
				}
				return insert_after(it, value);
			}

			/**
			 * Erase the node pointed to by the Iterator's cursor.
			 *
			 * If the 'pos' iterator does not point to a valid node,
			 * 	throw an std::range_error
			 *
			 * Return an iterator to the node AFTER the one we erased,
			 * 	or this->end() if we just erased the tail
			 */
			Iterator erase(Iterator pos)
			{
				if (pos.getCursor() == nullptr)
				{
					throw std::range_error("Invalid iterator");
				}
				if (pos.getCursor()->getNext() == nullptr)
				{
					return end();
				}
				else
				{
					Node<T> *node = pos.getCursor()->getNext();
					pos.getCursor()->setNext(nullptr);
					node->setPrev(nullptr);
					size_--;
					return Iterator(node, head_, tail_);
				}
			}

			/**
			 * Add an element just after the one pointed to by the 'pos' iterator
			 *
			 * Should return an iterator pointing to the newly created node
			 */
			Iterator push_after(Iterator pos, const T &value)
			{
				if (size_ == 0 || pos == end())
				{
					return insert_after(last(), value);
				}
				else
				{
					return insert_after(pos, value);
				}
			}

			/**
			 * Add a new element to the front of our list.
			 */
			void push_front(const T &value)
			{
				Node<T> *new_node = new Node<T>(value);
				if (size_ == 0)
				{
					head_ = new_node;
					tail_ = new_node;
				}
				else
				{
					new_node->setNext(head_);
					head_->setPrev(new_node);
					head_ = new_node;
				}
				size_++;
			}

			/**
			 * Add an element to the end of this list.
			 *
			 * Should return an iterator pointing to the newly created node.
			 */
			Iterator push_back(const T &value)
			{

				Node<T> *new_node = new Node<T>(value, nullptr, nullptr);
				if (tail_ == nullptr)
				{
					head_ = new_node;
					tail_ = new_node;
				}
				else
				{
					new_node->setPrev(tail_);
					tail_->setNext(new_node);
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
				if (size_ == 0)
				{
					throw std::underflow_error("Empty list");
				}
				Node<T> *old_head = head_;
				head_ = head_->getNext();

				if (head_ != nullptr)
				{
					head_->setPrev(nullptr);
				}
				else
				{
					tail_ = nullptr;
				}
				delete old_head;
				--size_;
			}

			/**
			 * Remove the node at the end of our list
			 *
			 * Should throw an exception if our list is empty
			 */
			void pop_back()
			{
				if (size_ == 0)
				{
					throw std::underflow_error("Empty list");
				}
				Node<T> *old_tail = tail_;
				tail_ = tail_->getPrev();

				if (tail_ != nullptr)
				{
					tail_->setNext(nullptr);
				}
				else
				{
					head_ = nullptr;
				}
				delete old_tail;
				--size_;
			}

			/**
			 * Return a reference to the element at the front.
			 *
			 * Throw an exception if the list is empty
			 */
			T &front()
			{
				if (size_ == 0)
				{
					throw std::underflow_error("List is empty");
				}
				return head_->getElement();
			}

			/**
			 * Return a reference to the element at the back.
			 *
			 * Throw an exception if the list is empty
			 */
			T &back()
			{
				if (size_ == 0)
				{
					throw std::underflow_error("List is empty");
				}
				return tail_->getElement();
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
				Node<T> *n = head_;
				for (size_t i = 0; i < index; ++i)
				{
					n = n->getNext();
				}
				return n->getElement();
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
				if (size_ > 1)
				{
					DoublyLinkedList<T> temp_list;
					Node<T> *current = head_;
					while (current != nullptr)
					{
						temp_list.push_front(current->getElement());
						current = current->getNext();
					}
					this->head_ = temp_list.head_;
					this->tail_ = temp_list.tail_;
					this->size_ = temp_list.size_;

					temp_list.head_ = nullptr;
					temp_list.tail_ = nullptr;
					temp_list.size_ = 0;
				}
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
				}

				Node<T> *c = other.head_;
				while (c != nullptr)
				{
					push_back(c->getElement());
					c = c->getNext();
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
				if (this->size_ != other.size_)
				{
					return false;
				}
				Node<T> *_c = head_;
				Node<T> *_d = other.head_;
				while (_c != nullptr && _d != nullptr)
				{
					if (_c->getElement() != _d->getElement())
					{
						return false;
					}
					_c = _c->getNext();
					_d = _d->getNext();
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