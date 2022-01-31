#pragma once
#include <vector>
#include <string>

class Log {
private:
    std::string logtext;
    std::string date;
    std::string address;
    std::string response;

    int n;
    int m;
    int t;

public:
    Log();
    Log(std::string logtext, std::string date, std::string address, std::string response, int n, int m, int t);
    ~Log();

    void set(std::string logtext, std::string date, std::string address, std::string response, int n, int m, int t);
    
    void set_logtext(std::string logtext);
    void set_date(std::string date);
    void set_address(std::string address);
    void set_response(std::string response);
    void set_n(int n);
    void set_m(int m);
    void set_t(int t);

    std::string get_logtext();
    std::string get_date();
    std::string get_address();
    std::string get_response();
    int get_n();
    int get_m();
    int get_t();
};
