/*
title:programming test for fixpoint
contents:read a log file and chek the accident
argument:1. "n" for timeout judgment
         2. "m" for overload judgment
         3. "t" for overload judgment

author:Hiroki Yamabayashi
since:2022/01/29
*/

#include <stdio.h>
#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <list>
#include <time.h>

#include <bitset>
#include <sstream>
#include <iomanip>

#include "log_structure.h"


// Split the text based on the delimiter of the argument.
std::vector<std::string> split(std::string str, char del) {
    int first = 0;
    int last = str.find_first_of(del);

    std::vector<std::string> result;

    while (first < str.size()) {
        std::string subStr(str, first, last - first);

        result.push_back(subStr);

        first = last + 1;
        last = str.find_first_of(del, first);

        if (last == std::string::npos) {
            last = str.size();
        }
    }

    return result;
}

tm string_to_date(std::string t) {
    time_t result;
    tm date;
    int year, mon, day, hour, min, sec;
    sscanf_s(t.c_str(), "%04d%02d%02d%02d%02d%02d", &year, &mon, &day, &hour, &min, &sec);
    date.tm_sec = sec;
    date.tm_min = min;
    date.tm_hour = hour;
    date.tm_mday = day;
    date.tm_mon = mon-1;
    date.tm_year = year-1900;

    return date;
}

bool judge_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int month_to_day(int month, int year) {
    int day;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        day = 30;
    }
    else if (month == 2)
    {
        if (judge_leap_year(year)) {
            day = 29;
        }
        else {
            day = 28;
        }
    }
    else {
        day = 31;
    }

    return day;
}

void compare_date(std::string a, std::string b) {
    tm date_a = string_to_date(a);
    tm date_b = string_to_date(b);

    double sec_diff = difftime(mktime(&date_b), mktime(&date_a));
    int min_diff = int(sec_diff / 60.0);
    int hour_diff = int(sec_diff / 60.0 / 60.0);

    int mon_diff = -1, year_diff = -1, day_diff = -1;
    int day_begin = date_a.tm_mday, day_end = 0;
    int mon_begin = date_a.tm_mon + 1, mon_end = 12;
    int year_begin = date_a.tm_year + 1900, year_end = date_b.tm_year + 1900;
    int fin = 0;
    for (int y = year_begin; y <=year_end; y++) {
        if (y == year_end)  mon_end = date_b.tm_mon + 1;

        for (int m = mon_begin; m <= mon_end; m++) {
            if (m == mon_begin) day_diff = date_b.tm_mday - date_a.tm_mday;
            else day_diff = date_b.tm_mday;
            mon_diff++;
        }
        year_diff++;
        mon_begin = 1;
    }

    std::cout << year_diff << "/" << mon_diff % 12 << "/" << day_diff << " "
        << hour_diff % 24 << ":" << min_diff % 60 << ":" << int(sec_diff) % 60 << std::endl;
}

std::string toBinary(int n)
{
    int decimal = n;
    int binary = 0;
    int base = 1;

    while (decimal > 0) {
        binary = binary + (decimal % 2) * base;
        decimal = decimal / 2;
        base = base * 10;
    }

    std::ostringstream sout;
    sout << std::setfill('0') << std::setw(8) << std::to_string(binary);
    std::string s = sout.str();

    return s;
}

