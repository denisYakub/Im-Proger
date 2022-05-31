#include <string>
#include <list>
#include <iterator>

class PhoneBook
{
public:
  typedef std::pair<std::string, std::string> record_;
  typedef std::list<record_>::iterator Record_;
  typedef std::pair<Record_, std::string> mark_;

  PhoneBook();

  void addRecord(const record_& record);
  void addMark(std::string& Markname);

  void moveToNext();
  void moveToPrev();
  void moveToRecord(int num);

  void insertBefore(const record_& record);
  void insertAfter(const record_& record);

  void replace(const record_& record);

  void deleteMark();

  int getSize();
  bool changeMark(std::string& name);
  record_& ShowRecord();

private:
  std::list<record_> records_;
  std::list<mark_>::iterator currentMark_;
  std::list<mark_> marks_;
};
