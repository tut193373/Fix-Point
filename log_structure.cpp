#include "log_structure.h"

Log::Log() {
    this->logtext.clear();
    this->date.clear();
    this->address.clear();
    this->response.clear();
    this->n = 0;
    this->m = 0;
    this->t = 0;
}

Log::Log(std::string logtext, std::string date, std::string address, std::string response, int n, int m, int t) {
    this->logtext = logtext;
    this->date = date;
    this->address = address;
    this->response = response;
    this->n = n;
    this->m = m;
    this->t = t;
}

Log::~Log() {
}


// set method
void Log::set(std::string logtext, std::string date, std::string address, std::string response, int n, int m, int t) {
    this->logtext = logtext;
    this->date = date;
    this->address = address;
    this->response = response;
    this->n = n;
    this->m = m;
    this->t = t;
}

void Log::set_logtext(std::string logtext) {
    this->logtext = logtext;
}
void Log::set_date(std::string date) {
    this->date = date;
}
void Log::set_address(std::string address){
    this->address = address;
}
void Log::set_response(std::string response){
    this->response = response;
}
void Log::set_n(int n){
    this->n = n;
}
void Log::set_m(int m){
    this->m = m;
}
void Log::set_t(int t){
    this->t = t;
}


// get method
std::string Log::get_logtext(){
    return this->logtext;
}

std::string Log::get_date() {
    return this->date;
}

std::string Log::get_address() {
    return this->address;
}

std::string Log::get_response() {
    return this->response;
}

int Log::get_n() {
    return this->n;
}

int Log::get_m() {
    return this->m;
}

int Log::get_t() {
    return this->t;
}