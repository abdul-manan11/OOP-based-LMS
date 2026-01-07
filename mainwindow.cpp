#include "mainwindow.h"
#include "studentdashboard.h"
#include "facultydashboard.h"
#include "admindashboard.h"
#include <QApplication>
#include <QScreen>
#include <QPalette>
#include <QFont>
#include <QSizePolicy>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , database(Database::getInstance())
{
    setWindowTitle("Learning Management System");

    // Get screen geometry for responsive sizing
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    // Set window to 80% of screen size
    int width = screenGeometry.width() * 0.8;
    int height = screenGeometry.height() * 0.8;
    resize(width, height);
    setMinimumSize(800, 600);

    // Center window on screen
    move(screenGeometry.center() - rect().center());

    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // Create central widget
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    setCentralWidget(centralWidget);

    // Set background gradient
    centralWidget->setStyleSheet(
        "#centralWidget {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "                               stop:0 #667eea, stop:1 #764ba2);"
        "}"
        );

    // Create main layout with center alignment
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Create login container frame
    QFrame *loginFrame = new QFrame(centralWidget);
    loginFrame->setObjectName("loginFrame");
    loginFrame->setFixedSize(500, 700);
    loginFrame->setStyleSheet(
        "#loginFrame {"
        "   background-color: white;"
        "   border-radius: 15px;"
        "   box-shadow: 0 10px 40px rgba(0, 0, 0, 0.2);"
        "}"
        );

    // Create main layout for login frame
    QVBoxLayout *frameMainLayout = new QVBoxLayout(loginFrame);
    frameMainLayout->setSpacing(0);
    frameMainLayout->setContentsMargins(50, 50, 50, 50);
    frameMainLayout->setAlignment(Qt::AlignTop);

    // TOP SECTION - Logo/Title
    QVBoxLayout *topLayout = new QVBoxLayout();
    topLayout->setSpacing(10);
    topLayout->setAlignment(Qt::AlignCenter);

    // Title - Two lines
    QLabel *titleLine1 = new QLabel("LEARNING MANAGEMENT", loginFrame);
    titleLine1->setAlignment(Qt::AlignCenter);
    titleLine1->setStyleSheet(
        "font-size: 28px;"
        "font-weight: 900;"
        "color: #2c3e50;"
        "margin: 0;"
        "padding: 0;"
        "letter-spacing: 1px;"
        );

    QLabel *titleLine2 = new QLabel("SYSTEM", loginFrame);
    titleLine2->setAlignment(Qt::AlignCenter);
    titleLine2->setStyleSheet(
        "font-size: 28px;"
        "font-weight: 900;"
        "color: #2c3e50;"
        "margin: 0;"
        "padding: 0;"
        "letter-spacing: 1px;"
        );

    // Subtitle
    QLabel *subtitleLabel = new QLabel("Welcome to the Login Portal", loginFrame);
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet(
        "font-size: 14px;"
        "color: #7f8c8d;"
        "margin-top: 10px;"
        );

    topLayout->addWidget(titleLine1);
    topLayout->addWidget(titleLine2);
    topLayout->addWidget(subtitleLabel);

    frameMainLayout->addLayout(topLayout);

    // Add spacing after title
    frameMainLayout->addSpacing(40);

    // FORM SECTION
    QVBoxLayout *formLayout = new QVBoxLayout();
    formLayout->setSpacing(30);
    formLayout->setContentsMargins(0, 0, 0, 0);

    // ROLE SELECTION
    QVBoxLayout *roleLayout = new QVBoxLayout();
    roleLayout->setSpacing(8);

    QLabel *roleLabel = new QLabel("SELECT ROLE:", loginFrame);
    roleLabel->setStyleSheet(
        "font-weight: bold;"
        "color: #34495e;"
        "font-size: 11px;"
        "text-transform: uppercase;"
        "letter-spacing: 1px;"
        );

    roleComboBox = new QComboBox(loginFrame);
    roleComboBox->setObjectName("roleComboBox");
    roleComboBox->addItem("Student");
    roleComboBox->addItem("Faculty");
    roleComboBox->addItem("Admin");
    roleComboBox->setMinimumHeight(45);
    roleComboBox->setStyleSheet(
        "#roleComboBox {"
        "   padding: 0 15px;"
        "   border: 2px solid #e0e0e0;"
        "   border-radius: 8px;"
        "   font-size: 16px;"
        "   background-color: white;"
        "   selection-background-color: #3498db;"
        "   selection-color: white;"
        "}"
        "#roleComboBox:hover {"
        "   border: 2px solid #3498db;"
        "}"
        "#roleComboBox:focus {"
        "   border: 2px solid #2980b9;"
        "   outline: none;"
        "}"
        "#roleComboBox::drop-down {"
        "   border: none;"
        "   width: 40px;"
        "}"
        "#roleComboBox::down-arrow {"
        "   image: none;"
        "   border-left: 6px solid transparent;"
        "   border-right: 6px solid transparent;"
        "   border-top: 6px solid #7f8c8d;"
        "}"
        );

    roleLayout->addWidget(roleLabel);
    roleLayout->addWidget(roleComboBox);
    formLayout->addLayout(roleLayout);

    // EMAIL INPUT
    QVBoxLayout *emailLayout = new QVBoxLayout();
    emailLayout->setSpacing(8);

    QLabel *emailLabel = new QLabel("EMAIL ADDRESS:", loginFrame);
    emailLabel->setStyleSheet(
        "font-weight: bold;"
        "color: #34495e;"
        "font-size: 11px;"
        "text-transform: uppercase;"
        "letter-spacing: 1px;"
        );

    emailLineEdit = new QLineEdit(loginFrame);
    emailLineEdit->setObjectName("emailLineEdit");
    emailLineEdit->setPlaceholderText("Enter your email address");
    emailLineEdit->setMinimumHeight(45);
    emailLineEdit->setStyleSheet(
        "#emailLineEdit {"
        "   padding: 0 15px;"
        "   border: 2px solid #e0e0e0;"
        "   border-radius: 8px;"
        "   font-size: 16px;"
        "   background-color: white;"
        "}"
        "#emailLineEdit:hover {"
        "   border: 2px solid #3498db;"
        "}"
        "#emailLineEdit:focus {"
        "   border: 2px solid #2980b9;"
        "   outline: none;"
        "}"
        );

    emailLayout->addWidget(emailLabel);
    emailLayout->addWidget(emailLineEdit);
    formLayout->addLayout(emailLayout);

    // PASSWORD INPUT
    QVBoxLayout *passwordLayout = new QVBoxLayout();
    passwordLayout->setSpacing(8);

    QLabel *passwordLabel = new QLabel("PASSWORD:", loginFrame);
    passwordLabel->setStyleSheet(
        "font-weight: bold;"
        "color: #34495e;"
        "font-size: 11px;"
        "text-transform: uppercase;"
        "letter-spacing: 1px;"
        );

    passwordLineEdit = new QLineEdit(loginFrame);
    passwordLineEdit->setObjectName("passwordLineEdit");
    passwordLineEdit->setPlaceholderText("Enter your password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setMinimumHeight(45);
    passwordLineEdit->setStyleSheet(
        "#passwordLineEdit {"
        "   padding: 0 15px;"
        "   border: 2px solid #e0e0e0;"
        "   border-radius: 8px;"
        "   font-size: 16px;"
        "   background-color: white;"
        "}"
        "#passwordLineEdit:hover {"
        "   border: 2px solid #3498db;"
        "}"
        "#passwordLineEdit:focus {"
        "   border: 2px solid #2980b9;"
        "   outline: none;"
        "}"
        );

    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordLineEdit);
    formLayout->addLayout(passwordLayout);

    // Add form layout to main layout
    frameMainLayout->addLayout(formLayout);

    // Add spacing before login button
    frameMainLayout->addSpacing(40);

    // LOGIN BUTTON
    loginButton = new QPushButton("LOGIN", loginFrame);
    loginButton->setObjectName("loginButton");
    loginButton->setCursor(Qt::PointingHandCursor);
    loginButton->setMinimumHeight(50);
    loginButton->setStyleSheet(
        "#loginButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "                               stop:0 #3498db, stop:1 #2980b9);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   font-weight: bold;"
        "   font-size: 16px;"
        "   letter-spacing: 1px;"
        "   text-transform: uppercase;"
        "}"
        "#loginButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "                               stop:0 #2980b9, stop:1 #1c6ea4);"
        "   transform: translateY(-2px);"
        "   box-shadow: 0 5px 15px rgba(41, 128, 185, 0.4);"
        "}"
        "#loginButton:pressed {"
        "   background: #1c6ea4;"
        "   transform: translateY(0);"
        "}"
        "#loginButton:disabled {"
        "   background: #bdc3c7;"
        "   color: #7f8c8d;"
        "}"
        );

    frameMainLayout->addWidget(loginButton);

    // Add spacing after login button
    frameMainLayout->addSpacing(20);

    // FORGOT PASSWORD LINK
    QLabel *forgotLabel = new QLabel("<a href='#' style='color: #3498db; text-decoration: none;'>Forgot Password?</a>", loginFrame);
    forgotLabel->setAlignment(Qt::AlignCenter);
    forgotLabel->setOpenExternalLinks(false);
    forgotLabel->setStyleSheet("font-size: 14px;");

    frameMainLayout->addWidget(forgotLabel);

    // Add stretch to push everything to top
    frameMainLayout->addStretch();

    // Add login frame to main layout
    mainLayout->addWidget(loginFrame, 0, Qt::AlignCenter);

    // Connect signals and slots
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(roleComboBox, &QComboBox::currentTextChanged, this, [this](const QString &text) {
        // Update placeholder based on role
        if (text == "Student") {
            emailLineEdit->setPlaceholderText("e.g., ali@university.edu");
        } else if (text == "Faculty") {
            emailLineEdit->setPlaceholderText("e.g., ahmed@university.edu");
        } else if (text == "Admin") {
            emailLineEdit->setPlaceholderText("e.g., admin@lms.com");
        }
    });

    // Enable/disable login button based on input
    auto updateLoginButton = [this]() {
        bool enabled = !emailLineEdit->text().isEmpty() &&
                       !passwordLineEdit->text().isEmpty();
        loginButton->setEnabled(enabled);
    };

    connect(emailLineEdit, &QLineEdit::textChanged, this, updateLoginButton);
    connect(passwordLineEdit, &QLineEdit::textChanged, this, updateLoginButton);

    // Set initial state to match the image
    loginButton->setEnabled(false);
    roleComboBox->setCurrentIndex(1);  // Set to Faculty as shown in image

    // Set email text to match the image
    emailLineEdit->setText("a_ahmed@university");

    // Set focus to password field as shown in image
    passwordLineEdit->setFocus();
}

