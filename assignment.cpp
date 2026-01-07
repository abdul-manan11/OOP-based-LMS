#include "assignment.h"

Assignment::Assignment()
    : assignmentId(""), assignmentTitle(""), assignmentDescription(""), courseCode(""),
    dueDate(QDate::currentDate()), submissionDate(QDate::currentDate()),
    studentId(""), submittedFilePath(""), obtainedMarks(0), totalMarks(100),
    feedback(""), isSubmitted(false), isGraded(false) {}

Assignment::Assignment(QString id, QString title, QString description, QString course,
                       QDate dueDate, double totalMarks)
    : assignmentId(id), assignmentTitle(title), assignmentDescription(description),
    courseCode(course), dueDate(dueDate), totalMarks(totalMarks),
    isSubmitted(false), isGraded(false) {}

QString Assignment::getAssignmentId() const { return assignmentId; }
QString Assignment::getAssignmentTitle() const { return assignmentTitle; }
QString Assignment::getAssignmentDescription() const { return assignmentDescription; }
QString Assignment::getCourseCode() const { return courseCode; }
QDate Assignment::getDueDate() const { return dueDate; }
QDate Assignment::getSubmissionDate() const { return submissionDate; }
QString Assignment::getStudentId() const { return studentId; }
QString Assignment::getSubmittedFilePath() const { return submittedFilePath; }
double Assignment::getObtainedMarks() const { return obtainedMarks; }
double Assignment::getTotalMarks() const { return totalMarks; }
QString Assignment::getFeedback() const { return feedback; }
bool Assignment::getIsSubmitted() const { return isSubmitted; }
bool Assignment::getIsGraded() const { return isGraded; }

void Assignment::setAssignmentId(QString id) { assignmentId = id; }
void Assignment::setAssignmentTitle(QString title) { assignmentTitle = title; }
void Assignment::setAssignmentDescription(QString description) { assignmentDescription = description; }
void Assignment::setCourseCode(QString course) { courseCode = course; }
void Assignment::setDueDate(QDate date) { dueDate = date; }
void Assignment::setTotalMarks(double marks) { totalMarks = marks; }

void Assignment::submitAssignment(QString studentId, QString filePath, QDate submissionDate) {
    this->studentId = studentId;
    this->submittedFilePath = filePath;
    this->submissionDate = submissionDate;
    this->isSubmitted = true;
}

void Assignment::gradeAssignment(double marks, QString feedback) {
    this->obtainedMarks = marks;
    this->feedback = feedback;
    this->isGraded = true;
}

Assignment::~Assignment() {}
