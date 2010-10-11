#ifndef Events_h
#define Events_h

#include <vector>
#include <string>
#include <iostream>

class Events {

 public:

  struct Event {
    unsigned long run;
    unsigned long ls;
    unsigned long orbit;
    unsigned bx;
    unsigned long id;

  };

  typedef std::vector<Event>::const_iterator const_iterator;

 public:

  Events(std::string file="");
  ~Events();

  unsigned size(){ return events_.size(); }
  const_iterator begin() { return events_.begin(); }
  const_iterator end() { return events_.end(); }

  unsigned countAfterBXMask(std::vector<bool> mask);

  void print(std::ostream& o);

 private:

  std::vector<Event> events_;

};

#endif
