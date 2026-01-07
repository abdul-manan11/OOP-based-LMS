#include "admin.h"
#include "database.h"
#include "student.h"      // Added: For Student class definition
#include "faculty.h"      // Added: For Faculty class definition
#include "course.h"       // Added: For Course class definition
#include <QDebug>

Admin::Admin() : Person(), adminDepartment("") {}

Admin::Admin(QString id, QString name, QString email, QString password,
             QDate dob, QString department)
    : Person(id, name, email, password, dob), adminDepartment(department) {}

void Admin::displayInfo() {
    qDebug() << "Admin ID:" << personId;
    qDebug() << "Name:" << personName;
    qDebug() << "Email:" << personEmail;
    qDebug() << "Department:" << adminDepartment;
}

QString Admin::getRole() {
    return "Admin";
}

QString Admin::getDepartment() const {
    return adminDepartment;
}

void Admin::setDepartment(QString department) {
    adminDepartment = department;
}

void Admin::addStudent(QString studentId, QString name, QString email, QDate dob) {
    Database* db = Database::getInstance();

    // Check if student already exists
    if (db->getStudent(studentId)) {
        qDebug() << "Student with ID" << studentId << "already exists!";
        return;
    }

    // Create new student with default values
    QString rollNumber = studentId; // Using ID as roll number
    QString password = "password123"; // Default password
    QString department = "Computer Science"; // Default department
    int semester = 1; // Default semester

    Student* student = new Student(studentId, rollNumber, name, email, password,
                                   dob, department, semester);
    db->addStudent(student);
    db->saveAllData(); // Save immediately

    qDebug() << "Student added:" << name << "(" << studentId << ")";
}

void Admin::removeStudent(QString studentId) {
    Database* db = Database::getInstance();
    Student* student = db->getStudent(studentId);

    if (student) {
        db->removeStudent(studentId);
        db->saveAllData(); // Save immediately
        qDebug() << "Student removed:" << studentId;
    } else {
        qDebug() << "Student not found:" << studentId;
    }
}

void Admin::addFaculty(QString facultyId, QString name, QString email, QDate dob, QString department) {
    Database* db = Database::getInstance();

    // Check if faculty already exists
    if (db->getFaculty(facultyId)) {
        qDebug() << "Faculty with ID" << facultyId << "already exists!";
        return;
    }

    // Create new faculty with default values
    QString password = "password123"; // Default password
    QString designation = "Professor"; // Default designation

    Faculty* faculty = new Faculty(facultyId, name, email, password, dob, department, designation);
    db->addFaculty(faculty);
    db->saveAllData(); // Save immediately

    qDebug() << "Faculty added:" << name << "(" << facultyId << ")";
}

void Admin::removeFaculty(QString facultyId) {
    Database* db = Database::getInstance();
    Faculty* faculty = db->getFaculty(facultyId);

    if (faculty) {
        db->removeFaculty(facultyId);
        db->saveAllData(); // Save immediately
        qDebug() << "Faculty removed:" << facultyId;
    } else {
        qDebug() << "Faculty not found:" << facultyId;
    }
}

void Admin::addCourse(QString courseCode, QString courseName, QString facultyId) {
    Database* db = Database::getInstance();

    // Check if course already exists
    if (db->getCourse(courseCode)) {
        qDebug() << "Course with code" << courseCode << "already exists!";
        return;
    }

    // Check if faculty exists
    if (!db->getFaculty(facultyId)) {
        qDebug() << "Faculty with ID" << facultyId << "not found!";
        return;
    }

    // Create new course with default values
    QString description = "Course description for " + courseName;
    int creditHours = 3; // Default credit hours

    Course* course = new Course(courseCode, courseName, description, facultyId, creditHours);
    db->addCourse(course);
    db->saveAllData(); // Save immediately

    qDebug() << "Course added:" << courseName << "(" << courseCode << ")";
}

void Admin::removeCourse(QString courseCode) {
    Database* db = Database::getInstance();
    Course* course = db->getCourse(courseCode);

    if (course) {
        db->removeCourse(courseCode);
        db->saveAllData(); // Save immediately
        qDebug() << "Course removed:" << courseCode;
    } else {
        qDebug() << "Course not found:" << courseCode;
    }
}
