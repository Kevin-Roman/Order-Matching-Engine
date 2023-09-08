#pragma once

#include "Order.h"

#include <memory>
#include <set>

struct IncreasingPriceComparator {
  bool operator()(
      const std::unique_ptr<Order> &order1, const std::unique_ptr<Order> &order2) const {
    // Time priority if prices are the same.
    if (order1->price() == order2->price()) {
      return order1->time() > order2->time();
    }
    // Price priority.
    return order1->price() < order2->price();
  }
};

struct DecreasingPriceComparator {
  bool operator()(
      const std::unique_ptr<Order> &order1, const std::unique_ptr<Order> &order2) const {
    // Time priority if prices are the same.
    if (order1->price() == order2->price()) {
      return order1->time() > order2->time();
    }
    // Price priority.
    return order1->price() > order2->price();
  }
};

class OrderBook {
 public:
  OrderBook();

  /// @brief  Add an order to the orderbook.
  void add(std::unique_ptr<Order> order);

  /// @brief  Remove an order from the orderbook.
  void remove(Order *order);

  /// @return A refernce to the bids.
  const std::multiset<std::unique_ptr<Order>, DecreasingPriceComparator> &bids() const;

  /// @return A refernce to the asks.
  const std::multiset<std::unique_ptr<Order>, IncreasingPriceComparator> &asks() const;

  /// @return The price of the best bid.
  double bestBid() const;

  /// @return The price of the best ask.
  double bestAsk() const;

 private:
  /// @brief The bids sorted by their price and time.
  std::multiset<std::unique_ptr<Order>, DecreasingPriceComparator> m_bids;

  /// @brief  The asks sorted by their price and time.
  std::multiset<std::unique_ptr<Order>, IncreasingPriceComparator> m_asks;
};