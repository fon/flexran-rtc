#ifndef STATS_MANAGER_H_
#define STATS_MANAGER_H_

#include <set>

#include "periodic_component.h"

class stats_manager : public periodic_component {

 public:

 stats_manager(const Rib& rib, const requests_manager& rm)
   : periodic_component(rib, rm), times_executed_(0) {}
  
  void run_periodic_task();

 private:

  std::set<int> agent_list_;
  int times_executed_;
  
};

#endif