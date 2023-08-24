#pragma once

#include <deque>
#include <vector>

#include "Order.h"
#include "Trade.h"
#include "OrderBook.h"

class MatchingEngine {
 public:
  MatchingEngine(std::unique_ptr<OrderBook> orderBook);

  void process(std::unique_ptr<Order> order);

  std::deque<Trade *> getTrades();

  void match(std::unique_ptr<Order> order);

  void run();

 private:
  std::unique_ptr<OrderBook> m_orderBook;
  std::deque<std::unique_ptr<Order>> m_queue;
  std::deque<Trade *> m_trades;
};
