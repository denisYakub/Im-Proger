#include <string>
#include <vector>
#include <list>

#include "addition.h"

class textConverter
{
public:
  textConverter(const size_t width);

  void read();
  void format();
  void print();

private:
  std::string input_;
  std::vector<token> tokens_;
  const size_t width_;
  std::vector<std::string> formattedText_;

  std::string newString(std::string& str);

  void readWord(std::string::iterator& line);
  void readNumber(std::string::iterator& line);
  void readDash(std::string::iterator& line);
  void readPunctuation(std::string::iterator& line);

  bool isPunctuation(const char c);
  bool isSpace(const char c);
  bool isDash(const std::string::iterator& iter);
};
