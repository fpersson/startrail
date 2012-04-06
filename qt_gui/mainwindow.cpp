#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
#include "../src/CProjWriter.h"

#include <vector>

#include <QListView>
#include <QListWidgetItem>
#include <QStringList>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QPixmap>
*/

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Ready...");
    ui->image->setBackgroundRole(QPalette::Base);
    ui->image->setScaledContents(true);

    QImage img("./test");

    img.scaledToWidth(400);

    if(img.isNull()){
        qDebug() << "Image not found";
    }else{
        qDebug() << "width: " << img.width() << " height: " << img.height();
        ui->image->setPixmap(QPixmap::fromImage(img));
    }
    //connect signal & slots..
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(onExit()));
    connect(ui->actionImport_Images, SIGNAL(triggered()), this, SLOT(onAddImages()));
    connect(ui->actionNew_Project, SIGNAL(triggered()), this, SLOT(onNewProject()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_triggered()));
    connect(ui->actionOpen_Project, SIGNAL(triggered()), this, SLOT(on_actionOpenProject()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewProject(){
    qDebug() << "onNewProject";
}

void MainWindow::onAddImages(){
    qDebug() << "onAddImages";
    QStringList filenames = QFileDialog::getOpenFileNames(this, "Open files", QDir::currentPath(), "jpg (*.jpg);;All files(*.*)");

    QStringList::ConstIterator it;
    for(it = filenames.begin(); it != filenames.end(); ++it){
        //qDebug((*it).toAscii());
        m_files.push_back((*it).toStdString());
        ui->listWidget->addItem((*it));
    }
}

void MainWindow::onExit(){
    qDebug() << "onExit";
    qApp->quit();
}

void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item)
{
    ui->image->setScaledContents(true);
    QImage img(item->text());

    //img.scaledToWidth(400);
    img.scaled(400,400, Qt::KeepAspectRatio, Qt::FastTransformation);

    if(img.isNull()){
        qDebug() << "Image" << item->text() << " not found";
    }else{
        qDebug() << "width: " << img.width() << " height: " << img.height();
        ui->image->setPixmap(QPixmap::fromImage(img));
    }
}

void MainWindow::on_actionSave_triggered(){
    qDebug() << "on_actionSave";
    if(m_files.size() > 0){
        if(m_projectfile == ""){
            qDebug() << "on_actionSave, no filename...";
            m_projectfile = QFileDialog::getSaveFileName(this, "Save As", QDir::currentPath(), "proj (*.proj)").toStdString();
        }
        qDebug() << "on_actionSave, will save to " << m_projectfile.c_str();
        m_writer.Save(m_projectfile, m_destfile, m_files);
    }

}

void MainWindow::on_actionSaveAs_triggered(){
    m_projectfile = QFileDialog::getSaveFileName(this, "Save As", QDir::currentPath(), "proj (*.proj)").toStdString();
    m_writer.Save(m_projectfile, m_destfile, m_files);
}

/**
 * @note ger bara användaren möjligheten att spara projektet under förutsättningen att m_destfile är tom, bugg eller feature?
 * @bug får exceptions om man väljer nej på att spara projektet.
 */
void MainWindow::on_actionRun_triggered(){
    qDebug() << "on_actionRun_triggered";
    if(m_files.size() > 0){
        if(m_destfile == ""){
            m_destfile = QFileDialog::getSaveFileName(this, "Save As", QDir::currentPath(), "jpg (*.jpg)").toStdString();
            QMessageBox::StandardButton replay;
            replay = QMessageBox::question(this, tr("QMessageBox::information()"), "Save your project before continue?", QMessageBox::Yes | QMessageBox::No );
            if(replay == QMessageBox::Yes){
                m_projectfile = QFileDialog::getSaveFileName(this, "Save As", QDir::currentPath(), "proj (*.proj)").toStdString();
                qDebug() << "on_actionRun_triggered, will save to " << m_projectfile.c_str();
                m_writer.Save(m_projectfile, m_destfile, m_files);
            }
        }
        /** @todo fixa till progressbaren så man ser att nått händer, samt skapa en composer tråd så guit inte är låst */
        CImageComposer composer;
        QString msg = QString("Processing %1 files, this might take some time").arg( m_files.size());
        this->statusBar()->showMessage(msg);
        composer.AddImages(m_files);
        composer.Compose(m_destfile);
        this->statusBar()->showMessage("Done...");
    }else{
        /** @todo skriv en dialog som säger att det inte finns nån lista med filer... */
    }
}

void MainWindow::on_actionOpenProject(){
    qDebug() << "on_actionOpenProject";
    QString file = QFileDialog::getOpenFileName(this, "Open project", QDir::currentPath(), "proj (*.proj);;All files(*.*)");
    qDebug() << "Open proj " << file;
    CProjReader reader(file.toStdString());
    m_destfile = reader.getDestFile();
    m_files = reader.GetFiles();

    ui->listWidget->clear();
    std::vector<std::string>::iterator it;
    for(it = m_files.begin(); it < m_files.end(); it++){
        ui->listWidget->addItem(QString::fromStdString(*it));
    }
}
