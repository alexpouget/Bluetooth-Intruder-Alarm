#include "mywindow.h"

using namespace std;


MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setActive(false);

    sirene = new Sirene();
    sirene->moveToThread(&sireneThread);
    sirene->connect(&sireneThread,SIGNAL(MyStart()),SLOT(alerte()));
    sirene->connect(&sireneThread,SIGNAL(MyStop()),SLOT(setFalse()));
    sireneThread.start();

    setFixedSize(750,300);
    scanButton = new QPushButton(tr("scanner"),this);
    connect(scanButton,SIGNAL(released()),this,SLOT (scan()));
    scanButton->setFont(QFont("Times",12,QFont::Bold));
    scanButton->setGeometry(10,10,80,20);
    activeButton = new QPushButton(tr("activer"),this);
    connect(activeButton,SIGNAL(released()),this,SLOT (active()));
    activeButton->setFont(QFont("Times",12,QFont::Bold));
    activeButton->setGeometry(90,10,80,20);
    addButton = new QPushButton(tr("ajouter"),this);
    connect(addButton,SIGNAL(released()),this,SLOT (add()));
    addButton->setFont(QFont("Times",12,QFont::Bold));
    addButton->setGeometry(170,10,80,20);

    label = new QLabel(this);
    label->setText("desactiver");
    label->setGeometry(290,10,80,20);


    codeButton = new QPushButton(tr("code"),this);
    connect(codeButton,SIGNAL(released()),this,SLOT (setCode()));
    codeButton->setFont(QFont("Times",12,QFont::Bold));
    codeButton->setGeometry(370,10,80,20);

    lPeriph = new QLabel(this);
    lPeriph->setText("peripherique accepter");
    lPeriph->setGeometry(560,10,180,20);

    listAll = new QListWidget(this);
    listAll->setGeometry(0,30,450,270);
    listAll->show();

    deleteButton = new QPushButton(tr("delete"),this);
    connect(deleteButton,SIGNAL(released()),this,SLOT (del()));
    deleteButton->setFont(QFont("Times",12,QFont::Bold));
    deleteButton->setGeometry(460,10,90,20);

    listPeriph = new QListWidget(this);
    listPeriph->setGeometry(460,30,290,270);
    listPeriph->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MyWindow::scan(){
    cout<<"scan"<<endl;
    emit updateScan();
}

void MyWindow::active(){

    if(listPeriph->count()>0){
        if(label->text()=="desactiver"){
            scanButton->setEnabled(false);
            deleteButton->setEnabled(false);
            addButton->setEnabled(false);
            codeButton->setEnabled(false);
            label->setText("activer");
            activeButton->setText("desactiver");
            setActive(true);
        }else{
            scanButton->setEnabled(true);
            deleteButton->setEnabled(true);
            addButton->setEnabled(true);
            codeButton->setEnabled(true);
            label->setText("desactiver");
            activeButton->setText("activer");
            setActive(false);
        }
    this->update();
    }else{
        QMessageBox::critical(this,"Pas de peripherique" ,"veuillez ajouter des peripherique de contrôle.",QMessageBox::Cancel);
    }
}
void MyWindow::add(){
    if(listAll->currentItem()!=NULL){
        cout<<listAll->currentItem()->text().toStdString()<<endl;
        listPeriph->addItem(listAll->currentItem()->text());
    }
}

void MyWindow::del(){
    if(listPeriph->currentItem()!=NULL){
        cout<<"delete "<<listPeriph->currentItem()->text().toStdString()<<endl;
        qDeleteAll(listPeriph->selectedItems());
    }
}

void MyWindow::checkAlert(list<Phone*> phoneList){

    if(!getActive()){
        return;
    }
    cout<<"Check Alerte"<<endl;

    for(list<Phone*>::iterator it = phoneList.begin();it != phoneList.end();it++){
        for(int i = 0;i<listPeriph->count();i++){
            if((*it)->getName()==listPeriph->item(i)->text().toStdString()){
                return;
            }
        }
    }
    digitalWrite (27, 0) ;// Off yellow
    digitalWrite (29, 1) ;// On red
    sireneThread.emitStart();
    bool ok;
    QInputDialog* inputDialog = new QInputDialog();
    inputDialog->setOptions(QInputDialog::NoButtons);
    QString code;
    while(code.isEmpty() || !verifCode(code)){
        code = inputDialog->getText(NULL,"Alerte","un intru est detectez entrez le code ou partez",QLineEdit::Normal,"default",&ok);
        while(!ok){
        }
    }

    sireneThread.emitStop();
    digitalWrite (27, 1) ;// Off yellow
    digitalWrite (29, 0) ;// On red
}

void MyWindow::paintEvent(QPaintEvent *e){
    QPainter paint(this);
    if(label->text()=="desactiver"){
        QBrush brush(Qt::green);
        paint.setBrush(brush);
    }else {
        QBrush brush(Qt::red);
        paint.setBrush(brush);
    }

    QRectF rect(260,10,10,10);
    paint.drawEllipse(rect);
    paint.end();
}

void MyWindow::setList(list<Phone*> phoneList){
    cout<<"set list"<<endl;
    listAll->clear();
    for(list<Phone*>::iterator it = phoneList.begin();it != phoneList.end();it++){
        QListWidgetItem item;
        item.setText(QString::fromStdString((*it)->getName()));
        cout<<"ajouter a la liste : "<<(*it)->getName()<<endl;
        listAll->addItem(QString::fromStdString((*it)->getName()));
    }
}

bool MyWindow::verifCode(QString code){
    ifstream fichier("code.txt", ios::in);
    string codeFile;
    if(fichier){

        getline(fichier, codeFile);
        fichier.close();
    }
    if(codeFile!= "" && codeFile == code.toStdString()){
        return true;
    }
    return false;
}

void MyWindow::setCode(){
    bool ok;
    QInputDialog* inputDialog = new QInputDialog();
    inputDialog->setOptions(QInputDialog::NoButtons);
    QString code;
    while(code.isEmpty()){
        code = inputDialog->getText(NULL,"Code","veuillez entrez un code de securité",QLineEdit::Normal,"",&ok);
    }

    ofstream fichier("code.txt", ios::out | ios::trunc);
    if(fichier){

        fichier << code.toStdString()<<endl;
    }

}

void MyWindow::setActive(bool _active){
    activeAlarm = _active;

    if(activeAlarm == false){
        digitalWrite (27, 0) ;// Off

    }else{
        digitalWrite (27, 1) ;// On
    }
}


bool MyWindow::getActive(){
    return activeAlarm;
}





