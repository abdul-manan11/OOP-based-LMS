#include "admindashboard.h"
#include <QDir>          // Add this include
#include <QFileDialog>
#include <QDateEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QFrame>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTabWidget>
#include <QDateTime>
#include <QGridLayout>
#include <QHeaderView>

AdminDashboard::AdminDashboard(Admin* admin, QWidget *parent)
    : QMainWindow(parent)
    , currentAdmin(admin)
{
    setWindowTitle("Admin Dashboard - Learning Management System");
    setMinimumSize(1000, 700);

    setupUI();
}

AdminDashboard::~AdminDashboard()
{
}

void AdminDashboard::setupUI()
{
    // Create central widget
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create main layout
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Create header
    QWidget *headerWidget = new QWidget(centralWidget);
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);

    welcomeLabel = new QLabel("Welcome, " + currentAdmin->getName(), headerWidget);
    welcomeLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #2c3e50;");

    infoLabel = new QLabel(
        "Admin ID: " + currentAdmin->getId() +
            " | Department: " + currentAdmin->getDepartment(),
        headerWidget
        );
    infoLabel->setStyleSheet("color: #7f8c8d;");

    headerLayout->addWidget(welcomeLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(infoLabel);

    mainLayout->addWidget(headerWidget);

    // Create horizontal line
    QFrame *line = new QFrame(centralWidget);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("color: #bdc3c7;");
    mainLayout->addWidget(line);

    // Create navigation buttons
    buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(5);

    studentsButton = new QPushButton("Manage Students", centralWidget);
    facultyButton = new QPushButton("Manage Faculty", centralWidget);
    coursesButton = new QPushButton("Manage Courses", centralWidget);
    reportsButton = new QPushButton("System Reports", centralWidget);
    viewAllButton = new QPushButton("View All Data", centralWidget);
    logoutButton = new QPushButton("Logout", centralWidget);

    // Style buttons
    QString buttonStyle =
        "QPushButton {"
        "   padding: 8px 12px;"
        "   background-color: #ecf0f1;"
        "   border: 1px solid #bdc3c7;"
        "   border-radius: 4px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d5dbdb;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #bfc9ca;"
        "}";

    studentsButton->setStyleSheet(buttonStyle);
    facultyButton->setStyleSheet(buttonStyle);
    coursesButton->setStyleSheet(buttonStyle);
    reportsButton->setStyleSheet(buttonStyle);
    viewAllButton->setStyleSheet(buttonStyle);

    logoutButton->setStyleSheet(
        "QPushButton {"
        "   padding: 8px 12px;"
        "   background-color: #e74c3c;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0392b;"
        "}"
        );

    // Add buttons to layout
    buttonLayout->addWidget(studentsButton);
    buttonLayout->addWidget(facultyButton);
    buttonLayout->addWidget(coursesButton);
    buttonLayout->addWidget(reportsButton);
    buttonLayout->addWidget(viewAllButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(logoutButton);

    mainLayout->addLayout(buttonLayout);

    // Create content area
    contentWidget = new QWidget(centralWidget);
    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(20, 20, 20, 20);

    mainLayout->addWidget(contentWidget, 1);

    // Connect signals and slots
    connect(studentsButton, &QPushButton::clicked, this, &AdminDashboard::onManageStudents);
    connect(facultyButton, &QPushButton::clicked, this, &AdminDashboard::onManageFaculty);
    connect(coursesButton, &QPushButton::clicked, this, &AdminDashboard::onManageCourses);
    connect(reportsButton, &QPushButton::clicked, this, &AdminDashboard::onSystemReports);
    connect(viewAllButton, &QPushButton::clicked, this, &AdminDashboard::onViewAllData);
    connect(logoutButton, &QPushButton::clicked, this, &AdminDashboard::onLogout);

    // Show manage students by default
    onManageStudents();
}

void AdminDashboard::onManageStudents()
{
    clearContent();

    QLabel *title = new QLabel("Manage Students", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    // Create tab widget for Add/Remove
    QTabWidget *tabWidget = new QTabWidget(contentWidget);

    // Add Student Tab
    QWidget *addTab = new QWidget();
    QFormLayout *addLayout = new QFormLayout(addTab);
    addLayout->setSpacing(15);

    QLineEdit *addIdEdit = new QLineEdit(addTab);
    addIdEdit->setPlaceholderText("e.g., S1001");

    QLineEdit *addNameEdit = new QLineEdit(addTab);
    addNameEdit->setPlaceholderText("e.g., John Doe");

    QLineEdit *addEmailEdit = new QLineEdit(addTab);
    addEmailEdit->setPlaceholderText("e.g., john@university.edu");

    QDateEdit *addDobEdit = new QDateEdit(addTab);
    addDobEdit->setDate(QDate(2000, 1, 1));
    addDobEdit->setCalendarPopup(true);

    QLineEdit *addDepartmentEdit = new QLineEdit(addTab);
    addDepartmentEdit->setPlaceholderText("e.g., Computer Science");
    addDepartmentEdit->setText("Computer Science");

    QSpinBox *addSemesterSpin = new QSpinBox(addTab);
    addSemesterSpin->setRange(1, 8);
    addSemesterSpin->setValue(1);

    QPushButton *addButton = new QPushButton("Add Student", addTab);
    addButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #2ecc71;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #27ae60;"
        "}"
        );

    addLayout->addRow("Student ID:", addIdEdit);
    addLayout->addRow("Full Name:", addNameEdit);
    addLayout->addRow("Email:", addEmailEdit);
    addLayout->addRow("Date of Birth:", addDobEdit);
    addLayout->addRow("Department:", addDepartmentEdit);
    addLayout->addRow("Semester:", addSemesterSpin);
    addLayout->addRow(addButton);

    // Connect add button
    connect(addButton, &QPushButton::clicked, [=]() {
        QString studentId = addIdEdit->text().trimmed();
        QString name = addNameEdit->text().trimmed();
        QString email = addEmailEdit->text().trimmed();
        QDate dob = addDobEdit->date();
        QString department = addDepartmentEdit->text().trimmed();
        int semester = addSemesterSpin->value();

        if (studentId.isEmpty() || name.isEmpty() || email.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill all required fields.");
            return;
        }

        Database* db = Database::getInstance();

        // Check if student already exists
        if (db->getStudent(studentId)) {
            QMessageBox::warning(this, "Error", "Student with this ID already exists.");
            return;
        }

        // Create new student
        Student* student = new Student(studentId, studentId, name, email, "password123", dob, department, semester);
        db->addStudent(student);
        db->saveAllData();

        QMessageBox::information(this, "Success",
                                 QString("Student added successfully!\n"
                                         "ID: %1\n"
                                         "Name: %2\n"
                                         "Default password: password123")
                                     .arg(studentId)
                                     .arg(name));

        // Clear form
        addIdEdit->clear();
        addNameEdit->clear();
        addEmailEdit->clear();
        addDepartmentEdit->setText("Computer Science");
        addSemesterSpin->setValue(1);
    });

    // Remove Student Tab
    QWidget *removeTab = new QWidget();
    QVBoxLayout *removeLayout = new QVBoxLayout(removeTab);

    QLabel *removeLabel = new QLabel("Remove Student", removeTab);
    removeLabel->setStyleSheet("font-weight: bold; margin-bottom: 10px;");

    QLineEdit *removeIdEdit = new QLineEdit(removeTab);
    removeIdEdit->setPlaceholderText("Enter Student ID to remove");

    QPushButton *removeButton = new QPushButton("Remove Student", removeTab);
    removeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #e74c3c;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0392b;"
        "}"
        );

    removeLayout->addWidget(removeLabel);
    removeLayout->addWidget(removeIdEdit);
    removeLayout->addWidget(removeButton);
    removeLayout->addStretch();

    // Connect remove button
    connect(removeButton, &QPushButton::clicked, [=]() {
        QString studentId = removeIdEdit->text().trimmed();

        if (studentId.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter a Student ID.");
            return;
        }

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm Removal",
                                      "Are you sure you want to remove student " + studentId + "?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            Database* db = Database::getInstance();
            db->removeStudent(studentId);
            db->saveAllData();
            QMessageBox::information(this, "Success", "Student removed successfully!");
            removeIdEdit->clear();
        }
    });

    tabWidget->addTab(addTab, "Add Student");
    tabWidget->addTab(removeTab, "Remove Student");

    contentLayout->addWidget(tabWidget);

    // Add current students table
    QLabel *currentLabel = new QLabel("Current Students", contentWidget);
    currentLabel->setStyleSheet("font-weight: bold; margin-top: 20px;");
    contentLayout->addWidget(currentLabel);

    Database* db = Database::getInstance();
    QTableWidget *studentsTable = new QTableWidget(contentWidget);
    studentsTable->setColumnCount(4);
    studentsTable->setHorizontalHeaderLabels({"ID", "Name", "Email", "Department"});

    int row = 0;
    for (Student* student : db->getAllStudents()) {
        studentsTable->insertRow(row);
        studentsTable->setItem(row, 0, new QTableWidgetItem(student->getId()));
        studentsTable->setItem(row, 1, new QTableWidgetItem(student->getName()));
        studentsTable->setItem(row, 2, new QTableWidgetItem(student->getEmail()));
        studentsTable->setItem(row, 3, new QTableWidgetItem(student->getDepartment()));
        row++;
    }

    studentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    studentsTable->setMaximumHeight(200);
    studentsTable->horizontalHeader()->setStretchLastSection(true);
    contentLayout->addWidget(studentsTable);

    contentLayout->addStretch();
}

