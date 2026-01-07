#ifndef ADMIN_H
#define ADMIN_H

#include "person.h"
#include "course.h"
#include <QVector>

class Admin : public Person {  // Pillar 2: Inheritance
private:
    QString adminDepartment;

public:
    Admin();
    Admin(QString id, QString name, QString email, QString password, QDate dob, QString department);

    // Override virtual functions
    void displayInfo() override;
    QString getRole() override;

    // Admin specific methods
    void addStudent(QString studentId, QString name, QString email, QDate dob);
    void removeStudent(QString studentId);
    void addFaculty(QString facultyId, QString name, QString email, QDate dob, QString department);
    void removeFaculty(QString facultyId);
    void addCourse(QString courseCode, QString courseName, QString facultyId);
    void removeCourse(QString courseCode);

    // Getter and Setter
    QString getDepartment() const;
    void setDepartment(QString department);
};

#endif // ADMIN_H
