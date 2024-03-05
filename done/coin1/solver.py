def testing_fake_one(x,y,n):
    if n==1:
        print(1,"st coin is the fake one")
    else:
            if n % 3==0 or n%3==1:
                A=[coins[i] for i in range(x,x+(y-x)//3 )]
                B=[coins[i] for i in range(x+(y-x)//3,x+2*(y-x)//3)]
                C=[coins[i] for i in range(x+2*(y-x)//3,y)]
                coins_index_A=[i+1 for i in range(x,x+(y-x)//3)]
                coins_index_B=[i+1 for i in range(x+(y-x)//3,x+2*(y-x)//3)]
                coins_index_C=[i+1 for i in range(x+2*(y-x)//3,y)]
                if sum(A)<sum(B):
                    if len(A)>1:
                        testing_fake_one(x,x+(y-x)//3,(y-x)//3)
                    if len(A)==1:
                        return print(coins_index_A[0],"th coin is the fake coin")
                elif sum(A)>sum(B):
                    if len(B)>1:
                        testing_fake_one(x+(y-x)//3,x+2*(y-x)//3,(y-x)//3)
                    if len(B)==1:
                        return print(coins_index_B[0],"th coin is the fake coin")
                else:
                    if len(C)>1:
                        testing_fake_one(x+2*(y-x)//3,y,y-2*(y-x)//3-x)
                    if len(C)==1:
                        return print(coins_index_C[0],"th coin is the fake coin")
            else:
                A=[coins[i] for i in range(x,x+(y-x)//3+1)]
                B=[coins[i] for i in range(x+(y-x)//3+1,x+2*(y-x)//3+1)]
                C=[coins[i] for i in range(x+2*(y-x)//3+1,y)]
                coins_index_A=[i+1 for i in range(x,x+(y-x)//3+1)]
                coins_index_B=[i+1 for i in range(x+(y-x)//3+1,x+2*(y-x)//3+1)]
                coins_index_C=[i+1 for i in range(x+2*(y-x)//3+1,y)]
                if sum(A)<sum(B):
                    if len(A)>1:
                        testing_fake_one(x,x+(y-x)//3+1,(y-x)//3+1)
                    if len(A)==1:
                        return print(coins_index_A[0],"th coin is the fake coin")
                elif sum(A)>sum(B):
                    if len(A)>1:
                        testing_fake_one(x+(y-x)//3+1,x+2*(y-x)//3+1,(y-x)//3)
                    if len(A)==1:
                        return print(coins_index_B[0],"th coin is the fake coin")
                else:
                    if len(A)>1:
                        testing_fake_one(x+2*(y-x)//3+1,y,y-2*(y-x)//3-1-x)
                    if len(A)==1:
                        return print(coins_index_C[0],"th coin is the fake coin")