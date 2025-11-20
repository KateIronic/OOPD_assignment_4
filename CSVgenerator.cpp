#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

// Random name generator
class NameGenerator {
private:
    vector<string> first_names = {
        "Rahul", "Priya", "Amit", "Sneha", "Vikram", "Anjali", "Rohan", "Pooja",
        "Arjun", "Neha", "Karan", "Divya", "Aditya", "Riya", "Siddharth", "Kavya",
        "Varun", "Ananya", "Dev", "Ishita", "Harsh", "Shruti", "Nikhil", "Tanvi",
        "Akash", "Meera", "Pranav", "Aditi", "Kunal", "Sakshi"
    };
    
    vector<string> last_names = {
        "Sharma", "Verma", "Kumar", "Singh", "Patel", "Gupta", "Reddy", "Rao",
        "Joshi", "Mehta", "Agarwal", "Nair", "Iyer", "Khan", "Malhotra", "Chopra",
        "Desai", "Sinha", "Pandey", "Mishra", "Bhat", "Kulkarni", "Saxena", "Pillai"
    };

public:
    string generateName(mt19937& gen) {
        uniform_int_distribution<> first_dist(0, first_names.size() - 1);
        uniform_int_distribution<> last_dist(0, last_names.size() - 1);
        return first_names[first_dist(gen)] + " " + last_names[last_dist(gen)];
    }
};

// Course code generator
class CourseGenerator {
private:
    vector<string> cse_courses;
    vector<string> ece_courses;
    vector<string> me_courses;
    vector<string> common_courses;

public:
    CourseGenerator() {
        // Initialize course vectors in constructor
        cse_courses = {"CSE101", "CSE102", "CSE201", "CSE202", "CSE231", "CSE301", 
                       "CSE302", "CSE401", "CSE402", "CSE501"};
        
        ece_courses = {"ECE101", "ECE102", "ECE201", "ECE202", "ECE301", 
                       "ECE302", "ECE401", "ECE402"};
        
        me_courses = {"ME101", "ME102", "ME201", "ME202", "ME301", "ME302"};
        
        common_courses = {"MTH100", "MTH101", "PHY100", "CHM100", "HSS101", "HSS102"};
    }
    
    string getRandomCourse(const string& branch, mt19937& gen) {
        uniform_int_distribution<> dist(0, 100);
        
        if (dist(gen) < 30) { // 30% chance of common course
            uniform_int_distribution<> common_dist(0, common_courses.size() - 1);
            return common_courses[common_dist(gen)];
        }
        
        if (branch == "CSE") {
            uniform_int_distribution<> course_dist(0, cse_courses.size() - 1);
            return cse_courses[course_dist(gen)];
        } else if (branch == "ECE") {
            uniform_int_distribution<> course_dist(0, ece_courses.size() - 1);
            return ece_courses[course_dist(gen)];
        } else if (branch == "ME") {
            uniform_int_distribution<> course_dist(0, me_courses.size() - 1);
            return me_courses[course_dist(gen)];
        }
        return "CSE101";
    }
};

struct StudentRecord {
    string name;
    int roll_number;
    string branch;
    int start_year;
    string current_courses;
    string completed_courses;
};

// Comparator for alphabetical sorting by name
bool compareByName(const StudentRecord& a, const StudentRecord& b) {
    return a.name < b.name;
}

