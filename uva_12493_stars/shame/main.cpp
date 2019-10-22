//
//  main.cpp
//  shame
//
//  Created by ernesto alvarado on 22/10/19.
//  Copyright © 2019 ernesto alvarado. All rights reserved.
//

// XXX: https://github.com/marioyc/Online-Judge-Solutions/blob/master/UVA/Contest%20Volumes/12493%20-%20Stars.cpp
#include <cstdio>
using namespace std;
int main(){
    int N;
    while(scanf("%d",&N) == 1){
        int ans = 1;
        for(int i = 2;i <= N / i;++i){
            if(N % i == 0){
                int aux = 1;
                while(N % i == 0){
                    N /= i;
                    aux *= i;
                }
                ans *= aux - aux / i;
            }
        }
        if(N > 1) ans *= N - 1;
        printf("%d\n",(ans + 1) / 2);
    }
    return 0;
}
