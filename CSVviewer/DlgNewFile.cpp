#include "DlgNewFile.h"
#include "ui_DlgNewFile.h"

DlgNewFile::DlgNewFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgNewFile)
{
    ui->setupUi(this);
    setWindowTitle("NewFile");
}

DlgNewFile::~DlgNewFile()
{
    delete ui;
}

int DlgNewFile::getRowCount() const
{
    return ui->sB_numOfRows->value();
}

int DlgNewFile::getColumnCount() const
{
    return ui->sB_numOfColumns->value();
}

void DlgNewFile::on_buttonBox_accepted()
{
    accept();
}


void DlgNewFile::on_buttonBox_rejected()
{
    reject();
}