int main() {
    // Initialize random generator
    random_device rd;
    mt19937 gen(rd());
    
    NameGenerator nameGen;
    CourseGenerator courseGen;
    
    // Open CSV file for writing
    ofstream csvFile("students_3000.csv");
    
    if (!csvFile.is_open()) {
        cerr << "Error: Could not create CSV file!" << endl;
        return 1;
    }
    
    // Write header
    csvFile << "name,roll_number,branch,start_year,current_courses,completed_courses_with_grades\n";
    
    vector<string> branches = {"CSE", "ECE", "ME"};
    uniform_int_distribution<> branch_dist(0, branches.size() - 1);
    uniform_int_distribution<> grade_dist(5, 10);
    uniform_int_distribution<> curr_course_count(1, 4);
    uniform_int_distribution<> comp_course_count(2, 8);
    
    cout << "Generating 3000 student records..." << endl;
    cout << "Admission order: RANDOM" << endl;
    cout << "Roll number assignment: ALPHABETICAL within each year\n" << endl;
    
    vector<StudentRecord> all_students;
    
    // Generate students year-wise: 2020, 2021, 2022, 2023, 2024
    for (int year = 2020; year <= 2024; year++) {
        int students_per_year = 600; // Equal distribution
        
        cout << "Generating " << students_per_year << " students for year " << year << "..." << endl;
        
        vector<StudentRecord> year_students;
        
        for (int i = 0; i < students_per_year; i++) {
            // Generate student data
            string name = nameGen.generateName(gen);
            string branch = branches[branch_dist(gen)];
            
            // Generate current courses (1-4 courses)
            int num_curr_courses = curr_course_count(gen);
            string current_courses = "";
            for (int j = 0; j < num_curr_courses; j++) {
                if (j > 0) current_courses += ";";
                current_courses += courseGen.getRandomCourse(branch, gen);
            }
            
            // Generate completed courses with grades (2-8 courses)
            int num_comp_courses = comp_course_count(gen);
            string completed_courses = "";
            for (int j = 0; j < num_comp_courses; j++) {
                if (j > 0) completed_courses += ";";
                completed_courses += courseGen.getRandomCourse(branch, gen) + ":" + to_string(grade_dist(gen));
            }
            
            // Store student record (roll number will be assigned later alphabetically)
            StudentRecord student;
            student.name = name;
            student.roll_number = 0; // Will be assigned after sorting
            student.branch = branch;
            student.start_year = year;
            student.current_courses = current_courses;
            student.completed_courses = completed_courses;
            
            year_students.push_back(student);
        }
        
        // STEP 1: Sort students alphabetically by name within this year
        cout << "  Sorting " << year_students.size() << " students alphabetically for roll number assignment..." << endl;
        sort(year_students.begin(), year_students.end(), compareByName);
        
        // STEP 2: Assign roll numbers in alphabetical order (YYYY001, YYYY002, etc.)
        for (size_t serial = 1; serial <= year_students.size(); serial++) {
            year_students[serial - 1].roll_number = year * 1000 + serial;
        }
        
        // STEP 3: Shuffle to create random admission order (but keep the alphabetically assigned roll numbers)
        cout << "  Shuffling for random admission order..." << endl;
        shuffle(year_students.begin(), year_students.end(), gen);
        
        // Add to main list
        all_students.insert(all_students.end(), year_students.begin(), year_students.end());
    }
    
    // Write all students to CSV in RANDOM admission order
    cout << "\nWriting students to CSV in RANDOM admission order..." << endl;
    
    for (size_t i = 0; i < all_students.size(); i++) {
        const auto& student = all_students[i];
        
        csvFile << student.name << ","
                << student.roll_number << ","
                << student.branch << ","
                << student.start_year << ","
                << student.current_courses << ","
                << student.completed_courses << "\n";
        
        if ((i + 1) % 500 == 0) {
            cout << "Written " << (i + 1) << " records..." << endl;
        }
    }
    
    csvFile.close();
    
    // Display verification of the process
    cout << "\n=== PROCESS VERIFICATION ===" << endl;
    cout << "First 15 students in CSV (RANDOM Admission Order):" << endl;
    cout << "Roll No  | Name           | Branch | Year" << endl;
    cout << "-----------------------------------------" << endl;
    for (size_t i = 0; i < 15 && i < all_students.size(); i++) {
        const auto& s = all_students[i];
        cout << s.roll_number << " | " << s.name << " | " 
             << s.branch << "   | " << s.start_year << endl;
    }
    
    // Show what happens when sorted
    cout << "\n=== EXPECTED SORTING BEHAVIOR ===" << endl;
    cout << "When you choose 'Sort by Roll Number' in CLI:" << endl;
    cout << "- Students will be grouped by year (2020, 2021, 2022...)" << endl;
    cout << "- Within each year, students will be in ALPHABETICAL order" << endl;
    cout << "- Because roll numbers were assigned alphabetically!" << endl;
    
    // Demonstrate with a sample
    vector<StudentRecord> sorted_demo = all_students;
    sort(sorted_demo.begin(), sorted_demo.end(), [](const StudentRecord& a, const StudentRecord& b) {
        return a.roll_number < b.roll_number;
    });
    
    cout << "\nSample of first 10 students when SORTED by roll number:" << endl;
    cout << "Roll No  | Name           | Year" << endl;
    cout << "---------------------------------" << endl;
    int count = 0;
    for (const auto& s : sorted_demo) {
        if (count >= 10) break;
        cout << s.roll_number << " | " << s.name << " | " << s.start_year << endl;
        count++;
    }
    
    cout << "\n Successfully generated 3000 student records in 'students_3000.csv'" << endl;
    cout << "Key Features:" << endl;
    cout << "   - Admission Order: RANDOM (as students actually get admitted)" << endl;
    cout << "   - Roll Numbers: ALPHABETICAL within each year" << endl;
    cout << "   - Format: YYYYSSS (7 digits)" << endl;
    cout << "   - Years: 2020-2024 (600 students each)" << endl;
    
    return 0;
}