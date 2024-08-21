// 此為使用ChatGPT所得出的答案
#include <iostream>
#include <cmath>  
using namespace std;

struct Term {
    float coef;                                                         // Coefficient = 係數
    int exp;                                                            // Exponent = 次方數
    Term* next;
};

class Polynomial {
    friend ostream& operator<<(ostream& os, const Polynomial& p);
    friend istream& operator>>(istream& is, Polynomial& p);

private:
    Term* first;

public:
    Polynomial() {
        first = new Term;                                               // 將first指針指到term
        first->next = first;                                            // 初始化first指回自己
    }

    Polynomial(const Polynomial& B) {
        first = new Term;
        first->next = first;
        *this = B;
    }

    ~Polynomial() {
        Term* p = first->next;
        // 當p不等於第一個index時，p = q，p往下指，把q刪掉，直到p指到first
        while (p != first) {
            Term* q = p;
            p = p->next;
            delete q;
        }
        delete first;
    }

    Polynomial& operator=(const Polynomial& B) {
        if (this == &B) return *this;  
        Term* p = first->next;
        while (p != first) {
            Term* q = p;
            p = p->next;
            delete q;
        }
        first->next = first;
        p = B.first->next;
        while (p != B.first) {
            newTerm(p->coef, p->exp);
            p = p->next;
        }
        return *this;
    }

    Polynomial operator+(const Polynomial& B) const {
        Polynomial result;
        Term* i = first->next;                                              
        Term* j = B.first->next;                                                            // i跟j為指針
        while (i != first && j != B.first) {
            if (i->exp == j->exp) {                                                         // 如果i的次方數 = j的次方數
                result.newTerm(i->coef + j->coef, i->exp);                                  // i的係數與j的係數相加
                i = i->next;
                j = j->next;
            } else if (i->exp > j->exp) {
                result.newTerm(i->coef, i->exp);
                i = i->next;
            } else {
                result.newTerm(j->coef, j->exp);
                j = j->next;
            }
        }
        while (i != first) {
            result.newTerm(i->coef, i->exp);
            i = i->next;                                                                    // 將剩下的i輸出完
        }
        while (j != B.first) {
            result.newTerm(j->coef, j->exp);
            j = j->next;                                                                    // 將剩下的j輸出完
        }
        return result;
    }

    Polynomial operator-(const Polynomial& B) const {
        Polynomial result;
        Term* i = first->next;
        Term* j = B.first->next;
        while (i != first && j != B.first) {
            if (i->exp == j->exp) {                                                          // 如果i的次方數 = j的次方數
                result.newTerm(i->coef - j->coef, i->exp);                                   // i的係數與j的係數相減
                i = i->next;
                j = j->next;
            } else if (i->exp > j->exp) {
                result.newTerm(i->coef, i->exp);
                i = i->next;
            } else {
                result.newTerm(-j->coef, j->exp);
                j = j->next;
            }
        }
        while (i != first) {
            result.newTerm(i->coef, i->exp);
            i = i->next;
        }
        while (j != B.first) {
            result.newTerm(-j->coef, j->exp);
            j = j->next;
        }
        return result;
    }

    Polynomial operator*(const Polynomial& B) const {
        Polynomial result;
        for (Term* i = first->next; i != first; i = i->next) {
            Polynomial temp;
            for (Term* j = B.first->next; j != B.first; j = j->next) {
                temp.newTerm(i->coef * j->coef, i->exp + j->exp);                                           // i跟j的係數相乘，次方數相加
            }
            result = result + temp;
        }
        return result;
    }

    float Evaluate(const float x) const {
        float result = 0.0;
        for (Term* p = first->next; p != first; p = p->next) {
            result += p->coef * pow(x, p->exp);
        }
        return result;
    }

    void newTerm(float coef, int exp) {
        if (coef == 0) return;                                                                              // 係數0則不加入term裡
        Term* p = first;
        Term* q = p->next;
        while (q != first && q->exp > exp) {
            p = q;
            q = q->next;
        }
        if (q != first && q->exp == exp) {
            q->coef += coef;
            if (q->coef == 0) {  
                p->next = q->next;
                delete q;
            }
        } else {
            Term* newTerm = new Term;
            newTerm->coef = coef;
            newTerm->exp = exp;
            newTerm->next = q;
            p->next = newTerm;
        }
    }
};

ostream& operator<<(ostream& os, const Polynomial& p) {
    Term* current = p.first->next;
    while (current != p.first) {                                                        
        if (current != p.first->next && current->coef > 0)
            os << "+";
        os << current->coef << "x^" << current->exp;                            // 將term的多項式結合在一起
        current = current->next;  
    }
    return os;
}

istream& operator>>(istream& is, Polynomial& p) {
    int n;
    is >> n;
    for (int i = 0; i < n; ++i) {                                           // for迴圈創建term
        float c;
        int e;
        is >> c >> e;
        p.newTerm(c, e);
    }
    return is;
}

int main() {
    Polynomial p1, p2, p3;
    cout << "Enter the first polynomial (format: n c1 e1 c2 e2 ...): ";
    cin >> p1;
    cout << "Enter the second polynomial (format: n c1 e1 c2 e2 ...): ";
    cin >> p2;

    p3 = p1 + p2;
    cout << "Sum: " << p3 << endl;

    p3 = p1 - p2;
    cout << "Difference: " << p3 << endl;

    p3 = p1 * p2;
    cout << "Product: " << p3 << endl;

    float x;
    cout << "Enter a value for x: ";
    cin >> x;
    cout << "Evaluation of first polynomial at x = " << x << ": " << p1.Evaluate(x) << endl;

    return 0;
}
// 此為使用ChatGPT所得出的答案
