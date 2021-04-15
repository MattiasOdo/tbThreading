#include <iostream> 
#include <thread> 
#include <vector>
#include <string>
#include <mutex>
#include <Windows.h>

using namespace std;

mutex cout_mutex;

void print(int n, const string& str) {
    //this_thread::sleep_for(chrono::seconds(n+0));
    
    //Lås cout med ett unique_lock + mutex (som du själv kan låsa upp när t.ex. cout inte behövs längre)
    
    unique_lock<mutex> unique(cout_mutex);
    cout << str << " ";
    unique.unlock();

    //låsa cout med en lock_guard + mutex, så att enbart en tråd åt gången kommer åt cout
    
    //lock_guard frigör mutex:en när den går 'out-of-scope'
    //lock_guard<mutex> guard(cout_mutex);
    //cout << str << " ";


}

int main() {
    SetConsoleCP(1252); //ÅÄÖ
    SetConsoleOutputCP(1252); //ÅÄÖ

    vector<string> words = { //En vector (array som kan utökas) med olika ord
        "Hej",
        "välkommen",
        "till",
        "theading",
        "koden"
    };

    vector<thread> threads; //En vector med trådar

    //Skapa trådar (lika många som det finns ord i vectorn 'words')
    for (int i = 0; i < words.size(); i++) {
        //varje tråd anropar funktionen 'print' med ett index och ett ord från 'words' som argument
        threads.push_back(thread(print, i, words[i]));
    }

    //huvudtråden ska vänta på att varje respektive tråd ska köras klart (blockerar huvudtråden)
    for (auto& th : threads) {
        th.join();
    }

    return 0; //Här avslutas huvudtråden
}