bool match_network_ipv4(std::string a, std::string b) {
    std::vector<std::string> network_a = split(a, '.');
    std::vector<std::string> network_b = split(b, '.');

    std::vector<std::string> prefix_a = split(network_a[3], '/');
    std::vector<std::string> prefix_b = split(network_b[3], '/');
    if (prefix_a[1] != prefix_b[1])   return false;

    network_a.push_back(network_a[0] + network_a[1] + network_a[2] + prefix_a[0]);
    network_b.push_back(network_b[0] + network_b[1] + network_b[2] + prefix_b[0]);

    std::string bin_a = toBinary(std::stoi(network_a[0])) + toBinary(std::stoi(network_a[1])) + toBinary(std::stoi(network_a[2])) + toBinary(std::stoi(prefix_a[0]));
    std::string bin_b = toBinary(std::stoi(network_b[0])) + toBinary(std::stoi(network_b[1])) + toBinary(std::stoi(network_b[2])) + toBinary(std::stoi(prefix_b[0]));

    int pre_num = std::stoi(prefix_a[1]);
    std::bitset<32> b_a(bin_a);
    std::bitset<32> b_b(bin_b);
    b_a = b_a >> pre_num;
    b_b = b_b >> pre_num;

    std::bitset<32> b_xor = b_a ^ b_b;

    if (b_xor != 0) return false;
    return true;
}




int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << "error >> please write the arguments when you compile this program." << std::endl;
        return -1;
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int t = atoi(argv[3]);

    std::string filename = "network_log.txt";
    std::ifstream ifs(filename);

    if (!ifs)
    {
        std::cout << "error >> failed to open the log file." << std::endl;
        return -1;
    }

    std::string logtext;
    std::list<Log> data;
    std::list<Log> error_server;
    while (getline(ifs, logtext)) {
        std::vector<std::string> split_text = split(logtext, ',');
        if (split_text.size() != 3) {
            std::cout << "error >> log text is wrong : " << logtext << std::endl;
            continue;
        }

        Log log(logtext, split_text[0], split_text[1], split_text[2], 0, 0, 0);

        if (log.get_response() != "-") {
            std::cout << "[Log] " << log.get_logtext() << std::endl;
            for (auto itr = data.rbegin(); itr != data.rend(); ++itr) {
                if ((*itr).get_address() == log.get_address()) {
                    if ((*itr).get_response() == "-")   std::cout << "\t\t(Ý–â2)recovery" << std::endl;
                    if (atoi(log.get_response().c_str()) >= t)  log.set_m((*itr).get_m() + 1);
                     
                    break;
                }
            }
            int count = log.get_m();
            if (count > 0) {
                for (auto itr = data.rbegin(); itr != data.rend(); ++itr) {
                    if ((*itr).get_address() == log.get_address() && count == 0) {
                        if (count == 0) {
                            std::cout << "\t\t(Ý–â3)overload ";
                            compare_date((*itr).get_date(), log.get_date());     // (Ý–â1)
                            break;
                        }
                    }
                    if ((*itr).get_address() == log.get_address())      count -= 1;
                }
            }
        }
        else {
            std::cout << "[Time Out] " << log.get_logtext() << std::endl;
            for (auto itr = data.rbegin(); itr != data.rend(); ++itr) {
                if ((*itr).get_address() == log.get_address()) {
                    if ((*itr).get_response() == "-") {
                        log.set_n((*itr).get_n() + 1);
                    }
                    break;
                }
            }
            int count = log.get_n();

            for (auto itr = data.rbegin(); itr != data.rend(); ++itr) {
                if ((*itr).get_address() == log.get_address() && count == 0) {
                    if (count == 0) {
                        std::cout << "\t(Ý–â1)span ";
                        compare_date((*itr).get_date(), log.get_date());     // (Ý–â1)
                        break;
                    }
                }
                if ((*itr).get_address() == log.get_address())      count -= 1;
            }
            
            if (log.get_n() >= n) {
                std::cout << "\t\t(Ý–â2)network failure" << std::endl;
                int error_count = 0;
                for (auto itr = error_server.rbegin(); itr != error_server.rend(); ++itr) {
                    if (match_network_ipv4((*itr).get_address(), log.get_address())) {
                        error_count++;
                    }
                }
                if (error_count >= n)   std::cout << "\t\t(Ý–â4)There may be a switch failure on this network." << std::endl;
                error_server.push_back(log);
            }
            std::cout << std::endl;

        }

        data.push_back(log);
    }

    return 0;
}
