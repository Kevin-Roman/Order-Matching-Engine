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

size_t OrderBook::bidSize() const {
  return m_bids.size();
};

size_t OrderBook::askSize() const {
  return m_asks.size();
};

void OrderBook::add(std::unique_ptr<Order> order) {
  if (order->getDirection() == "buy") {
    // TODO: make sure that order also takes into account the time when the order was added
    m_bids.insert(std::move(order));
  } else if (order->getDirection() == "sell") {
    m_asks.insert(std::move(order));
  }
};

void OrderBook::remove(Order *order) {
  if (order->getDirection() == "buy") {
    m_bids.erase(std::find_if(m_bids.begin(), m_bids.end(), PointerEquality(order)));
  } else if (order->getDirection() == "sell") {
    m_asks.erase(std::find_if(m_bids.begin(), m_bids.end(), PointerEquality(order)));
  }
};

// What's the point of the 2nd const?
const std::multiset<std::unique_ptr<Order>, DecreasingPriceComparator> &OrderBook::getBids() const {
  return m_bids;
};

const std::multiset<std::unique_ptr<Order>, IncreasingPriceComparator> &OrderBook::getAsks() const {
  return m_asks;
};

double OrderBook::bestBid() {
  if (!m_bids.empty()) {
    return (*m_bids.begin())->getPrice();
  }

  return std::numeric_limits<int>::max();
};

double OrderBook::bestAsk() {
  if (!m_bids.empty()) {
    return (*m_bids.begin())->getPrice();
  }

  return std::numeric_limits<int>::min();
};