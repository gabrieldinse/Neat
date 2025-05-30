#pragma once

#include <vector>

#include "Neat/Core/Exceptions.hpp"
#include "Neat/Core/Log.hpp"
#include "Neat/Events/EventListener.hpp"

namespace Neat {
class EventManager {
 public:
  using EventsConnectionsVector =
      std::vector<std::shared_ptr<EventToListenersConnection>>;

 public:
  EventManager() = default;
  virtual ~EventManager() = default;

  EventManager(const EventManager &) = delete;
  EventManager &operator=(const EventManager &) = delete;

  template <typename E, typename Listener>
  void addListener(Listener &listener,
                   EventPriority priority = EventPriority::Lowest,
                   bool ignoreIfHandled = false) {
    auto event_connection = getEventConnection<E>();
    auto connection_id = event_connection->template addListener<E>(
        listener, priority, ignoreIfHandled);

    BaseEventListener &base = listener;
    base.m_connectedEvents.insert(std::make_pair(
        Event<E>::getFamily(),
        std::make_pair(
            std::weak_ptr<EventToListenersConnection>(event_connection),
            connection_id)));
  }

  template <typename E, typename Listener>
  void removeListener(Listener &listener) {
    BaseEventListener &base = listener;
    auto family = Event<E>::getFamily();

    if (base.m_connectedEvents.find(family) == base.m_connectedEvents.end())
      throw EventListenerError();

    auto &[event_connection, connection_id] = base.m_connectedEvents[family];

    if (not event_connection.expired())
      event_connection.lock()->removeListener(connection_id);

    base.m_connectedEvents.erase(family);
  }

  template <typename E>
  void generateEvent(const E &event) {
    auto event_connection = getEventConnection<E>();
    event_connection->template publishEvent<E>(event);
  }

  template <typename E>
  void generateEvent(std::unique_ptr<E> event) {
    auto event_connection = getEventConnection<E>();
    event_connection->template publishEvent<E>(event);
  }

  template <typename E, typename... Args>
  void generateEvent(Args &&...args) {
    auto event_connection = getEventConnection<E>();
    event_connection->template publishEvent<E>(std::forward<Args>(args)...);
  }

  std::size_t getNumberOfListeners() const {
    std::size_t count = 0;
    for (auto &event_connection : m_eventsConnections)
      if (event_connection) count += event_connection->size();

    return count;
  }

 private:
  template <typename E>
  std::shared_ptr<EventToListenersConnection> &getEventConnection() {
    auto family = Event<E>::getFamily();

    if (family >= m_eventsConnections.size()) {
      m_eventsConnections.resize(family + 1);
    }

    if (not m_eventsConnections[family]) {
      m_eventsConnections[family] =
          std::make_shared<EventToListenersConnection>();
    }

    return m_eventsConnections[family];
  }

 private:
  EventsConnectionsVector m_eventsConnections;
};

}  // namespace Neat