#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

static const int MAX_USERS = 100001;
static const int MAX_PAGES = 1000;

class EBook{
public:
    EBook(): users_(MAX_USERS, 0), users_at_page_(MAX_PAGES, 0){}

    void UserRead(int user, int pages){
        if (users_.at(user) == 0){
            ++users_at_page_[0];
        }
        if (pages != 0){
            int old_page = users_.at(user);
            users_[user] = pages;
            ++users_at_page_[pages];
            if (old_page != 0){
                --users_at_page_[old_page];
            }
        } else{
            return;
        }
    }

    double CheerUser(int user){
        if (users_.at(user) == 0){
            return 0;
        }
        if (users_at_page_.at(0) == 1){
            return 1;
        }
        double slower = 0;
        for (int i = 1; i < users_.at(user); ++i){
            slower += users_at_page_.at(i);
        }
        return slower / (users_at_page_.at(0)-1);
    }

private:
    std::vector<int> users_{};
    std::vector<int> users_at_page_;
};


int main(){
    int request_num;
    std::cin >> request_num;
    EBook ebook{};
    for (int i = 0; i < request_num; ++i){
        std::string request_type;
        std::cin >> request_type;
        if (request_type == "READ"){
            int user, pages;
            std::cin >> user >> pages;
            ebook.UserRead(user, pages);
        }
        if (request_type == "CHEER"){
            int user;
            std::cin >> user;
            std:: cout << std::setprecision(6) << ebook.CheerUser(user) << std::endl;
        }
    }
}