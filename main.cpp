// #include <iostream>
// #include <vector>
// #include <sstream>   
// #include <fstream>   
// #include <chrono>    
// #include <iomanip>
// #include <thread>
// using namespace std;

// enum class Branch{
//     CSE,
//     ECE,
//     UNKNOWN
// };

// Branch stringToBranch(const string& branchStr) {
//     if (branchStr == "CSE") return Branch::CSE;
//     if (branchStr == "ECE") return Branch::ECE;
//     return Branch::UNKNOWN;
// }

// string branchToString(Branch b) {
//     switch(b) {
//         case Branch::CSE: return "CSE";
//         case Branch::ECE: return "ECE";
//         default: return "Unknown";
//     }
// }


// vector<string> split(const string& str, char delimiter) {
//     vector<string> tokens;
//     stringstream ss(str);
//     string token;
    
//     while (getline(ss, token, delimiter)) {
//         tokens.push_back(token);
//     }
    
//     return tokens;
// }


// template<typename CourseCodeType>
// class Course{
//     private:
//         string course_name;
//         CourseCodeType course_code;
//         unsigned int credits;
//         string acronym;

//     public:
//         Course() : course_code(CourseCodeType()), credits(0) {}
        
//         Course(string name, CourseCodeType code, unsigned int cred, string acr)
//         : course_name(name), course_code(code), credits(cred), acronym(acr) {}
    
//         CourseCodeType getCode() const { return course_code; }
//         string getName() const { return course_name; }
//         unsigned int getCredits() const { return credits; }

//         void display() const {
//             cout << "Course: " << course_name << " (" << acronym << ")" << endl;
//             cout << "Code: " << course_code << ", Credits: " << credits << endl;
//         }
// };


// template<typename CourseCodeType>
// class CourseRecord{
//     private:
//         Course<CourseCodeType> course;
//         int grade;
//     public:
//         CourseRecord(Course<CourseCodeType> c, int g): course(c), grade(g) {}

//         int getGrade() const {
//             return grade;
//         }
        
//         Course<CourseCodeType> getCourse() const {
//             return course;
//         }
        
//         void display() const {
//             cout << "  - " << course.getCode() << ": Grade " << grade << endl;
//         }
// };


// template<typename RollNumType, typename CourseCodeType>
// class Student{
//     private:
//         string name;
//         RollNumType rollNum;
//         Branch branch;
//         int start_year;

//         vector<Course<CourseCodeType>> curr_courses;
//         vector<CourseRecord<CourseCodeType>> completed_courses;
        
//     public:
//         Student() : rollNum(RollNumType()), branch(Branch::UNKNOWN), start_year(0) {}
        
//         Student(string name, RollNumType rollNum, Branch branch, int start_year)
//         : name(name), rollNum(rollNum), branch(branch), start_year(start_year) {}
    
//         void addCurrentCourse(const Course<CourseCodeType>& course) {
//             curr_courses.push_back(course);
//         }
        
//         void addCompletedCourse(const Course<CourseCodeType>& course, int grade) {
//             completed_courses.push_back(CourseRecord<CourseCodeType>(course, grade));
//         }
        

//         string getName() const { return name; }
//         RollNumType getRollNum() const { return rollNum; }
//         Branch getBranch() const { return branch; }
//         int getStartYear() const { return start_year; }
        
//         vector<CourseRecord<CourseCodeType>> getCompletedCourses() const { 
//             return completed_courses; 
//         }

//         void display() const {
//             cout << "\n========================================" << endl;
//             cout << "Student Name: " << name << endl;
//             cout << "Roll Number: " << rollNum << endl;
//             cout << "Branch: " << branchToString(branch) << endl;
//             cout << "Start Year: " << start_year << endl;
            
//             cout << "\nCurrent Courses:" << endl;
//             if (curr_courses.empty()) {
//                 cout << "  None" << endl;
//             } else {
//                 for (const auto& course : curr_courses) {
//                     cout << "  - " << course.getCode() << endl;
//                 }
//             }
            
//             cout << "\nCompleted Courses:" << endl;
//             if (completed_courses.empty()) {
//                 cout << "  None" << endl;
//             } else {
//                 for (const auto& record : completed_courses) {
//                     record.display();
//                 }
//             }
//             cout << "========================================" << endl;
//         }
        
//         void displayBrief() const {
//             cout << rollNum << " | " << name << " | " 
//                  << branchToString(branch) << " | " << start_year << endl;
//         }
// };


// bool compareByRollNumber(const Student<int, string>& a, const Student<int, string>& b) {
//     return a.getRollNum() < b.getRollNum();
// }


// void merge(vector<Student<int, string>>& arr, int left, int mid, int right) {
//     vector<Student<int, string>> leftArr(arr.begin() + left, arr.begin() + mid + 1);
//     vector<Student<int, string>> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

//     int i = 0;
//     int j = 0;
//     int k = left;

//     while(i < leftArr.size() && j < rightArr.size()) {
//         if(compareByRollNumber(leftArr[i], rightArr[j])) {
//             arr[k++] = leftArr[i++];
//         } else {
//             arr[k++] = rightArr[j++];
//         }
//     }

//     while (i < leftArr.size()) {
//         arr[k++] = leftArr[i++];
//     }

//     while (j < rightArr.size()) {
//         arr[k++] = rightArr[j++];
//     }
// }

