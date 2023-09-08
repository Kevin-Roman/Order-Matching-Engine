#include "MatchingEngine.h"
#include "OrderData.h"
#include "OrderBook.h"
#include "ConsoleOutput.h"
#include "CSVParser.h"

#include <ctime>
#include <thread>
#include <chrono>

MatchingEngine::MatchingEngine(std::unique_ptr<OrderBook> orderBook, CSVParser *csvParser)
    : m_orderBook(std::move(orderBook)), m_csvParser(csvParser){};

void MatchingEngine::addToQueue(std::unique_ptr<Order> order) {
  m_queue.push_back(std::move(order));
};

void MatchingEngine::match(std::unique_ptr<Order> order) {
  if (order->side() == "buy" && order->price() >= m_orderBook->bestAsk()) {
    matchBuyOrder(std::move(order));
  } else if (order->side() == "sell" && order->price() <= m_orderBook->bestBid()) {
    matchSellOrder(std::move(order));
  } else {
    m_orderBook->add(std::move(order));
  }
}

void MatchingEngine::matchBuyOrder(std::unique_ptr<Order> order) {
  // The total volume filled for the order.
  int filled = 0;
  std::vector<Order *> filledAsks;

  for (auto &ask : m_orderBook->asks()) {
    // Break if the ask price is higher than the buy order or if the buy order is already filled.
    if (ask->price() > order->price() || filled == order->volume()) {
      break;
    }

    if (ask->volume() + filled <= order->volume()) {
      // Ask can be fully filled.
      filled += ask->volume();

      Trade *trade = new Trade(ask->price(), ask->volume());
      m_trades.push_back(trade);

      filledAsks.push_back(&*ask);
    } else if (ask->volume() + filled > order->volume()) {
      // Ask can be partially filled.
      int volume = order->volume() - filled;
      filled += volume;

      Trade *trade = new Trade(ask->price(), volume);
      m_trades.push_back(trade);

      ask->subtractVolume(volume);
    }
  }

  if (filled < order->volume()) {
    // Add remaining volume as a new order.
    m_orderBook->add(std::make_unique<Order>(OrderData(
        time(NULL), 0, "Insert", 0, "buy", order->volume() - filled, order->price(), "")));
  }

  for (auto &ask : filledAsks) {
    m_orderBook->remove(ask);
  }
}

void MatchingEngine::matchSellOrder(std::unique_ptr<Order> order) {
  // The total volume filled for the order.
  int filled = 0;
  std::vector<Order *> filledBids;

  for (auto &bid : m_orderBook->bids()) {
    if (bid->price() < order->price() || filled == order->volume()) {
      // Break if the bid price is lower than the sell order or if the sell order is already filled.
      break;
    }

    if (bid->volume() + filled <= order->volume()) {
      // Bid can be fully filled.
      filled += bid->volume();

      Trade *trade = new Trade(bid->price(), bid->volume());
      m_trades.push_back(trade);

      filledBids.push_back(&*bid);
    } else if (bid->volume() + filled > order->volume()) {
      // Bid can be partially filled.
      int volume = order->volume() - filled;
      filled += volume;

      Trade *trade = new Trade(bid->price(), volume);
      m_trades.push_back(trade);

      bid->subtractVolume(volume);
    }
  }

  if (filled < order->volume()) {
    // Add remaining volume as a new order.
    m_orderBook->add(std::make_unique<Order>(OrderData(
        time(NULL), 0, "Insert", 0, "sell", order->volume() - filled, order->price(), "")));
  }

  for (auto &bid : filledBids) {
    m_orderBook->remove(bid);
  }
}

void MatchingEngine::run() {
  while (true) {
    if (m_queue.size() > 0) {
      match(std::move(m_queue.front()));

      m_queue.pop_front();
    }
  }
};

void MatchingEngine::parseOrders() {
  while (const auto orderData = m_csvParser->nextOrder()) {
    // TODO: implement cancel order by adding ID to orders.
    if (orderData.value().instrument != 0 || orderData.value().operation != "Insert") {
      continue;
    }

    auto order = std::make_unique<Order>(OrderData(
        orderData.value().time,
        0,  // Currently set to instrument 0.
        "Insert",
        0,  // Currently not a unique ID.
        orderData.value().side,
        orderData.value().volume,
        orderData.value().price,
        ""));

    addToQueue(std::move(order));
    // TODO: add order based off currTime + orderData.time
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
};