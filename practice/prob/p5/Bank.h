#include <string>
#include <unordered_map>

using namespace std;

class Bank{
private:
    bool isLogin;
    Account loginAccount;
    unordered_map<string, Account> allAccount;
public:
    void login(string loginID, string loginPassword);
    void create(string newID, string newPassword);
    void deleteAccount(string deleteID, string deletePassword);
    void merge(string ID1, string password1, string ID2, string password2);
};