// // Utility function for recursive merge sort with threading
// void mergeSortUtil(vector<Student<int, string>>& arr, int left, int right, 
//                    int depth, int maxDepth, 
//                    chrono::high_resolution_clock::time_point threadStart,
//                    int threadId) {
    
//     if (left >= right) {
//         return;
//     }
    
//     int mid = (left + right) / 2;
    
//     // If we can create more threads
//     if (depth < maxDepth) {
//         cout << "  [Thread " << threadId << " @ Depth " << depth 
//              << "] Sorting range [" << left << ", " << right << "]" << endl;
        
//         // Create two threads for left and right halves
//         thread t1(mergeSortUtil, ref(arr), left, mid, depth + 1, maxDepth, threadStart, 2*threadId);
//         thread t2(mergeSortUtil, ref(arr), mid + 1, right, depth + 1, maxDepth, threadStart, 2*threadId + 1);
        
//         // Wait for both threads to complete
//         t1.join();
//         t2.join();
        
//     } else {
//         // Reached max depth, continue sequentially
//         mergeSortUtil(arr, left, mid, depth + 1, maxDepth, threadStart, threadId);
//         mergeSortUtil(arr, mid + 1, right, depth + 1, maxDepth, threadStart, threadId);
//     }
    
//     // Merge the sorted halves
//     merge(arr, left, mid, right);
// }

// // Main merge sort function
// void mergeSort(vector<Student<int, string>>& arr, int maxThreads = 2) {
    
//     if (arr.empty()) {
//         cerr << "Error: Array is empty!" << endl;
//         return;
//     }
    
//     // Calculate max depth based on number of threads
//     int maxDepth = 0;
//     int tempThreads = maxThreads;
//     while (tempThreads > 1) {
//         maxDepth++;
//         tempThreads /= 2;
//     }
    
//     cout << "\n========================================" << endl;
//     cout << "Starting Parallel Merge Sort" << endl;
//     cout << "Total students: " << arr.size() << endl;
//     cout << "Max threads: " << maxThreads << endl;
//     cout << "Max depth: " << maxDepth << endl;
//     cout << "========================================\n" << endl;
    
//     // Start timing
//     auto sortStart = chrono::high_resolution_clock::now();
    
//     // Call the utility function
//     mergeSortUtil(arr, 0, arr.size() - 1, 0, maxDepth, sortStart, 1);
    
//     // End timing
//     auto sortEnd = chrono::high_resolution_clock::now();
//     auto totalDuration = chrono::duration_cast<chrono::milliseconds>(sortEnd - sortStart);
    
//     cout << "\n========================================" << endl;
//     cout << "✅ Sorting Completed!" << endl;
//     cout << "Total time: " << totalDuration.count() << " ms" << endl;
//     cout << "========================================\n" << endl;
// }

// // Display sorted students
// void displaySortedStudents(const vector<Student<int, string>>& students, int count = 10) {
//     cout << "\n=== First " << count << " Sorted Students ===" << endl;
//     cout << "Roll No | Name" << endl;
//     cout << "----------------------------------------" << endl;
    
//     for (int i = 0; i < min(count, (int)students.size()); i++) {
//         cout << students[i].getRollNum() << " | " << students[i].getName() << endl;
//     }
// }


// class CSVLoader {
// public:
//     static vector<Student<int, string>> loadStudents(const string& filename) {
//         vector<Student<int, string>> students;
//         ifstream file(filename);
        
//         if (!file.is_open()) {
//             cerr << "Error: Could not open file " << filename << endl;
//             return students;
//         }
        
//         string line;
//         bool isHeader = true;
//         int lineCount = 0;
        
//         auto start_time = chrono::high_resolution_clock::now();
        
//         while (getline(file, line)) {
//             if (isHeader) {
//                 isHeader = false;
//                 continue;
//             }
            
//             lineCount++;
            
//             vector<string> fields;
//             stringstream ss(line);
//             string field;
            
//             while (getline(ss, field, ',')) {
//                 fields.push_back(field);
//             }
            
//             if (fields.size() < 6) {
//                 cerr << "Warning: Skipping malformed line " << lineCount << endl;
//                 continue;
//             }
            
//             string name = fields[0];
//             int roll_number = stoi(fields[1]);
//             Branch branch = stringToBranch(fields[2]);
//             int start_year = stoi(fields[3]);
//             string current_courses_str = fields[4];
//             string completed_courses_str = fields[5];
            
//             Student<int, string> student(name, roll_number, branch, start_year);
            
//             if (!current_courses_str.empty()) {
//                 vector<string> curr_courses = split(current_courses_str, ';');
//                 for (const string& course_code : curr_courses) {
//                     Course<string> course("", course_code, 4, "");
//                     student.addCurrentCourse(course);
//                 }
//             }
            
//             if (!completed_courses_str.empty()) {
//                 vector<string> comp_courses = split(completed_courses_str, ';');
//                 for (const string& course_grade : comp_courses) {
//                     vector<string> parts = split(course_grade, ':');
//                     if (parts.size() == 2) {
//                         string course_code = parts[0];
//                         int grade = stoi(parts[1]);
//                         Course<string> course("", course_code, 4, "");
//                         student.addCompletedCourse(course, grade);
//                     }
//                 }
//             }
            
//             students.push_back(student);
            
//             if (lineCount % 500 == 0) {
//                 cout << "Loaded " << lineCount << " students..." << endl;
//             }
//         }
        
//         file.close();
        
