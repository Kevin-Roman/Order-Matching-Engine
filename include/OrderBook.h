#pragma once

#include "Order.h"

#include <memory>
#include <set>

struct IncreasingPriceComparator {
  bool operator()(
      const std::unique_ptr<Order> &order1, const std::unique_ptr<Order> &order2) const {
    return order1->getPrice() < order2->getPrice();
  }
};

struct DecreasingPriceComparator {
  bool operator()(
      const std::unique_ptr<Order> &order1, const std::unique_ptr<Order> &order2) const {
    return order1->getPrice() > order2->getPrice();
  }
};

class OrderBook {
 public:
  OrderBook();

  size_t bidSize() const;
  size_t askSize() const;

  void add(std::unique_ptr<Order> order);

  void remove(Order *order);

  void display();

  const std::multiset<std::unique_ptr<Order>, DecreasingPriceComparator> &getBids() const;
  const std::multiset<std::unique_ptr<Order>, IncreasingPriceComparator> &getAsks() const;

  double bestBid();
  double bestAsk();

 private:
  std::multiset<std::unique_ptr<Order>, DecreasingPriceComparator> m_bids;
  std::multiset<std::unique_ptr<Order>, IncreasingPriceComparator> m_asks;
};