#include <string>
#include <vector>
#include <iostream>

class Element {
public:
	std::string name;
	int priority;

	Element(std::string name, int priority) : name(name), priority(priority) {}
};

class PriorityQueue {
private:
	std::vector<Element> elements;

	int getMaxPriorityIndex() {
		int maxIndex = 0;
		for (int i = 1; i < elements.size(); i++)
			if (elements[i].priority > elements[maxIndex].priority)
				maxIndex = i;
		return maxIndex;
	}

public:

	void push(std::string name, int priority) {
		Element newElement(name, priority);
		elements.push_back(newElement);
	}

	void pop() {
		if (!elements.empty()) {
			int maxIndex = getMaxPriorityIndex();
			elements.erase(elements.begin() + maxIndex);
		}
	}

	Element getItem() {
		if (!elements.empty()) {
			return elements[getMaxPriorityIndex()];
		}
		return Element("", -1);
	}

	void clear() {
		elements.clear();
	}

	void show() {
		for (const auto& element: elements) 
			std::cout << "Name: " << element.name << "\nPriority " << element.priority << "\n\n";
	}
};