#ifndef QUESTIONNAIRE
#define QUESTIONNAIRE

#include "question.h"

class Questionnaire {
public:
	Questionnaire(std::ifstream& content) {
		currentQ = 0;
		if (!content) {
			throw ("No questions to read!");
		}

		while (!content.eof()) {
			char question[256], ans1[256], ans2[256], ans3[256], ans4[256];
			char correctAns;
			content.getline(question, 256);
			content.getline(ans1, 256);
			content.getline(ans2, 256);
			content.getline(ans3, 256);
			content.getline(ans4, 256);
			content >> correctAns;
			Question* q = new Question(question, ans1, ans2, ans3, ans4, correctAns);
			addQuestion(q);
		}
	}

	~Questionnaire() {
		while (!questions.empty()) {
			delete questions.at(questions.size() - 1);
			questions.pop_back();
		}
	}
	
	void addQuestion(Question*& q) {
		questions.push_back(q);
	}

	void askNextQ() {
		if (currentQ == questions.size() - 1) {
			throw ("No more questions!");
		}
		questions[currentQ++]->ask();
	}

	bool checkAnswer(const char a) {
		return questions[currentQ - 1]->checkAnswer(a);
	}

	char getAnswer() {
		return questions[currentQ - 1]->getAnswer();
	}

	bool end() {
		return (currentQ == questions.size() - 1);
	}

	static const char* correct_msg;
	static const char* incorrect_msg;
	static const char* welcome_msg;

private:
	std::vector<Question*> questions;
	uint currentQ = 0;
};

const char* Questionnaire::correct_msg = "Correct!\n";
const char* Questionnaire::incorrect_msg = "Incorrect answer! The correct answer was: ";
const char* Questionnaire::welcome_msg = "Welcome to the FMI quiz!\n";


#endif