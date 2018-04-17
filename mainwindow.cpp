#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "objects.h"
Patron *patronSession = new Patron();
QPluginLoader loadPlugin("sqldrivers/qsqlmysql.dll");
QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
        ui->setupUi(this);
        //loade db plugin
        if(!loadPlugin.load()) {
            ui->loginValidationOutput->setText("Failed to load SQL drivers.");
        } else if (loadPlugin.isLoaded()) {
                //sjekke db connection
                if(dbConnect(db)) {
                    ui->loginValidationOutput->setText("Connected!");
                    db.close();
                } else {
                    ui->loginValidationOutput->setText(db.lastError().text());
                }

        }
        ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//hver eneste knapp i GUI har egen redirection/programmering:

//Login
void MainWindow::on_loginBtn_clicked()
{
    if(dbConnect(db)) {
        if(verifyLogin(ui->loginEmail->text(), ui->loginPassword->text())){
            if(patronSession->getUserlvl() >= 1) {
                ui->stackedWidget->setCurrentIndex(14);
            } else if(patronSession->getUserlvl() == 0) {
                ui->stackedWidget->setCurrentIndex(2);
            }
            ui->loginEmail->setText("");
            ui->loginPassword->setText("");
            ui->profileGreeting->setText(QString::fromStdString(patronSession->getName()+"'s profile"));
            ui->profileDebt->setText(QString::number(patronSession->getDebt()));
        }
        else {
            ui->loginValidationOutput->setText("Invalid email or password.");
        }
        db.close();
    } else {
        ui->loginValidationOutput->setText("Database connection error:\n"+db.lastError().text());
        db.close();
    }
    //Page2 = user, page 13 = admin
}

void MainWindow::on_createNewUserBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

    //Create User
    void MainWindow::on_createNewUserConfrimBtn_clicked()
    {
        if(dbConnect(db)) {
            ui->createNewUserValidationOutput->setText(QString::fromStdString(createUser(ui->registrationEmail->text(), ui->registrationPassword->text(), ui->registrationName->text())));
            db.close();
        } else {
            ui->createNewUserValidationOutput->setText("Database connection error:\n"+db.lastError().text());
            db.close();
        }
    }

    void MainWindow::on_createNewUserBackBtn_clicked()
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->loginValidationOutput->setText("");
        ui->createNewUserValidationOutput->setText("");
        ui->registrationEmail->setText("");
        ui->registrationPassword->setText("");
        ui->registrationName->setText("");
    }

    //User Options
    void MainWindow::on_menyPageFindBtn_clicked()
    {
        ui->stackedWidget->setCurrentIndex(5);
    }

    void MainWindow::on_menyPageMyProfileBtn_clicked()
    {
        ui->profileDebt->setText(QString::number(patronSession->getDebt()));
        ui->stackedWidget->setCurrentIndex(3);
    }

    void MainWindow::on_menyPageLogoutBtn_clicked()
    {
        ui->loginValidationOutput->setText("Successful user logout:\n"+ QString::fromStdString(patronSession->getEmail()));
        patronSession->clear();
        ui->stackedWidget->setCurrentIndex(0);
    }

        //Profile
        void MainWindow::on_myProfilePageBackBtn_clicked()
        {
            if(patronSession->getUserlvl() >= 1) {
                ui->stackedWidget->setCurrentIndex(14);
            } else if(patronSession->getUserlvl() == 0) {
                ui->stackedWidget->setCurrentIndex(2);
            }
        }

        void MainWindow::on_myProfilePageChangeInfoBtn_clicked()
        {
            ui->stackedWidget->setCurrentIndex(4);
        }

            //Change User Info
            void MainWindow::on_changeUserDataBackBtn_clicked()
            {
                ui->profileGreeting->setText(QString::fromStdString(patronSession->getName()+"'s profile"));
                ui->changeUserValidationOutput->setText("");
                ui->changeUserEmail->setText("");
                ui->changeUserPassword->setText("");
                ui->changeUserName->setText("");
                ui->stackedWidget->setCurrentIndex(3);
            }

            void MainWindow::on_changeUserInfoConfirmBtn_clicked()
            {
                if(dbConnect(db)) {
                    ui->changeUserValidationOutput->setText(QString::fromStdString(changeUser(ui->changeUserEmail->text(), ui->changeUserPassword->text(), ui->changeUserName->text())));
                    db.close();
                } else {
                    ui->createNewUserValidationOutput->setText("Database connection error:\n"+db.lastError().text());
                    db.close();
                }
            }

        //Find Book
        void MainWindow::on_findBookPageSearchBtn_clicked()
        {

        }

        void MainWindow::on_findBookPageChooseBtn_clicked()
        {

        }

        void MainWindow::on_findBookPageDiscoveryBtn_clicked()
        {
            ui->stackedWidget->setCurrentIndex(6);
        }

        void MainWindow::on_findBookPageConfirmBtn_clicked()
        {
            ui->stackedWidget->setCurrentIndex(7);
        }

        void MainWindow::on_findBookPageBackBtn_clicked()
        {
            if(patronSession->getUserlvl() >= 1) {
                ui->stackedWidget->setCurrentIndex(14);
            } else if(patronSession->getUserlvl() == 0) {
                ui->stackedWidget->setCurrentIndex(2);
            }
        }

            //Discovery
            void MainWindow::on_discoveryPageConfirmBtn_clicked()
            {
                ui->stackedWidget->setCurrentIndex(7);
            }

            void MainWindow::on_discoveryPageBackBtn_clicked()
            {
                ui->stackedWidget->setCurrentIndex(5);
            }