//         auto end_time = chrono::high_resolution_clock::now();
//         auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        
//         cout << "\n✅ Successfully loaded " << students.size() 
//              << " students in " << duration.count() << " ms" << endl;
        
//         return students;
//     }
// };


// template<typename RollNumType, typename CourseCodeType>
// class ERP {
//     private:
//         string collegeName;
//         vector<Course<CourseCodeType>> courses;
//         vector<Student<RollNumType, CourseCodeType>> students;

//     public:
//         ERP(string collegeName, vector<Student<RollNumType, CourseCodeType>> st, 
//             vector<Course<CourseCodeType>> cou)
//         : collegeName(collegeName), students(st), courses(cou) {}
// };


// int main() {
//     cout << "=== CSV Student Loader ===" << endl;
//     cout << "Loading students from CSV file...\n" << endl;
    
//     cout << "\n=== Demonstrating Template Flexibility ===" << endl;

//     // IIIT-Delhi student with string course codes
//     Course<string> iiitd_course("OOPD", "CSE201", 4, "OOPD");
//     Student<int, string> iiitd_student("Test Student 1", 9999001, Branch::CSE, 2023);
//     iiitd_student.addCurrentCourse(iiitd_course);
//     cout << "✅ IIIT-Delhi student created with string course codes" << endl;

//     // IIT-Delhi student with integer course codes
//     Course<int> iitd_course("Machine Learning", 401, 4, "ML");
//     Student<int, int> iitd_student("Test Student 2", 9999002, Branch::CSE, 2023);
//     iitd_student.addCurrentCourse(iitd_course);
//     cout << "✅ IIT-Delhi student created with integer course codes" << endl;

//     cout << "✅ Same template class handles both!\n" << endl;
    
//     // Load students from CSV
//     vector<Student<int, string>> students = CSVLoader::loadStudents("students_3000.csv");
    
//     if (students.empty()) {
//         cerr << "No students loaded. Please check if 'students_3000.csv' exists." << endl;
//         return 1;
//     }
    
//     cout << "\n=== Statistics ===" << endl;
//     cout << "Total students loaded: " << students.size() << endl;
    
//     int cse_count = 0, ece_count = 0;
//     for (const auto& student : students) {
//         if (student.getBranch() == Branch::CSE) cse_count++;
//         else if (student.getBranch() == Branch::ECE) ece_count++;
//     }
    
//     cout << "CSE Students: " << cse_count << endl;
//     cout << "ECE Students: " << ece_count << endl;
    
//     cout << "\n=== First 10 Students (Original Order) ===" << endl;
//     cout << "Roll No | Name | Branch | Year" << endl;
//     cout << "----------------------------------------" << endl;
//     for (int i = 0; i < min(10, (int)students.size()); i++) {
//         students[i].displayBrief();
//     }
    
//     // ========== SORTING STARTS HERE ==========
//     cout << "\n\n=====================================" << endl;
//     cout << "QUESTION 3: PARALLEL MERGE SORT" << endl;
//     cout << "=====================================" << endl;
    
//     // Create a copy for sorting
//     vector<Student<int, string>> studentsCopy = students;
    
//     // Perform parallel merge sort with 2 threads
//     mergeSort(studentsCopy, 2);
    
//     // Display sorted results
//     displaySortedStudents(studentsCopy, 10);
    
//     // Verify sorting is correct
//     bool isSorted = true;
//     for (int i = 0; i < (int)studentsCopy.size() - 1; i++) {
//         if (studentsCopy[i].getRollNum() > studentsCopy[i+1].getRollNum()) {
//             isSorted = false;
//             break;
//         }
//     }
    
//     cout << "\n" << (isSorted ? "✅ Array is correctly sorted!" : "❌ Array is NOT correctly sorted!") << endl;
    
//     cout << "\n✅ Program completed successfully!" << endl;
    
//     return 0;
// }



#include <iostream>
#include <vector>
#include <sstream>   
#include <fstream>   
#include <chrono>    
#include <iomanip>
#include <thread>
#include <mutex>
#include <map>
#include <set>
#include <algorithm>
#include <memory>
using namespace std;

// ==================== ENUMS AND UTILITIES ====================

enum class Branch {
    CSE,
    ECE,
    CSAM,
    CSD,
    CSSS,
    UNKNOWN
};

Branch stringToBranch(const string& branchStr) {
    if (branchStr == "CSE") return Branch::CSE;
    if (branchStr == "ECE") return Branch::ECE;
    if (branchStr == "CSAM") return Branch::CSAM;
    if (branchStr == "CSD") return Branch::CSD;
    if (branchStr == "CSSS") return Branch::CSSS;
    return Branch::UNKNOWN;
}

string branchToString(Branch b) {
    switch(b) {
        case Branch::CSE: return "CSE";
        case Branch::ECE: return "ECE";
        case Branch::CSAM: return "CSAM";
        case Branch::CSD: return "CSD";
        case Branch::CSSS: return "CSSS";
        default: return "UNKNOWN";
    }
}

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

// ==================== QUESTION 1: TEMPLATE CLASSES ====================

template<typename CourseCodeType>
class Course {
private:
    string course_name;
    CourseCodeType course_code;
    unsigned int credits;
    string acronym;

public:
    Course() : course_code(CourseCodeType()), credits(0) {}
    
    Course(string name, CourseCodeType code, unsigned int cred, string acr)
        : course_name(name), course_code(code), credits(cred), acronym(acr) {}
    
