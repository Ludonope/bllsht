#ifndef BLLSHT_BLLSHT_IBROADCASTER_HPP
#define BLLSHT_BLLSHT_IBROADCASTER_HPP

#include "BroadcastPacket.hpp"
#include <string>

namespace bllsht {
namespace broadcast {
}
class IBroadcaster {
public:
  virtual ~IBroadcaster(){};
  virtual void broadcast(broadcast::Packet &) = 0;
  virtual bool fetch(broadcast::Packet &) = 0;
};
} // namespace bllsht

#endif // BLLSHT_BLLSHT_IBROADCASTER_HPP