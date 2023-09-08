#include "OrderBook.h"
#include "Order.h"

#include <algorithm>
#include <memory>
#include <set>
#include <limits>

struct PointerEquality {
  const Order *m_order;

  explicit PointerEquality(const Order *order) : m_order(order) {
  }

  bool operator()(const std::unique_ptr<Order> &order) const {
    return order.get() == m_order;
  }
};

OrderBook::OrderBook(){};

void OrderBook::add(std::unique_ptr<Order> order) {
  if (order->side() == "buy") {
    m_bids.insert(std::move(order));
  } else if (order->side() == "sell") {
    m_asks.insert(std::move(order));
  }
};

void OrderBook::remove(Order *order) {
  if (order->side() == "buy") {
    m_bids.erase(std::find_if(m_bids.begin(), m_bids.end(), PointerEquality(order)));
  } else if (order->side() == "sell") {
    m_asks.erase(std::find_if(m_asks.begin(), m_asks.end(), PointerEquality(order)));
  }
};

const std::multiset<std::unique_ptr<Order>, DecreasingPriceComparator> &OrderBook::bids() const {
  return m_bids;
};

const std::multiset<std::unique_ptr<Order>, IncreasingPriceComparator> &OrderBook::asks() const {
  return m_asks;
};

double OrderBook::bestBid() const {
  if (!m_bids.empty()) {
    return (*m_bids.begin())->price();
  }

  // return 'infinite' if no bid orders exist.
  return std::numeric_limits<int>::max();
};

double OrderBook::bestAsk() const {
  if (!m_bids.empty()) {
    return (*m_bids.begin())->price();
  }

  // return '-infinite' if no ask orders exist.
  return std::numeric_limits<int>::min();
};