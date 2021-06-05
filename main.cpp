#include <iostream>
#include <string>
#include "interface.h"  // interface.h includes app.h
using namespace std;

int main()
{
    // Package* testP = new S_Package("A", "B", true, false);
    // std::cout << testP->getInfo() << std::endl;

    App* app = App::GetInstanceOfCompany();
    Interface inter(app);
    inter.open();

    // Hub myhub("MyHub");
    // const Package* pack = new L_Package("A", "B", true, true);
    // myhub += pack;

    // std::cout << myhub.getPackagesNumber() << std::endl;


    // const Package* del_pack =  myhub.getPackages()[0];
    // // std::cout << del_pack->getSenderAddress() << std::endl;

    // std::cout << &del_pack << std::endl;

    // delete del_pack;
    
    // // std::cout << &del_pack << std::endl;
    // // std::cout << del_pack->getSenderAddress() << std::endl;
    // // delete myhub.getPackages()[0];

    // std::cout << myhub.getPackagesNumber() << std::endl;

    // const Package* mypackage = myhub.getPackages()[0];
    // std::cout << mypackage->getSenderAddress();

    // mypackage->setPriority(false);
    // std::cout << mypackage->getPriority();
    // std::cout << "Dziala" << std::endl;

    // int numb = 345;
    // int *ptr = &numb;
    // const std::vector<const int*> v = {ptr};
    // *v[0] = 43;
    // std::cout << *v[0];

    // app.createHub(myhub);
    return 0;
}