    CourseCodeType getCode() const { return course_code; }
    string getName() const { return course_name; }
    unsigned int getCredits() const { return credits; }
    string getAcronym() const { return acronym; }

    void display() const {
        cout << "Course: " << course_name << " (" << acronym << ")" << endl;
        cout << "Code: " << course_code << ", Credits: " << credits << endl;
    }
};

template<typename CourseCodeType>
class CourseRecord {
private:
    Course<CourseCodeType> course;
    int grade;

public:
    CourseRecord() : grade(0) {}
    
    CourseRecord(Course<CourseCodeType> c, int g) : course(c), grade(g) {}

    int getGrade() const { return grade; }
    Course<CourseCodeType> getCourse() const { return course; }
    CourseCodeType getCourseCode() const { return course.getCode(); }
    
    void display() const {
        cout << "  - " << course.getCode() << ": Grade " << grade << endl;
    }
};

template<typename RollNumType, typename CourseCodeType>
class Student {
private:
    string name;
    RollNumType rollNum;
    Branch branch;
    int start_year;
    vector<Course<CourseCodeType>> curr_courses;
    vector<CourseRecord<CourseCodeType>> completed_courses;
    
public:
    Student() : rollNum(RollNumType()), branch(Branch::UNKNOWN), start_year(0) {}
    
    Student(string name, RollNumType rollNum, Branch branch, int start_year)
        : name(name), rollNum(rollNum), branch(branch), start_year(start_year) {}
    
    // Mutators
    void addCurrentCourse(const Course<CourseCodeType>& course) {
        curr_courses.push_back(course);
    }
    
    void addCompletedCourse(const Course<CourseCodeType>& course, int grade) {
        completed_courses.push_back(CourseRecord<CourseCodeType>(course, grade));
    }
    
    // Accessors
    string getName() const { return name; }
    RollNumType getRollNum() const { return rollNum; }
    Branch getBranch() const { return branch; }
    int getStartYear() const { return start_year; }
    
    const vector<Course<CourseCodeType>>& getCurrentCourses() const { 
        return curr_courses; 
    }
    
    const vector<CourseRecord<CourseCodeType>>& getCompletedCourses() const { 
        return completed_courses; 
    }

    void display() const {
        cout << "\n========================================" << endl;
        cout << "Student Name: " << name << endl;
        cout << "Roll Number: " << rollNum << endl;
        cout << "Branch: " << branchToString(branch) << endl;
        cout << "Start Year: " << start_year << endl;
        
        cout << "\nCurrent Courses:" << endl;
        if (curr_courses.empty()) {
            cout << "  None" << endl;
        } else {
            for (const auto& course : curr_courses) {
                cout << "  - " << course.getCode() << endl;
            }
        }
        
        cout << "\nCompleted Courses:" << endl;
        if (completed_courses.empty()) {
            cout << "  None" << endl;
        } else {
            for (const auto& record : completed_courses) {
                record.display();
            }
        }
        cout << "========================================" << endl;
    }
    
    void displayBrief() const {
        cout << rollNum << " | " << name << " | " 
             << branchToString(branch) << " | " << start_year << endl;
    }
};

// ==================== QUESTION 3: PARALLEL SORTING ====================

mutex coutMutex;

template<typename RollNumType, typename CourseCodeType>
bool compareByRollNumber(const Student<RollNumType, CourseCodeType>& a, 
                         const Student<RollNumType, CourseCodeType>& b) {
    return a.getRollNum() < b.getRollNum();
}

template<typename RollNumType, typename CourseCodeType>
void merge(vector<Student<RollNumType, CourseCodeType>>& arr, int left, int mid, int right) {
    vector<Student<RollNumType, CourseCodeType>> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<Student<RollNumType, CourseCodeType>> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;

    while(i < leftArr.size() && j < rightArr.size()) {
        if(compareByRollNumber(leftArr[i], rightArr[j])) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < leftArr.size()) arr[k++] = leftArr[i++];
    while (j < rightArr.size()) arr[k++] = rightArr[j++];
}

