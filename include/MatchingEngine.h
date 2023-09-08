#pragma once

#include <deque>
#include <vector>

#include "Order.h"
#include "Trade.h"
#include "OrderBook.h"
#include "CSVParser.h"

// TODO: Convert this to a derived class of a `MatchingEngine` base class that can be derived for
// different matching algorithms.
/// @brief Class for matching orders.
class MatchingEngine {
 public:
  MatchingEngine(std::unique_ptr<OrderBook> orderBook, CSVParser *csvParser);

  /// @return A queue of the fulfilled trades.
  // std::deque<Trade *> trades();

  void addToQueue(std::unique_ptr<Order> order);

  /// @brief Matches orders based off price and time priority.
  /// @param order The first order in the queue that needs to be filled.
  void match(std::unique_ptr<Order> order);

  /// @brief Matches orders based off price and time priority.
  void matchBuyOrder(std::unique_ptr<Order> order);

  /// @brief Matches orders based off price and time priority.
  void matchSellOrder(std::unique_ptr<Order> order);

  /// @brief Matches the orders in the queue in a loop.
  void run();

  /// @brief Parses the data and retrieves the next order that needs to be filled.
  void parseOrders();

 private:
  /// @brief The fulfilled trades. Currently, there is no need to use this data.
  std::deque<Trade *> m_trades;

  std::unique_ptr<OrderBook> m_orderBook;

  /// @brief The queue of incoming orders.
  std::deque<std::unique_ptr<Order>> m_queue;

  /// @brief The data input parser.
  CSVParser *m_csvParser;
};
