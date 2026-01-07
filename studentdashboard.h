#ifndef STUDENTDASHBOARD_H
#define STUDENTDASHBOARD_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QGroupBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QFrame>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDate>
#include <QDir>
#include <QFileInfo>
#include "student.h"
#include "database.h"
#include "course.h"
#include "assignment.h"

class StudentDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentDashboard(Student* student, QWidget *parent = nullptr);
    ~StudentDashboard();

private slots:
    void onViewCourses();
    void onViewGrades();
    void onViewAttendance();
    void onUploadAssignment();
    void onViewLectures();
    void onViewFeedback();
    void onUpdateProfile();
    void onLogout();

private:
    // UI Widgets
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;

    // Header
    QLabel *welcomeLabel;
    QLabel *infoLabel;

    // Navigation
    QHBoxLayout *buttonLayout;
    QPushButton *coursesButton;
    QPushButton *gradesButton;
    QPushButton *attendanceButton;
    QPushButton *assignmentButton;
    QPushButton *lecturesButton;
    QPushButton *feedbackButton;
    QPushButton *profileButton;
    QPushButton *logoutButton;

    // Content Area
    QWidget *contentWidget;
    QVBoxLayout *contentLayout;

    // Current student
    Student* currentStudent;

    void setupUI();
    void clearContent();
};

#endif // STUDENTDASHBOARD_H
