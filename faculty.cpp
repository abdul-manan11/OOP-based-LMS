#include "faculty.h"
#include "database.h"
#include <QDebug>
#include <QMessageBox>

Faculty::Faculty()
    : Person(), facultyDepartment(""), facultyDesignation("") {}

Faculty::Faculty(QString id, QString name, QString email, QString password,
                 QDate dob, QString department, QString designation)
    : Person(id, name, email, password, dob),
    facultyId(id),
    facultyDepartment(department),
    facultyDesignation(designation) {}

void Faculty::displayInfo() {
    qDebug() << "Faculty ID:" << personId;
    qDebug() << "Name:" << personName;
    qDebug() << "Email:" << personEmail;
    qDebug() << "Department:" << facultyDepartment;
    qDebug() << "Designation:" << facultyDesignation;
}

QString Faculty::getRole() { return "Faculty"; }

QString Faculty::getFacultyId() const { return facultyId; }
QString Faculty::getDepartment() const { return facultyDepartment; }
QString Faculty::getDesignation() const { return facultyDesignation; }
QVector<Course*> Faculty::getTeachingCourses() const { return teachingCourses; }

void Faculty::setFacultyId(QString id) { facultyId = id; }
void Faculty::setDepartment(QString department) { facultyDepartment = department; }
void Faculty::setDesignation(QString designation) { facultyDesignation = designation; }

void Faculty::addTeachingCourse(Course* course) {
    if (course) {
        teachingCourses.append(course);
    }
}

void Faculty::uploadLecture(QString courseCode, QString lectureTitle, QString filePath) {
    Database* db = Database::getInstance();
    Course* course = db->getCourse(courseCode);
    if (course) {
        course->addLectureMaterial(filePath);
        QMessageBox::information(nullptr, "Success", "Lecture uploaded successfully!");
    }
}

void Faculty::createAssignment(QString courseCode, QString title, QString description, QDate dueDate) {
    QString assignmentId = courseCode + "_" + title + "_" + QDate::currentDate().toString("yyyyMMdd");
    Assignment* assignment = new Assignment(assignmentId, title, description, courseCode, dueDate, 100);

    Database* db = Database::getInstance();
    Course* course = db->getCourse(courseCode);
    if (course) {
        course->addAssignment(assignment);
        QMessageBox::information(nullptr, "Success", "Assignment created successfully!");
    }
}

void Faculty::gradeAssignment(QString assignmentId, QString studentId, double marks, QString feedback) {
    // Implementation for grading assignment
    QMessageBox::information(nullptr, "Success", "Assignment graded successfully!");
}

void Faculty::markAttendance(QString courseCode, QString studentId, bool present) {
    Database* db = Database::getInstance();
    Student* student = db->getStudent(studentId);
    if (student) {
        // Update attendance logic here
        QMessageBox::information(nullptr, "Success", "Attendance marked successfully!");
    }
}

Faculty::~Faculty() {
    for (Assignment* assignment : assignmentsToGrade) {
        delete assignment;
    }
}
