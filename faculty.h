#ifndef FACULTY_H
#define FACULTY_H

#include "person.h"
#include "course.h"
#include "assignment.h"
#include <QVector>
#include <QMap>

class Faculty : public Person {  // Pillar 2: Inheritance
private:
    QString facultyId;
    QString facultyDepartment;
    QString facultyDesignation;
    QVector<Course*> teachingCourses;
    QVector<Assignment*> assignmentsToGrade;

public:
    Faculty();
    Faculty(QString id, QString name, QString email, QString password,
            QDate dob, QString department, QString designation);

    // Override virtual functions
    void displayInfo() override;
    QString getRole() override;

    // Faculty specific methods
    void uploadLecture(QString courseCode, QString lectureTitle, QString filePath);
    void createAssignment(QString courseCode, QString title, QString description, QDate dueDate);
    void gradeAssignment(QString assignmentId, QString studentId, double marks, QString feedback);
    void markAttendance(QString courseCode, QString studentId, bool present);
    void calculateFinalGrades(QString courseCode);
    void viewStudentSubmissions(QString courseCode);
    void addQuizMarks(QString courseCode, QString studentId, double marks);
    void addAssignmentMarks(QString courseCode, QString studentId, double marks);
    void addMidMarks(QString courseCode, QString studentId, double marks);
    void addFinalMarks(QString courseCode, QString studentId, double marks);

    // Getter methods
    QString getFacultyId() const;
    QString getDepartment() const;
    QString getDesignation() const;
    QVector<Course*> getTeachingCourses() const;

    // Setter methods
    void setFacultyId(QString id);
    void setDepartment(QString department);
    void setDesignation(QString designation);
    void addTeachingCourse(Course* course);

    ~Faculty();
};

#endif // FACULTY_H
