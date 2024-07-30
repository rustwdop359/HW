#include <iostream>
#include <string>
using namespace std;

int ack(int m,int n){        //宣告ack函數並設定條件式   
    while(true){
        if(m == 0){          
        return n+1;          //m=0, 回傳n+1
    }
    else if(m>0 && n==0) {   
        return ack(m-1,1);   //m>0且n=0, 回傳(m-1,1)
    }
    else if(m>0 && n>0){     
        return ack(m-1,ack(m,n-1));     //m>0且n>0, 回傳(m-1,ack(m,n-1)
    }
}
}

int main() {

    int m,n;                 //宣告變數以利後續作輸入使用   
    
    
    while (true) {
        cin>>m>>n;              //輸入數值
        cout << ack(m,n) << "\n";    //呼叫ack函數計算並輸出
    }
    return 0;

}