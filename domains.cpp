#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std;

class Domain {
    // разработайте класс домена
public:
    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами
    Domain(const std::string& full_name): domain_(full_name){
        std::reverse(domain_.begin(), domain_.end());
        domain_.push_back('.');
    }

    // разработайте operator==
    bool operator==(const Domain& rhs){
        return domain_ == rhs.domain_;
    }

    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain(const Domain& other) const {
        if (domain_ < other.domain_){
            return false;
        }
        if (!std::equal(other.domain_.begin(), other.domain_.end(), domain_.begin())){
            return false;
        }
        return true;
    }

    std::string GetValue() const {
        return domain_;
    }

private:
    std::string domain_{};
};

std::vector<Domain> ReadDomains(istream& in, size_t lines){
    std::vector<Domain> to_return{};
    for (size_t i = 0; i < lines; ++i){
        std::string to_read;
        std::getline(in, to_read);
        to_return.push_back(Domain(to_read));
    }
    return to_return;
}

class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    template <typename InputIt>
    DomainChecker(InputIt begin, InputIt end): forbidden_(begin, end){
        std::sort(forbidden_.begin(), forbidden_.end(), [](const Domain& lhs, const Domain& rhs){return lhs.GetValue() < rhs.GetValue();});
        auto last = std::unique(forbidden_.begin(), forbidden_.end(), [](const Domain& lhs, const Domain& rhs){return rhs.IsSubdomain(lhs);});
        forbidden_.erase(last, forbidden_.end());
    }

    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
    bool IsForbidden(const Domain& to_check) const {
        auto it = std::upper_bound(forbidden_.begin(), forbidden_.end(), to_check, 
                              [](const Domain& lhs, const Domain& rhs){return lhs.GetValue() < rhs.GetValue();});
        if (it == forbidden_.begin()){
            return false;
        }
        return to_check.IsSubdomain(*(it-1));
    }

private:
    std::vector<Domain> forbidden_;
};



// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

int main() {
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}