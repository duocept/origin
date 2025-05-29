#ifndef COUNTER_H
#define COUNTER_H

class Counter {
private:
    int value;

public:
    Counter();
    Counter(int initial);

    void increment();

    void decrement();

    int get_value() const;
};

#endif COUNTER_H