#include <iostream>
#include <fstream>

int genTicket()
{
  int ticket_number = rand() % 999999 + 100000;
  std::string tickets;
  std::ifstream Myfile("tickets.txt");
  if(Myfile)
  {
    while(std::getline(Myfile, tickets))
    {
      while(std::to_string(ticket_number) == tickets)
      {
        ticket_number = rand() % 999999 + 100000;
      }
    }
  }
  std::ofstream file("tickets.txt", std::ios_base::app);
  file << ticket_number << std::endl;
  file.close();
  return ticket_number;
}

int getEmail(std::string& email)
{
  std::string info;
  std::ifstream Myfile("customer.txt");
  if(Myfile)
  {
    while(std::getline(Myfile, info))
    {
      if (info == email)
      {
        return 1;
      }
    }
  }
  return 0;
}

int purchase(std::string& email)
{
  bool used = getEmail(email);
  if(!used)
  {
    int ticket_number = genTicket();
    std::ofstream Myfile("customer.txt", std::ios_base::app);
    Myfile << ticket_number << std::endl;
    Myfile << email << std::endl;
    Myfile.close();
    return 0;
  }
  return 1;
}

int verification(int& ticket)
{
  std::string ticket_number = std::to_string(ticket);
  std::string info;
  std::ifstream Myfile("customer.txt");
  while(std::getline(Myfile, info))
  {
    if(info == ticket_number)
    {
      std::getline(Myfile, info);
      std::cout << "Email: " << info << "\nTicket #: " << ticket << std::endl;
      Myfile.close();
      return 0;
    }
  }
  Myfile.close();
  return 1;
}

int main()
{
  srand(static_cast<unsigned int>(time(NULL)));
  system("clear");
  int choice;
  int result;
  std::string email;
  int ticket;
  std::cout << "[1] Buy" << std::endl;
  std::cout << "[2] Verify" << std::endl;
  std::cout << "Select: ";
  std::cin >> choice;
  switch(choice)
  {
    case 1:
      std::cout << "Enter Email: ";
      std::getline(std::cin >> std::ws, email);
      system("clear");
      result = purchase(email);
      if(result == 0)
      {
        std::cout << "Purchase was successful" << std::endl;
      }
      else 
      {
        std::cout << "[!] Error Email already used!" << std::endl;
      }
      break;
    case 2:
      std::cout << "Enter Ticket #: ";
      std::cin >> ticket;
      system("clear");
      result = verification(ticket);
      if(result == 0)
      {
        std::cout << "Ticket is valid!" << std::endl;
        break;
      }
      else 
      {
        std::cout << "Ticket is invalid!" << std::endl;
      }
  }
}
