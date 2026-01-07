#include "course.h"
#include <QDebug>

Course::Course()
    : courseCode(""), courseName(""), courseDescription(""), facultyId(""), creditHours(0) {}

Course::Course(QString code, QString name, QString description, QString faculty, int credits)
    : courseCode(code), courseName(name), courseDescription(description),
    facultyId(faculty), creditHours(credits) {}

QString Course::getCourseCode() const { return courseCode; }
QString Course::getCourseName() const { return courseName; }
QString Course::getCourseDescription() const { return courseDescription; }
QString Course::getFacultyId() const { return facultyId; }
int Course::getCreditHours() const { return creditHours; }
QVector<Assignment*> Course::getAssignments() const { return assignments; }
QVector<QString> Course::getLectureMaterials() const { return lectureMaterials; }

void Course::setCourseCode(QString code) { courseCode = code; }
void Course::setCourseName(QString name) { courseName = name; }
void Course::setCourseDescription(QString description) { courseDescription = description; }
void Course::setFacultyId(QString faculty) { facultyId = faculty; }
void Course::setCreditHours(int credits) { creditHours = credits; }

void Course::addAssignment(Assignment* assignment) {
    if (assignment) {
        assignments.append(assignment);
    }
}

void Course::removeAssignment(QString assignmentId) {
    for (int i = 0; i < assignments.size(); ++i) {
        if (assignments[i]->getAssignmentId() == assignmentId) {
            delete assignments[i];
            assignments.removeAt(i);
            break;
        }
    }
}

void Course::addLectureMaterial(QString filePath) {
    lectureMaterials.append(filePath);
}

void Course::addFeedback(QString studentId, QString feedback) {
    studentFeedback[studentId] = feedback;
}

QString Course::getFeedback(QString studentId) const {
    return studentFeedback.value(studentId, "No feedback available");
}

Course::~Course() {
    for (Assignment* assignment : assignments) {
        delete assignment;
    }
}
