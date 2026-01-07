#include "student.h"
#include "database.h"
#include <QDebug>
#include <QMessageBox>

Student::Student()
    : Person(), studentRollNumber(""), studentDepartment(""), currentSemester(1) {}

Student::Student(QString id, QString roll, QString name, QString email, QString password,
                 QDate dob, QString department, int semester)
    : Person(id, name, email, password, dob),
    studentRollNumber(roll),
    studentDepartment(department),
    currentSemester(semester) {}

void Student::displayInfo() {
    qDebug() << "Student ID:" << personId;
    qDebug() << "Roll Number:" << studentRollNumber;
    qDebug() << "Name:" << personName;
    qDebug() << "Email:" << personEmail;
    qDebug() << "Department:" << studentDepartment;
    qDebug() << "Semester:" << currentSemester;
}

QString Student::getRole() { return "Student"; }

QString Student::getRollNumber() const { return studentRollNumber; }
QString Student::getDepartment() const { return studentDepartment; }
int Student::getSemester() const { return currentSemester; }
QVector<Course*> Student::getRegisteredCourses() const { return registeredCourses; }
QMap<QString, double> Student::getCourseGrades() const { return courseGrades; }
QMap<QString, double> Student::getCourseAttendance() const { return courseAttendance; }

void Student::setRollNumber(QString roll) { studentRollNumber = roll; }
void Student::setDepartment(QString department) { studentDepartment = department; }
void Student::setSemester(int semester) { currentSemester = semester; }

void Student::addGrade(QString courseCode, double grade) {
    courseGrades[courseCode] = grade;
}

void Student::addAttendance(QString courseCode, double attendance) {
    courseAttendance[courseCode] = attendance;
}

double Student::getGradeForCourse(QString courseCode) const {
    return courseGrades.value(courseCode, 0.0);
}

double Student::getAttendanceForCourse(QString courseCode) const {
    return courseAttendance.value(courseCode, 0.0);
}

void Student::registerCourse(Course* course) {
    if (course) {
        registeredCourses.append(course);
        QMessageBox::information(nullptr, "Success", "Course registered successfully!");
    }
}

void Student::unregisterCourse(QString courseCode) {
    for (int i = 0; i < registeredCourses.size(); ++i) {
        if (registeredCourses[i]->getCourseCode() == courseCode) {
            registeredCourses.removeAt(i);
            break;
        }
    }
}

void Student::submitAssignment(Assignment* assignment) {
    if (assignment) {
        submittedAssignments.append(assignment);
        QMessageBox::information(nullptr, "Success", "Assignment submitted successfully!");
    }
}

void Student::viewGrades() {
    qDebug() << "Grades for Student:" << personName;
    for (auto it = courseGrades.begin(); it != courseGrades.end(); ++it) {
        qDebug() << "Course:" << it.key() << "Grade:" << it.value();
    }
}

void Student::viewAttendance() {
    qDebug() << "Attendance for Student:" << personName;
    for (auto it = courseAttendance.begin(); it != courseAttendance.end(); ++it) {
        qDebug() << "Course:" << it.key() << "Attendance:" << it.value() << "%";
    }
}

void Student::viewCourses() {
    qDebug() << "Registered Courses for Student:" << personName;
    for (Course* course : registeredCourses) {
        qDebug() << "Course Code:" << course->getCourseCode()
        << "Course Name:" << course->getCourseName();
    }
}

Student::~Student() {
    for (Assignment* assignment : submittedAssignments) {
        delete assignment;
    }
}
