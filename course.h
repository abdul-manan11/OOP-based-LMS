#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <QDate>
#include <QVector>
#include "assignment.h"

class Course {
private:
    QString courseCode;
    QString courseName;
    QString courseDescription;
    QString facultyId;
    int creditHours;
    QVector<Assignment*> assignments;
    QVector<QString> lectureMaterials;  // File paths to lecture materials
    QMap<QString, QString> studentFeedback;  // studentId -> feedback

public:
    Course();
    Course(QString code, QString name, QString description, QString faculty, int credits);

    // Methods
    void addAssignment(Assignment* assignment);
    void removeAssignment(QString assignmentId);
    void addLectureMaterial(QString filePath);
    void addFeedback(QString studentId, QString feedback);
    QString getFeedback(QString studentId) const;

    // Getter methods
    QString getCourseCode() const;
    QString getCourseName() const;
    QString getCourseDescription() const;
    QString getFacultyId() const;
    int getCreditHours() const;
    QVector<Assignment*> getAssignments() const;
    QVector<QString> getLectureMaterials() const;

    // Setter methods
    void setCourseCode(QString code);
    void setCourseName(QString name);
    void setCourseDescription(QString description);
    void setFacultyId(QString faculty);
    void setCreditHours(int credits);

    ~Course();
};

#endif // COURSE_H
