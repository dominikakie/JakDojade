#pragma once
struct Position {
	int x;
	int y;
};


class City {
public:
	char* name;
	int x;
	int y;
	City(char* name, int x, int y) :name(name), x(x), y(y) {}
	~City() {
		delete(name);
	}
	char* getName() {
		return name;
	}
};


struct Point {
	Position position;
	Point* next;
	Point(Position position) : position(position), next(nullptr) {}
public:
	Position getPosition() {
		return position;
	}
};


class LinkedList {
	Point* head;
public:
	LinkedList() : head(nullptr) {}
	Position getFirst(){
			return head->getPosition();
	}
	void deleteFirst() {
		if (head != nullptr) {
			Point* temp = head;
			head = head->next;
			delete temp;
		}
	}
	void addElement(Position position) {
		Point* newPoint = new Point(position);
		if (head == nullptr) {
			head = newPoint;
		}
		else {
			Point* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = newPoint;
		}
	}
	int lengthOfLinkedList() {
		int length = 0;
		Point* current = head;
		while (current != nullptr) {
			length++;
			current = current->next;
		}
		return length;
	}

};