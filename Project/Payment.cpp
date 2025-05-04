#include "Payment.hpp"

void Cash::pay() {
    std::cout << "Paid with Cash" << std::endl;
}

std::string Cash::getType() {
    return "Cash";
}

void Paypal::pay() {
    std::cout << "Paid with PayPal" << std::endl;
}

std::string Paypal::getType() {
    return "Paypal";
}

void CreditCard::pay() {
    std::cout << "Paid with Credit Card" << std::endl;
}

std::string CreditCard::getType() {
    return "CreditCard";
}

Payment* PaymentFactory::createPayment(const std::string& type) {
    if (type == "Cash") {
        return new Cash();
    } else if (type == "Paypal") {
        return new Paypal();
    } else if (type == "CreditCard") {
        return new CreditCard();
    } else {
        return nullptr;
    }
}
