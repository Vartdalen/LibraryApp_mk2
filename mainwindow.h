#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "objects.h"

#include <iostream>
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <regex>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loginBtn_clicked();
    void on_createNewUserBtn_clicked();

    void on_createNewUserConfrimBtn_clicked();
    void on_createNewUserBackBtn_clicked();

    void on_menyPageMyProfileBtn_clicked();
    void on_menyPageFindBtn_clicked();
    void on_menyPageLogoutBtn_clicked();

    void on_myProfilePageChangeInfoBtn_clicked();
    void on_myProfilePageBackBtn_clicked();

    void on_changeUserInfoConfirmBtn_clicked();
    void on_changeUserDataBackBtn_clicked();

    void on_findBookPageSearchBtn_clicked();
    void on_findBookPageChooseBtn_clicked();
    void on_findBookPageDiscoveryBtn_clicked();
    void on_findBookPageConfirmBtn_clicked();
    void on_findBookPageBackBtn_clicked();

    void on_discoveryPageConfirmBtn_clicked();
    void on_discoveryPageBackBtn_clicked();

    void on_showLibraryConfirmBtn_clicked();
    void on_showLibraryBackBtn_clicked();

    void on_checkoutPageAddBtn_clicked();
    void on_checkoutPageCheckoutBtn_clicked();
    void on_checkoutPageCancelBtn_clicked();

    void on_adminFunctionPageNewAdminBtn_clicked();
    void on_adminFunctionPageLibraryBtn_clicked();
    void on_adminFunctionPageBookBtn_clicked();
    void on_adminFunctionPageRemoveBookBtn_clicked();
    void on_adminFunctionPageBackBtn_clicked();

    void on_removeBookPageBackBtn_clicked();
    void on_removeBookPageRemoveBtn_clicked();

    void on_adminPageFindBtn_2_clicked();
    void on_adminPageMyProfileBtn_2_clicked();
    void on_adminPageFunctionBtn_clicked();
    void on_adminPageLogoutBtn_2_clicked();

    void on_adminPageConfirmBtn_clicked();
    void on_adminPageBackBtn_clicked();

    void on_addBookPageBackBtn_clicked();
    void on_addLibraryBackBtn_clicked();

    void on_confirmationPageBackBtn_clicked();

    void on_addLibraryAddBtn_clicked();

private:
    Ui::MainWindow *ui;
    bool dbConnect(QSqlDatabase db);
    bool verifyLogin(QString email, QString password);
    string createUser(QString email, QString password, QString name);
    string changeUser(QString email, QString password, QString name);
    string createAdmin(QString email, QString password, QString name);
    string addLibrary(QString name, QString address);
    bool verifyEmail(QString email);
    bool verifyPassword(QString password);
    bool verifyName(QString name);
};

#endif // MAINWINDOW_H
