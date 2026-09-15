#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef _DEBUG
	#define LOG(x) std::cout << x << std::endl;
#else
	#define LOG(x)
#endif

struct STUDENT_DATA
{
	std::string firstname;
	std::string lastname;
};

int main() {
	std::ifstream inputFile("../StudentData.txt");
	if (!inputFile.is_open()) {
		std::cerr << "Error: Could not open the file!" << std::endl;
		return 1;
	}

	//make students vector to store student data
	std::vector<STUDENT_DATA> students;

	std::string line;
	std::string del = ",";
	while (std::getline(inputFile, line)) { // read line from file
		std::string firstname, lastname;
		size_t pos;
		while ((pos = line.find(del)) != std::string::npos) { // split name/last name by delimiter "del"
			firstname = line.substr(0, pos);
			line.erase(0, pos + del.length());
			lastname = line;
		}
		
		// Create a STUDENT_DATA object and store the data
		STUDENT_DATA student;
		student.firstname = firstname;
		student.lastname = lastname;

		// push student object into vector space
		students.push_back(student);

		LOG("First Name: " << firstname << ", Last Name: " << lastname)
	}

	inputFile.close();

	return 1;
}