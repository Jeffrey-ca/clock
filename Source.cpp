#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

using namespace std;

#pragma warning(disable : 4996)
string
get_system_time() { // https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
  return ss.str();
}

int menu() {
  int choice;
  cout << " 0 - Refresh Time" << endl;
  cout << " 1 - Add One Hour" << endl;
  cout << " 2 - Add One Minute" << endl;
  cout << " 3 - Add One Second" << endl;
  cout << " 4 - Exit" << endl;
  cin >> choice;
  return choice;
}

void display12hr(int hours = 0, int minutes = 0, int seconds = 0) {
  string str;
  string time_12 = get_system_time();
  time_12 = time_12.substr(11, 8);

  int semi = time_12.find(':');
  string hour_num = time_12.substr(0, semi);
  int num = stoi(hour_num) + hours;
  if (num >= 12) {
    num = num % 12;
  }
  if (num > 12) {
    num = num - 12;
  }
  if (num < 10) {
    str = '0' + to_string(num);
    if (str == "00") {
      str = "12";
    }
  } else {
    str = to_string(num);
  }
  time_12.replace(0, semi, str);

  int semi_2 = time_12.find(':', 3);
  string temp_num = time_12.substr(semi + 1, semi_2 - 3);
  int num_2 = stoi(temp_num) + minutes;
  if (num_2 >= 60) {
    num_2 = num_2 % 60;
  }
  if (num_2 < 10) {
    str = "0" + std::to_string(num_2);
  } else {
    str = std::to_string(num_2);
  }
  time_12.replace(semi + 1, semi_2 - 3, str);

  string temp_num2 = time_12.substr(semi_2 + 1, time_12.size());
  int num_3 = stoi(temp_num2) + seconds;
  if (num_3 >= 60) {
    num_3 = num_3 % 60;
  }
  if (num_3 < 10) {
    str = "0" + std::to_string(num_3);
  } else {
    str = std::to_string(num_3);
  }
  time_12.replace(semi_2 + 1, time_12.size(), str);

  cout << "12 Hour Clock: " << time_12 << endl;
}

void display24hr(int hours = 0, int minutes = 0, int seconds = 0) {
  string time_24 = get_system_time();
  string str;

  time_24 = time_24.substr(11, 8);

  int semi = time_24.find(':');
  string hour_num = time_24.substr(0, semi);
  int num = stoi(hour_num) + hours;
  if (num >= 24) {
    num = num % 24;
  }
  if (num < 10) {
    str = "0" + std::to_string(num);
  } else {
    str = std::to_string(num);
  }
  time_24.replace(0, semi, str);

  int semi_2 = time_24.find(':', 3);
  string temp_num = time_24.substr(semi + 1, semi_2 - 3);
  int num_2 = stoi(temp_num) + minutes;
  if (num_2 >= 60) {
    num_2 = num_2 % 60;
  }
  if (num_2 < 10) {
    str = "0" + std::to_string(num_2);
  } else {
    str = std::to_string(num_2);
  }
  time_24.replace(semi + 1, semi_2 - 3, str);

  string temp_num2 = time_24.substr(semi_2 + 1, time_24.size() - 1);
  int num_3 = stoi(temp_num2) + seconds;
  if (num_3 >= 60) {
    num_3 = num_3 % 60;
  }
  if (num_3 < 10) {
    str = "0" + std::to_string(num_3);
  } else {
    str = std::to_string(num_3);
  }
  time_24.replace(semi_2 + 1, time_24.size() - 1, str);

  cout << "24 Hour Clock: " << time_24 << endl;
}

#pragma warning(disable : 4996)
int main() {
  int choice = 0;
  int added_hours = 0;
  int added_minutes = 0;
  int added_seconds = 0;

  while (choice != 4) {
    system("CLS");
    display12hr(added_hours, added_minutes, added_seconds);
    display24hr(added_hours, added_minutes, added_seconds);
    choice = menu();
    if (choice == 1) {
      added_hours++;
    } else if (choice == 2) {
      added_minutes++;
    } else if (choice == 3) {
      added_seconds++;
    }
  }
}
