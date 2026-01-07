#include "studentdashboard.h"
#include <QSpinBox>
#include <QCheckBox>
#include"faculty.h"

StudentDashboard::StudentDashboard(Student* student, QWidget *parent)
    : QMainWindow(parent)
    , currentStudent(student)
{
    setWindowTitle("Student Dashboard - Learning Management System");
    setMinimumSize(900, 600);

    setupUI();
}

StudentDashboard::~StudentDashboard()
{
}

void StudentDashboard::setupUI()
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

    welcomeLabel = new QLabel("Welcome, " + currentStudent->getName(), headerWidget);
    welcomeLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #2c3e50;");

    infoLabel = new QLabel(
        "Roll No: " + currentStudent->getRollNumber() +
            " | Department: " + currentStudent->getDepartment() +
            " | Semester: " + QString::number(currentStudent->getSemester()),
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

    coursesButton = new QPushButton("My Courses", centralWidget);
    gradesButton = new QPushButton("My Grades", centralWidget);
    attendanceButton = new QPushButton("Attendance", centralWidget);
    assignmentButton = new QPushButton("Submit Assignment", centralWidget);
    lecturesButton = new QPushButton("View Lectures", centralWidget);
    feedbackButton = new QPushButton("Feedback", centralWidget);
    profileButton = new QPushButton("My Profile", centralWidget);
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

    coursesButton->setStyleSheet(buttonStyle);
    gradesButton->setStyleSheet(buttonStyle);
    attendanceButton->setStyleSheet(buttonStyle);
    assignmentButton->setStyleSheet(buttonStyle);
    lecturesButton->setStyleSheet(buttonStyle);
    feedbackButton->setStyleSheet(buttonStyle);
    profileButton->setStyleSheet(buttonStyle);

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
    buttonLayout->addWidget(coursesButton);
    buttonLayout->addWidget(gradesButton);
    buttonLayout->addWidget(attendanceButton);
    buttonLayout->addWidget(assignmentButton);
    buttonLayout->addWidget(lecturesButton);
    buttonLayout->addWidget(feedbackButton);
    buttonLayout->addWidget(profileButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(logoutButton);

    mainLayout->addLayout(buttonLayout);

    // Create content area
    contentWidget = new QWidget(centralWidget);
    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(20, 20, 20, 20);

    mainLayout->addWidget(contentWidget, 1);

    // Connect signals and slots
    connect(coursesButton, &QPushButton::clicked, this, &StudentDashboard::onViewCourses);
    connect(gradesButton, &QPushButton::clicked, this, &StudentDashboard::onViewGrades);
    connect(attendanceButton, &QPushButton::clicked, this, &StudentDashboard::onViewAttendance);
    connect(assignmentButton, &QPushButton::clicked, this, &StudentDashboard::onUploadAssignment);
    connect(lecturesButton, &QPushButton::clicked, this, &StudentDashboard::onViewLectures);
    connect(feedbackButton, &QPushButton::clicked, this, &StudentDashboard::onViewFeedback);
    connect(profileButton, &QPushButton::clicked, this, &StudentDashboard::onUpdateProfile);
    connect(logoutButton, &QPushButton::clicked, this, &StudentDashboard::onLogout);

    // Show courses by default
    onViewCourses();
}

void StudentDashboard::onViewCourses()
{
    clearContent();

    QLabel *title = new QLabel("My Registered Courses", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    Database* db = Database::getInstance();

    if (currentStudent->getRegisteredCourses().isEmpty()) {
        QLabel *noCourses = new QLabel("No courses registered yet.", contentWidget);
        noCourses->setStyleSheet("color: #7f8c8d; font-style: italic;");
        contentLayout->addWidget(noCourses);
    } else {
        QTableWidget *coursesTable = new QTableWidget(contentWidget);
        coursesTable->setColumnCount(4);
        coursesTable->setHorizontalHeaderLabels({"Course Code", "Course Name", "Faculty", "Credit Hours"});

        int row = 0;
        for (Course* course : currentStudent->getRegisteredCourses()) {
            coursesTable->insertRow(row);
            coursesTable->setItem(row, 0, new QTableWidgetItem(course->getCourseCode()));
            coursesTable->setItem(row, 1, new QTableWidgetItem(course->getCourseName()));

            Faculty* faculty = db->getFaculty(course->getFacultyId());
            QString facultyName = faculty ? faculty->getName() : "Unknown";
            coursesTable->setItem(row, 2, new QTableWidgetItem(facultyName));

            coursesTable->setItem(row, 3, new QTableWidgetItem(QString::number(course->getCreditHours())));
            row++;
        }

        coursesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        coursesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        coursesTable->horizontalHeader()->setStretchLastSection(true);
        coursesTable->resizeColumnsToContents();

        contentLayout->addWidget(coursesTable);
    }

    contentLayout->addStretch();
}

void StudentDashboard::onViewGrades()
{
    clearContent();

    QLabel *title = new QLabel("My Grades", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    QMap<QString, double> grades = currentStudent->getCourseGrades();

    if (grades.isEmpty()) {
        QLabel *noGrades = new QLabel("No grades available yet.", contentWidget);
        noGrades->setStyleSheet("color: #7f8c8d; font-style: italic;");
        contentLayout->addWidget(noGrades);
    } else {
        QTableWidget *gradesTable = new QTableWidget(contentWidget);
        gradesTable->setColumnCount(3);
        gradesTable->setHorizontalHeaderLabels({"Course Code", "Grade", "Status"});

        int row = 0;
        for (auto it = grades.begin(); it != grades.end(); ++it) {
            gradesTable->insertRow(row);
            gradesTable->setItem(row, 0, new QTableWidgetItem(it.key()));
            gradesTable->setItem(row, 1, new QTableWidgetItem(QString::number(it.value())));

            QString status;
            if (it.value() >= 85) status = "A+ (Excellent)";
            else if (it.value() >= 80) status = "A (Very Good)";
            else if (it.value() >= 75) status = "B+ (Good)";
            else if (it.value() >= 70) status = "B (Satisfactory)";
            else if (it.value() >= 65) status = "C+ (Below Average)";
            else if (it.value() >= 60) status = "C (Poor)";
            else status = "F (Fail)";

            gradesTable->setItem(row, 2, new QTableWidgetItem(status));
            row++;
        }

        gradesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        gradesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        gradesTable->horizontalHeader()->setStretchLastSection(true);

        contentLayout->addWidget(gradesTable);
    }

    // Add overall GPA
    if (!grades.isEmpty()) {
        double total = 0;
        int count = 0;
        for (double grade : grades.values()) {
            total += grade;
            count++;
        }
        double gpa = total / count;

        QLabel *gpaLabel = new QLabel(
            QString("Overall GPA: %1").arg(gpa, 0, 'f', 2),
            contentWidget
            );
        gpaLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #27ae60; margin-top: 20px;");
        contentLayout->addWidget(gpaLabel);
    }

    contentLayout->addStretch();
}

void StudentDashboard::onViewAttendance()
{
    clearContent();

    QLabel *title = new QLabel("My Attendance", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    QMap<QString, double> attendance = currentStudent->getCourseAttendance();

    if (attendance.isEmpty()) {
        QLabel *noAttendance = new QLabel("No attendance records available yet.", contentWidget);
        noAttendance->setStyleSheet("color: #7f8c8d; font-style: italic;");
        contentLayout->addWidget(noAttendance);
    } else {
        QTableWidget *attendanceTable = new QTableWidget(contentWidget);
        attendanceTable->setColumnCount(3);
        attendanceTable->setHorizontalHeaderLabels({"Course Code", "Attendance %", "Status"});

        int row = 0;
        for (auto it = attendance.begin(); it != attendance.end(); ++it) {
            attendanceTable->insertRow(row);
            attendanceTable->setItem(row, 0, new QTableWidgetItem(it.key()));
            attendanceTable->setItem(row, 1, new QTableWidgetItem(QString::number(it.value(), 'f', 1) + "%"));

            QString status;
            QString color;
            if (it.value() >= 75) {
                status = "Good";
                color = "#27ae60";
            } else if (it.value() >= 50) {
                status = "Warning";
                color = "#f39c12";
            } else {
                status = "Critical";
                color = "#e74c3c";
            }

            QTableWidgetItem *statusItem = new QTableWidgetItem(status);
            statusItem->setForeground(QColor(color));
            attendanceTable->setItem(row, 2, statusItem);
            row++;
        }

        attendanceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        attendanceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        attendanceTable->horizontalHeader()->setStretchLastSection(true);

        contentLayout->addWidget(attendanceTable);
    }

    contentLayout->addStretch();
}

void StudentDashboard::onUploadAssignment()
{
    clearContent();

    QLabel *title = new QLabel("Submit Assignment", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    // Create form
    QWidget *formWidget = new QWidget(contentWidget);
    QFormLayout *formLayout = new QFormLayout(formWidget);
    formLayout->setSpacing(15);

    QLineEdit *courseCodeEdit = new QLineEdit(formWidget);
    courseCodeEdit->setPlaceholderText("e.g., CS101");

    QLineEdit *assignmentIdEdit = new QLineEdit(formWidget);
    assignmentIdEdit->setPlaceholderText("e.g., Assignment1");

    QLineEdit *titleEdit = new QLineEdit(formWidget);
    titleEdit->setPlaceholderText("Enter assignment title");

    QTextEdit *descriptionEdit = new QTextEdit(formWidget);
    descriptionEdit->setMaximumHeight(100);
    descriptionEdit->setPlaceholderText("Enter assignment description (optional)");

    QLineEdit *filePathEdit = new QLineEdit(formWidget);
    filePathEdit->setPlaceholderText("Select file to upload");
    filePathEdit->setReadOnly(true);

    QPushButton *browseButton = new QPushButton("Browse...", formWidget);
    QPushButton *submitButton = new QPushButton("Submit Assignment", formWidget);
    submitButton->setStyleSheet(
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

    QHBoxLayout *fileLayout = new QHBoxLayout();
    fileLayout->addWidget(filePathEdit);
    fileLayout->addWidget(browseButton);

    formLayout->addRow("Course Code:", courseCodeEdit);
    formLayout->addRow("Assignment ID:", assignmentIdEdit);
    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Description:", descriptionEdit);
    formLayout->addRow("File:", fileLayout);
    formLayout->addRow(submitButton);

    contentLayout->addWidget(formWidget);

    // Connect browse button
    connect(browseButton, &QPushButton::clicked, [=]() {
        QString filePath = QFileDialog::getOpenFileName(
            this,
            "Select Assignment File",
            QDir::homePath(),
            "All Files (*)"
            );
        if (!filePath.isEmpty()) {
            filePathEdit->setText(filePath);
        }
    });

    // Connect submit button
    connect(submitButton, &QPushButton::clicked, [=]() {
        QString courseCode = courseCodeEdit->text().trimmed();
        QString assignmentId = assignmentIdEdit->text().trimmed();
        QString title = titleEdit->text().trimmed();
        QString filePath = filePathEdit->text();

        if (courseCode.isEmpty() || assignmentId.isEmpty() || title.isEmpty() || filePath.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill all required fields and select a file.");
            return;
        }

        // Create assignment
        Assignment* assignment = new Assignment(
            assignmentId,
            title,
            descriptionEdit->toPlainText(),
            courseCode,
            QDate::currentDate().addDays(7), // Due in 7 days
            100
            );

        assignment->submitAssignment(currentStudent->getId(), filePath, QDate::currentDate());
        currentStudent->submitAssignment(assignment);

        QMessageBox::information(this, "Success",
                                 "Assignment submitted successfully!\n"
                                 "Course: " + courseCode + "\n"
                                                    "Assignment: " + title + "\n"
                                               "Due Date: " + QDate::currentDate().addDays(7).toString("dd/MM/yyyy")
                                 );

        // Clear form
        courseCodeEdit->clear();
        assignmentIdEdit->clear();
        titleEdit->clear();
        descriptionEdit->clear();
        filePathEdit->clear();
    });

    contentLayout->addStretch();
}

void StudentDashboard::onViewLectures()
{
    clearContent();

    QLabel *title = new QLabel("Lecture Materials", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    QLineEdit *courseCodeEdit = new QLineEdit(contentWidget);
    courseCodeEdit->setPlaceholderText("Enter course code to view lectures");

    QPushButton *searchButton = new QPushButton("View Lectures", contentWidget);

    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(courseCodeEdit);
    searchLayout->addWidget(searchButton);

    contentLayout->addLayout(searchLayout);

    QTextEdit *lecturesDisplay = new QTextEdit(contentWidget);
    lecturesDisplay->setReadOnly(true);
    lecturesDisplay->setMinimumHeight(200);

    contentLayout->addWidget(lecturesDisplay);

    connect(searchButton, &QPushButton::clicked, [=]() {
        QString courseCode = courseCodeEdit->text().trimmed();

        if (courseCode.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter a course code.");
            return;
        }

        Database* db = Database::getInstance();
        Course* course = db->getCourse(courseCode);

        if (course) {
            QString displayText = "Lecture Materials for " + courseCode + ":\n";
            displayText += "================================\n\n";

            int lectureNum = 1;
            for (const QString& lecture : course->getLectureMaterials()) {
                QString fileName = QFileInfo(lecture).fileName();
                displayText += QString("%1. %2\n   Path: %3\n\n")
                                   .arg(lectureNum)
                                   .arg(fileName)
                                   .arg(lecture);
                lectureNum++;
            }

            if (lectureNum == 1) {
                displayText = "No lecture materials available for this course.";
            }

            lecturesDisplay->setText(displayText);
        } else {
            QMessageBox::warning(this, "Error", "Course not found.");
        }
    });

    contentLayout->addStretch();
}

void StudentDashboard::onViewFeedback()
{
    clearContent();

    QLabel *title = new QLabel("Course Feedback", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    QLineEdit *courseCodeEdit = new QLineEdit(contentWidget);
    courseCodeEdit->setPlaceholderText("Enter course code to view feedback");

    QPushButton *viewButton = new QPushButton("View Feedback", contentWidget);

    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(courseCodeEdit);
    searchLayout->addWidget(viewButton);

    contentLayout->addLayout(searchLayout);

    QTextEdit *feedbackDisplay = new QTextEdit(contentWidget);
    feedbackDisplay->setReadOnly(true);
    feedbackDisplay->setMinimumHeight(150);

    contentLayout->addWidget(feedbackDisplay);

    connect(viewButton, &QPushButton::clicked, [=]() {
        QString courseCode = courseCodeEdit->text().trimmed();

        if (courseCode.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter a course code.");
            return;
        }

        Database* db = Database::getInstance();
        Course* course = db->getCourse(courseCode);

        if (course) {
            QString feedback = course->getFeedback(currentStudent->getId());
            if (feedback == "No feedback available") {
                feedbackDisplay->setText("No feedback available for you in this course yet.");
            } else {
                feedbackDisplay->setText("Feedback for " + courseCode + ":\n\n" + feedback);
            }
        } else {
            QMessageBox::warning(this, "Error", "Course not found.");
        }
    });

    contentLayout->addStretch();
}

void StudentDashboard::onUpdateProfile()
{
    clearContent();

    QLabel *title = new QLabel("My Profile", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    // Create form
    QWidget *formWidget = new QWidget(contentWidget);
    QFormLayout *formLayout = new QFormLayout(formWidget);
    formLayout->setSpacing(15);

    QLineEdit *nameEdit = new QLineEdit(currentStudent->getName(), formWidget);
    QLineEdit *emailEdit = new QLineEdit(currentStudent->getEmail(), formWidget);
    QLineEdit *rollEdit = new QLineEdit(currentStudent->getRollNumber(), formWidget);
    rollEdit->setReadOnly(true);

    QLineEdit *deptEdit = new QLineEdit(currentStudent->getDepartment(), formWidget);
    QSpinBox *semesterSpin = new QSpinBox(formWidget);
    semesterSpin->setRange(1, 8);
    semesterSpin->setValue(currentStudent->getSemester());

    QLineEdit *passwordEdit = new QLineEdit(formWidget);
    passwordEdit->setPlaceholderText("Enter new password (leave blank to keep current)");
    passwordEdit->setEchoMode(QLineEdit::Password);

    QPushButton *saveButton = new QPushButton("Save Changes", formWidget);
    saveButton->setStyleSheet(
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

    formLayout->addRow("Name:", nameEdit);
    formLayout->addRow("Email:", emailEdit);
    formLayout->addRow("Roll Number:", rollEdit);
    formLayout->addRow("Department:", deptEdit);
    formLayout->addRow("Semester:", semesterSpin);
    formLayout->addRow("New Password:", passwordEdit);
    formLayout->addRow(saveButton);

    contentLayout->addWidget(formWidget);

    connect(saveButton, &QPushButton::clicked, [=]() {
        // Update student information
        currentStudent->setName(nameEdit->text());
        currentStudent->setEmail(emailEdit->text());
        currentStudent->setDepartment(deptEdit->text());
        currentStudent->setSemester(semesterSpin->value());

        if (!passwordEdit->text().isEmpty()) {
            currentStudent->setPassword(passwordEdit->text());
        }

        // Update UI
        welcomeLabel->setText("Welcome, " + currentStudent->getName());
        infoLabel->setText(
            "Roll No: " + currentStudent->getRollNumber() +
            " | Department: " + currentStudent->getDepartment() +
            " | Semester: " + QString::number(currentStudent->getSemester())
            );

        QMessageBox::information(this, "Success", "Profile updated successfully!");
        passwordEdit->clear();
    });

    contentLayout->addStretch();
}

void StudentDashboard::onLogout()
{
    // Save data
    Database::getInstance()->saveAllData();

    // Close dashboard
    this->close();

    // Note: You need to handle showing the login window again
    // This is typically done in main.cpp
}

void StudentDashboard::clearContent()
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
