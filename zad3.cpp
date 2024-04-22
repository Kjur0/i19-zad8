#include <iostream>
#include <queue>
#include <vector>

class Patient {
public:
	std::string name;
	int age;

	Patient(std::string name, int age) : name(name), age(age) {}

	// Operator porównania, który umożliwia sortowanie pacjentów w kolejce priorytetowej
	bool operator<(const Patient& other) const {
		return age < other.age;
	}
};

class Clinic {
private:
	std::priority_queue<Patient> patients;

public:
	void addPatient(std::string name, int age) {
		patients.push(Patient(name, age));
	}

	void printPatients() {
		while (!patients.empty()) {
			Patient patient = patients.top();
			std::cout << "Name: " << patient.name << ", Age: " << patient.age << std::endl;
			patients.pop();
		}
	}
};

int main() {
	Clinic clinic;

	// przykładowi pacjenci
	clinic.addPatient("John", 30);
	clinic.addPatient("Mary", 60);
	clinic.addPatient("Alice", 45);
	clinic.addPatient("Bob", 50);

	clinic.printPatients();

	return 0;
}