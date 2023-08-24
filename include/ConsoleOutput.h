#pragma once

#include "IOutput.h"
#include "OrderBook.h"

#include <iostream>

class ConsoleOutput : public IOutput {
 public:
  ConsoleOutput(const OrderBook& orderBook);

  void displayOrderBook() const override;
};