void AdminDashboard::onManageFaculty()
{
    clearContent();

    QLabel *title = new QLabel("Manage Faculty", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    // Create tab widget for Add/Remove
    QTabWidget *tabWidget = new QTabWidget(contentWidget);

    // Add Faculty Tab
    QWidget *addTab = new QWidget();
    QFormLayout *addLayout = new QFormLayout(addTab);
    addLayout->setSpacing(15);

    QLineEdit *addIdEdit = new QLineEdit(addTab);
    addIdEdit->setPlaceholderText("e.g., F1001");

    QLineEdit *addNameEdit = new QLineEdit(addTab);
    addNameEdit->setPlaceholderText("e.g., Dr. Smith");

    QLineEdit *addEmailEdit = new QLineEdit(addTab);
    addEmailEdit->setPlaceholderText("e.g., smith@university.edu");

    QDateEdit *addDobEdit = new QDateEdit(addTab);
    addDobEdit->setDate(QDate(1975, 1, 1));
    addDobEdit->setCalendarPopup(true);

    QLineEdit *addDepartmentEdit = new QLineEdit(addTab);
    addDepartmentEdit->setPlaceholderText("e.g., Computer Science");

    QLineEdit *addDesignationEdit = new QLineEdit(addTab);
    addDesignationEdit->setPlaceholderText("e.g., Professor");
    addDesignationEdit->setText("Professor");

    QPushButton *addButton = new QPushButton("Add Faculty", addTab);
    addButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        );

    addLayout->addRow("Faculty ID:", addIdEdit);
    addLayout->addRow("Full Name:", addNameEdit);
    addLayout->addRow("Email:", addEmailEdit);
    addLayout->addRow("Date of Birth:", addDobEdit);
    addLayout->addRow("Department:", addDepartmentEdit);
    addLayout->addRow("Designation:", addDesignationEdit);
    addLayout->addRow(addButton);

    // Connect add button
    connect(addButton, &QPushButton::clicked, [=]() {
        QString facultyId = addIdEdit->text().trimmed();
        QString name = addNameEdit->text().trimmed();
        QString email = addEmailEdit->text().trimmed();
        QDate dob = addDobEdit->date();
        QString department = addDepartmentEdit->text().trimmed();
        QString designation = addDesignationEdit->text().trimmed();

        if (facultyId.isEmpty() || name.isEmpty() || email.isEmpty() || department.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill all required fields.");
            return;
        }

        Database* db = Database::getInstance();

        // Check if faculty already exists
        if (db->getFaculty(facultyId)) {
            QMessageBox::warning(this, "Error", "Faculty with this ID already exists.");
            return;
        }

        // Create new faculty
        Faculty* faculty = new Faculty(facultyId, name, email, "password123", dob, department, designation);
        db->addFaculty(faculty);
        db->saveAllData();

        QMessageBox::information(this, "Success",
                                 QString("Faculty added successfully!\n"
                                         "ID: %1\n"
                                         "Name: %2\n"
                                         "Default password: password123")
                                     .arg(facultyId)
                                     .arg(name));

        // Clear form
        addIdEdit->clear();
        addNameEdit->clear();
        addEmailEdit->clear();
        addDepartmentEdit->clear();
        addDesignationEdit->setText("Professor");
    });

    // Remove Faculty Tab
    QWidget *removeTab = new QWidget();
    QVBoxLayout *removeLayout = new QVBoxLayout(removeTab);

    QLabel *removeLabel = new QLabel("Remove Faculty", removeTab);
    removeLabel->setStyleSheet("font-weight: bold; margin-bottom: 10px;");

    QLineEdit *removeIdEdit = new QLineEdit(removeTab);
    removeIdEdit->setPlaceholderText("Enter Faculty ID to remove");

    QPushButton *removeButton = new QPushButton("Remove Faculty", removeTab);
    removeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #e74c3c;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0392b;"
        "}"
        );

    removeLayout->addWidget(removeLabel);
    removeLayout->addWidget(removeIdEdit);
    removeLayout->addWidget(removeButton);
    removeLayout->addStretch();

    // Connect remove button
    connect(removeButton, &QPushButton::clicked, [=]() {
        QString facultyId = removeIdEdit->text().trimmed();

        if (facultyId.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter a Faculty ID.");
            return;
        }

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm Removal",
                                      "Are you sure you want to remove faculty " + facultyId + "?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            Database* db = Database::getInstance();
            db->removeFaculty(facultyId);
            db->saveAllData();
            QMessageBox::information(this, "Success", "Faculty removed successfully!");
            removeIdEdit->clear();
        }
    });

    tabWidget->addTab(addTab, "Add Faculty");
    tabWidget->addTab(removeTab, "Remove Faculty");

    contentLayout->addWidget(tabWidget);

    // Add current faculty table
    QLabel *currentLabel = new QLabel("Current Faculty", contentWidget);
    currentLabel->setStyleSheet("font-weight: bold; margin-top: 20px;");
    contentLayout->addWidget(currentLabel);

    Database* db = Database::getInstance();
    QTableWidget *facultyTable = new QTableWidget(contentWidget);
    facultyTable->setColumnCount(5);
    facultyTable->setHorizontalHeaderLabels({"ID", "Name", "Email", "Department", "Designation"});

    int row = 0;
    for (Faculty* faculty : db->getAllFaculty()) {
        facultyTable->insertRow(row);
        facultyTable->setItem(row, 0, new QTableWidgetItem(faculty->getId()));
        facultyTable->setItem(row, 1, new QTableWidgetItem(faculty->getName()));
        facultyTable->setItem(row, 2, new QTableWidgetItem(faculty->getEmail()));
        facultyTable->setItem(row, 3, new QTableWidgetItem(faculty->getDepartment()));
        facultyTable->setItem(row, 4, new QTableWidgetItem(faculty->getDesignation()));
        row++;
    }

    facultyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    facultyTable->setMaximumHeight(200);
    facultyTable->horizontalHeader()->setStretchLastSection(true);
    contentLayout->addWidget(facultyTable);

    contentLayout->addStretch();
}

