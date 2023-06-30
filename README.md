# Book Store (DLL Adapter)

Welcome to the second project of our series, the Book Store! This project focuses on creating an adapter for a doubly linked list in a bookstore simulation. We utilize the DoublyLinkedList custom class and a wrapper class named BookStore.

## Overview

- Doubly Linked List: The backbone of our bookstore, this custom class allows us to store and manage data efficiently.

- BookStore Class: This is an adapter class that interacts with the bookstore simulation while avoiding direct interaction with the DoublyLinkedList. It enables the user to add books to the inventory, sell books, and view the list of all books.

## Source Files

The implementation is spread across several files:

- DoublyLinkedList.hpp: Contains the DoublyLinkedList class implementation.

- BookStore.hpp: (Optional) Header file for the BookStore class.

- BookStore.cpp: Contains the BookStore class implementation.

## Execution and Testing

Execution and testing are controlled with a Makefile written for GNU Make. The Makefile includes several targets that you can use during development. As mentioned earlier, do not modify the Makefile

See a help menu with available commands:

```
make help
```

See a quick preview/estimate of your grade with the following command:

```
make test
```

Execute the program defined by main.cpp:

```
make run
```

## Demo

![](./demo.gif)

## Contributor

Erik Williams
