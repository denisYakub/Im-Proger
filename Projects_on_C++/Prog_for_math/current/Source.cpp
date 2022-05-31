#include <iostream>
#include <sstream>
#include <string>

#include "Class.h"

bool isNumberCorrect(const std::string& number)
{
  for (auto i = number.begin(); i != number.end(); i++)
  {
    if (!std::isdigit(*i))
    {
      return false;
    }
  }
  return true;
}

bool correctFormat(std::string& string)
{
  if (!(*(string.begin()) == '\"' && *(string.end() - 1) == '\"'))
  {
    return false;
  }
  string.erase(string.begin());
  string.erase(string.end() - 1);
  auto num = string.begin();
  while (num != string.end())
  {
    if (*num == '\\')
    {
      if ((*(num + 1) == '\\') || (*(num + 1) == '\"'))
      {
        string.erase(num);
        ++num;
      }
      else
      {
        return false;
      }
    }
    else
    {
      ++num;
    }
  }
  return true;
}

void add(std::stringstream& sstream, PhoneBook& book)
{
  std::string number;
  std::string name;
  sstream >> number;
  sstream.ignore();
  std::getline(sstream, name);
  if (number.empty() || name.empty() || !correctFormat(name) || !isNumberCorrect(number) || !sstream.eof())
  {
    std::cout << "<INVALID COMMAND>" << std::endl;
  }
  else
  {
    book.addRecord(std::make_pair(name, number));
  }
}

void store(std::stringstream& sstream, PhoneBook& book)
{
  std::string markname, newmarkname;
  sstream >> markname >> newmarkname;
  if (markname.empty() || newmarkname.empty() || !sstream.eof())
  {
    std::cout << "<INVALID COMMAND>" << std::endl;
    return;
  }
  if (book.changeMark(markname))
  {
    book.addMark(newmarkname);
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>" << std::endl;
  }
}

void insert(std::stringstream& sstream, PhoneBook& book)
{
  std::string insert, markname, number, name;
  sstream >> insert >> markname >> number;
  sstream.ignore();
  std::getline(sstream, name);
  if (insert.empty() || markname.empty() || number.empty() || !isNumberCorrect(number) || name.empty() || !correctFormat(name) || !sstream.eof())
  {
    std::cout << "<INVALID COMMAND>" << std::endl;
    return;
  }
  if (book.changeMark(markname))
  {
    if (insert == "before")
    {
      book.insertBefore(std::make_pair(name, number));
    }
    else if (insert == "after")
    {
      book.insertAfter(std::make_pair(name, number));
    }
    else
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
    }
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>" << std::endl;
  }
}

void deleteMark(std::stringstream& sstream, PhoneBook& book)
{
  std::string markname;
  sstream >> markname;
  if (!sstream.eof() || markname.empty())
  {
    std::cout << "<INVALID COMMAND>" << std::endl;
    return;
  }

  if (book.changeMark(markname))
  {
    book.deleteMark();
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>" << std::endl;
  }
  return;
}

void show(std::stringstream& sstream, PhoneBook& book)
{
  std::string markname;
  sstream >> markname;
  if (!sstream.eof() || markname.empty())
  {
    std::cout << "<INVALID COMMAND>" << std::endl;
    return;
  }
  if (book.changeMark(markname))
  {
    if (book.getSize() == 0)
    {
      std::cout << "<EMPTY>" << std::endl;
      return;
    }
    PhoneBook::record_ rec = book.ShowRecord();
    std::cout << rec.second << " " << rec.first << std::endl;
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>" << std::endl;
  }
  return;
}

void move(std::stringstream& sstream, PhoneBook& book)
{
  std::string markname, step;
  sstream >> markname >> step;
  if (!sstream.eof() || markname.empty() || step.empty())
  {
    std::cout << "<INVALID COMMAND>" << std::endl;
    return;
  }
  if (book.changeMark(markname))
  {
    if (step == "first")
    {
      book.moveToRecord(-book.getSize());
    }
    else if (step == "last")
    {
      book.moveToRecord(book.getSize());
    }
    else
    {
      try
      {
        book.moveToRecord(std::stoi(step));
      }
      catch (std::invalid_argument&)
      {
        std::cout << "<INVALID STEP>" << std::endl;
      }
    }
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>" << std::endl;
  }
  return;
}
