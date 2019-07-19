# 1. A Tutorial Introduction
## 1.1. Getting Started
```c
#include <stdio.h>
int main(){
  printf("hello, world\n");
}
```
함수의 이름은 원하는 대로 붙일 수 있지만 메인 프로그램의 이름은 꼭 `main`으로 해주어야 한다. `main`은 대개 다른 함수들을 호출하게 되는데 같은 프로그램 내에 있는 함수를 호출할 수도 있고, 라이브러리에 있는 함수를 호출할 수도 있다. 라이브러리는 여러 개가 있는데 그중에서 우리가 사용하고자 하는 함수가 어떤 라이브러리에 있는지 프로그램에 명시해주어야 한다. 위 프로그램에서 사용한 함수는 `printf`이며 이 함수는 `stdio`(stands for **st**andard **i**nput **o**utput, 표준입출력라이브러리)에 들어있다. 따라서 프로그램의 맨 첫줄에
```c
#include <stdio.h>
```
가 있는 것이다.

매개변수는 함수이름 바로 뒤에 오는 괄호 속에 써준다. 예제의 함수에는 매개변수를 넣어주지 않았다. 매개변수가 없더라도 괄호는 꼭 있어야한다.

중괄호는 문장들을 묶어서 하나의 덩어리로 만들어 주는 역할을 한다. 위의 예제에서는 {}가 main함수의 바디라는 것을 나타낸다.

함수를 호출할 때는 함수의 이름과 매개변수만 써 주면 된다.
```c
  printf("hello, world\n");
```
이 문장은 `printf`라는 이름의 함수를 호출하고 매개변수로 `"hello, world\n"`를 전달하고 있다.

""는 인용부호로 이 부호 안에 있는 문자들은 `character string` 또는 `string constant`라고 불리운다. 

다시 예제를 해석하면
```c
#include <stdio.h>
// stdio 라이브러리 사용
int main()
// main 함수 정의. 매개변수는 없는 상태다.
{
// main 함수 시작
  printf("hello, world\n");
  //string 출력을 위해 printf함수 호출
}
// main 함수 종료
```
로 정리할 수 있다.

`\n`은 하나의 문자이다. 이러한 문자를 escape 문자라고 한다. 출력의 양식을 정해준다.
### escape 문자
`\n` | `\t` | `\b` | `\\`
-----|------|------|-----
new line(return이라고도 한다)|tab|backspace| \

## 1.2. Fahrenheit-Celsius table
```c
#include <stdio.h>
/*
  print Fahrenheit-celsius table
  for fahr = 0, 20, ..., 300
*/
int main(){
  int fahr, celsius;
  int lower, upper, step;
  lower = 0; /* lower limit of temperature table */
  upper = 300; /* upper limit of temperature table */
  step = 20; /* step size */
  fahr = lower;
  while(fahr <= upper){
    celsius = 5 * (fahr-32)/9;
    printf("%d\t%d\n",fahr,celsius);
    fahr = fahr + step;
  }
}
```
/* */ 사이의 문장은 comment로 프로그램 실행에 아무런 영향을 미치지 않는다. 

**주의:** C에서는 모든 변수는 사용되기 전에 선언해 주어야 한다. 위의 프로그램에서는 총 5개의 변수가 쓰였다.

`int`는 변수의 `data-type`이 정수형이라는 것을 의미하고 뒤의 `fahr`, `celsius`는 변수 이름이다. 

실수형 변수에는 `float`이 있는데 부동소수점(floating-point)을 의미한다. 그 외의 기본 `data-type`에는 다음과 같은 것들이 있다

type | descriptio
-----|-----------
char | 문자형 1바이트
short | 단정도 정수형
long | 배정도 정수형
double | 배정도 부동소수점

그 다음은 각 변수의 초기값을 지정해주는 영역이 있다.

같은 방법을 여러번 실행하는 것은 `while`문을 통해 할 수 있다. 뒤의 괄호 속의 조건이 만족되는 동안만 반복 수행한다는 의미다.

while뒤에는 중괄호가 오는데 한문장만이 쓰인다면 중괄호를 생략해도 상관없다.
```c
while (i<j)
  i=2*i;
```

그리고 `main`과 `while`문 안의 문장들은 들여쓰기(indentation)되어 있는데 이는 프로그램의 구조를 알기 쉽게 하기 위해 쓴 것이며 몇칸이냐는 상관없다. 

수학적으로
```c
  celsius = 5 * (fahr-32)/9;  
```
와
```c
  celsius = (5/9) * (fahr-32);
```
는 같지만 C에서는 정수형 데이터의 계산 결과는 무조건 정수가 되어야 하므로 `5/9`가 `0`이 되어버려 `celsius`의 값은 항상 `0`이 되버린다.

```c
    printf("%d\t%d\n",fahr,celsius);
```
이 문장에서는 인용부호 속에서 출력양식을 지정해준다. `%d`는 정수형 출력을 의미하고, 뒤의 매개변수로 들어오는 변수가 순서대로 `%d`의 자리에 들어가게 된다.

#### REPL 까진 아니어도 온라인 컴파일러
[Online C Compiler](https://repl.it/languages/c) 여기서 연습하는게 더 편하다.