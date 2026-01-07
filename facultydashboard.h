#ifndef FACULTYDASHBOARD_H
#define FACULTYDASHBOARD_H

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
#include <QDateEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QTabWidget>
#include "faculty.h"
#include "database.h"
#include "course.h"
#include "assignment.h"

class FacultyDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit FacultyDashboard(Faculty* faculty, QWidget *parent = nullptr);
    ~FacultyDashboard();

private slots:
    void onUploadLecture();
    void onCreateAssignment();
    void onMarkAttendance();
    void onGradeAssignment();
    void onViewSubmissions();
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
    QPushButton *lectureButton;
    QPushButton *assignmentButton;
    QPushButton *attendanceButton;
    QPushButton *gradeButton;
    QPushButton *submissionsButton;
    QPushButton *logoutButton;

    // Content Area
    QWidget *contentWidget;
    QVBoxLayout *contentLayout;

    // Current faculty
    Faculty* currentFaculty;

    void setupUI();
    void clearContent();
};

#endif // FACULTYDASHBOARD_H
