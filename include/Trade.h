#pragma once

/// @brief An executed trade.
class Trade {
 public:
  Trade(double price, int volume);

 private:
  const double m_price;

  const int m_volume;
};