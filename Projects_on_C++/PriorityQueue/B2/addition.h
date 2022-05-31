#include <string>
#include <vector>
#include <list>

const std::vector<char> punctuations = { '.', ',', '!', '?', ':', ';' };
const std::vector<char> spaces = { ' ', '\t', '\n' };
const size_t maxWord = 20;
const size_t maxNumber = 20;

enum symbolType
{
  WORD,
  SIGN,
  NUMBER,
  DASH
};

struct token
{
  std::string str;
  symbolType type;
};
