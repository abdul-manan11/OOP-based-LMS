#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include "course.h"
#include "assignment.h"
#include <QVector>
#include <QMap>

class Student : public Person {  // Pillar 2: Inheritance
private:
    QString studentRollNumber;
    QString studentDepartment;
    int currentSemester;
    QVector<Course*> registeredCourses;
    QMap<QString, double> courseGrades;  // courseCode -> grade
    QMap<QString, double> courseAttendance;  // courseCode -> attendance percentage
    QVector<Assignment*> submittedAssignments;

public:
    Student();
    Student(QString id, QString roll, QString name, QString email, QString password,
            QDate dob, QString department, int semester);

    // Override virtual functions
    void displayInfo() override;
    QString getRole() override;

    // Student specific methods
    void registerCourse(Course* course);
    void unregisterCourse(QString courseCode);
    void submitAssignment(Assignment* assignment);
    void viewGrades();
    void viewAttendance();
    void viewCourses();
    void viewLectures(QString courseCode);
    void viewFeedback(QString courseCode);

    // Getter methods
    QString getRollNumber() const;
    QString getDepartment() const;
    int getSemester() const;
    QVector<Course*> getRegisteredCourses() const;
    QMap<QString, double> getCourseGrades() const;
    QMap<QString, double> getCourseAttendance() const;
    double getGradeForCourse(QString courseCode) const;
    double getAttendanceForCourse(QString courseCode) const;

    // Setter methods
    void setRollNumber(QString roll);
    void setDepartment(QString department);
    void setSemester(int semester);
    void addGrade(QString courseCode, double grade);
    void addAttendance(QString courseCode, double attendance);

    ~Student();
};

#endif // STUDENT_H
