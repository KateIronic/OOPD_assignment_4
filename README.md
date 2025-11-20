# University ERP System - Assignment 4

## 📚 Assignment Overview
**Object-Oriented Programming and Design - Monsoon 2025**  
**Assignment 4 - Templates and Threads**  
**Total Marks: 200**

A comprehensive University ERP system implementing C++ templates, multithreading, and advanced OOP concepts.

## 🎯 Features Implemented

### ✅ Question 1: Template Class for University ERP
- Generic `Student<RollNumType, CourseCodeType>` class
- Supports different data types for roll numbers and course codes
- Full data abstraction and encapsulation

### ✅ Question 2: Multi-University Compatibility
- **IIIT-Delhi**: `int` roll numbers + `string` course codes
- **IIT-Delhi**: `int` roll numbers + `int` course codes
- Same template class handles both systems

### ✅ Question 3: Parallel Sorting
- Multi-threaded merge sort implementation
- Configurable thread count
- Thread-safe logging with performance timing
- Handles 3000+ student records

### ✅ Question 4: Zero-Copy Iterators
- **OriginalOrderIterator**: Insertion order
- **SortedOrderIterator**: Index mapping (no data copy)
- **ReverseOrderIterator**: Bidirectional traversal

### ✅ Question 5: Efficient Grade Lookup
- `CourseGradeIndex` for O(1) lookups
- Fast `findStudentsWithMinGrade()` method
- No linear search required

## 🏗️ Project Structure

### Source Files:
- `main.cpp` - Interactive CLI application
- `CSVgenerator.cpp` - Student data generator
- `students_3000.csv` - Generated dataset

### Executables:
- `erp_system` - Main ERP application
- `csv_generator` - CSV data generator

## 🚀 Quick Start

### Build:
```bash
make all
