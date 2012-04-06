#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "../src/CProjWriter.h"
#include "../src/CProjReader.h"
#include "../src/CImageComposer.h"

#include <vector>
#include <QDialog>
#include <QMessageBox>
#include <QListView>
#include <QListWidgetItem>
#include <QStringList>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QPixmap>
#include <QStatusBar>
#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<std::string> m_files;
    std::string m_projectfile;
    std::string m_destfile;
    CProjWriter m_writer;

private slots:
    /**
     * @brief Skapar ett nytt tom projekt, kan senare även visa ett föster projekt inställningar.
     */
    void onNewProject();

    /**
     * @brief Lägger till bilder i listan.
     */
    void onAddImages();

    /**
     * @brief Oromatiskt avslut.
     */
    void onExit();
    /**
     * @brief ska kopplas så något händer när man klickar på ett listellement
     * @todo implementera
     */
    void on_listWidget_itemActivated(QListWidgetItem *item);
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionRun_triggered();
    void on_actionOpenProject();
};

#endif // MAINWINDOW_H
