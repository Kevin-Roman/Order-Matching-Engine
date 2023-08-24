#pragma once

class Trade {
 public:
  Trade(const double price, const int quantity);

 private:
  const double m_price;
  const int m_quantity;
};