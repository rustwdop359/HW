#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int powerset(int num){      //宣告powerset函數並設定條件式
    if (num == 0){
        return 1;           //元素為0時只有空集合一個, 因此回傳值為1
    }
    else return 2 * powerset(num-1);    //當n!=0, 回傳(2 * (2 * num - 1))
}

int main() {
    int num;
    while(true){
        cin>>num;           //輸入有幾個元素
        cout<<powerset(num)<<"\n";      //呼叫powerset函數計算並輸出
    }
    return 0;
}