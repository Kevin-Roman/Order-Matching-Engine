#pragma once

#include <iostream>

/// @brief The data of an order.
struct OrderData {
  /// @brief The time the order was received.
  std::time_t time;

  /// @brief The instrument. The Ready Trader Go 2023 market data included two instruments (the ETF
  /// and it's Futures)
  int instrument;

  /// @brief The operation such as "Insert" or "Cancel"
  std::string operation;

  /// @brief A unique order ID.
  int orderId;

  /// @brief Bid or Ask which is converted to "buy" or "sell".
  std::string side;

  int volume;

  double price;

  std::string lifespan;
};