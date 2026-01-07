#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QFrame>
#include <QDate>
#include "database.h"
#include "student.h"
#include "faculty.h"
#include "admin.h"

// Forward declarations to avoid including .cpp files
class StudentDashboard;
class FacultyDashboard;
class AdminDashboard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginClicked();
    void onRoleChanged(int index);

private:
    // UI Widgets
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;

    QLabel *titleLabel;
    QComboBox *roleComboBox;
    QLineEdit *emailLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;

    Database* database;

    void setupUI();
};

#endif // MAINWINDOW_H