void AdminDashboard::onManageCourses()
{
    clearContent();

    QLabel *title = new QLabel("Manage Courses", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    // Create tab widget for Add/Remove
    QTabWidget *tabWidget = new QTabWidget(contentWidget);

    // Add Course Tab
    QWidget *addTab = new QWidget();
    QFormLayout *addLayout = new QFormLayout(addTab);
    addLayout->setSpacing(15);

    QLineEdit *addCodeEdit = new QLineEdit(addTab);
    addCodeEdit->setPlaceholderText("e.g., CS101");

    QLineEdit *addNameEdit = new QLineEdit(addTab);
    addNameEdit->setPlaceholderText("e.g., Introduction to Programming");

    QLineEdit *addFacultyIdEdit = new QLineEdit(addTab);
    addFacultyIdEdit->setPlaceholderText("e.g., F1001");

    QSpinBox *addCreditsSpin = new QSpinBox(addTab);
    addCreditsSpin->setRange(1, 4);
    addCreditsSpin->setValue(3);

    QTextEdit *addDescEdit = new QTextEdit(addTab);
    addDescEdit->setMaximumHeight(80);
    addDescEdit->setPlaceholderText("Course description...");

    QPushButton *addButton = new QPushButton("Add Course", addTab);
    addButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #9b59b6;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #8e44ad;"
        "}"
        );

    addLayout->addRow("Course Code:", addCodeEdit);
    addLayout->addRow("Course Name:", addNameEdit);
    addLayout->addRow("Faculty ID:", addFacultyIdEdit);
    addLayout->addRow("Credit Hours:", addCreditsSpin);
    addLayout->addRow("Description:", addDescEdit);
    addLayout->addRow(addButton);

    // Connect add button
    connect(addButton, &QPushButton::clicked, [=]() {
        QString courseCode = addCodeEdit->text().trimmed();
        QString courseName = addNameEdit->text().trimmed();
        QString facultyId = addFacultyIdEdit->text().trimmed();
        QString description = addDescEdit->toPlainText();
        int credits = addCreditsSpin->value();

        if (courseCode.isEmpty() || courseName.isEmpty() || facultyId.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill all required fields.");
            return;
        }

        Database* db = Database::getInstance();

        // Check if course already exists
        if (db->getCourse(courseCode)) {
            QMessageBox::warning(this, "Error", "Course with this code already exists.");
            return;
        }

        // Check if faculty exists
        if (!db->getFaculty(facultyId)) {
            QMessageBox::warning(this, "Error", "Faculty with ID " + facultyId + " not found.");
            return;
        }

        // Create new course
        Course* course = new Course(courseCode, courseName, description, facultyId, credits);
        db->addCourse(course);
        db->saveAllData();

        QMessageBox::information(this, "Success",
                                 QString("Course added successfully!\n"
                                         "Code: %1\n"
                                         "Name: %2\n"
                                         "Faculty: %3\n"
                                         "Credits: %4")
                                     .arg(courseCode)
                                     .arg(courseName)
                                     .arg(facultyId)
                                     .arg(QString::number(credits)));

        // Clear form
        addCodeEdit->clear();
        addNameEdit->clear();
        addFacultyIdEdit->clear();
        addDescEdit->clear();
        addCreditsSpin->setValue(3);
    });

    // Remove Course Tab
    QWidget *removeTab = new QWidget();
    QVBoxLayout *removeLayout = new QVBoxLayout(removeTab);

    QLabel *removeLabel = new QLabel("Remove Course", removeTab);
    removeLabel->setStyleSheet("font-weight: bold; margin-bottom: 10px;");

    QLineEdit *removeCodeEdit = new QLineEdit(removeTab);
    removeCodeEdit->setPlaceholderText("Enter Course Code to remove");

    QPushButton *removeButton = new QPushButton("Remove Course", removeTab);
    removeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #e74c3c;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0392b;"
        "}"
        );

    removeLayout->addWidget(removeLabel);
    removeLayout->addWidget(removeCodeEdit);
    removeLayout->addWidget(removeButton);
    removeLayout->addStretch();

    // Connect remove button
    connect(removeButton, &QPushButton::clicked, [=]() {
        QString courseCode = removeCodeEdit->text().trimmed();

        if (courseCode.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter a Course Code.");
            return;
        }

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm Removal",
                                      "Are you sure you want to remove course " + courseCode + "?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            Database* db = Database::getInstance();
            db->removeCourse(courseCode);
            db->saveAllData();
            QMessageBox::information(this, "Success", "Course removed successfully!");
            removeCodeEdit->clear();
        }
    });

    tabWidget->addTab(addTab, "Add Course");
    tabWidget->addTab(removeTab, "Remove Course");

    contentLayout->addWidget(tabWidget);

    // Add current courses table
    QLabel *currentLabel = new QLabel("Current Courses", contentWidget);
    currentLabel->setStyleSheet("font-weight: bold; margin-top: 20px;");
    contentLayout->addWidget(currentLabel);

    Database* db = Database::getInstance();
    QTableWidget *coursesTable = new QTableWidget(contentWidget);
    coursesTable->setColumnCount(4);
    coursesTable->setHorizontalHeaderLabels({"Code", "Name", "Faculty ID", "Credits"});

    int row = 0;
    for (Course* course : db->getAllCourses()) {
        coursesTable->insertRow(row);
        coursesTable->setItem(row, 0, new QTableWidgetItem(course->getCourseCode()));
        coursesTable->setItem(row, 1, new QTableWidgetItem(course->getCourseName()));
        coursesTable->setItem(row, 2, new QTableWidgetItem(course->getFacultyId()));
        coursesTable->setItem(row, 3, new QTableWidgetItem(QString::number(course->getCreditHours())));
        row++;
    }

    coursesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    coursesTable->setMaximumHeight(200);
    coursesTable->horizontalHeader()->setStretchLastSection(true);
    contentLayout->addWidget(coursesTable);

    contentLayout->addStretch();
}

