#pragma once

#include "OrderBook.h"

class IOutput {
 public:
  IOutput(const OrderBook& orderBook);

  virtual void displayOrderBook() const = 0;

 protected:
  const OrderBook& m_orderBook;
};