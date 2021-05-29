#include <iostream>
using namespace std;

int flag = 0;
int SecuritySystemTest(int smoke,int motion,int door,int camera,int alarm,int ValidPassword,int UserConfirmation)
{
    if(smoke==1 && motion==1)
    {
            if(door==1)
                cout << "error code:01(1)" << endl;
            if(alarm==0)
                cout << "error code:02(1)" << endl;
            if(camera==0)
                cout << "error code:03(1)" << endl;
            else
                flag++;
    }
    else if(smoke==1 && motion==0)
    {
        if(door==1)
            cout << "error code:01(2)" << endl;
        if(alarm==0)
            cout << "error code:02(2)" << endl;
        if(camera==1)
            cout << "error code:03(2)" << endl;
        else
            flag++;
    }
    else if(smoke==0 && motion==0)
    {
        if(door==0)
            cout << "error code:01(3)" << endl;
        if(alarm==1)
            cout << "error code:02(3)" << endl;
        if(camera==1)
            cout << "error code:03(3)" << endl;
        else
            flag++;
    }
    else if(smoke==0 && motion==1)
    {
        if(ValidPassword==1)
        {
            if(door==1)
                cout << "error code:01(4)" << endl;
            if(alarm==1)
                cout << "error code:02(4)" << endl;
            if(camera==0)
                cout << "error code:03(4)" << endl;
        }
        else
        {
            if(UserConfirmation==1)
            {
                if(door==1)
                    cout << "error code:01(5)" << endl;
                if(alarm==1)
                    cout << "error code:02(5)" << endl;
                if(camera==0)
                    cout << "error code:03(5)" << endl;
            }
            else
            {
                if(door==0)
                    cout << "error code:01(6)" << endl;
                if(alarm==0)
                    cout << "error code:02(6)" << endl;
                if(camera==0)
                    cout << "error code:03(6)" << endl;
            }
        }
    }

    if(flag > 0)
        cout << "Status: pass" << endl;
    //cout << flag << endl;
    //cout << smoke << motion << door << camera << alarm << ValidPassword << UserConfirmation << endl;
    return 0;
}