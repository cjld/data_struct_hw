# Palindrome

## 题目大意
求X在那些进制下是回文数，X<1e10

## 解法
对于 2~sqrt(n) 进制暴力枚举， 对于大于sqrt(n)进制，数字不会超过两位，又因为是回文数 aa,故 a*x+a=n x=n/a-1,我们枚举 a 即可

## 复杂度
O(sqrt(n))