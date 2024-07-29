//此為使用ChatGPT所得出的答案
#include <iostream>
#include <stack>

using namespace std;

unsigned int Ackerman(unsigned int m, unsigned int n) {
    stack<pair<unsigned int, unsigned int>> s;
    s.push({m, n});              //將m跟n放入堆疊中

    while (!s.empty()) {         //當s堆疊內不為空值則運行while
        pair<unsigned int, unsigned int> top = s.top();         //
        m = top.first;
        n = top.second;
        s.pop();                 //彈出m

        if (m == 0) {
            if (!s.empty()) {
                s.top().second = n + 1;         //m=0,n+1
            } else {
                return n + 1;                   //s堆疊內為空值, (m,n) = (0,0), 則輸出為1
            }
        } else if (n == 0) {
            s.push({m - 1, 1});                 //m!=0, n=0, 則(m-1,1)
        } else {                                //m!=0, n!=0,
            s.push({m - 1, 0});                 //將(m-1,(m,n-1))拆為(m-1,0) 
            s.push({m, n - 1});                 //將(m-1,(m,n-1))拆為(m,n-1)
        }
    }

    return 0;
}

int main() {
    int m, n;                                   //宣告變數以利後續作輸入使用
    while(true){
        cin >> m >> n;                          //輸入數值
        
        cout << Ackerman(m, n) << endl;         //呼叫ack函數計算並輸出
    }

    return 0;
}
//此為使用ChatGPT所得出的答案