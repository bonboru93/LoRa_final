#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include <QStringList>
#include <QStringListModel>
#include <QStandardItemModel>
#include <newserver.h>
#include <dbmanager.h>
#include <mapmanager.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

    void to_read_survival_page(uint);

    void to_read_survival_detail(uint);

    void to_read_survival_message(uint);

    void to_fetch_survival_location(float, float);

    void to_send_message(QString);

private slots:

    void on_read_survival_page_finished(QStringList);

    void on_read_survival_detail_finished(QStringList);

    void on_read_survival_message_finished(QStringList);

    void on_fetch_survival_location_finished(QPixmap);

    void on_survivalView_doubleClicked(const QModelIndex &index);

    void on_new_survival_arrived(uint);

    void on_new_message_arrived(uint);

    void on_actionSet_Server_port_triggered();

    void on_actionExit_triggered();

    void on_sendButton_clicked();

    void on_nextButton_clicked();

    void on_lastButton_clicked();

private:
    Ui::MainWindow *ui;

    void startDB_SC();

    void startMM();
};

#endif // MAINWINDOW_H
