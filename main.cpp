#include "DataStream.hpp"
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace uuy::serialize;

class People : public Serializeble
{
public:
    People(const string name, const int age):m_name(name), m_age(age){}
    People(){}
    ~People(){}
    SERIALIZE(m_name, m_age)
    void show()
    {
        std::cout << m_name<<','<<m_age<<std::endl;
    }

public:
    string m_name;
    int m_age;

};

int main()
{
    DataStream ds;
    People p("hjy", 11);
    ds<<p;
    People p2;
    ds>>p2;
    p2.show();

    clock_t start = clock();
    bool b = true;

    ds << b;

    char ch = 'n';
    ds << ch;

    bool bb;
    ds >> bb;
    std::cout << bb << std::endl;

    char chh;
    ds >> chh;
    std::cout << chh << std::endl;

    short s = 3000;
    short ss;
    ds << s;
    ds >> ss;
    std::cout << ss << std::endl;

    int32_t i = -49833;
    int32_t ii;
    ;
    ds << i;
    ds >> ii;
    std::cout << ii << std::endl;

    uint32_t ui = 29432354;
    uint32_t uii;
    ds << ui;
    ds >> uii;
    std::cout << uii << std::endl;

    long long l = 394839243333332;
    long long ll;
    ds << l;
    ds >> ll;
    std::cout << ll << std::endl;

    float f = -3.23;
    float ff;
    ds << f;
    ds >> ff;
    std::cout << ff << std::endl;

    double d = -2.4922;
    double dd;
    ds << d;
    ds >> dd;
    std::cout << dd << std::endl;

    string str = "12433kdsklf\njdaslfjdsalfjo998777777777777vvvvvvvvv\
vvvvvvvvvkhjklghfhgkghjhfaru   kjlbb klfdsfajiosdgfjfdlvjkjjfdsikjfsdjr0pewiurw,=-867221`jhm,.liihhjgfgfbnb\
mmmmmkl//iaewgjskdgkjasl;gjklfjweifjdlajaghfksjalkdslaw9i9923584tjfvlsac,vdjlksdghaiowqo41";
    string strr;
    ds << str;
    ds >> strr;
    std::cout << strr << std::endl;

    std::cout << "vector:" << std::endl;
    std::vector<string> v = {"ajd", "dsla23", "12433kdsklf\njdaslfjdsalfjo998777777777777vvvvvvvvvvvvvvvvvvkhjklghfhgkghjhfaru   kjlbb kl,=-867221`jhm,.liihhjgfgfbnbmmmmmkl//iaewgjskdgkjasl;gjklfjweifjdlajaghfksjalkdslaw9i9923584tjfvlsac,vdjlksdghaiowqo41"};
    ds << v;
    std::vector<string> v2;
    ds >> v2;
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        std::cout << *it << ' ';
    }

    std::cout << "\n";

    std::cout << "list:" << std::endl;
    std::list<string> l1 = {"02003", "239", "21dkds"};
    ds << l1;
    std::list<string> l2;
    ds >> l2;
    for (auto it = l1.begin(); it != l1.end(); ++it)
    {
        std::cout << *it << ' ';
    }

    std::cout << "\n";

    std::cout << "map:" << std::endl;
    std::map<int, std::vector<string>> m1;
    m1[1] = v;
    m1[2] = v2;
    ds << m1;
    std::map<int, std::vector<string>> m2;
    ds >> m2;
    for (auto it = m2.begin(); it != m2.end(); ++it)
    {
        std::cout << it->first << ':';
        for (auto it1 = it->second.begin(); it1 != it->second.end(); ++it1)
        {
            std::cout << *it1 << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "set:" << std::endl;
    std::set<double> s1;
    s1.insert(1.245);
    s1.insert(3234.87);
    s1.insert(32345);
    ds << s1;
    std::set<double> s2;
    ds >> s2;
    for (auto it = s1.begin(); it != s1.end(); ++it)
    {
        std::cout << *it << " ";
    }

    std::cout << "\n";
    clock_t end = clock();
    std::cout << "runTime:" << (double)(end - start) / CLK_TCK;

    return 0;
}