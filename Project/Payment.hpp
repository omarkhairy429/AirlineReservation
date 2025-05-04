#ifndef PAYMENT_HPP
#define PAYMENT_HPP

#include <iostream>
#include <string>

class Payment {
public:
    virtual ~Payment() = default;
    virtual void pay() = 0;
    virtual std::string getType() = 0;
};

class Cash : public Payment {
public:
    void pay() override;
    std::string getType() override;
};

class Paypal : public Payment {
public:
    void pay() override;
    std::string getType() override;
};

class CreditCard : public Payment {
public:
    void pay() override;
    std::string getType() override;
};

class PaymentFactory {
public:
    static Payment* createPayment(const std::string& type);
};

#endif // PAYMENT_HPP