//Admin
void MainWindow::on_adminPageFindBtn_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_adminPageMyProfileBtn_2_clicked()
{
    ui->profileDebt->setText(QString::number(patronSession->getDebt()));
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_adminPageFunctionBtn_clicked()
{
    if(patronSession->getUserlvl() >= 1) {
        ui->stackedWidget->setCurrentIndex(9);
    } else {
        ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
        patronSession->clear();
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::on_adminPageLogoutBtn_2_clicked()
{
    if(patronSession->getUserlvl() == 2) {
        ui->loginValidationOutput->setText("Successful master logout:\n"+ QString::fromStdString(patronSession->getEmail()));
        patronSession->clear();
        ui->stackedWidget->setCurrentIndex(0);
    } else if (patronSession->getUserlvl() == 1){
        ui->loginValidationOutput->setText("Successful admin logout:\n"+ QString::fromStdString(patronSession->getEmail()));
        patronSession->clear();
    ui->stackedWidget->setCurrentIndex(0);
    } else {
        ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
        patronSession->clear();
        ui->stackedWidget->setCurrentIndex(0);
    }
}

    //Admin Functions
    void MainWindow::on_adminFunctionPageNewAdminBtn_clicked()
    {
        if(patronSession->getUserlvl() >= 1) {
            ui->stackedWidget->setCurrentIndex(11);
        } else {
            ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
            patronSession->clear();
            ui->stackedWidget->setCurrentIndex(0);
        }
    }

    void MainWindow::on_adminFunctionPageLibraryBtn_clicked()
    {
        if(patronSession->getUserlvl() >= 1) {
            ui->stackedWidget->setCurrentIndex(13);
        } else {
            ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
            patronSession->clear();
            ui->stackedWidget->setCurrentIndex(0);
        }
    }

    void MainWindow::on_adminFunctionPageBookBtn_clicked()
    {
        if(patronSession->getUserlvl() >= 1) {
            ui->stackedWidget->setCurrentIndex(12);
        } else {
            ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
            patronSession->clear();
            ui->stackedWidget->setCurrentIndex(0);
        }
    }

    void MainWindow::on_adminFunctionPageRemoveBookBtn_clicked()
    {
        if(patronSession->getUserlvl() >= 1) {
            ui->stackedWidget->setCurrentIndex(10);
        } else {
            ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
            patronSession->clear();
            ui->stackedWidget->setCurrentIndex(0);
        }
    }

    void MainWindow::on_adminFunctionPageBackBtn_clicked()
    {
        if(patronSession->getUserlvl() >= 1) {
            ui->stackedWidget->setCurrentIndex(14);
        } else {
            ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
            patronSession->clear();
            ui->stackedWidget->setCurrentIndex(0);
        }
    }

        //Create Admin
        void MainWindow::on_adminPageConfirmBtn_clicked()
        {
            if(patronSession->getUserlvl() >= 1) {
                if(dbConnect(db)) {
                    ui->adminPageValidationOutput->setText(QString::fromStdString(createAdmin(ui->adminPageEmail->text(),ui->adminPagePassword->text(),ui->adminPageName->text())));
                    db.close();
                }
            } else {
                ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
                patronSession->clear();
                ui->stackedWidget->setCurrentIndex(0);
                db.close();
            }
        }

        void MainWindow::on_adminPageBackBtn_clicked()
        {
            if(patronSession->getUserlvl() >= 1) {
                ui->adminPageEmail->setText("");
                ui->adminPagePassword->setText("");
                ui->adminPageName->setText("");
                ui->adminPageValidationOutput->setText("");
                ui->stackedWidget->setCurrentIndex(9);
            } else {
                ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
                patronSession->clear();
                ui->stackedWidget->setCurrentIndex(0);
            }
        }

        //Create Library
        void MainWindow::on_addLibraryAddBtn_clicked()
        {
            if(patronSession->getUserlvl() >= 1) {
                if(dbConnect(db)) {
                    ui->addLibraryValidationOutput->setText(QString::fromStdString(addLibrary(ui->addLibraryName->text(),ui->addLibraryAddress->text())));
                    db.close();
                }
            } else {
                ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
                patronSession->clear();
                ui->stackedWidget->setCurrentIndex(0);
                db.close();
            }
        }
        void MainWindow::on_addLibraryBackBtn_clicked()
        {
            if(patronSession->getUserlvl() >= 1) {
                ui->addLibraryName->setText("");
                ui->addLibraryAddress->setText("");
                ui->addLibraryValidationOutput->setText("");
                ui->stackedWidget->setCurrentIndex(9);
            } else {
                ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
                patronSession->clear();
                ui->stackedWidget->setCurrentIndex(0);
            }
        }

        //Create Book
        void MainWindow::on_addBookPageBackBtn_clicked()
        {
            if(patronSession->getUserlvl() >= 1) {
                ui->stackedWidget->setCurrentIndex(9);
            } else {
                ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
                patronSession->clear();
                ui->stackedWidget->setCurrentIndex(0);
            }
        }

        //Remove book
        void MainWindow::on_removeBookPageRemoveBtn_clicked()
        {

        }
        void MainWindow::on_removeBookPageBackBtn_clicked()
        {
            if(patronSession->getUserlvl() >= 1) {
                ui->stackedWidget->setCurrentIndex(9);
            } else {
                ui->loginValidationOutput->setText("Security error! Forced logout:\n"+ QString::fromStdString(patronSession->getEmail()));
                patronSession->clear();
                ui->stackedWidget->setCurrentIndex(0);
            }
        }

//ShowLibrary
void MainWindow::on_showLibraryConfirmBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}
void MainWindow::on_showLibraryBackBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


//Checkout
void MainWindow::on_checkoutPageAddBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}
void MainWindow::on_checkoutPageCheckoutBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(15);
}
void MainWindow::on_checkoutPageCancelBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

