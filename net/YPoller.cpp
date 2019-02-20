#include <LX/net/YPoller.h>
#include <LX/net/YChannel.h>

using namespace YBASE;
using namespace YBASE::net;

Poller::Poller(EventLoop* loop)
{

}

Poller::~Poller()
{

}

bool Poller::hasChannel(Channel* channel) const
{
    assertInLoopThread();
    ChannelMap::const_iterator it = channels_.find(channel->fd());
    return it != channels_.end() && it->second == channel;
}