void MainWindow::onLoginClicked()
{
    QString role = roleComboBox->currentText();
    QString email = emailLineEdit->text().trimmed();
    QString password = passwordLineEdit->text();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed",
                             "Please enter both email and password.");
        return;
    }

    Person* user = database->authenticateUser(email, password, role);

    if (user) {
        // Clear password field for security
        passwordLineEdit->clear();

        // Open appropriate dashboard
        if (role == "Student") {
            Student *student = dynamic_cast<Student*>(user);
            if (student) {
                StudentDashboard *studentDash = new StudentDashboard(student);
                studentDash->showMaximized();
                this->hide();
            }
        }
        else if (role == "Faculty") {
            Faculty *faculty = dynamic_cast<Faculty*>(user);
            if (faculty) {
                FacultyDashboard *facultyDash = new FacultyDashboard(faculty);
                facultyDash->showMaximized();
                this->hide();
            }
        }
        else if (role == "Admin") {
            Admin *admin = dynamic_cast<Admin*>(user);
            if (admin) {
                AdminDashboard *adminDash = new AdminDashboard(admin);
                adminDash->showMaximized();
                this->hide();
            }
        }
    }
    else {
        QMessageBox::warning(this, "Login Failed",
                             "Invalid email or password. Please try again.\n\n"
                             "Default credentials:\n"
                             "• Student: ali@university.edu / password123\n"
                             "• Faculty: ahmed@university.edu / password123\n"
                             "• Admin: admin@lms.com / admin123");

        // Clear password field and set focus
        passwordLineEdit->clear();
        passwordLineEdit->setFocus();
    }
}

void MainWindow::onRoleChanged(int index)
{
    Q_UNUSED(index);
    // Keep this function for compatibility but don't use it
    // We're using lambda connection instead
}
