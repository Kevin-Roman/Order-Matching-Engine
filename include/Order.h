#pragma once

#include "OrderData.h"

#include <ctime>
#include <string>

/// @brief Class representing an order.
class Order {
 public:
  Order(OrderData orderData);

  void subtractVolume(int volume);

  /// @return The id of the Order.
  int id() const;

  /// @return The side of the Order.
  std::string side() const;

  /// @return The price of the Order.
  double price() const;

  /// @return The volume of the Order.
  int volume() const;

  /// @return The time the Order was received.
  std::time_t time() const;

 private:
  OrderData m_orderData;
};