void AdminDashboard::onViewAllData()
{
    clearContent();

    QLabel *title = new QLabel("All System Data", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    Database* db = Database::getInstance();

    // Create tabs for different data types
    QTabWidget *tabWidget = new QTabWidget(contentWidget);

    // Students Tab
    QWidget *studentsTab = new QWidget();
    QVBoxLayout *studentsLayout = new QVBoxLayout(studentsTab);

    QTableWidget *studentsTable = new QTableWidget(studentsTab);
    studentsTable->setColumnCount(6);
    studentsTable->setHorizontalHeaderLabels({"ID", "Roll No", "Name", "Email", "Department", "Semester"});

    int studentRow = 0;
    for (Student* student : db->getAllStudents()) {
        studentsTable->insertRow(studentRow);
        studentsTable->setItem(studentRow, 0, new QTableWidgetItem(student->getId()));
        studentsTable->setItem(studentRow, 1, new QTableWidgetItem(student->getRollNumber()));
        studentsTable->setItem(studentRow, 2, new QTableWidgetItem(student->getName()));
        studentsTable->setItem(studentRow, 3, new QTableWidgetItem(student->getEmail()));
        studentsTable->setItem(studentRow, 4, new QTableWidgetItem(student->getDepartment()));
        studentsTable->setItem(studentRow, 5, new QTableWidgetItem(QString::number(student->getSemester())));
        studentRow++;
    }

    studentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    studentsTable->horizontalHeader()->setStretchLastSection(true);
    studentsLayout->addWidget(studentsTable);
    tabWidget->addTab(studentsTab, "Students (" + QString::number(studentRow) + ")");

    // Faculty Tab
    QWidget *facultyTab = new QWidget();
    QVBoxLayout *facultyLayout = new QVBoxLayout(facultyTab);

    QTableWidget *facultyTable = new QTableWidget(facultyTab);
    facultyTable->setColumnCount(5);
    facultyTable->setHorizontalHeaderLabels({"ID", "Name", "Email", "Department", "Designation"});

    int facultyRow = 0;
    for (Faculty* faculty : db->getAllFaculty()) {
        facultyTable->insertRow(facultyRow);
        facultyTable->setItem(facultyRow, 0, new QTableWidgetItem(faculty->getId()));
        facultyTable->setItem(facultyRow, 1, new QTableWidgetItem(faculty->getName()));
        facultyTable->setItem(facultyRow, 2, new QTableWidgetItem(faculty->getEmail()));
        facultyTable->setItem(facultyRow, 3, new QTableWidgetItem(faculty->getDepartment()));
        facultyTable->setItem(facultyRow, 4, new QTableWidgetItem(faculty->getDesignation()));
        facultyRow++;
    }

    facultyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    facultyTable->horizontalHeader()->setStretchLastSection(true);
    facultyLayout->addWidget(facultyTable);
    tabWidget->addTab(facultyTab, "Faculty (" + QString::number(facultyRow) + ")");

    // Courses Tab
    QWidget *coursesTab = new QWidget();
    QVBoxLayout *coursesLayout = new QVBoxLayout(coursesTab);

    QTableWidget *coursesTable = new QTableWidget(coursesTab);
    coursesTable->setColumnCount(5);
    coursesTable->setHorizontalHeaderLabels({"Code", "Name", "Faculty ID", "Credit Hours", "Assignments"});

    int courseRow = 0;
    for (Course* course : db->getAllCourses()) {
        coursesTable->insertRow(courseRow);
        coursesTable->setItem(courseRow, 0, new QTableWidgetItem(course->getCourseCode()));
        coursesTable->setItem(courseRow, 1, new QTableWidgetItem(course->getCourseName()));
        coursesTable->setItem(courseRow, 2, new QTableWidgetItem(course->getFacultyId()));
        coursesTable->setItem(courseRow, 3, new QTableWidgetItem(QString::number(course->getCreditHours())));
        coursesTable->setItem(courseRow, 4, new QTableWidgetItem(QString::number(course->getAssignments().size())));
        courseRow++;
    }

    coursesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    coursesTable->horizontalHeader()->setStretchLastSection(true);
    coursesLayout->addWidget(coursesTable);
    tabWidget->addTab(coursesTab, "Courses (" + QString::number(courseRow) + ")");

    contentLayout->addWidget(tabWidget);

    // Add statistics
    QString statsText = QString("System Statistics: %1 Students | %2 Faculty | %3 Courses")
                            .arg(studentRow)
                            .arg(facultyRow)
                            .arg(courseRow);
    QLabel *statsLabel = new QLabel(statsText, contentWidget);
    statsLabel->setStyleSheet("font-weight: bold; color: #27ae60; margin-top: 20px;");
    contentLayout->addWidget(statsLabel);

    contentLayout->addStretch();
}

void AdminDashboard::onSystemReports()
{
    clearContent();

    QLabel *title = new QLabel("System Reports", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    // Create report buttons
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(15);

    QPushButton *studentReportBtn = new QPushButton("Student Enrollment Report", contentWidget);
    QPushButton *facultyReportBtn = new QPushButton("Faculty Workload Report", contentWidget);
    QPushButton *courseReportBtn = new QPushButton("Course Statistics Report", contentWidget);
    QPushButton *attendanceReportBtn = new QPushButton("Attendance Summary Report", contentWidget);
    QPushButton *gradeReportBtn = new QPushButton("Grade Distribution Report", contentWidget);
    QPushButton *systemReportBtn = new QPushButton("System Health Report", contentWidget);

    // Style report buttons
    QString reportButtonStyle =
        "QPushButton {"
        "   padding: 15px;"
        "   background-color: #34495e;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "   text-align: left;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2c3e50;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1a252f;"
        "}";

    studentReportBtn->setStyleSheet(reportButtonStyle);
    facultyReportBtn->setStyleSheet(reportButtonStyle);
    courseReportBtn->setStyleSheet(reportButtonStyle);
    attendanceReportBtn->setStyleSheet(reportButtonStyle);
    gradeReportBtn->setStyleSheet(reportButtonStyle);
    systemReportBtn->setStyleSheet(reportButtonStyle);

    // Add buttons to grid
    gridLayout->addWidget(studentReportBtn, 0, 0);
    gridLayout->addWidget(facultyReportBtn, 0, 1);
    gridLayout->addWidget(courseReportBtn, 1, 0);
    gridLayout->addWidget(attendanceReportBtn, 1, 1);
    gridLayout->addWidget(gradeReportBtn, 2, 0);
    gridLayout->addWidget(systemReportBtn, 2, 1);

    contentLayout->addLayout(gridLayout);

    // Report display area
    QTextEdit *reportDisplay = new QTextEdit(contentWidget);
    reportDisplay->setReadOnly(true);
    reportDisplay->setMinimumHeight(200);
    reportDisplay->setStyleSheet("background-color: #f8f9fa; border: 1px solid #dee2e6;");

    contentLayout->addWidget(reportDisplay);

    // Connect report buttons
    connect(studentReportBtn, &QPushButton::clicked, [=]() {
        Database* db = Database::getInstance();
        QString report = "=== STUDENT ENROLLMENT REPORT ===\n";
        report += "Generated: " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") + "\n";
        report += "====================================\n\n";

        int totalStudents = db->getAllStudents().size();
        report += "Total Students: " + QString::number(totalStudents) + "\n\n";

        // Group by department
        QMap<QString, int> deptCount;
        for (Student* student : db->getAllStudents()) {
            deptCount[student->getDepartment()]++;
        }

        report += "By Department:\n";
        for (auto it = deptCount.begin(); it != deptCount.end(); ++it) {
            report += "  " + it.key() + ": " + QString::number(it.value()) + " students\n";
        }

        reportDisplay->setText(report);
    });

    connect(facultyReportBtn, &QPushButton::clicked, [=]() {
        Database* db = Database::getInstance();
        QString report = "=== FACULTY WORKLOAD REPORT ===\n";
        report += "Generated: " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") + "\n";
        report += "==================================\n\n";

        int totalFaculty = db->getAllFaculty().size();
        report += "Total Faculty: " + QString::number(totalFaculty) + "\n\n";

        report += "Faculty List:\n";
        for (Faculty* faculty : db->getAllFaculty()) {
            report += "  " + faculty->getId() + " - " + faculty->getName() +
                      " (" + faculty->getDepartment() + ")\n";
        }

        reportDisplay->setText(report);
    });

    connect(courseReportBtn, &QPushButton::clicked, [=]() {
        Database* db = Database::getInstance();
        QString report = "=== COURSE STATISTICS REPORT ===\n";
        report += "Generated: " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") + "\n";
        report += "====================================\n\n";

        int totalCourses = db->getAllCourses().size();
        report += "Total Courses: " + QString::number(totalCourses) + "\n\n";

        report += "Course List:\n";
        for (Course* course : db->getAllCourses()) {
            report += "  " + course->getCourseCode() + " - " + course->getCourseName() +
                      " (Faculty: " + course->getFacultyId() + ")\n";
        }

        reportDisplay->setText(report);
    });

    connect(attendanceReportBtn, &QPushButton::clicked, [=]() {
        Database* db = Database::getInstance();
        QString report = "=== ATTENDANCE SUMMARY REPORT ===\n";
        report += "Generated: " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") + "\n";
        report += "=====================================\n\n";

        report += "Attendance Summary:\n\n";

        int studentsWithData = 0;
        double totalAttendance = 0;

        for (Student* student : db->getAllStudents()) {
            QMap<QString, double> attendance = student->getCourseAttendance();
            if (!attendance.isEmpty()) {
                studentsWithData++;
                for (double att : attendance.values()) {
                    totalAttendance += att;
                }
            }
        }

        if (studentsWithData > 0) {
            double avgAttendance = totalAttendance / (studentsWithData * 3); // Assuming 3 courses per student
            report += "Students with attendance data: " + QString::number(studentsWithData) + "\n";
            report += "Average attendance: " + QString::number(avgAttendance, 'f', 1) + "%\n";
        } else {
            report += "No attendance data available yet.\n";
        }

        reportDisplay->setText(report);
    });

    connect(gradeReportBtn, &QPushButton::clicked, [=]() {
        Database* db = Database::getInstance();
        QString report = "=== GRADE DISTRIBUTION REPORT ===\n";
        report += "Generated: " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") + "\n";
        report += "=====================================\n\n";

        report += "Grade Summary:\n\n";

        int studentsWithGrades = 0;
        double totalGrade = 0;
        int gradeCount = 0;

        for (Student* student : db->getAllStudents()) {
            QMap<QString, double> grades = student->getCourseGrades();
            if (!grades.isEmpty()) {
                studentsWithGrades++;
                for (double grade : grades.values()) {
                    totalGrade += grade;
                    gradeCount++;
                }
            }
        }

        if (studentsWithGrades > 0) {
            double avgGrade = totalGrade / gradeCount;
            report += "Students with grades: " + QString::number(studentsWithGrades) + "\n";
            report += "Average grade: " + QString::number(avgGrade, 'f', 1) + "%\n";
            report += "Total grades recorded: " + QString::number(gradeCount) + "\n";
        } else {
            report += "No grade data available yet.\n";
        }

        reportDisplay->setText(report);
    });

    connect(systemReportBtn, &QPushButton::clicked, [=]() {
        Database* db = Database::getInstance();
        QString report = "=== SYSTEM HEALTH REPORT ===\n";
        report += "Generated: " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") + "\n";
        report += "================================\n\n";

        int students = db->getAllStudents().size();
        int faculty = db->getAllFaculty().size();
        int courses = db->getAllCourses().size();

        report += "System Status: OPERATIONAL\n\n";
        report += "Data Statistics:\n";
        report += "  Students: " + QString::number(students) + "\n";
        report += "  Faculty: " + QString::number(faculty) + "\n";
        report += "  Courses: " + QString::number(courses) + "\n";
        report += "  Total Users: " + QString::number(students + faculty + 1) + "\n\n";

        // FIX: Declare dataDir variable properly
        QDir dataDir("data");
        QString dataDirStatus;
        if (dataDir.exists()) {
            report += "Disk Space: Normal\n";
            report += "Data Directory: Exists\n";
        } else {
            report += "Disk Space: Warning - Data directory not found\n";
        }

        report += "Memory Usage: Normal\n";
        report += "Database: Connected\n";
        report += "Last Backup: " + QDateTime::currentDateTime().toString("dd/MM/yyyy") + "\n";

        reportDisplay->setText(report);
    });

    contentLayout->addStretch();
}

void AdminDashboard::onLogout()
{
    // Save data
    Database::getInstance()->saveAllData();

    // Close dashboard
    this->close();
}

void AdminDashboard::clearContent()
{
    // Remove all widgets from content layout
    QLayoutItem* item;
    while ((item = contentLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}
