#include <iostream>
#include <iomanip>
using namespace std;

struct rational {
    // numerator and denominator
    long long int numer, denom;
};
rational rational_from_int(long long int x) {
    return (rational){x, 1};
};

rational rational_from_frac(long long int numer, long long int denom) {
    return (rational){numer, denom};
}

rational canonical(rational x) {
    // Using Euclidean algo
    bool found = false;
    long long int gcd, a, b;
    if (x.numer < x.denom) {
        a = x.numer;
        b = x.denom;
    } else {
        a = x.denom;
        b = x.numer;
    }
    while (found == false) {
        long long int remainder = b % a;
        if (remainder == 0) {
            gcd = a;
            found = true;
        } else {
            b = a;
            a = remainder;
        }
    }
    return (rational){(x.numer / gcd), (x.denom / gcd)};
}

rational multiply(rational lhs, rational rhs) {
    return canonical((rational){lhs.numer * rhs.numer, lhs.denom * rhs.denom});
}

rational add(rational lhs, rational rhs) {
    return canonical((rational){(lhs.numer * rhs.denom) + (lhs.denom * rhs.numer), lhs.denom * rhs.denom});
}

rational divide(rational lhs, rational rhs) {
    return canonical((rational){lhs.numer * rhs.denom, lhs.denom * rhs.numer});
}

rational subtract(rational lhs, rational rhs) {
    return canonical((rational){(lhs.numer * rhs.denom) - (lhs.denom * rhs.numer), lhs.denom * rhs.denom});
}

bool less_than(rational lhs, rational rhs) {
    return ((lhs.numer * rhs.denom) < (lhs.denom * rhs.numer)) ? true : false;
}

bool more_than(rational lhs, rational rhs) {
    return ((lhs.numer * rhs.denom) > (lhs.denom * rhs.numer)) ? true : false;
}

rational abs_value(rational x) {
    if (x.numer < 0) {
        x.numer = 0 - x.numer;
    }
    if (x.denom < 0) {
        x.denom = 0 - x.denom;
    }
    return x;
}

rational closest(rational x, rational y, rational target) {
    rational diff_x = abs_value(subtract(target, multiply(x,x)));
    rational diff_y = abs_value(subtract(target, multiply(y,y)));
    return less_than(diff_x, diff_y) ? x : y;
};

void print(rational x) {
    cout << x.numer << "/" << x.denom << "\n";
    return;
}

int precision = 0;
bool interval_1;

rational recursive(rational x, rational y, rational target) {
    // print(x);
    // print(y);
    if (precision == 30) {
        if (interval_1 == true) {
            return closest(x, divide(add(x, y), rational_from_int(2)), target);
        } else {
            return closest(divide(add(x, y), rational_from_int(2)), y, target);
        }
    } else {
        rational mid = divide(add(x, y), rational_from_int(2));
        rational mid_sq = multiply(mid, mid);
        rational x_sq = multiply(x, x);
        precision += 1;
        if (less_than(x_sq, target) && more_than(mid_sq, target)) {
            interval_1 = true;
            return recursive(x, mid, target);
        } else {
            interval_1 = false;
            return recursive(mid, y, target);
        }
    }
}

rational sqrt(uint input) {
    if (input == 0 || input < 0) {
        return (rational){0,0};
    } else {
        for (int i = 1; i <= input; i++) {
            int sq = i * i;
            if (sq == input) {
                return (rational)rational_from_int(i);
            } else {
                int sq_peek = (i + 1) * (i + 1);
                if (sq < input && sq_peek > input) {
                    return recursive(
                        rational_from_int(i),
                        rational_from_int(i + 1),
                        rational_from_int(input));
                }
            }
        }
        return (rational){0,0};      
    }  
}

int main() {
    cout << "42 is the answer to the universe!\n";
    rational answer = sqrt(42);
    if (answer.numer == 0 && answer.denom == 0) {
        cout << "Error";
    } else {
        print(answer);
        double answer_decimal = double(answer.numer) / double(answer.denom);
        cout << setprecision(30) << answer_decimal << "\n";
    }
    return 0;
}