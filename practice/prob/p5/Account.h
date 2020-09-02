#include <string>
#include <vector> 
#include "Record.h"
using namespace std;

class Account{
private:
    string id;
    string password;
    int money;
    vector<Record> records;
public:
    void deposit(int num);
    void withdraw(int num);
    void transfer(string toID, int num);
    void search(string searchID);
    void find(string wildcardID);
};
