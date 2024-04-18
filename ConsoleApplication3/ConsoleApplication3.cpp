#include <iostream>
#include <iomanip>
#include <string>
#include <locale>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    // Конструктор
    BankAccount(int accountNumber, double initialBalance) {
        this->accountNumber = accountNumber;
        this->balance = initialBalance;
        this->interestRate = 0.0;
    }

    // Внести средства на счет
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
        else {
            cout << "Неверная сумма для внесения средств." << endl;
        }
    }

    // Снять средства со счета
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
        }
        else {
            cout << "Неверная сумма для снятия средств или недостаточно средств на счете." << endl;
        }
    }

    // Рассчитать и вернуть текущий баланс
    double getBalance() {
        return balance;
    }

    // Рассчитать и вернуть сумму процентов, заработанных на счете
    double getInterest() {
        return balance * interestRate * (1.0 / 12.0);
    }

    // Обновить процентную ставку
    void setInterestRate(double interestRate) {
        if (interestRate >= 0.0) {
            this->interestRate = interestRate;
        }
        else {
            cout << "Неверная процентная ставка." << endl;
        }
    }

    // Получить номер банковского счёта
    int getAccountNumber() {
        return accountNumber;
    }

    // Перевод средств с одного счета на другой
    friend bool transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount);
};

// Перевод средств с одного счета на другой
bool transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount) {
    if (amount > 0 && amount <= fromAccount.getBalance()) {
        fromAccount.withdraw(amount);
        toAccount.deposit(amount);
        return true;
    }
    else {
        cout << "Неверная сумма для перевода или недостаточно средств на счете." << endl;
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Создание объектов банковских счетов
    BankAccount account1(12345, 1000.0);
    BankAccount account2(67890, 500.0);

    // Внесение средств на счет
    account1.deposit(500.0);

    // Снятие средств со счета
    account2.withdraw(200.0);

    // Обновление процентной ставки
    account1.setInterestRate(0.05);
    account2.setInterestRate(0.03);

    // Расчет и вывод текущего баланса и суммы процентов
    cout << "Счет №" << account1.getAccountNumber() << ": Баланс = " << fixed << setprecision(2) << account1.getBalance() << ", Проценты = " << account1.getInterest() << endl;
    cout << "Счет №" << account2.getAccountNumber() << ": Баланс = " << fixed << setprecision(2) << account2.getBalance() << ", Проценты = " << account2.getInterest() << endl;

    // Перевод средств с одного счета на другой
    transfer(account1, account2, 250.0);

    // Расчет и вывод текущего баланса и суммы процентов после перевода
    cout << "Счет №" << account1.getAccountNumber() << ": Баланс = " << fixed << setprecision(2) << account1.getBalance() << ", Проценты = " << account1.getInterest() << endl;
    cout << "Счет №" << account2.getAccountNumber() << ": Баланс = " << fixed << setprecision(2) << account2.getBalance() << ", Проценты = " << account2.getInterest() << endl;

    return 0;
}
