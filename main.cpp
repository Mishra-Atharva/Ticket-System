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
  file << ticket_number;
  file.close();
  return ticket_number;
}

int purchase(std::string& email)
{
  int ticket_number = genTicket();
  std::ofstream Myfile("customer.txt", std::ios_base::app);
  Myfile << email << std::endl;
  Myfile << ticket_number << std::endl;
  Myfile.close();
  return 0;
}

int verification(std::string& email)
{
  std::string ticket_number;
  std::string info;
  std::ifstream Myfile("customer.txt");
  while(std::getline(Myfile, info))
  {
    if(info == email)
    {
      std::getline(Myfile, info);
      ticket_number = info;
      std::cout << "Email: " << email << "\nTicket #: " << ticket_number << std::endl;
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
        std::cout << "Purchase was successful check email for ticket" << std::endl;
      }
      else 
      {
        std::cout << "[!] Error..!" << std::endl;
      }
      break;
    case 2:
      std::cout << "Enter Email: ";
      std::getline(std::cin >> std::ws, email);
      system("clear");
      result = verification(email);
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
