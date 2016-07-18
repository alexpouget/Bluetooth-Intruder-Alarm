#include "mybluetooth.h"


MyBluetooth::MyBluetooth(){

}
void MyBluetooth::scanList(){
    scan();
    std::cout<<"emit signal"<<std::endl;
    emit finishedScan(phoneList);
}

void MyBluetooth::checkAlert(){
    scan();
    std::cout<<"emit signal"<<std::endl;
    emit finishedCheck(phoneList);
}

void MyBluetooth::scan(){
    std::cout<<"bluetooth Mise a jour"<<std::endl;

    phoneList.clear();
    inquiry_info *ii = NULL;
    int dev_id , max_rsp, num_rsp, sock, len, i;
    int flags;
    char name[248] = {0};
    char adr[19] = {0};

    dev_id = hci_get_route(NULL);
    sock = hci_open_dev(dev_id);

    if(dev_id < 0 || sock < 0){
        std::cout<<"erreur socket"<<std::endl;
        return;
    }

    len = 8 ;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;

    ii= (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));

    num_rsp = hci_inquiry(dev_id,len,max_rsp,NULL,&ii,flags);

    if(num_rsp < 0){
        std::cout<<"erreur hci inquiry"<<std::endl;
        return;
    }

    for(i = 0;i < num_rsp;i++){
        ba2str(&(ii+i)->bdaddr,adr);
        memset(name, 0, sizeof(name));
        if(hci_read_remote_name(sock,&(ii+i)->bdaddr,sizeof(name),name,0)<0){
            strcpy( name , "uknown");
        }
        std::cout<<"adresse : "<<adr<<" name : "<<name<<std::endl;
        Phone *phone = new Phone(name,adr);
        phoneList.push_back(phone);
    }


}


