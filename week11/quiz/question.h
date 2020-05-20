#ifndef QUESTION_H
#define QUESTION_H

#include "id.h"
#include <cstring>
#include <vector>

typedef unsigned int uint;

class Question {
public:
	Question(std::string q, std::string a1, std::string a2, std::string a3, std::string a4, const char a, const uint p = 1): 
		question(q), ans1(a1), ans2(a2), ans3(a3), ans4(a4), answer(a), points(p) {}

	//friend std::istream& operator >> (std::istream& is, Question& q);

	void ask() {
		std::cout << question << std::endl;
		std::cout << ans1  << std::endl <<
			ans2 << std::endl <<
			ans3 << std::endl <<
			ans4 << std::endl;
	}

	bool checkAnswer(const char a) {
		return (a == answer);
	}

	char getAnswer() {
		return answer;
	}

private:
	std::string question;

	std::string ans1;
	std::string ans2;
	std::string ans3;
	std::string ans4;
	
	const char answer;
	const uint points;
};

#endif