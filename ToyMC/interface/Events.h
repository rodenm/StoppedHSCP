#ifndef Events_h
#define Events_h

#include <vector>
#include <string>
#include <iostream>

class Events {
 public:

  Events(std::string file="");
  ~Events();

  unsigned countAfterBXMask(std::vector<bool> mask);

  void print(std::ostream& o);

 private:

  struct Event {
    unsigned long run;
    unsigned long ls;
    unsigned long orbit;
    unsigned bx;
    unsigned long id;

  };

  std::vector<Event> events_;

};

#endif
