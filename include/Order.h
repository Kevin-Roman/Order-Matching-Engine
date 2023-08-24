#pragma once

#include <string>

class Order {
 public:
  // TODO: use string reference
  Order(
      const std::string orderType,
      const std::string direction,
      const double price,
      const int quantity);

  std::string getDirection() const;
  double getPrice() const;
  int getQuantity() const;
  void subtractQuantity(int quantity);

 private:
  const std::string m_orderType;
  const std::string m_direction;
  const double m_price;
  int m_quantity;
};