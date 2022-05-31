#include <iostream>
#include <string>
#include <sstream>

#include "Class.h"

PhoneBook::PhoneBook()
{
  marks_.push_back(std::make_pair(records_.begin(), "current"));
  currentMark_ = marks_.begin();
}

void PhoneBook::addRecord(const record_& record)
{
  records_.push_back(record);
  if (records_.size() == 1)
  {
    currentMark_->first = records_.begin();
  }
}

void PhoneBook::addMark(std::string& mark)
{
  mark_ newMark_;
  newMark_.first = currentMark_->first;
  newMark_.second = mark;
  marks_.push_back(newMark_);
}

void PhoneBook::moveToNext()
{
  if (records_.empty())
  {
    throw std::invalid_argument("Records is empty");
  }
  if (std::next(currentMark_->first) != records_.end())
  {
    currentMark_->first = std::next(currentMark_->first);
  }
  else
  {
    throw std::invalid_argument("Iterator on last position");
  }
}

void PhoneBook::moveToPrev()
{
  if (currentMark_->first != records_.begin())
  {
    currentMark_->first = std::prev(currentMark_->first);
  }
  else
  {
    throw std::invalid_argument("Iterator on first position");
  }
}

void PhoneBook::insertBefore(const record_& record)
{
  records_.insert(currentMark_->first, record);
  if (currentMark_->first == records_.end())
  {
    --currentMark_->first;
  }
}

void PhoneBook::insertAfter(const record_& record)
{
  if (currentMark_->first == records_.end())
  {
    records_.push_back(record);
    currentMark_->first--;
  }
  else
  {
    records_.insert(std::next(currentMark_->first), record);
  }
}

void PhoneBook::replace(const record_& record)
{
  if (currentMark_->first == records_.end())
  {
    throw std::invalid_argument("Current in last position");
  }
  *(currentMark_->first) = record;
}

void PhoneBook::moveToRecord(int num)
{
  if (records_.empty())
  {
    throw std::invalid_argument("Records is empty");
  }
  if (((num < 0) && (num < std::distance(currentMark_->first, records_.begin()))))
  {
    currentMark_->first = records_.begin();
    return;
  }
  if ((num > 0) && (num > std::distance(currentMark_->first, std::prev(records_.end()))))
  {
    currentMark_->first = std::prev(records_.end());
    return;
  }
  std::advance(currentMark_->first, num);
}

PhoneBook::record_& PhoneBook::ShowRecord()
{
  if (records_.empty())
  {
    throw std::invalid_argument("Records is empty");
  }
  return *(currentMark_->first);
}

void PhoneBook::deleteMark()
{
  if (records_.empty())
  {
    throw std::invalid_argument("Records is empty");
  }
  Record_ mark = currentMark_->first;
  if (std::next(mark) == records_.end() && records_.size() > 1)
  {
    for (auto&& i : marks_)
    {
      if (i.first == mark)
      {
        i.first--;
      }
    }
  }
  else
  {
    for (auto&& i : marks_)
    {
      if (i.first == mark)
      {
        i.first++;
      }
    }
  }
  records_.erase(mark);
}

int PhoneBook::getSize()
{
  return records_.size();
}

bool PhoneBook::changeMark(std::string& name)
{
  for (auto i = marks_.begin(); i != marks_.end(); i++)
  {
    if (i->second == name)
    {
      currentMark_ = i;
      return true;
    }
  }
  return false;
}
