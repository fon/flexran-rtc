#include <thread>
#include <iostream>

#include <pthread.h>
#include <sched.h>
#include <linux/sched.h>

#include "rt_wrapper.h"

#include "async_xface.h"
#include "progran.pb.h"
#include "rib_updater.h"
#include "rib.h"
#include "task_manager.h"
#include "stats_manager.h"
#include "remote_scheduler.h"
#include "remote_scheduler_delegation.h"
#include "requests_manager.h"

#include <errno.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  async_xface net_xface(2210);

  // Create the rib
  Rib rib;

  // Create the rib update manager
  rib_updater r_updater(net_xface, rib);

  // Create the task manager
  task_manager tm(r_updater);

  // Create the requests manager
  requests_manager rm(net_xface);

  // Register any applications that we might want to execute in the controller
  // Stats manager
  std::shared_ptr<component> stats_app(new stats_manager(rib, rm));
  tm.register_app(stats_app);

  // Remote scheduler
  std::shared_ptr<component> remote_sched(new remote_scheduler(rib, rm));
  tm.register_app(remote_sched);

  // Remote scheduler with delegation (TEST purposes)
  // std::shared_ptr<component> remote_sched(new remote_scheduler_delegation(rib, rm));
  // tm.register_app(remote_sched);
  
  // Start the network thread
  std::thread networkThread(&async_xface::execute_task, &net_xface);

  // Start the task manager thread
  std::thread task_manager_thread(&task_manager::execute_task, &tm);
  
  if (task_manager_thread.joinable())
    task_manager_thread.join();
  
  if (networkThread.joinable())
    networkThread.join();
  
  return 0;
}
