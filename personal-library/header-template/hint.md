


##################### number theory ######################""
1. For any int M, we can achieve all int numbers with the same parity as M(M+1)/2 that is <= M(M+1)/2.  \
2. GCD(a1,a2,a3,…,an) = GCD(a1, a1+a2, a1+a2+a3, …, a1+a2+a3+…+an)  \

3. [proof](https://math.stackexchange.com/questions/904519/gcd-and-lcm-from-prime-factorization-proof) \
$ X = p_1 ^ {a_1} p_2 ^ {a_2} \ldots p_k ^ {a_k} \\
  Y = p_1 ^ {b_1} p_2 ^ {b_2} \ldots p_k ^ {b_k}
$

$
\gcd(X, Y) = p_1 ^ {\min(a_1, b_1)} p_2 ^ {\min(a_2, b_2)} \ldots p_k ^ {\min(a_k, b_k)} \\
\text{lcm}(X, Y) = p_1 ^ {\max(a_1, b_1)} p_2 ^ {\max(a_2, b_2)} \ldots p_k ^ {\max(a_k, b_k)}
$



############# bitwise properties

1. ||  ==>  X∣Y ≤ X+Y always. Further, they are equal if and only if X and Y don't have any common bits.

2. ⊕  ==>  XOR is an involution, i.e, X⊕Y=Z ==> X=Z⊕Y.

3. &  ==>  X is submask(meaning any bit set in X will also be set in Y)  of Y ==> X & Y = X  :: => x & y = z, then x & z = z and y & z = z.

4. $x+y = (x\oplus y) + 2\cdot (x\ \&\ y)$ ; Futhermore $\left\lfloor \frac{x\oplus y}{2} \right\rfloor = \left\lfloor \frac{x}{2}\oplus \frac{y}{2}\right\rfloor = \left\lfloor \frac{x}{2}\right\rfloor \oplus \left\lfloor\frac{y}{2}\right\rfloor$

5. given three integers $x, y, z$ such that
$x \lt y \lt z$, we always have $\min(x\oplus y, y\oplus z) \lt x\oplus z$.  This means that given any set of integers, the minimum bitwise XOR between some pair of them will always be obtained by some adjacent pair in sorted order.




########### 2D Matrix

1. Pref Sum:
    Pref[x][y] = A[x][y] + Pref[x-1][y] + Pref[x][y-1] - Pref[x-1][y-1]
    sum[x1][y1] ->[x2][y2] = Pref[x2][y2] - Pref[x1-1][y2] - Pref[x2][y1-1] + Pref[x1-1][y1-1]



###########string############
1. use s += b instead of s = s + b


################################ input <---> output ##############
printf("%.8Lf\n",ans); with ld;     printf("%.8lf\n",ans);  with double



https://codeforces.com/blog/entry/106451

https://github.com/kamyu104/MetaHackerCup-2022
    


https://github.com/kamyu104/MetaHackerCup-2023