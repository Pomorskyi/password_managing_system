#pragma once
#include <iostream>
#include <string>
#include "Node.h"

namespace codingFiles {
	template <typename T>
	class MyList {
	private:
		codingFiles::Node<T>* head;
		int lenght;

	public:
		MyList<T>() { this->head = nullptr; this->lenght = 0; }
		void add(T data) {
			if (this->lenght == 0) {
				codingFiles::Node<T>* newNode = new Node<T>(data);
				this->head = newNode;
				this->lenght++;
				return;
			}

			codingFiles::Node<T>* cur = this->head;
			while (cur->next != nullptr) {
				cur = cur->next;
			}
			codingFiles::Node<T>* newNode = new Node<T>(data);
			cur->next = newNode;
			this->lenght++;
		};
		void deleteByIndex(int ind) {
			if (ind == 0) {
				if (this->lenght == 1) {
					this->head = nullptr;
				}
				else {
					this->head = this->head->next;
				}
			}
			else if(ind == this->lenght - 1){
				codingFiles::Node<T>* prev = this->getNodeByInd(ind - 1);
				prev->next = nullptr;
			}
			else {
				codingFiles::Node<T>* prev = this->getNodeByInd(ind - 1);
				codingFiles::Node<T>* toDelete = this->getNodeByInd(ind);
				codingFiles::Node<T>* nex = this->getNodeByInd(ind + 1);
				prev->next = nex;
			}
			this->lenght--;
		};
		int getLenght() { return this->lenght; };
		T operator [](int index) {
			if (index >= 0 && index < this->lenght) {
				codingFiles::Node<T>* cur = this->head;
				while (cur->next != nullptr && index > 0) {
					cur = cur->next;
					index--;
				}
				return cur->data;
			}
			else {

			}
		};

		void clear() {
			for (int i = this->getLenght() - 1; i >= 0; i--) {
				this->getNodeByInd(i)->next = nullptr;
				this->getNodeByInd(i)->~Node();
			}
			this->lenght = 0;
		};

		codingFiles::Node<T>* getNodeByInd(int index) {
			codingFiles::Node<T>* cur = this->head;
			while (cur->next != nullptr && index > 0) {
				cur = cur->next;
				index--;
			}
			return cur;
		};

		void swaping(int pos1, int pos2){
			if (pos1 == 0) {
				Node<T>* el1 = this->getNodeByInd(pos1);
				Node<T>* el2 = this->getNodeByInd(pos2);
				el1->next = el2->next;
				el2->next = el1;
				this->head = el2;
			}
			else {
				Node<T>* el1 = this->getNodeByInd(pos1);
				Node<T>* el2 = this->getNodeByInd(pos2);
				el1->next = el2->next;
				el2->next = el1;
				this->getNodeByInd(pos1 - 1)->next = el2;
			}
			
		};

	};
}

