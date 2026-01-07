#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QGroupBox>
#include <QMessageBox>
#include <QFrame>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDateEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QTabWidget>
#include <QDateTime>
#include <QMap>
#include "admin.h"
#include "database.h"
#include "student.h"
#include "faculty.h"
#include "course.h"

class AdminDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminDashboard(Admin* admin, QWidget *parent = nullptr);
    ~AdminDashboard();

private slots:
    void onManageStudents();
    void onManageFaculty();
    void onManageCourses();
    void onViewAllData();
    void onSystemReports();
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
    QPushButton *studentsButton;
    QPushButton *facultyButton;
    QPushButton *coursesButton;
    QPushButton *reportsButton;
    QPushButton *viewAllButton;
    QPushButton *logoutButton;

    // Content Area
    QWidget *contentWidget;
    QVBoxLayout *contentLayout;

    // Current admin
    Admin* currentAdmin;

    void setupUI();
    void clearContent();
};

#endif // ADMINDASHBOARD_H
