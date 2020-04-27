#ifndef TEACHING_ASSISTANT_H
#define TEACHING_ASSISTANT_H

#include "Teacher.h"
#include "Student.h"

class TeachingAssistant: public Student, public Teacher {
public:
	TeachingAssistant() {} // : Student(), Teacher(), Person()
	TeachingAssistant(const char* name, unsigned int age, unsigned int major_id):
		Student(name, age, major_id) {}
	TeachingAssistant(const TeachingAssistant& other): Student(other), Teacher(other) {}
	TeachingAssistant& operator=(const TeachingAssistant& other) {
		if (this != &other) {
			Student::operator=(other);
			Teacher::operator=(other);
		}
		return *this;
	}
	virtual ~TeachingAssistant() override {}

	void sayHello() const override {
		std::cout << "Hello, I am " << getName() << " and I belong to class TeachingAssistant.\n";
	}

private:

};

#endif // !TEACHING_ASSISTANT_H
