#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <QString>
#include <QDate>
#include <QMap>

class Assignment {
private:
    QString assignmentId;
    QString assignmentTitle;
    QString assignmentDescription;
    QString courseCode;
    QDate dueDate;
    QDate submissionDate;
    QString studentId;
    QString submittedFilePath;
    double obtainedMarks;
    double totalMarks;
    QString feedback;
    bool isSubmitted;
    bool isGraded;

public:
    Assignment();
    Assignment(QString id, QString title, QString description, QString course,
               QDate dueDate, double totalMarks);

    // Methods
    void submitAssignment(QString studentId, QString filePath, QDate submissionDate);
    void gradeAssignment(double marks, QString feedback);

    // Getter methods
    QString getAssignmentId() const;
    QString getAssignmentTitle() const;
    QString getAssignmentDescription() const;
    QString getCourseCode() const;
    QDate getDueDate() const;
    QDate getSubmissionDate() const;
    QString getStudentId() const;
    QString getSubmittedFilePath() const;
    double getObtainedMarks() const;
    double getTotalMarks() const;
    QString getFeedback() const;
    bool getIsSubmitted() const;
    bool getIsGraded() const;

    // Setter methods
    void setAssignmentId(QString id);
    void setAssignmentTitle(QString title);
    void setAssignmentDescription(QString description);
    void setCourseCode(QString course);
    void setDueDate(QDate date);
    void setTotalMarks(double marks);

    ~Assignment();
};

#endif // ASSIGNMENT_H
