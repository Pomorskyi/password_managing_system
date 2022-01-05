#pragma once
#include <iostream>
#include <string>

namespace codingFiles {
	template <typename T>
	class Node {
	public:
		T data;
		codingFiles::Node<T>* next;

		Node() : data(new T()), next(nullptr) {}
		Node(T d) : data(d), next(nullptr) {}
	};
}

