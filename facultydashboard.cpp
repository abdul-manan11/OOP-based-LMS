#include "facultydashboard.h"
#include <QDir>
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
#include <utility>  // For std::as_const
#include"student.h"
FacultyDashboard::FacultyDashboard(Faculty* faculty, QWidget *parent)
    : QMainWindow(parent)
    , currentFaculty(faculty)
{
    setWindowTitle("Faculty Dashboard - Learning Management System");
    // Allow window to be resized to full screen
    setMinimumSize(800, 600); // Reasonable minimum, not too large

    setupUI();
}

FacultyDashboard::~FacultyDashboard()
{
}

void FacultyDashboard::setupUI()
{
    // Create central widget
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create main layout
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    // Create header
    QWidget *headerWidget = new QWidget(centralWidget);
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    welcomeLabel = new QLabel("Welcome, " + currentFaculty->getName(), headerWidget);
    welcomeLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #2c3e50;");

    infoLabel = new QLabel(
        "ID: " + currentFaculty->getFacultyId() +
            " | Department: " + currentFaculty->getDepartment() +
            " | Designation: " + currentFaculty->getDesignation(),
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

    lectureButton = new QPushButton("Upload Lecture", centralWidget);
    assignmentButton = new QPushButton("Create Assignment", centralWidget);
    attendanceButton = new QPushButton("Mark Attendance", centralWidget);
    gradeButton = new QPushButton("Grade Assignment", centralWidget);
    submissionsButton = new QPushButton("View Submissions", centralWidget);
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

    lectureButton->setStyleSheet(buttonStyle);
    assignmentButton->setStyleSheet(buttonStyle);
    attendanceButton->setStyleSheet(buttonStyle);
    gradeButton->setStyleSheet(buttonStyle);
    submissionsButton->setStyleSheet(buttonStyle);

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
    buttonLayout->addWidget(lectureButton);
    buttonLayout->addWidget(assignmentButton);
    buttonLayout->addWidget(attendanceButton);
    buttonLayout->addWidget(gradeButton);
    buttonLayout->addWidget(submissionsButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(logoutButton);

    mainLayout->addLayout(buttonLayout);

    // Create content area - make it expandable
    contentWidget = new QWidget(centralWidget);
    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(20, 20, 20, 20);
    contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(contentWidget, 1); // The "1" makes it stretch

    // Connect signals and slots
    connect(lectureButton, &QPushButton::clicked, this, &FacultyDashboard::onUploadLecture);
    connect(assignmentButton, &QPushButton::clicked, this, &FacultyDashboard::onCreateAssignment);
    connect(attendanceButton, &QPushButton::clicked, this, &FacultyDashboard::onMarkAttendance);
    connect(gradeButton, &QPushButton::clicked, this, &FacultyDashboard::onGradeAssignment);
    connect(submissionsButton, &QPushButton::clicked, this, &FacultyDashboard::onViewSubmissions);
    connect(logoutButton, &QPushButton::clicked, this, &FacultyDashboard::onLogout);

    // Show upload lecture by default
    onUploadLecture();
}

void FacultyDashboard::onUploadLecture()
{
    clearContent();

    QLabel *title = new QLabel("Upload Lecture Material", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    // Create form
    QWidget *formWidget = new QWidget(contentWidget);
    QFormLayout *formLayout = new QFormLayout(formWidget);
    formLayout->setSpacing(15);
    formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow); // Makes fields expand
    formLayout->setLabelAlignment(Qt::AlignRight); // Align labels to right

    QLineEdit *courseCodeEdit = new QLineEdit(formWidget);
    courseCodeEdit->setPlaceholderText("e.g., CS101");
    courseCodeEdit->setMinimumWidth(300);
    courseCodeEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QLineEdit *lectureTitleEdit = new QLineEdit(formWidget);
    lectureTitleEdit->setPlaceholderText("e.g., Introduction to Programming");
    lectureTitleEdit->setMinimumWidth(300);
    lectureTitleEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QLineEdit *filePathEdit = new QLineEdit(formWidget);
    filePathEdit->setPlaceholderText("Select file to upload");
    filePathEdit->setReadOnly(true);
    filePathEdit->setMinimumWidth(350);
    filePathEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QPushButton *browseButton = new QPushButton("Browse...", formWidget);
    browseButton->setFixedWidth(100);
    QPushButton *uploadButton = new QPushButton("Upload Lecture", formWidget);
    uploadButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "   min-width: 150px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        );

    QHBoxLayout *fileLayout = new QHBoxLayout();
    fileLayout->addWidget(filePathEdit);
    fileLayout->addWidget(browseButton);

    formLayout->addRow("Course Code:", courseCodeEdit);
    formLayout->addRow("Lecture Title:", lectureTitleEdit);
    formLayout->addRow("File:", fileLayout);
    formLayout->addRow("", uploadButton);

    formWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    contentLayout->addWidget(formWidget);

    // Connect browse button
    connect(browseButton, &QPushButton::clicked, [=]() {
        QString filePath = QFileDialog::getOpenFileName(
            this,
            "Select Lecture File",
            QDir::homePath(),
            "All Files (*);;PDF Files (*.pdf);;PPT Files (*.ppt *.pptx)"
            );
        if (!filePath.isEmpty()) {
            filePathEdit->setText(filePath);
        }
    });

    // Connect upload button
    connect(uploadButton, &QPushButton::clicked, [=]() {
        QString courseCode = courseCodeEdit->text().trimmed();
        QString lectureTitle = lectureTitleEdit->text().trimmed();
        QString filePath = filePathEdit->text();

        if (courseCode.isEmpty() || lectureTitle.isEmpty() || filePath.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill all required fields and select a file.");
            return;
        }

        Database* db = Database::getInstance();
        Course* course = db->getCourse(courseCode);
        if (course) {
            course->addLectureMaterial(filePath);
            QMessageBox::information(this, "Success",
                                     QString("Lecture uploaded successfully!\n"
                                             "Course: %1\n"
                                             "Title: %2").arg(courseCode).arg(lectureTitle));

            // Clear form
            courseCodeEdit->clear();
            lectureTitleEdit->clear();
            filePathEdit->clear();
        } else {
            QMessageBox::warning(this, "Error", "Course not found.");
        }
    });

    contentLayout->addStretch();
}

void FacultyDashboard::onCreateAssignment()
{
    clearContent();

    QLabel *title = new QLabel("Create New Assignment", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    // Create form
    QWidget *formWidget = new QWidget(contentWidget);
    QFormLayout *formLayout = new QFormLayout(formWidget);
    formLayout->setSpacing(15);
    formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    formLayout->setLabelAlignment(Qt::AlignRight);

    QLineEdit *courseCodeEdit = new QLineEdit(formWidget);
    courseCodeEdit->setPlaceholderText("e.g., CS101");
    courseCodeEdit->setMinimumWidth(300);
    courseCodeEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QLineEdit *assignmentTitleEdit = new QLineEdit(formWidget);
    assignmentTitleEdit->setPlaceholderText("e.g., Programming Assignment 1");
    assignmentTitleEdit->setMinimumWidth(300);
    assignmentTitleEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QTextEdit *descriptionEdit = new QTextEdit(formWidget);
    descriptionEdit->setMaximumHeight(100);
    descriptionEdit->setPlaceholderText("Enter assignment description");
    descriptionEdit->setMinimumHeight(80);

    QDateEdit *dueDateEdit = new QDateEdit(formWidget);
    dueDateEdit->setDate(QDate::currentDate().addDays(7));
    dueDateEdit->setCalendarPopup(true);
    dueDateEdit->setMinimumWidth(200);

    QSpinBox *totalMarksSpin = new QSpinBox(formWidget);
    totalMarksSpin->setRange(1, 100);
    totalMarksSpin->setValue(100);
    totalMarksSpin->setMinimumWidth(100);

    QPushButton *createButton = new QPushButton("Create Assignment", formWidget);
    createButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #2ecc71;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "   min-width: 150px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #27ae60;"
        "}"
        );

    formLayout->addRow("Course Code:", courseCodeEdit);
    formLayout->addRow("Assignment Title:", assignmentTitleEdit);
    formLayout->addRow("Description:", descriptionEdit);
    formLayout->addRow("Due Date:", dueDateEdit);
    formLayout->addRow("Total Marks:", totalMarksSpin);
    formLayout->addRow("", createButton);

    formWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    contentLayout->addWidget(formWidget);

    // Connect create button
    connect(createButton, &QPushButton::clicked, [=]() {
        QString courseCode = courseCodeEdit->text().trimmed();
        QString assignmentTitle = assignmentTitleEdit->text().trimmed();
        QString description = descriptionEdit->toPlainText();
        QDate dueDate = dueDateEdit->date();
        int totalMarks = totalMarksSpin->value();

        if (courseCode.isEmpty() || assignmentTitle.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter course code and assignment title.");
            return;
        }

        if (dueDate < QDate::currentDate()) {
            QMessageBox::warning(this, "Error", "Due date cannot be in the past.");
            return;
        }

        // Generate assignment ID
        QString assignmentId = courseCode + "_" + assignmentTitle + "_" + QDate::currentDate().toString("yyyyMMdd");

        // Create assignment object
        Assignment* assignment = new Assignment(assignmentId, assignmentTitle, description, courseCode, dueDate, totalMarks);

        // Add assignment to course
        Database* db = Database::getInstance();
        Course* course = db->getCourse(courseCode);
        if (course) {
            course->addAssignment(assignment);
            QMessageBox::information(this, "Success",
                                     QString("Assignment created successfully!\n"
                                             "Course: %1\n"
                                             "Title: %2\n"
                                             "Due Date: %3\n"
                                             "Total Marks: %4")
                                         .arg(courseCode)
                                         .arg(assignmentTitle)
                                         .arg(dueDate.toString("dd/MM/yyyy"))
                                         .arg(QString::number(totalMarks)));

            // Clear form
            courseCodeEdit->clear();
            assignmentTitleEdit->clear();
            descriptionEdit->clear();
            dueDateEdit->setDate(QDate::currentDate().addDays(7));
            totalMarksSpin->setValue(100);
        } else {
            QMessageBox::warning(this, "Error", "Course not found.");
            delete assignment; // Clean up memory if course not found
        }
    });

    contentLayout->addStretch();
}

void FacultyDashboard::onMarkAttendance()
{
    clearContent();

    QLabel *title = new QLabel("Mark Student Attendance", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    // Create form
    QWidget *formWidget = new QWidget(contentWidget);
    QFormLayout *formLayout = new QFormLayout(formWidget);
    formLayout->setSpacing(15);
    formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    formLayout->setLabelAlignment(Qt::AlignRight);

    QLineEdit *courseCodeEdit = new QLineEdit(formWidget);
    courseCodeEdit->setPlaceholderText("e.g., CS101");
    courseCodeEdit->setMinimumWidth(300);
    courseCodeEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QLineEdit *studentIdEdit = new QLineEdit(formWidget);
    studentIdEdit->setPlaceholderText("e.g., S12345");
    studentIdEdit->setMinimumWidth(300);
    studentIdEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QDateEdit *dateEdit = new QDateEdit(formWidget);
    dateEdit->setDate(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    dateEdit->setMinimumWidth(200);

    QCheckBox *presentCheckBox = new QCheckBox("Present", formWidget);
    presentCheckBox->setChecked(true);

    QPushButton *markButton = new QPushButton("Mark Attendance", formWidget);
    markButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #f39c12;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "   min-width: 150px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #e67e22;"
        "}"
        );

    formLayout->addRow("Course Code:", courseCodeEdit);
    formLayout->addRow("Student ID:", studentIdEdit);
    formLayout->addRow("Date:", dateEdit);
    formLayout->addRow("Status:", presentCheckBox);
    formLayout->addRow("", markButton);

    formWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    contentLayout->addWidget(formWidget);

    // Connect mark button
    connect(markButton, &QPushButton::clicked, [=]() {
        QString courseCode = courseCodeEdit->text().trimmed();
        QString studentId = studentIdEdit->text().trimmed();
        QDate date = dateEdit->date();
        bool present = presentCheckBox->isChecked();

        if (courseCode.isEmpty() || studentId.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter course code and student ID.");
            return;
        }

        // Update attendance in database
        Database* db = Database::getInstance();
        Student* student = db->getStudent(studentId);
        if (student) {
            // For simplicity, just update with a random attendance value
            // In a real system, you would track daily attendance
            double currentAttendance = student->getAttendanceForCourse(courseCode);
            double newAttendance = present ? currentAttendance + 5 : currentAttendance - 5;
            if (newAttendance > 100) newAttendance = 100;
            if (newAttendance < 0) newAttendance = 0;

            student->addAttendance(courseCode, newAttendance);

            QString status = present ? "Present" : "Absent";
            QMessageBox::information(this, "Success",
                                     QString("Attendance marked successfully!\n"
                                             "Course: %1\n"
                                             "Student ID: %2\n"
                                             "Date: %3\n"
                                             "Status: %4\n"
                                             "New Attendance: %5%")
                                         .arg(courseCode)
                                         .arg(studentId)
                                         .arg(date.toString("dd/MM/yyyy"))
                                         .arg(status)
                                         .arg(QString::number(newAttendance)));

            // Clear form
            studentIdEdit->clear();
        } else {
            QMessageBox::warning(this, "Error", "Student not found.");
        }
    });

    contentLayout->addStretch();
}

void FacultyDashboard::onGradeAssignment()
{
    clearContent();

    QLabel *title = new QLabel("Grade Student Assignment", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    // Create form
    QWidget *formWidget = new QWidget(contentWidget);
    QFormLayout *formLayout = new QFormLayout(formWidget);
    formLayout->setSpacing(15);
    formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    formLayout->setLabelAlignment(Qt::AlignRight);

    QLineEdit *assignmentIdEdit = new QLineEdit(formWidget);
    assignmentIdEdit->setPlaceholderText("e.g., CS101_Assignment1");
    assignmentIdEdit->setMinimumWidth(300);
    assignmentIdEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QLineEdit *studentIdEdit = new QLineEdit(formWidget);
    studentIdEdit->setPlaceholderText("e.g., S12345");
    studentIdEdit->setMinimumWidth(300);
    studentIdEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QSpinBox *marksSpin = new QSpinBox(formWidget);
    marksSpin->setRange(0, 100);
    marksSpin->setValue(85);
    marksSpin->setMinimumWidth(100);

    QTextEdit *feedbackEdit = new QTextEdit(formWidget);
    feedbackEdit->setMaximumHeight(100);
    feedbackEdit->setPlaceholderText("Enter feedback for the student");
    feedbackEdit->setMinimumHeight(80);

    QPushButton *gradeButton = new QPushButton("Submit Grade", formWidget);
    gradeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #9b59b6;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "   min-width: 150px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #8e44ad;"
        "}"
        );

    formLayout->addRow("Assignment ID:", assignmentIdEdit);
    formLayout->addRow("Student ID:", studentIdEdit);
    formLayout->addRow("Marks (out of 100):", marksSpin);
    formLayout->addRow("Feedback:", feedbackEdit);
    formLayout->addRow("", gradeButton);

    formWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    contentLayout->addWidget(formWidget);

    // Connect grade button
    connect(gradeButton, &QPushButton::clicked, [=]() {
        QString assignmentId = assignmentIdEdit->text().trimmed();
        QString studentId = studentIdEdit->text().trimmed();
        double marks = marksSpin->value();
        QString feedback = feedbackEdit->toPlainText();

        if (assignmentId.isEmpty() || studentId.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter assignment ID and student ID.");
            return;
        }

        Database* db = Database::getInstance();
        Student* student = db->getStudent(studentId);
        if (student) {
            // Extract course code from assignment ID (simple logic)
            QString courseCode = assignmentId.split("_").first();

            // Update student grade
            student->addGrade(courseCode, marks);

            // Update course feedback
            Course* course = db->getCourse(courseCode);
            if (course) {
                course->addFeedback(studentId, feedback);
            }

            QMessageBox::information(this, "Success",
                                     QString("Assignment graded successfully!\n"
                                             "Assignment: %1\n"
                                             "Student: %2\n"
                                             "Marks: %3/100\n"
                                             "Feedback submitted")
                                         .arg(assignmentId)
                                         .arg(studentId)
                                         .arg(QString::number(marks)));

            // Clear form
            assignmentIdEdit->clear();
            studentIdEdit->clear();
            marksSpin->setValue(85);
            feedbackEdit->clear();
        } else {
            QMessageBox::warning(this, "Error", "Student not found.");
        }
    });

    contentLayout->addStretch();
}

void FacultyDashboard::onViewSubmissions()
{
    clearContent();

    QLabel *title = new QLabel("View Student Submissions", contentWidget);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 20px;");
    contentLayout->addWidget(title);

    QWidget *searchWidget = new QWidget(contentWidget);
    QHBoxLayout *searchLayout = new QHBoxLayout(searchWidget);
    searchLayout->setContentsMargins(0, 0, 0, 0);

    QLineEdit *courseCodeEdit = new QLineEdit(searchWidget);
    courseCodeEdit->setPlaceholderText("Enter course code to view submissions");
    courseCodeEdit->setMinimumWidth(300);
    courseCodeEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QPushButton *viewButton = new QPushButton("View Submissions", searchWidget);
    viewButton->setFixedWidth(150);

    searchLayout->addWidget(courseCodeEdit);
    searchLayout->addWidget(viewButton);
    searchLayout->addStretch();

    contentLayout->addWidget(searchWidget);

    QTextEdit *submissionsDisplay = new QTextEdit(contentWidget);
    submissionsDisplay->setReadOnly(true);
    submissionsDisplay->setMinimumHeight(300);
    submissionsDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    contentLayout->addWidget(submissionsDisplay, 1); // Make it stretch

    connect(viewButton, &QPushButton::clicked, [=]() {
        QString courseCode = courseCodeEdit->text().trimmed();

        if (courseCode.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter a course code.");
            return;
        }

        Database* db = Database::getInstance();
        Course* course = db->getCourse(courseCode);

        if (course) {
            QString report = "=== SUBMISSIONS FOR COURSE: " + courseCode + " ===\n";
            report += "Course: " + course->getCourseName() + "\n";
            report += "========================================\n\n";

            QVector<Assignment*> assignments = course->getAssignments();

            if (assignments.isEmpty()) {
                report += "No assignments created for this course yet.\n";
            } else {
                report += "Assignments:\n";
                for (Assignment* assignment : std::as_const(assignments)) {
                    report += QString("\nAssignment: %1\n").arg(assignment->getAssignmentTitle());
                    report += QString("  ID: %1\n").arg(assignment->getAssignmentId());
                    report += QString("  Due Date: %1\n").arg(assignment->getDueDate().toString("dd/MM/yyyy"));
                    report += QString("  Total Marks: %1\n").arg(QString::number(assignment->getTotalMarks()));
                    report += QString("  Submitted: %1\n").arg(assignment->getIsSubmitted() ? "Yes" : "No");

                    if (assignment->getIsSubmitted()) {
                        report += QString("  Student ID: %1\n").arg(assignment->getStudentId());
                        report += QString("  Submission Date: %1\n").arg(assignment->getSubmissionDate().toString("dd/MM/yyyy"));
                        report += QString("  File: %1\n").arg(assignment->getSubmittedFilePath());
                        report += QString("  Graded: %1\n").arg(assignment->getIsGraded() ? "Yes" : "No");
                        if (assignment->getIsGraded()) {
                            report += QString("  Marks: %1/%2\n")
                            .arg(QString::number(assignment->getObtainedMarks()))
                                .arg(QString::number(assignment->getTotalMarks()));
                        }
                    }
                }
            }

            submissionsDisplay->setText(report);
        } else {
            QMessageBox::warning(this, "Error", "Course not found.");
        }
    });

    contentLayout->addStretch();
}

void FacultyDashboard::onLogout()
{
    // Save data
    Database::getInstance()->saveAllData();

    // Close dashboard
    this->close();
}

void FacultyDashboard::clearContent()
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