//Confirmation
void MainWindow::on_confirmationPageBackBtn_clicked()
{
    if(patronSession->getUserlvl() >= 1) {
        ui->stackedWidget->setCurrentIndex(14);
    } else if(patronSession->getUserlvl() == 0) {
        ui->stackedWidget->setCurrentIndex(2);
    }
}

//kobler til db, tar db objekt som parameter slik at man
bool MainWindow::dbConnect(QSqlDatabase db) {
        db.setHostName("student.cs.hioa.no");
        db.setDatabaseName("s315613");
        db.setUserName("s315613");
        db.setPassword("");

        if (db.open()) {
            return true;
        } else {
            cout << db.lastError().text().toStdString() << endl;
            return false;
        }
}

//verifiserer login på server side og binder verdier til det statiske patron objektet.
bool MainWindow::verifyLogin(QString email, QString password) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Patron WHERE Patron.Email = :email && Patron.Password = :password;");
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.exec();
    if(query.next()) {
            patronSession->setName(query.value(1).toString().toStdString());
            patronSession->setEmail(query.value(2).toString().toStdString());
            patronSession->setPassword(query.value(3).toString().toStdString());
            patronSession->setDebt(query.value(4).toInt());
            patronSession->setUserlvl(query.value(5).toInt());
//            ui->loginValidationOutput->setText(QString::fromStdString(patronSession->getName()));
        return true;
    } else {
        return false;
    }
}

