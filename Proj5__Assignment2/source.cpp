#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef _DEBUG
	#define LOG(x) std::cout << x << std::endl;
#else
	#define LOG(x)
#endif

#define PRE_RELEASE

struct STUDENT_DATA
{
	std::string firstname;
	std::string lastname;

#ifdef PRE_RELEASE
	std::string email;
#endif
};

int main() {
#ifdef PRE_RELEASE
	std::cout << "Running Pre-release build" << std::endl;
#else
	std::cout << "Running Standard build" << std::endl;
#endif


#ifdef PRE_RELEASE
	std::ifstream inputFile("../StudentData_Emails.txt");
#else
	std::ifstream inputFile("../StudentData.txt");
#endif

	if (!inputFile.is_open()) {
		std::cerr << "Error: Could not open the file!" << std::endl;
		return 1;
	}

	//make students vector to store student data
	std::vector<STUDENT_DATA> students;

	std::string line;
	std::string del = ",";
	while (std::getline(inputFile, line)) { // read line from file
		std::string firstname, lastname, email;
		std::vector<std::string> parts;

		size_t pos = 0;
		while ((pos = line.find(del)) != std::string::npos) { // split name/last name by delimiter "del"
			parts.push_back(line.substr(0, pos));
			line.erase(0, pos + del.length());
		}
		parts.push_back(line);

		if (parts.size() >= 2) {
			firstname = parts[0];
			lastname = parts[1];
		}

#ifdef PRE_RELEASE
		if (parts.size() == 3) {
			email = parts[2];
		}
#endif

		
		// Create a STUDENT_DATA object and store the data
		STUDENT_DATA student;
		student.firstname = firstname;
		student.lastname = lastname;
#ifdef PRE_RELEASE
		student.email = email;
#endif

		// push student object into vector space
		students.push_back(student);


#ifdef PRE_RELEASE
		LOG("First Name: " << firstname << ", Last Name: " << lastname << ", Email: " << email)
#else
		LOG("First Name: " << firstname << ", Last Name: " << lastname)
#endif
	}

	inputFile.close();

	return 1;
}