template<typename RollNumType, typename CourseCodeType>
void mergeSortSequential(vector<Student<RollNumType, CourseCodeType>>& arr, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSortSequential(arr, left, mid);
    mergeSortSequential(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

template<typename RollNumType, typename CourseCodeType>
void mergeSortThread(vector<Student<RollNumType, CourseCodeType>>& arr, 
                     int left, int right, int threadId) {
    auto threadStart = chrono::high_resolution_clock::now();
    
    {
        lock_guard<mutex> lock(coutMutex);
        cout << "[Thread " << threadId << "] Started: sorting range [" 
             << left << ", " << right << "] (" << (right - left + 1) << " students)" << endl;
    }
    
    mergeSortSequential(arr, left, right);
    
    auto threadEnd = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(threadEnd - threadStart);
    
    {
        lock_guard<mutex> lock(coutMutex);
        cout << "[Thread " << threadId << "] Completed in " 
             << duration.count() << " ms" << endl;
    }
}

template<typename RollNumType, typename CourseCodeType>
void parallelMergeSort(vector<Student<RollNumType, CourseCodeType>>& arr, int numThreads = 2) {
    if (arr.empty()) {
        cerr << "Error: Cannot sort empty array!" << endl;
        return;
    }
    
    cout << "\n========================================" << endl;
    cout << "PARALLEL MERGE SORT" << endl;
    cout << "========================================" << endl;
    cout << "Total students: " << arr.size() << endl;
    cout << "Number of threads: " << numThreads << endl;
    cout << "========================================\n" << endl;
    
    auto sortStart = chrono::high_resolution_clock::now();
    
    vector<thread> threads;
    int chunkSize = arr.size() / numThreads;
    
    // Create threads for sorting chunks
    for (int i = 0; i < numThreads; i++) {
        int left = i * chunkSize;
        int right = (i == numThreads - 1) ? arr.size() - 1 : (i + 1) * chunkSize - 1;
        threads.emplace_back(mergeSortThread<RollNumType, CourseCodeType>, 
                           ref(arr), left, right, i + 1);
    }
    
    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }
    
    cout << "\n[Main Thread] All sorting threads completed. Merging chunks..." << endl;
    
    // Merge all sorted chunks sequentially
    for (int i = 1; i < numThreads; i++) {
        int left = 0;
        int mid = i * chunkSize - 1;
        int right = (i == numThreads - 1) ? arr.size() - 1 : (i + 1) * chunkSize - 1;
        merge(arr, left, mid, right);
    }
    
    auto sortEnd = chrono::high_resolution_clock::now();
    auto totalDuration = chrono::duration_cast<chrono::milliseconds>(sortEnd - sortStart);
    
    cout << "\n========================================" << endl;
    cout << "✅ SORTING COMPLETED!" << endl;
    cout << "Total time: " << totalDuration.count() << " ms" << endl;
    cout << "========================================\n" << endl;
}

// ==================== QUESTION 4: ITERATORS ====================

// Original Order Iterator (Forward Iterator)
template<typename RollNumType, typename CourseCodeType>
class OriginalOrderIterator {
private:
    const vector<Student<RollNumType, CourseCodeType>>* students;
    size_t index;
    
public:
    OriginalOrderIterator(const vector<Student<RollNumType, CourseCodeType>>* vec, size_t idx = 0) 
        : students(vec), index(idx) {}
    
    const Student<RollNumType, CourseCodeType>& operator*() const {
        return (*students)[index];
    }
    
    const Student<RollNumType, CourseCodeType>* operator->() const {
        return &(*students)[index];
    }
    
    OriginalOrderIterator& operator++() {
        ++index;
        return *this;
    }
    
    OriginalOrderIterator operator++(int) {
        OriginalOrderIterator temp = *this;
        ++index;
        return temp;
    }
    
    bool operator!=(const OriginalOrderIterator& other) const {
        return index != other.index;
    }
    
    bool operator==(const OriginalOrderIterator& other) const {
        return index == other.index;
    }
    
    bool hasNext() const {
        return index < students->size();
    }
};

// Sorted Order Iterator (uses index mapping - NO DATA COPY)
template<typename RollNumType, typename CourseCodeType>
class SortedOrderIterator {
private:
    const vector<Student<RollNumType, CourseCodeType>>* students;
    vector<size_t> sortedIndices;
    size_t position;
    
public:
    SortedOrderIterator(const vector<Student<RollNumType, CourseCodeType>>* vec) 
        : students(vec), position(0) {
        
        // Create index array
        for (size_t i = 0; i < vec->size(); i++) {
            sortedIndices.push_back(i);
        }
        
        // Sort indices based on roll number (NOT copying student objects)
        sort(sortedIndices.begin(), sortedIndices.end(), 
             [vec](size_t a, size_t b) {
                 return compareByRollNumber((*vec)[a], (*vec)[b]);
             });
    }
    
    const Student<RollNumType, CourseCodeType>& operator*() const {
        return (*students)[sortedIndices[position]];
    }
    
    const Student<RollNumType, CourseCodeType>* operator->() const {
        return &(*students)[sortedIndices[position]];
    }
    
    SortedOrderIterator& operator++() {
        ++position;
        return *this;
    }
    
    SortedOrderIterator operator++(int) {
        SortedOrderIterator temp = *this;
        ++position;
        return temp;
    }
    
    bool hasNext() const {
        return position < sortedIndices.size();
    }
    
    void reset() {
        position = 0;
    }
    
    size_t getPosition() const {
        return position;
    }
};

// Reverse Order Iterator (Bidirectional Iterator)
template<typename RollNumType, typename CourseCodeType>
class ReverseOrderIterator {
private:
    const vector<Student<RollNumType, CourseCodeType>>* students;
    int index;
    
public:
    ReverseOrderIterator(const vector<Student<RollNumType, CourseCodeType>>* vec) 
        : students(vec), index(vec->size() - 1) {}
    
    const Student<RollNumType, CourseCodeType>& operator*() const {
        return (*students)[index];
    }
    
    const Student<RollNumType, CourseCodeType>* operator->() const {
        return &(*students)[index];
    }
    
    ReverseOrderIterator& operator++() {
        --index;
        return *this;
    }
    
    ReverseOrderIterator operator++(int) {
        ReverseOrderIterator temp = *this;
        --index;
        return temp;
    }
    
    ReverseOrderIterator& operator--() {
        ++index;
        return *this;
    }
    
    ReverseOrderIterator operator--(int) {
        ReverseOrderIterator temp = *this;
        ++index;
        return temp;
    }
    
    bool hasNext() const {
        return index >= 0;
    }
};

// ==================== QUESTION 5: QUICK LOOKUP ====================

template<typename RollNumType, typename CourseCodeType>
class CourseGradeIndex {
private:
    // Map: CourseCode -> Map: Grade -> Set of student indices
    map<CourseCodeType, map<int, set<size_t>>> gradeIndex;
    const vector<Student<RollNumType, CourseCodeType>>* students;
    
public:
    CourseGradeIndex(const vector<Student<RollNumType, CourseCodeType>>* vec) 
        : students(vec) {
        buildIndex();
    }
    
    void buildIndex() {
        cout << "\n[Index Builder] Building course-grade index..." << endl;
        auto start = chrono::high_resolution_clock::now();
        
        for (size_t i = 0; i < students->size(); i++) {
            const auto& student = (*students)[i];
            const auto& completed = student.getCompletedCourses();
            
            for (const auto& record : completed) {
                CourseCodeType courseCode = record.getCourseCode();
                int grade = record.getGrade();
                
                gradeIndex[courseCode][grade].insert(i);
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        cout << "✅ Index built in " << duration.count() << " ms" << endl;
        cout << "   Indexed " << gradeIndex.size() << " unique courses" << endl;
    }
    
    vector<const Student<RollNumType, CourseCodeType>*> 
    findStudentsWithMinGrade(const CourseCodeType& courseCode, int minGrade) {
        vector<const Student<RollNumType, CourseCodeType>*> result;
        
        auto courseIt = gradeIndex.find(courseCode);
        if (courseIt == gradeIndex.end()) {
            return result; // Course not found
        }
        
        // Collect all students with grade >= minGrade
        set<size_t> studentIndices;
        for (const auto& [grade, indices] : courseIt->second) {
            if (grade >= minGrade) {
                studentIndices.insert(indices.begin(), indices.end());
            }
        }
        
        // Convert indices to student pointers (NO COPYING)
        for (size_t idx : studentIndices) {
            result.push_back(&(*students)[idx]);
        }
        
        return result;
    }
    
    void displayStatistics() const {
        cout << "\n=== Course-Grade Index Statistics ===" << endl;
        cout << "Total unique courses: " << gradeIndex.size() << endl;
        
        if (!gradeIndex.empty()) {
            cout << "\nSample courses (up to 10):" << endl;
            int count = 0;
            for (const auto& [courseCode, gradeMap] : gradeIndex) {
                if (count++ >= 10) break;
                
                int totalStudents = 0;
                for (const auto& [grade, indices] : gradeMap) {
                    totalStudents += indices.size();
                }
                
                cout << "  Course " << courseCode << ": " 
                     << totalStudents << " students enrolled" << endl;
            }
        }
    }
};

// ==================== CSV LOADER ====================

class CSVLoader {
public:
    static vector<Student<int, string>> loadStudents(const string& filename) {
        vector<Student<int, string>> students;
        ifstream file(filename);
        
        if (!file.is_open()) {
            cerr << "Error: Could not open file '" << filename << "'" << endl;
            return students;
        }
        
        cout << "\n[CSV Loader] Reading from: " << filename << endl;
        
        string line;
        bool isHeader = true;
        int lineCount = 0;
        
        auto start_time = chrono::high_resolution_clock::now();
        
        while (getline(file, line)) {
            if (isHeader) {
                isHeader = false;
                continue;
            }
            
            lineCount++;
            
            vector<string> fields;
            stringstream ss(line);
            string field;
            
            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }
            
            if (fields.size() < 6) {
                cerr << "Warning: Skipping malformed line " << lineCount << endl;
                continue;
            }
            
            try {
                string name = fields[0];
                int roll_number = stoi(fields[1]);
                Branch branch = stringToBranch(fields[2]);
                int start_year = stoi(fields[3]);
                string current_courses_str = fields[4];
                string completed_courses_str = fields[5];
                
                Student<int, string> student(name, roll_number, branch, start_year);
                
                if (!current_courses_str.empty()) {
                    vector<string> curr_courses = split(current_courses_str, ';');
                    for (const string& course_code : curr_courses) {
                        Course<string> course("", course_code, 4, "");
                        student.addCurrentCourse(course);
                    }
                }
                
                if (!completed_courses_str.empty()) {
                    vector<string> comp_courses = split(completed_courses_str, ';');
                    for (const string& course_grade : comp_courses) {
                        vector<string> parts = split(course_grade, ':');
                        if (parts.size() == 2) {
                            string course_code = parts[0];
                            int grade = stoi(parts[1]);
                            Course<string> course("", course_code, 4, "");
                            student.addCompletedCourse(course, grade);
                        }
                    }
                }
                
                students.push_back(student);
                
                if (lineCount % 500 == 0) {
                    cout << "  Loaded " << lineCount << " students..." << endl;
                }
            } catch (const exception& e) {
                cerr << "Error parsing line " << lineCount << ": " << e.what() << endl;
            }
        }
        
        file.close();
        
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        
        cout << "\n✅ Successfully loaded " << students.size() 
             << " students in " << duration.count() << " ms" << endl;
        
        return students;
    }
};

// ==================== ERP CLASS ====================

template<typename RollNumType, typename CourseCodeType>
class ERP {
private:
    string universityName;
    vector<Student<RollNumType, CourseCodeType>> students;
    vector<Course<CourseCodeType>> courses;

public:
    ERP(string name) : universityName(name) {}
    
    ERP(string name, vector<Student<RollNumType, CourseCodeType>> st, 
        vector<Course<CourseCodeType>> cou)
        : universityName(name), students(st), courses(cou) {}
    
    void addStudent(const Student<RollNumType, CourseCodeType>& student) {
        students.push_back(student);
    }
    
    void addCourse(const Course<CourseCodeType>& course) {
        courses.push_back(course);
    }
    
    const vector<Student<RollNumType, CourseCodeType>>& getStudents() const {
        return students;
    }
    
    string getUniversityName() const {
        return universityName;
    }
};

void displayMainMenu() {
    cout << "\n================================================" << endl;
    cout << "  UNIVERSITY ERP SYSTEM - ASSIGNMENT 4" << endl;
    cout << "  Templates and Threads" << endl;
    cout << "================================================" << endl;
    cout << "1. Display Student Records (Original Order)" << endl;
    cout << "2. Display Student Records (Sorted by Roll Number)" << endl;
    cout << "3. Display Student Records (Reverse Order)" << endl;
    cout << "4. Perform Parallel Sorting" << endl;
    cout << "5. Find Students with Minimum Grade in Course" << endl;
    cout << "6. Display System Statistics" << endl;
    cout << "7. Demonstrate Template Flexibility (IIIT-D vs IIT-D)" << endl;
    cout << "8. Exit" << endl;
    cout << "================================================" << endl;
    cout << "Enter your choice (1-8): ";
}

void displayStudentsOriginal(const vector<Student<int, string>>& students, int limit = 0) {
    cout << "\n--- STUDENTS IN ORIGINAL ORDER ---" << endl;
    cout << "Roll No | Name | Branch | Year" << endl;
    cout << "----------------------------------------" << endl;
    
    OriginalOrderIterator<int, string> origIter(&students);
    int count = 0;
    while (origIter.hasNext() && (limit == 0 || count < limit)) {
        (*origIter).displayBrief();
        ++origIter;
        count++;
    }
    cout << "Total displayed: " << count << " students" << endl;
}

void displayStudentsSorted(const vector<Student<int, string>>& students, int limit = 0) {
    cout << "\n--- STUDENTS SORTED BY ROLL NUMBER ---" << endl;
    cout << "Roll No | Name | Branch | Year" << endl;
    cout << "----------------------------------------" << endl;
    
    SortedOrderIterator<int, string> sortedIter(&students);
    int count = 0;
    while (sortedIter.hasNext() && (limit == 0 || count < limit)) {
        (*sortedIter).displayBrief();
        ++sortedIter;
        count++;
    }
    cout << "Total displayed: " << count << " students" << endl;
}

void displayStudentsReverse(const vector<Student<int, string>>& students, int limit = 0) {
    cout << "\n--- STUDENTS IN REVERSE ORDER ---" << endl;
    cout << "Roll No | Name | Branch | Year" << endl;
    cout << "----------------------------------------" << endl;
    
    ReverseOrderIterator<int, string> revIter(&students);
    int count = 0;
    while (revIter.hasNext() && (limit == 0 || count < limit)) {
        (*revIter).displayBrief();
        ++revIter;
        count++;
    }
    cout << "Total displayed: " << count << " students" << endl;
}

void performParallelSorting(vector<Student<int, string>>& students) {
    if (students.empty()) {
        cout << "❌ No students available for sorting!" << endl;
        return;
    }
    
    int numThreads;
    cout << "Enter number of threads for sorting (default 2): ";
    string threadInput;
    cin >> threadInput;
    
    try {
        numThreads = stoi(threadInput);
        if (numThreads < 1) numThreads = 2;
    } catch (...) {
        numThreads = 2;
    }
    
    // Create a copy for sorting
    vector<Student<int, string>> sortedStudents = students;
    parallelMergeSort(sortedStudents, numThreads);
    
    // Verify sorting
    bool isSorted = true;
    for (size_t i = 0; i < sortedStudents.size() - 1; i++) {
        if (sortedStudents[i].getRollNum() > sortedStudents[i+1].getRollNum()) {
            isSorted = false;
            break;
        }
    }
    
    if (isSorted) {
        cout << "✅ Sorting verification: SUCCESS - Array is correctly sorted!" << endl;
        
        char saveChoice;
        cout << "Do you want to keep this sorted order? (y/n): ";
        cin >> saveChoice;
        
        if (tolower(saveChoice) == 'y') {
            students = sortedStudents;
            cout << "✅ Sorted order saved!" << endl;
        }
    } else {
        cout << "❌ Sorting verification: FAILED - Array is not sorted correctly!" << endl;
    }
}

void findStudentsByGrade(const vector<Student<int, string>>& students) {
    if (students.empty()) {
        cout << "❌ No students available!" << endl;
        return;
    }
    
    // Build index first
    cout << "Building course-grade index..." << endl;
    CourseGradeIndex<int, string> gradeIndex(&students);
    gradeIndex.displayStatistics();
    
    string courseCode;
    int minGrade;
    
    cout << "\nEnter course code (e.g., CSE201): ";
    cin >> courseCode;
    
    cout << "Enter minimum grade (0-10): ";
    cin >> minGrade;
    
    if (minGrade < 0 || minGrade > 10) {
        cout << "❌ Invalid grade! Please enter between 0-10." << endl;
        return;
    }
    
    auto highAchievers = gradeIndex.findStudentsWithMinGrade(courseCode, minGrade);
    
    cout << "\n=== STUDENTS WITH GRADE >= " << minGrade << " IN " << courseCode << " ===" << endl;
    cout << "Found: " << highAchievers.size() << " students" << endl;
    cout << "Roll No | Name | Branch | Year" << endl;
    cout << "----------------------------------------" << endl;
    
    if (highAchievers.empty()) {
        cout << "No students found matching the criteria." << endl;
    } else {
        for (const auto* student : highAchievers) {
            student->displayBrief();
        }
    }
}

void displaySystemStatistics(const vector<Student<int, string>>& students) {
    cout << "\n=== SYSTEM STATISTICS ===" << endl;
    cout << "Total students: " << students.size() << endl;
    
    // Branch statistics
    map<Branch, int> branchCount;
    int totalCourses = 0;
    int studentsWithCompletedCourses = 0;
    
    for (const auto& student : students) {
        branchCount[student.getBranch()]++;
        totalCourses += student.getCompletedCourses().size();
        if (!student.getCompletedCourses().empty()) {
            studentsWithCompletedCourses++;
        }
    }
    
    cout << "\n--- Branch Distribution ---" << endl;
    for (const auto& [branch, count] : branchCount) {
        cout << branchToString(branch) << ": " << count << " students (" 
             << (count * 100.0 / students.size()) << "%)" << endl;
    }
    
    cout << "\n--- Course Statistics ---" << endl;
    cout << "Total completed courses: " << totalCourses << endl;
    cout << "Average courses per student: " << (students.empty() ? 0 : (double)totalCourses / students.size()) << endl;
    cout << "Students with completed courses: " << studentsWithCompletedCourses << endl;
    
    // Year statistics
    map<int, int> yearCount;
    for (const auto& student : students) {
        yearCount[student.getStartYear()]++;
    }
    
    cout << "\n--- Year Distribution ---" << endl;
    for (const auto& [year, count] : yearCount) {
        cout << year << ": " << count << " students" << endl;
    }
}

void demonstrateTemplateFlexibility() {
    cout << "\n=== TEMPLATE FLEXIBILITY DEMONSTRATION ===" << endl;
    
    cout << "\n[IIIT-Delhi System]" << endl;
    cout << "Roll Number Type: int, Course Code Type: string" << endl;
    
    Course<string> iiitd_course1("Object Oriented Programming", "CSE201", 4, "OOPD");
    Course<string> iiitd_course2("Data Structures", "CSE102", 4, "DSA");
    
    Student<int, string> iiitd_student("Rajesh Kumar", 2023001, Branch::CSE, 2023);
    iiitd_student.addCurrentCourse(iiitd_course1);
    iiitd_student.addCompletedCourse(iiitd_course2, 9);
    
    iiitd_student.display();
    
    cout << "\n[IIT-Delhi System]" << endl;
    cout << "Roll Number Type: int, Course Code Type: int" << endl;
    
    Course<int> iitd_course1("Machine Learning", 401, 4, "ML");
    Course<int> iitd_course2("Artificial Intelligence", 301, 4, "AI");
    
    Student<int, int> iitd_student("Priya Sharma", 2023002, Branch::CSE, 2023);
    iitd_student.addCurrentCourse(iitd_course1);
    iitd_student.addCompletedCourse(iitd_course2, 10);
    
    iitd_student.display();
    
    cout << "\n✅ SAME template class handles BOTH university systems!" << endl;
}

int main() {
    // Load students from CSV
    cout << "Loading student data..." << endl;
    vector<Student<int, string>> students = CSVLoader::loadStudents("students_3000.csv");
    
    // If CSV loading fails, create sample data
    if (students.empty()) {
        cout << "⚠️  Creating sample data for demonstration..." << endl;
        for (int i = 0; i < 100; i++) {
            int rollNum = 2023001 + i;
            Student<int, string> s("Student_" + to_string(i), rollNum, 
                                   (i % 2 == 0) ? Branch::CSE : Branch::ECE, 2023 + (i % 3));
            
            Course<string> c1("OOPD", "CSE201", 4, "OOPD");
            Course<string> c2("DSA", "CSE102", 4, "DSA");
            Course<string> c3("Math", "MTH101", 3, "MATH");
            
            s.addCompletedCourse(c1, 6 + (i % 5));
            s.addCompletedCourse(c2, 7 + (i % 4));
            if (i % 3 == 0) {
                s.addCompletedCourse(c3, 8 + (i % 3));
            }
            
            students.push_back(s);
        }
        cout << "✅ Created " << students.size() << " sample students" << endl;
    }
    
    // Interactive menu loop
    int choice;
    bool exitProgram = false;
    
    while (!exitProgram) {
        displayMainMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int limit;
                cout << "Enter number of students to display (0 for all): ";
                cin >> limit;
                displayStudentsOriginal(students, limit);
                break;
            }
            case 2: {
                int limit;
                cout << "Enter number of students to display (0 for all): ";
                cin >> limit;
                displayStudentsSorted(students, limit);
                break;
            }
            case 3: {
                int limit;
                cout << "Enter number of students to display (0 for all): ";
                cin >> limit;
                displayStudentsReverse(students, limit);
                break;
            }
            case 4:
                performParallelSorting(students);
                break;
            case 5:
                findStudentsByGrade(students);
                break;
            case 6:
                displaySystemStatistics(students);
                break;
            case 7:
                demonstrateTemplateFlexibility();
                break;
            case 8:
                cout << "Thank you for using University ERP System. Goodbye!" << endl;
                exitProgram = true;
                break;
            default:
                cout << "❌ Invalid choice! Please enter 1-8." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
        
        if (!exitProgram) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
    
    return 0;
}