//sjekke om bruker finnes, hvis ikke lage ny bruker.
string MainWindow::createUser(QString email, QString password, QString name) {
    //sjekke om email og passord er gyldige(regex)
    if(!verifyEmail(email)) {
        return "Request rejected:\nInvalid email submitted.";
    }
    if(!verifyPassword(password)) {
        return "Request rejected:\nInvalid password submitted.\nLength must be 4 to 20 characters.";
    }
    if(!verifyName(name)) {
        return "Request rejected:\nInvalid name submitted.\nFirst letter uppercase. Letters/spaces.";
    }
    //sjekke om email er tatt
    QSqlQuery query;
    query.prepare("SELECT * FROM Patron WHERE Patron.Email = :email;");
    query.bindValue(":email", email);
    query.exec();
    if(query.next()) {
        return "Request rejected:\nEmail already in use.";
    } else {
        //lage ny bruker
        QSqlQuery query;
        query.prepare("INSERT INTO Patron (Name, Email, Password) "
                      "VALUES (:name, :email, :password)");
        query.bindValue(":name", name);
        query.bindValue(":email", email);
        query.bindValue(":password", password);
        query.exec();
        return "Request accepted:\nNew user created!";
    }
}

string MainWindow::changeUser(QString email, QString password, QString name) {
    //sjekk om noe finnes i feltet og inputtet er gyldig
    if(email.length() > 0) {
        if(!verifyEmail(email)) {
            return "Request rejected:\nInvalid email submitted.";
        }
        //sjekke om email er tatt
        QSqlQuery query;
        query.prepare("SELECT * FROM Patron WHERE Patron.Email = :email;");
        query.bindValue(":email", email);
        query.exec();
        if(query.next()) {
            return "Request rejected:\nEmail already in use.";
        } else {
            //oppdater email
            QSqlQuery query;
            query.prepare("UPDATE Patron SET Email = :newEmail WHERE Patron.Email = :currentEmail");
            query.bindValue(":newEmail", email);
            query.bindValue(":currentEmail", QString::fromStdString(patronSession->getEmail()));
            query.exec();
            patronSession->setEmail(email.toStdString());
        }
    }
    if(password.length() > 0) {
        if(!verifyPassword(password)) {
            return "Request rejected:\nInvalid password submitted.\nLength must be 4 to 20 characters.";
        } else {
            //oppdater passord
            QSqlQuery query;
            query.prepare("UPDATE Patron SET Password = :newPassword WHERE Patron.Email = :currentEmail");
            query.bindValue(":newPassword", password);
            query.bindValue(":currentEmail", QString::fromStdString(patronSession->getEmail()));
            query.exec();
            patronSession->setPassword(password.toStdString());
        }
    }
    if(name.length() > 0) {
        if(!verifyName(name)) {
            return "Request rejected:\nInvalid name submitted.\nFirst letter uppercase. Letters/spaces.";
        } else {
            //oppdater navn
            QSqlQuery query;
            query.prepare("UPDATE Patron SET Name = :newName WHERE Patron.Email = :currentEmail");
            query.bindValue(":newName", name);
            query.bindValue(":currentEmail", QString::fromStdString(patronSession->getEmail()));
            query.exec();
            patronSession->setName(name.toStdString());
        }
    }
    if((email.length() > 0) || (password.length() > 0) || (name.length() > 0)) {
        return "Request accepted!";
    } else {
        return "Request rejected!\nFill at least one field.";
    }
}

