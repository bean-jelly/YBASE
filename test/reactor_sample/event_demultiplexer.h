#ifndef R_EVENTDE_H
#define R_EVENTDE_H

#include "event.h"
#include "event_handler.h"
#include <map>

class EventDemultiplexer
{
public:
    EventDemultiplexer(){}
    virtual ~EventDemultiplexer() {}
    virtual int wait_event(std::map<Handle, EventHandler*>& handlers, int timeout=0)=0;
    virtual int regist(Handle handle, Event evt)=0;
    virtual int remove(Handle handle)=0;
};

#endif
