
#include <iostream>

#include "include/ReactThread.hpp"

int main() {
  gaia::ReactThread react;
  react.MaxTaskCount(1);
  std::cout << "AddTask1" << std::endl;
  react.AddTask([]() { std::cout << "Task1" << std::endl; });
  std::cout << "AddTask2" << std::endl;
  react.AddTask([]() { std::cout << "Task2" << std::endl; });
  std::cout << "AddTask3" << std::endl;
  react.AddTask([]() { std::cout << "Task3" << std::endl; });
  std::cout << "AddTask4" << std::endl;
  react.AddTask([]() { std::cout << "Task4" << std::endl; });
  std::cout << "AddTask5" << std::endl;
  react.AddTask([]() { std::cout << "Task5" << std::endl; });
  std::cout << "AddTask6" << std::endl;
  react.AddTask([]() { std::cout << "Task6" << std::endl; });
  react.Stop();
  react.Join();
}