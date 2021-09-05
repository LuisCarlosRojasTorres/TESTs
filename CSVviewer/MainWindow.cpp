#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DlgNewFile.h"

#include <QStandardItemModel>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mModel = new QStandardItemModel(this);
    //The QStandardItemModel class provides a generic model for storing custom data!!

    //Set the tableView with QStandardModel
    ui->tableView->setModel(mModel);

    setCentralWidget(ui->tableView);
    setWindowTitle("CSV viewer");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_File_triggered()
{
    DlgNewFile dlgNewFile(this);
    if(dlgNewFile.exec() == QDialog::Rejected){
        return;
    }

    //get the field variables of DlgNewFile
    const int rowCount = dlgNewFile.getRowCount();
    const int columnCount = dlgNewFile.getColumnCount();

    //create a tableView with rowCount rows and columnCount columns!
    mModel->setRowCount(rowCount);
    mModel->setColumnCount(columnCount);
}


void MainWindow::on_actionOpen_File_triggered()
{
    //Basic: OpenFile
    //auto fileName = QFileDialog::getOpenFileName(this);
    // opens file at source files folder

//    auto fileName = QFileDialog::getOpenFileName(this, "Open new CSV file",
//                                                 QDir::rootPath(), "CSV File (*.csv)");
    auto fileName = QFileDialog::getOpenFileName(this, "Open new CSV file",
                                                 QDir::currentPath(), "CSV File (*.csv)");
    // opens file at C:\ and apply a filter showing CSV files only

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
         //QIODevice::Text When reading, the end-of-line terminators are translated to '\n'.
        return;
    }

    QTextStream qTextStream(&file);
    // QTextStream(FILE *fileHandle, QIODevice::OpenMode
    // QTextStream class provides a convenient interface for reading and writing text


    int currentRow = 0; // This will be current row of the document
    int maxNumOfColumnsInFile = 0;
    while(!qTextStream.atEnd()){
        //While the end is not reached...

        mModel->setRowCount((currentRow));
        //update the number of files in the document

        auto line = qTextStream.readLine();
        // read the next line of the documents and return it as QString

        auto values = line.split(",");
        // convert the line QString into a QStringList of all the values (columns) separated by comma

        const int columnCount = values.size();
        // number of columns equals to the size of values

        if(columnCount > maxNumOfColumnsInFile){
            //If some row has less columns than the previous one, all the values before that row will
            //be lost...
            //for that reason i add maxNumOfColumnsInFle which set the num of columns in the file
            //preventing data lost
            maxNumOfColumnsInFile = columnCount;
            mModel->setColumnCount(columnCount);
        }

        for(int currentColumn = 0; currentColumn < columnCount; ++currentColumn){
            //Set the values of the stringList (which corresponds to each column)
            // in currentRow and currentColumn  position of table mModel
            setValueAt(currentRow, currentColumn, values.at(currentColumn));
        }
        ++currentRow;
    }
    file.close();
}


void MainWindow::on_actionSava_as_csv_triggered()
{
    auto fileName = QFileDialog::getSaveFileName(this, "Save CSV file",
                                                 QDir::rootPath(), "CSV File (*.csv)");

    if(fileName.isEmpty()){ //QString is empty?
        return;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }

    QTextStream qTextStream(&file);

    const int rowCount = mModel->rowCount();
    const int colCount = mModel->columnCount(); //it will get maxNumOfColumns

    //The file is created from a QTextStream object where each element is added through << symbol

    for(int currentRow = 0; currentRow < rowCount; ++currentRow){
        qTextStream << getValueAt(currentRow,0);
        // Added the first element of the row

        for(int currentColumn = 0; currentColumn < colCount; ++currentColumn){
            qTextStream << " , " << getValueAt(currentRow, currentColumn);

        }
        qTextStream << "\n";
    }

    file.flush(); //Flushes any buffered data to the file.
    file.close();

}


void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::setValueAt(int ix, int jx, const QString &value)
{
    if(!mModel->item(ix,jx)){
        mModel->setItem(ix,jx,new QStandardItem(value));
    } else{
        mModel->item(ix,jx)->setText(value);
    }
}

QString MainWindow::getValueAt(int ix, int jx)
{
    if(!mModel->item(ix,jx)){
        return "";
    }
    return mModel->item(ix, jx)->text();
}

