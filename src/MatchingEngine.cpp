#include "MatchingEngine.h"
#include "OrderBook.h"

MatchingEngine::MatchingEngine(std::unique_ptr<OrderBook> orderBook)
    : m_orderBook(std::move(orderBook)){};

void MatchingEngine::process(std::unique_ptr<Order> order) {
  match(std::move(order));
};

std::deque<Trade *> MatchingEngine::getTrades() {
  return m_trades;
};

void MatchingEngine::match(std::unique_ptr<Order> order) {
  if (order->getDirection() == "buy" && order->getPrice() >= m_orderBook->bestAsk()) {
    int filled = 0;
    std::vector<Order *> consumed_asks;

    for (auto &ask : m_orderBook->getAsks()) {
      if (ask->getPrice() > order->getPrice()) {
        break;
      } else if (filled == order->getQuantity()) {
        break;
      }

      if (filled + ask->getQuantity() <= order->getQuantity()) {
        filled += ask->getQuantity();
        Trade *trade = new Trade(ask->getPrice(), ask->getQuantity());
        m_trades.push_back(trade);
        consumed_asks.push_back(&*ask);
      } else if (filled + ask->getQuantity() > order->getQuantity()) {
        int volume = order->getQuantity() - filled;
        filled += volume;
        Trade *trade = new Trade(ask->getPrice(), volume);
        m_trades.push_back(trade);
        ask->subtractQuantity(volume);
      }
    }

    if (filled < order->getQuantity()) {
      m_orderBook->add(std::make_unique<Order>(
          "limit", "buy", order->getPrice(), order->getQuantity() - filled));
    }

    for (auto &ask : consumed_asks) {
      m_orderBook->remove(ask);
    }
  } else if (order->getDirection() == "sell" and order->getPrice() <= m_orderBook->bestBid()) {
    int filled = 0;
    std::vector<Order *> consumed_bids;

    for (auto &bid : m_orderBook->getBids()) {
      if (bid->getPrice() < order->getPrice()) {
        break;
      }

      if (filled == order->getQuantity()) {
        break;
      }

      if (filled + bid->getQuantity() <= order->getQuantity()) {
        filled += bid->getQuantity();
        Trade *trade = new Trade(bid->getPrice(), bid->getQuantity());
        m_trades.push_back(trade);
        consumed_bids.push_back(&*bid);
      } else if (filled + bid->getQuantity() > order->getQuantity()) {
        int volume = order->getQuantity() - filled;
        filled += volume;
        Trade *trade = new Trade(bid->getPrice(), volume);
        m_trades.push_back(trade);
        bid->subtractQuantity(volume);
      }
    }

    if (filled < order->getQuantity()) {
      m_orderBook->add(std::make_unique<Order>(
          "limit", "sell", order->getPrice(), order->getQuantity() - filled));
    }

    for (auto &bid : consumed_bids) {
      m_orderBook->remove(bid);
    }
  } else {
    m_orderBook->add(std::move(order));
  }
};

void MatchingEngine::run() {
  while (true) {
    if (m_queue.size() > 0) {
      match(std::move(m_queue.front()));

      m_queue.pop_front();
    }
  }
};