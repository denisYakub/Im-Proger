#include <iostream>
#include <iterator>
#include <algorithm>

#include "PriorityQueue.hpp"

textConverter::textConverter(const size_t width) :
  input_(),
  tokens_(),
  width_(width)
{}

void textConverter::read()
{
  std::cin >> std::ws;
  while (std::getline(std::cin, input_))
  {
    for (auto iter = input_.begin(); iter != input_.end();)
    {
      if (isalpha(*iter))
      {
        readWord(iter);
      }
      else if (isdigit(*iter))
      {
        readNumber(iter);
      }
      else if (isPunctuation(*iter))
      {
        readPunctuation(iter);
      }
      else if (*iter == '-')
      {
        if (isdigit(*std::next(iter)))
        {
          readNumber(++iter);
        }
        else if (isDash(iter))
        {
          readDash(iter);
        }
        else
        {
          throw std::invalid_argument("Lyphen incorrect position");
        }
      }
      else if (*iter == '+')
      {
        if (isdigit(*(std::next(iter))))
        {
          readNumber(++iter);
        }
      }
      else if (isSpace(*iter))
      {
        ++iter;
      }
      else
      {
        throw std::invalid_argument("Invalid symbol");
      }
    }
  }
}

void textConverter::format()
{
  std::string str;
  for (auto it = tokens_.begin(); it != tokens_.end(); ++it)
  {
    switch (it->type)
    {
    case WORD:
    case NUMBER:
      if (str.size() + it->str.size() + 1 > width_)
      {
        formattedText_.push_back(str);
        str.clear();
      }
      else if (str.size() != 0)
      {
        str += ' ';
      }
      str += it->str;
      break;
    case SIGN:
      if (str.size() + it->str.size() > width_)
      {
        str = newString(str);
      }
      str += it->str;
      break;

    case DASH:
      if (str.size() + it->str.size() + 1 > width_)
      {
        str = newString(str);
      }
      str += ' ';
      str += it->str;
      break;
    }
  }
  if (str.size() != 0)
  {
    formattedText_.push_back(str);
  }
}

void textConverter::print()
{
  for (auto it = formattedText_.begin(); it != formattedText_.end(); ++it)
  {
    std::cout << *it << '\n';
  }
}

std::string textConverter::newString(std::string& str)
{
  std::string result;
  while (str.size() != 0)
  {
    std::string temp;
    size_t i = str.size() - 1;
    for (; !isSpace(str.at(i)); --i)
    {
      temp += str.at(i);
    }
    std::reverse(temp.begin(), temp.end());
    result += temp;
    str.erase(i + 1, temp.size());

    if (isalpha(result.front()) || isdigit(result.front()))
    {
      break;
    }
  }
  formattedText_.push_back(str);
  return result;
}

void textConverter::readWord(std::string::iterator& line)
{
  std::string content;
  auto lastHyphen = input_.begin();

  while (line != input_.end())
  {
    if (isalpha(*line))
    {
      content += *line;
    }
    else if (isSpace(*line) || isPunctuation(*line) || isDash(line))
    {
      if (content.size() > maxWord)
      {
        throw std::invalid_argument("Too long word");
      }
      tokens_.push_back({ content, WORD });
      return;
    }
    else if (*line == '-')
    {

      content += *line;
      if (lastHyphen == std::prev(line) && lastHyphen != input_.begin())
      {
        throw std::invalid_argument("Too many hyphen (word)");
      }
      lastHyphen = line;
    }
    else
    {
      std::cout << "Word: " << content << '\n';
      throw std::invalid_argument("Incorrect input (word)");
    }
    ++line;
  }
  if (content.size() > maxWord)
  {
    throw std::invalid_argument("Too long word");
  }
  tokens_.push_back({ content, WORD });
}

void textConverter::readPunctuation(std::string::iterator& line)
{
  std::string content(1, *line);

  if (tokens_.empty())
  {
    throw std::invalid_argument("First symbol is a sign (sign)");
  }


  while (line != std::prev(input_.end()))
  {
    if (isSpace(*std::next(line)))
    {
      ++line;
    }
    break;
  }

  if (line != std::prev(input_.end()) && !tokens_.empty())
  {
    if (isPunctuation(*std::next(line)) || tokens_.back().type == SIGN)
    {
      throw std::invalid_argument("Two signs in a row aren't allowed");
    }
    else if (isDash(std::next(line)))
    {
      if (content != ",")
      {
        throw std::invalid_argument("Dash after sign isn't allowed");
      }
      else
      {
        content += " ---";
        line += 4;
        tokens_.push_back({ content, SIGN });
        return;
      }
    }
  }
  if (tokens_.size() > 0)
  {
    tokens_.push_back({ content, SIGN });
  }
  else
  {
    throw std::invalid_argument("Invalid input (sign)");
  }
  ++line;
}

void textConverter::readNumber(std::string::iterator& line)
{
  size_t dotCount = 0;
  std::string content;
  if (line != input_.begin())
  {
    if (*std::prev(line) == '+' || *std::prev(line) == '-')
    {
      content += *std::prev(line);
    }
  }

  while (line != input_.end())
  {
    if (isdigit(*line))
    {
      content += *line;
    }
    else if (*line == '.')
    {
      if (dotCount > 1)
      {
        throw std::invalid_argument("Too many delimeters (digit)");
      }
      content += *line;
      ++dotCount;
    }
    else if (isSpace(*line) || isPunctuation(*line))
    {
      if (content.size() > maxNumber)
      {
        throw std::invalid_argument("Too long number");
      }
      tokens_.push_back({ content, NUMBER });
      return;
    }
    else
    {
      throw std::invalid_argument("Incorrect input (digit)");
    }
    ++line;
  }
  if (content.size() > maxNumber)
  {
    throw std::invalid_argument("Too long number");
  }
  tokens_.push_back({ content, NUMBER });
}

void textConverter::readDash(std::string::iterator& line)
{
  line += 2;//скипнуть 2 дефиса
  while (line != std::prev(input_.end()))
  {
    if (isSpace(*std::next(line)))
    {
      ++line;
    }
    break;
  }
  if (line != std::prev(input_.end()))
  {
    if (isPunctuation(*std::next(line)))
    {
      throw std::invalid_argument("Two signs in a row aren't allowed (dash)");
    }
    else if (isDash(std::next(line)))
    {
      throw std::invalid_argument("Dash after sign isn't allowed (dash)");
    }
  }
  if (tokens_.size() == 0)
  {
    throw std::invalid_argument("First symbol is a sign (dash)");
  }
  else if (tokens_.back().str == ",")
  {
    tokens_.pop_back();
    tokens_.push_back({ ", ---", SIGN });
    ++line;
    return;
  }
  else if (tokens_.back().type == DASH)
  {
    throw std::invalid_argument("Dash after dash isn't allowed (dash)");
  }
  tokens_.push_back({ "---", DASH });
  ++line;
}

bool textConverter::isPunctuation(const char chr)
{
  for (auto i = punctuations.begin(); i != punctuations.end(); ++i)
  {
    if (chr == *i)
    {
      return true;
    }
  }
  return false;
}

bool textConverter::isSpace(const char chr)
{
  for (auto i = spaces.begin(); i != spaces.end(); ++i)
  {
    if (chr == *i)
    {
      return true;
    }
  }
  return false;
}

bool textConverter::isDash(const std::string::iterator& line)
{
  if (line != input_.end() && std::next(line) != input_.end() && std::next(std::next(line)) != input_.end())
  {
    return (*line == '-' && *(std::next(line)) == '-' && *(std::next(std::next(line))) == '-');
  }
  return false;
}

