#pragma once

#include <sys/epoll.h>

namespace verona::rt 
{
  class IOThread
  {
    public:
      IOThread() 
      {
        efd = epoll_create1(0);
        assert(efd>0);
      }

      void register_fd(int fd, void *cown, uint32_t events)
      {
        int ret;
        struct epoll_event ev;

        ev.events = events;
        ev.data.ptr = cown;
        ret = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ev);
        assert(!ret);
        std::cout << "Just registered fd" << std::endl;

        active_fds++;
      }

      int active_fds_count()
      {
        return active_fds;
      }

      void loop();
    private:
      int efd;
      int active_fds=0;
      friend class Cown;
  };
}