string MainWindow::createAdmin(QString email, QString password, QString name) {
    //sjekk om noe finnes i feltet og om input er gyldig
    if(email.length() > 0) {
        if(!verifyEmail(email)) {
            return "Request rejected:\nInvalid email submitted.";
        }
        //hente mailen
        QSqlQuery query;
        query.prepare("SELECT * FROM Patron WHERE Patron.Email = :email;");
        query.bindValue(":email", email);
        query.exec();
        if(query.next()) {
            if(query.value(5).toInt() == 0) {
                //oppdater userlvl
                query.prepare("UPDATE Patron SET Userlvl = 1 WHERE Patron.Email = :email");
                query.bindValue(":email", email);
                query.exec();
                return "Request accepted:\nUser promoted.";
            } else if(query.value(5).toInt() == 2) {
                return "Request rejected:\nRequested to demote master.";
            } else if(patronSession->getUserlvl() == 2){
                query.prepare("UPDATE Patron SET Userlvl = 0 WHERE Patron.Email = :email");
                query.bindValue(":email", email);
                query.exec();
                return "Request accepted:\nAdmin demoted.";
            } else {
            return "Request rejected:\nAlready admin.";
            }
        } else {
            if((password.length() == 0) || (name.length() == 0)) {
                return "Request rejected:\nPassword and name are required\nfor admin creation.";
            } else {
                //validere passord og navn
                if(!verifyPassword(password)) {
                    return "Request rejected:\nInvalid password submitted.";
                } else if(!verifyName(name)) {
                    return "Request rejected:\nInvalid name submitted.";
                }
                //lage ny admin
                query.prepare("INSERT INTO Patron (Name, Email, Password, Userlvl) "
                              "VALUES (:name, :email, :password, 1)");
                query.bindValue(":name", name);
                query.bindValue(":email", email);
                query.bindValue(":password", password);
                query.exec();
                return "Request accepted:\nNew admin created!";
            }
        }
    } else {
        return "Request rejected:\nEmail is required.";
    }
}

string MainWindow::addLibrary(QString name, QString address) {
    //valider input
        if(verifyName(name)) {
            if(verifyName(address)) {
                //Sjekke om navnet finnes
                QSqlQuery query;
                query.prepare("SELECT * FROM Library WHERE Library.Name = :name;");
                query.bindValue(":name", name);
                query.exec();
                if(query.next()) {
                    return "Request rejected:\nName already in use.";
                } else {
                    //lage nytt bibliotek
                    query.prepare("INSERT INTO Library (Name, Address) "
                                  "VALUES (:name, :address)");
                    query.bindValue(":name", name);
                    query.bindValue(":address", address);
                    query.exec();
                    return "Request accepted:\nNew library created!";
                }

            } else {
                return "Request rejected:\nInvalid address.";
            }
        } else {
            return "Request rejected:\nInvalid name.";
        }
}

bool MainWindow::verifyEmail(QString email) {
    regex regexEmail ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    if(!regex_match(email.toStdString(),regexEmail)) {
        return false;
    } else {
        return true;
    }
}

bool MainWindow::verifyPassword(QString password) {
    regex regexPassword ("(^.{4,20}$)");
    if(!regex_match(password.toStdString(),regexPassword)) {
        return false;
    } else {
        return true;
    }
}

bool MainWindow::verifyName(QString name) {
    regex regexName ("(^([A-Z]{1,1})([a-z]{1,10})(([ ]{0,1})([A-Z]{1,1})([a-z]{1,10}))*)");
    if(!regex_match(name.toStdString(),regexName)) {
        return false;
    } else {
        return true;
    }
}
