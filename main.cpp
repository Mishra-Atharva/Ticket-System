#include <iostream>
#include <fstream>
#include <mutex>

void purchase(std::string& fname, std::string& lname, std::string& dob, std::string& sex)
{
  std::mutex buy_mtx;
  std::unique_lock<std::mutex> buy_lock(buy_mtx);
  std::ofstream Myfile("purchase.txt");
  Myfile << "START" << std::endl;
  Myfile << fname << "\n" << lname << "\n" << dob << "\n" << sex << std::endl; 
  Myfile << "END" << std::endl;
  buy_lock.unlock();
}

std::string refund(std::string& fname, std::string& lname, std::string& dob, std::string& sex)
{
  std::mutex refund_mtx;
  std::unique_lock<std::mutex> refund_lock(refund_mtx);
  std::ifstream Myfile("purchase.txt");
  std::string text;
  std::string successful = "Refund was successful";
  std::string unsuccessful = "Refund couldn't be processed!";
  while(std::getline(Myfile, text))
  {
    if(text == fname)
    {
      std::getline(Myfile, text);
      if(text == lname)
      {
        std::getline(Myfile, text);
        if(text == dob)
        {
          std::getline(Myfile, text);
          if(text == sex)
          {
            return successful;
          }
        }
      }
    }
  }
  refund_lock.unlock();
  return unsuccessful;
}

void homepage()
{
  std::cout << "+---------WELCOME--------+" << std::endl;
  std::cout << "+                        +" << std::endl;
  std::cout << "+  [1]. Buy Ticket       +" << std::endl;
  std::cout << "+  [2]. Refund           +" << std::endl;
  std::cout << "+  [3]. Log-off          +" << std::endl;
  std::cout << "+                        +" << std::endl; 
  std::cout << "+------------------------+" << std::endl;
}

int main()
{
  system("clear");
  std::string fname;
  std::string lname;
  std::string dob;
  std::string sex;
  int choice;

  homepage();
  std::cout << "\n Enter: ";
  std::cin >> choice;
  
  while(choice > 3 || choice < 1)
  {
    system("clear");
    homepage();
    std::cout << "\n Enter: ";
    std::cin >> choice;
  }

  switch(choice)
  {
    case 1:
      system("clear");
      std::cout << "+----------ENTER DETAILS---------+" << std::endl;
      std::cout << "+                                +" << std::endl;
      std::cout << "    First Name: ";
      std::getline(std::cin >> std::ws, fname);
      std::cout << "    Last Name: ";
      std::getline(std::cin >> std::ws, lname);
      std::cout << "    DOB (dd/mm/yy): ";
      std::getline(std::cin >> std::ws, dob);
      std::cout << "    SEX (M/F): ";
      std::cin >> sex;
      std::cout << "+                                +" << std::endl;
      std::cout << "+--------------------------------+" << std::endl;
      purchase(fname, lname, dob, sex);
      break;

    case 2:
      system("clear");
      std::cout << "+----------ENTER DETAILS---------+" << std::endl;
      std::cout << "+                                +" << std::endl;
      std::cout << "    First Name: ";
      std::getline(std::cin >> std::ws, fname);
      std::cout << "    Last Name: ";
      std::getline(std::cin >> std::ws, lname);
      std::cout << "    DOB (dd/mm/yy): ";
      std::getline(std::cin >> std::ws, dob);
      std::cout << "    SEX (M/F): ";
      std::cin >> sex;
      std::cout << "+                                +" << std::endl;
      std::cout << "+--------------------------------+" << std::endl;
      std::cout << refund(fname, lname, dob, sex) << std::endl;
      break;
    
    case 3:
      break;
  }

  std::cout << "Logging off...." << std::endl;

  return 0;
}
