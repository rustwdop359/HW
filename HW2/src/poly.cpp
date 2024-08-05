// 此為使用ChatGPT所得出的答案
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

class Polynomial;                                                           // forward declaration

class Term {
    friend Polynomial;
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
    friend istream& operator>>(istream& is, Polynomial& poly);
public:
    Term(float c = 0, int e = 0) : coef(c), exp(e) {}                       // 將係數跟次方數初始化
private:
    float coef;                                                             // Coefficient = 係數
    int exp;                                                                // Exponent = 次方數
};

class Polynomial {
public:
    Polynomial();                                                           // Construct the polynomial p(x) = 0
    ~Polynomial();                                                          
    Polynomial Add(const Polynomial& poly) const;                           // Return the sum of the polynomials *this and poly      
    Polynomial Mult(const Polynomial& poly) const;                          // Return the product of the polynomials *this and poly
    float Eval(float f) const;                                              // Evaluate the polynomial *this at f and return the result
    friend ostream& operator<<(ostream& os, const Polynomial& poly);        // Output polynomial
    friend istream& operator>>(istream& is, Polynomial& poly);              // Input polynomial
private:
    Term *termArray;                                                        // Array of nonzero terms
    int capacity;                                                           // size of termArray
    int terms;                                                              // number of nonzero terms
    void resize(int newCapacity);
};

Polynomial::Polynomial() {
    capacity = 1;
    terms = 0;
    termArray = new Term[capacity];
}

Polynomial::~Polynomial() {                                                 // 建立刪除termArray的方法
    delete[] termArray;
}

void Polynomial::resize(int newCapacity) {                                  
    if (newCapacity <= capacity) return;                                    // 當新的儲存空間 < 舊的，不做動作
    Term* newArray = new Term[newCapacity];                                
    for (int i = 0; i < terms; i++) {
        newArray[i] = termArray[i];
    }
    delete[] termArray;
    termArray = newArray;
    capacity = newCapacity;                                                 // 否則建立一個新的termArray(儲存空間需 > 舊的)，將舊的內容移到新的，並且把舊的termArray刪掉
}

Polynomial Polynomial::Add(const Polynomial& poly) const {
    Polynomial result;
    result.resize(max(terms, poly.terms));                                  // 將儲存空間resize成能放進兩個多項式相加
    int i = 0, j = 0, k = 0;                                                // i跟j為指針

    while (i < terms && j < poly.terms) {                                   // 當i跟j小於termArray跟poly.termArray，while開始動作
        if (termArray[i].exp == poly.termArray[j].exp) {                    // 如果termArray的次方數 = poly.termArray的次方數              
            float coefSum = termArray[i].coef + poly.termArray[j].coef;     // termArray的係數與poly.termArray的係數相加
            if (coefSum != 0) {
                result.termArray[k++] = Term(coefSum, termArray[i].exp);    // 如果係數相加不為0則放進termArray[k]裡面
            }
            i++;
            j++;                                                            // i跟j指針往下一項
        } else if (termArray[i].exp > poly.termArray[j].exp) {
            result.termArray[k++] = termArray[i++];                         // 當termArray係數 > poly.termArray的係數，將termArray[i]放進termArray[k]，並且i指針往下一項
        } else {
            result.termArray[k++] = poly.termArray[j++];                    // 當poly.termArray係數 > termArray的係數，將poly.termArray[j]放進termArray[k]，並且j指針往下一項
        }
    }

    // 將剩下的termArray[i]跟poly.termArray[j]放進termArray[k]
    while (i < terms) {
        result.termArray[k++] = termArray[i++];
    }

    while (j < poly.terms) {
        result.termArray[k++] = poly.termArray[j++];
    }

    result.terms = k;                                                       // 將termArray[k]放到result裡
    // 88到90行是讓加完的多項式照項次排列
    sort(result.termArray, result.termArray + result.terms, [](const Term& a, const Term& b) {
        return a.exp > b.exp;
    });

    return result;
}

Polynomial Polynomial::Mult(const Polynomial& poly) const {
    Polynomial result;
    result.resize(terms * poly.terms);                                      // 將儲存空間resize成能放進兩個多項式相乘
    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < poly.terms; j++) {                              // e.g. (a+b) * (c+d) = 先讀ac再讀ad，再讀bc跟bd
            float coefProduct = termArray[i].coef * poly.termArray[j].coef; // 多項式乘法 = 係數相乘
            int expSum = termArray[i].exp + poly.termArray[j].exp;          // 多項式乘法的次方數 = 相加
            bool termFound = false;                                         // 紀錄if是否有找到相同的

            for (int k = 0; k < result.terms; k++) {                        // 找目前的結果裡面有沒有次方相同
                if (result.termArray[k].exp == expSum) {
                    result.termArray[k].coef += coefProduct;                // 如果有就相加
                    termFound = true;                                       // 代表if有執行到
                    break;
                }
            }

            if (!termFound) {                                               // 旗標無變true
                if (result.terms == result.capacity) {                      // 先檢查空間是否足夠
                    result.resize(result.capacity * 2);
                }
                result.termArray[result.terms++] = Term(coefProduct, expSum);   // 將乘法結果放入
            }
        }
    }
    return result;
}

// 輸入值給x，將答案算出來
float Polynomial::Eval(float f) const {
    float result = 0.0;
    for (int i = 0; i < terms; i++) {
        result += termArray[i].coef * pow(f, termArray[i].exp);
    }
    return result;
}

// 將poly.termArray的值回傳給os
ostream& operator<<(ostream& os, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; i++) {
        os << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
        if (i != poly.terms - 1) {
            os << " + ";
        }
    }
    return os;
}

// 接受input並將值傳給ostream
istream& operator>>(istream& is, Polynomial& poly) {
    cout << "Enter number of terms: ";
    is >> poly.terms;
    if (poly.terms > poly.capacity) {                           
        poly.resize(poly.terms);                                          // 如果儲存空間不夠則resize成能放得下input
    }
    for (int i = 0; i < poly.terms; i++) {
        cout << "Enter coefficient and exponent: ";
        is >> poly.termArray[i].coef >> poly.termArray[i].exp;            // 將輸入的值依序放進poly.termArray[i].coef跟poly.termArray[i].exp
    }

    // 156到158行是將乘完的多項式照項次排列
    sort(poly.termArray, poly.termArray + poly.terms, [](const Term& a, const Term& b) {
        return a.exp > b.exp;
    });

    return is;
}

int main() {
    Polynomial p1, p2;                          // 在類別Polynomial創建p1跟p2，讓p1跟p2能使用Polynomial的方法
    cout << "Enter polynomial 1:\n";
    cin >> p1;
    cout << "Enter polynomial 2:\n";
    cin >> p2;
    Polynomial sum = p1.Add(p2);                      // 呼叫類別Polynomial的Add方法，讓p1跟p2相加
    Polynomial product = p1.Mult(p2);                             // 呼叫類別Polynomial的Mult方法，讓p1跟p2相乘
    cout << "Sum: " << sum << endl;
    cout << "Product: " << product << endl;
    float evalPoint;
    cout << "Enter the value to evaluate the polynomials: ";
    cin >> evalPoint;
    cout << "p1(" << evalPoint << ") = " << p1.Eval(evalPoint) << endl;
    cout << "p2(" << evalPoint << ") = " << p2.Eval(evalPoint) << endl;
    cout << "Sum(" << evalPoint << ") = " << sum.Eval(evalPoint) << endl;
    cout << "Product(" << evalPoint << ") = " << product.Eval(evalPoint) << endl;
    return 0;
}
// 此為使用ChatGPT所得出的答案