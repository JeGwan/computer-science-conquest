# 5. PointersandArrays
## 5.1 Pointers and Addresses
포인터는 다른 변수의 주소를 그 값으로 가지는 변수이다. 또한 배열과 밀접한 관계를 가지고 있다.

`ANSI C`에서는 포인터 사용이 더 명확하게 되었고 일반적인 포인터 형태로 void*가 사용된다.

### 포인터와 주소
보통 배열은 메모리에 연속적으로 기록되며 한 `byte`가 문자가 될 수도 있고(이 당시에는 `ASCII`를 썼고 `ASCII`는 `7bit`의 사이즈를 갖으므로 `8bit = byte`, 한바이트를 갖는 것이 맞다) 연속된 두개의 바이트가 `short integer`가 될 수도 있으며(이 역시 `short`타입은 `16bit`를 갖기 때문), 연속된 네개의 바이트가 `long integer`가 될 수도 있다. 포인터는 어떤 변수의 번지를 기억한다. 예를 들어 `c`가 `char`형이고 그 포인터가 `p`라고 할 때 `p`의 값은 **`c`가 기록되어 있는 메모리의 번지**가 된다.

요컨대 둘다 메모리에 기록된 값이며 변수이다. 다만 `p`의 값은 **`c`의 주소**라는 점이 포인터 변수의 핵심이다.

항목 |`c` | `p`
-----|----|-----
type | char | pointer
value | 'a'(임의의 문자, 여기선 'a' 로 했다) | 25292
address | 25292 | 35154

이렇게 보면 더 확실하게 보인다. `p`는 **`c`의 주소**를 가지고 있는 메모리를 차지하는 변수라는 것이.

### & operator (비트연산자가 아니다! 비트연산자 &은 두개의 operand를 받는다!)
포인터의 할당
```c
p = &c;
```
`&c`는 c의 주소를 리턴한다. 다시 말해 위식은 `p`라는 변수에 `c`의 주소를 값으로 담은 것이다.

당연하게도 메모리를 사용하지 않은 상수는(이를테면 123, '1') 포인터를 사용할 수 없고, 메모리를 차지하고 있는 변수와 배열에만 사용할 수 있다.

### * operator
`*`연산자는 반대 역할을 한다. 즉 포인터 변수에 `*` 연산을 하면 그 포인터가 가리키고 있는 변수의 값을 가리킨다(때문에 `*p`는 사실상 `c`와 같다). 

```c
char c = 'a';
p = &c;

printf("%c",*p); 
```
이 문장에서 `*p`는 `'a'`를 나타낸다. 즉 `p`가 가지고 있는 값인 `c`의 주소로 가서 `c`가 가지고 있는 값인 `'a'`를 나타내는 것이다.

### 포인터의 선언
```c
char *p;
```
제일 먼저 와야할 선언을 제일 뒤로 빼는 이유는 위의 개념들을 알고 와야 이 수식이 이상해보이지 않는다. 포인터는 `int p`의 형태로 선언되지 않는다. 오로지 `char(포인터로 가리키는 변수가 가진 데이터형) *p`의 형태로 선언된다.

### void*
특별히 `void`타입이라는 것이 있는데 제약이 있지만 어떤 타입의 포인터도 될 수 있다.

### *p 는 c이다
`*p`는 `c`대신 쓰일 수 있다. 즉
```c
int c = 1;
int *p;
p = &c;
*p = *p + 1;
```
에서 마지막줄은 `c = c + 1`과 같고 `c++`, `++c`와 같은 표현이다.

### 포인터 역시 변수이다
포인터 역시 변수이기에 다른 변수에 할당이 가능하다.
```c
q = p;
```
이 식에서 q는 p가 가리켰던 c의 주소를 가리키게 된다.

다음식에서 이 것을 정리해보았다.
```c
#include <stdio.h>
int main(void) {
  int x =1 , y=2, z[10];
  int *ip;
  ip=&x; // get x address
  y=*ip; // equals to y=x; y assigned x's value, 1
  *ip=0; // equals to x=0; x assigned 0, now x == 0
  ip = &z[0]; // get z[0]'s address, now *ip == z[0]
  printf("x:%d, y:%d",x,y); // x:0, y:1
}
```
## 5.2. Pointers and Function Arguments
C에서는 호출할 때 arguments는 그 값만 전달되므로 (`call by value`) 호출된 함수에서 호출한 함수에 할당된 변수의 값을 바꾸는 것은 불가능하다. 예를들어
```c
swap(a,b);
```
에서 `swap`이라는 함수가 다음과 같다면
```c
void swap(int x, int y){
  int temp;
  temp = x;
  x = y;
  y = temp;
}
```
호출된 함수 `swap`은 스코프 내에서 값만을 전달 받아 지역변수 `x, y`에 할당하는 것이므로 호출한 함수가 있는 곳의 `x, y`에 영향을 주지 않는다.

원하는 결과를 얻으려면 다음과 같이 포인터를 사용하면 된다.

```c
swap(&a,&b);

void swap(int *px, int *py){
  int temp;

  temp = *px;
  *px = *py;
  *py = temp;
}
```
이것은 `&a,&b`를 통해 `a,b`의 주소를 포인터 `px, py`에 할당하고 아래의 식은 전에 언급한 것처럼 `temp = a; a = b; b = temp;`와 동치가 된다.

즉 `call by value`로 C언어에서 함수가 호출 되는 것은 어쩔 수 없기에 `value`에 `address`를 실어 보내 마치 전역변수처럼 다른 스코프에서 해당 변수를 조작할 수 있는 것이다.


## 5.3. Pointers and Arrays
C에서 포인터와 배열은 밀접한 관계가 있다. 배열에 의한 연산은 포인터를 사용해서 할 수 있으며, 포인터를 사용하는 것이 더 빠르기는 하지만 좀 더 어렵다.

길이가 10인 배열
```
int a[10];
```
을 선언했을 때, 우리는 `a[0],...,a[9]`까지의 변수를 사용할 수 있다. 배열은 변수를 한번에 쉽게 생성하고, 인덱스를 통해 수식적 접근을 가능하게 해준다.

배열과 포인터를 함께 쓰면 좋은 점은 **배열은 처음부터 끝까지 1씩 증가하는(바로 옆에 붙어있는) 주소를 가지기 때문이다.** 즉 `a[0]`의 메모리주소에 1만 더하면 `a[1]`의 메모리주소가 된다.

코드를 통해 보자.

```c
int a[10];
int *pa; // pointer of a
pa = &a[0]; // now *pa == a[0]
x = *pa; // equals to x = a[0], if a[0]'s value was 0, x has value 0
*(pa+1) == a[1]; // 1, true
```
`pa`는 `a[0]`의 주소를 가지고 있었기 때문에 1만 더하면 `a[1]`의 주소를 가지게 되고 * 연산자를 쓰게 되면 `*(pa+1)`는 `a[1]`과 동치(equivalent)가 된다.

### a는 a[0]의 주소를 가진 포인터!
배열로 선언된 변수 자체는 이름으로 쓸 때 첫번째 원소의 주소와 같기 때문에 다음 두 문장은 equivalent 하다.

```c
pa = a;
pa = &a[0];
```
즉 배열 자체를 expression으로 쓰면 첫번째 원소의 주소를 리턴한다는 말이다.

조금만 생각하면 `a[i]`는 `*(a+i)`와 같다. 단계별로 나누어 보자.
```c
a+i; // &a[0] + i == a[i]의 주소 == &a[i]
*(a+i) // *(&a[i]) == a[i]
```

`pa[i]`는 `*(pa + i)`와 같고 그냥 `a[i]`와 같다.

다시 말해 **배열과 인덱스의 표현은 포인터와 오프셋(한점으로 부터 떨어진 거리)으로 표현한 것과 equivalent하다!**

### 배열의 이름 a는 포인터 "상수"이다!
위 코드에 `pa`는 변수이다 다시말해 `pa=a`나 `pa++`과 같은 표현을 쓸 수 있다.

하지만 배열의 이름은 변수가 아닌 **상수**이다. 때문에 `a=pa` 나 `a++`등의 표현은 사용할 수 없다.

이번엔 문자열을 넘겨받아 길이를 반환하는 함수를 보자.
문자열은 `char` 데이터 타입의 원소로 이루어진 배열이고, 문자열을 넘긴다는 것은 곳 배열을 넘긴다는 것이며, 배열을 넘긴다는 것은 곧 그 배열의 첫번째 원소의 주소를 넘긴다는 말임을 우리는 이제 안다. 따라서 함수의 매개변수는 `char`형을 값으로 갖는 **포인터**가 될것이며 길이를 리턴하므로 int를 함수명 앞에 써주어야 한다.

```c
int strlen(char *s){
  int n;
  for(n=0; *s != '\0'; s++)
    n++;
  return n;
}
```
조건 `*s != '\0'`은 **문자열이 끝나지 않는 동안** 이라는 뜻이다(모든 문자열은 마지막 인덱스에 `'\0'`으로 끝을 표시해주는 값을 갖는다).

위의 함수를 호출할 때에는 단순히
```c
char a[] = "abcde";
strlen(a);
```
와 같이 쓰면된다.

## 5.4. Address Arithmetic
C의 주소 연산(Address Arithmetic)은 아주 체계적이다. 포인터와 배열 그리고 주소 연산이 통합되어 있다는 것은 C의 큰 장점 중 하나이다.

단순한 기억장소할당 프로그램을 예로 들어보자. 이 프로그램에는 `alloc(n)`과 `afree(p)` 두 루틴이 필요하다. 구조는 두 루틴이 사용할 메모리공간 `allocbuf`, 그리고 사용하지 않은 메모리 주소를 가진 `allocp` 그리고 두 루틴 `alloc(n)`(할당하는 함수)과 `afree(p)`(해제하는 함수)로 이루어져 있다.

`alloc(n)`은 n이라는 문자열을 받고 `allocbuf`에 여유가 있는지를 조사해야한다. 있으면 할당한 문자열의 첫번째 메모리 주소(동시에 할당전 비어있는 첫번째 메모리)를 가진 포인터 `allocp`를 리턴하고 `allocp`를 n만큼 증가시킨다. 없으면 0을 리턴한다. 

`afree(p)`는 `p`가 `allocbuf` 내를 가리키면 `allocp`에 `p`의 값을 넣어준다(`p`이후로 버리므로 이제 `allocbuf`의 첫공간 주소는 `p`이기 때문).

함수로 보면 더 이해가 편한다. 다음을 보자

```c
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE]; //외부 함수에서 사용할 필요가 없으므로 static 선언.
static char *allocp = allocbuf; //allocbuf의 첫 공간 주소를 가진 포인터 allocp 선언.
// allocp = allocbuf 가 맞는 식이겠지만 포인터 선언식이기에 이렇게 쓰인 것이다.

char *alloc(int n){
  // 매개변수 데이터 타입이 int인 이유는 문자 char을 ascii코드 int로 처리할 수 있어서이다.
  if(allocbuf + ALLOCSIZE - allocp >= n){
    // 위의 식은 빈공간의 가장 처음 주소 allocp를 전체에서 빼준 값이 n보다 커야 
    // 자리가 있다는 뜻이므로 조건식으로 쓴 것이다.
    allocp += n;
    return allocp - n;
    // 여기서는 allocp를 리턴하고 더 할수가 없어서 더하고 다시 뺀 값을 리턴했다.
  }else{
    return 0;
  }
}

void afree(char *p){
  if(p>=allocbuf && p < alocbuff+ALLOCSIZE){
    // 위식은 'p가 allocbuf의 공간 내에 있으면' 이라는 조건이다.
    allocp = p;
  }
}
```

위의 코드에서 포인터의 몇가지 특징을 볼 수 있다.

**하나**, 포인터의 값으로 0을 사용할 수 있다. 포인터와 0을 비교할 수도 있다. 0 대신 NULL을 사용하기도 한다.

**둘**, 포인터 끼리 계산할 수 있다. 만약 `p`와 `q`가 같은 배열 내의 원소를 가리키는 포인터라면 비교연산자를 통한 비교, 차이 계산을 할 수 있다(한마디로 앞에 있냐, 뒤에 있냐, 오프셋은 얼마냐).

### 주의 사항
1. 포인터에 대한 정수를 더하거나 뺄 수 있다.
2. 포인터를 0과 비교할 수도 있고 같은 배열 내의 두 포인터를 비교하거나 뺄 수도 있다.
3. 그러나 그 외는 모두 할 수 없는 연산이다.
### 할수 없는 연산
1. 포인터 끼리 더하기, 곱하기, 나누기등을 할 수 없다.
2. 포인터에 float이나 double을 더하거나 빼서도 안된다.
3. 포인터를 곱셈, 나눗셈 해서도 안된다.
4. 포인터에 비트연산을 하면 안된다.
5. cast 연산자 없이 타입이 서로 다른 포인터를 하나에서 다른 하나로 할당할 수 없다.

### 이것만 기억하자
**포인터끼리의 연산은 오로지 배열 내의 주소와 그 주소로부터의 오프셋을 위한 것**이다.

그렇게만 생각하면 할 수 있는 것과 없는 것이 구분된다.

## 5.5. Character Pointers and Functions
```c
char amessage[] = "now is the time";
char *pmessage = "now is the time";
```
언뜻 같아 보이는 문자열 선언이지만 차이가 있다.

`amessage`는 배열이며 끝에 `\0`이 있고 각각의 문자를 바꿀 수도 있지만 항상 같은 주소에 저장된다. 반면 `pmessage`는 포인트이고 가리키는 위치를 바꿀 수 있지만 내용을 바꾸는 것은 정의되어 있지 않다(바꿀수 있긴 하다, 그러나 책에서 이에 대한 더 자세한 설명은 나오지 않는다).

이 절에서는 함수가 받는 인자로서의 포인터를 어떻게 다루는지 함수들을 보면서 알아보자.

`strcpy`의 예(string copy)
```c
void strcpy(char *s, char *t){
  while(*s++ = *t++) ;
}
```
위의 식은 간단명료하게 포인터와 배열 call by value의 개념을 함축시켰다.
즉, call by value로 받았기에 `while`문 안에서 `++` 연산을 해도 본래 포인터 s가 가리키는 주소는 변하지 않으며, `++`연산을 할 수 있는 이유는 문자열의 인덱스간 주소차이가 1씩 나는 배열과 같은 형태이기 때문이다.

문자열, 배열의 끝은 `\0`이고 이는 `0`을 리턴하므로 `while`문이 종료되는 조건에도 부합된다.

`strcmp`의 예(string compare)
```c
int strcmp(char *s, char *t){
  for(; *s == *t; s++, t++)
    if(*s == `\0`)
      return 0;
  return *s - *t;
}
```
두 문자열을 사전 처럼 순서를 비교하는 함수 `strcmp`도 마찬가지다. 포인터만 넘겨주고 call by value라는 것을 이용하여 변수처럼 사용하면 함수가 간결해진다.

`++`, `--`연산자를 이용하면 스택의 `push`, `pop`을 아주 쉽게 표현할 수 있다.
```c
*p++ = val; // push and add index
val = *--p; // pop top of stack
```

## 5.6. Pointer Arrays : Pointers to Pointers
포인터도 일종의 변수이기 때문에 포인터들로 이루어진 배열도 가능하다. 설명을 위해서 문자로 이루어진 행의 순서를 사전순서로 정렬하는 프로그램을 보자.

각 행의 첫번째 문자의 포인터를 가진 배열을 만들면 편하다. 비교는 단순히 두 행의 포인터를 `strcmp`에 보내주면 되고, 바꾸고자 할 때는 배열상의 포인터만 바꿔주면 되기 때문이다.

함수식은 생략한다. 다만 다음 선언이 포인터들의 배열이다.
```c
char *lineptr[MAXLINES];
```
이렇게 하면 `lineptr` 는 `MAXLINES`개의 요소로 이루어진 배열이 된다. 그리고 각 요소는 "`char`형 변수의 포인터"이다. 즉 `lineptr[i]`는 (`char`를 가리키는)포인터이고 `*lineptr[i]`는 포인터가 가리키는 한행의 첫문자이다. 

```
0x00001 => lineptr[0] => 0x31521 == "a new book"의 첫번재 문자 'a'의 포인터 
0x00002 => lineptr[1] => 0x12092 == "bravo"의 첫번째 문자 'b'의 포인터
...
```
이런식이다. 즉 `lineptr`은 그 자체로 배열이기 때문에 인덱스간 주소차이가 1씩나지만, 각 원소들은 다른 배열의 포인터를 가지고 있다는 점이 중요하다. 위의 예시값을 이용하면 다음과 같은 식이 성립한다.
```
*(lineptr + 1) == lineptr[1]
*(*(lineptr + 1) + 1) == 'r'
```
`*(lineptr+1)`은 두번째 행인 `"bravo"`의 첫문자 `'b'`의 포인터이고 거기다 1을 더해 가지고 있는 값을 반환했으니 `'r'`이 나오는 것이다.

## 5.7. Multi-dimensionalArrays
C는 다차원 배열을 제공해주지만 포인터의 배열보다는 많이 사용되지 않는다.

월-일을 그 해의 몇번째 날짜인지 계산하는 함수 `day_of_year`와 그 반대로 그 해의 몇번째 날짜를 월-일로 바꾸는 함수 `month_day`를 만들어보자.

두 함수는 같은 정보로 실행되는데 그 정보는 어느 달이 며칠가지 있는지와 어느 해가 윤년인지 하는 것이다. 이 정보를 가지고 있는 배열과 두 함수는 다음과 같다.

```c
static char daytab[2][13] = {
  {0,31,28,31,30,31,30,31,31,30,31,30,31},
  {0,31,29,31,30,31,30,31,31,30,31,30,31}
};
// 13개의 원소를 가진 배열을 원소로 하는 사이즈 2짜리 배열 선언
// data type은 int로 하는게 맞지만 char형으로 표현할 수 있다는 것을 보여주기위해 씀
// 배열 리터럴은 {}이고, 여기서는 해당 월의 숫자가 그대로 인덱스로 들어가게 하기 위해 
// 0번째는 0으로 대입해주어 총 13의 길이가 됨
int day_of_year(int year, int month, int day){
  int i, leap;
  leap = year%4 == 0 && year%100 !=0 || year%400 == 0;
  // leap는 윤년이면 1 아니면 0이 된다.
  for(i = 1; i < month; i++){
    day+=daytab[leap][i];
    // 윤년인지 아닌지, 그리고 몇번째 달인지에 따라 daytab의 일수가 더해진다.
  }
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday){
  int i, leap;
  leap = year%4 == 0 && year%100 !=0 || year%400 == 0;
  for(i=1; yearday > daytab[leap][i]; i++){
    yearday -= daytab[leap][i]
    // 해당년의 몇일짼지가 yearday이고 1월부터 차례로 일수를 빼주어 몇월인지 캐치한다.
  }
  *pmonth = i; // 월을 받아들인 포인터가 가리키는 값에 입력해준다.
  *pday = yearday; // 지금은 yearday가 해당 월의 총 일수보다 작은 상태이므로 그냥 그대로 대입하면 된다.
}
```
만약 다차원 배열 자체를 인수로 함수에 넘길 경우엔 다음과 같이 써준다.
```c
f(int daytab[2][13]){...}
f(int daytab[][13]){...}
// 2차원 배열을 매개변수로 사용할 때 첫번째 index는 포인터로 전달되므로 써줄 필요가 없다.
f(int (*daytab)[13]){...}
// 따라서 이런 표현도 가능하다. a[] 와 *a는 인자로서 equivalent이므로.
// 다만 연산자 우선순위가 []가 더 높아서 괄호를 써주었다.
```

## 5.8. Initialization of Pointer Arrays
몇 번째 달인지 알려 주면 그 달의 이름을 출력하는 함수 `month_name(n)`을 만들어보자. 출력은 이름을 가리키는 포인터가 될 것이다. 함수 `month_name`은 문자열을 원소로 가지고 있다가 이 함수가 호출될 때 적절한 원소를 가리키는 포인터를 리턴한다.
```c
char *month_name(int n){
  static char *name[] = {
    "Illegal month",
    "January",
    "February",
    ...
  }
  return (n < 1 || n > 12) ? name[0] : name[n];
}
```
문자를 가리키는 포인터의 배열로 name을 선언했다.

우리는 이것만 기억하면 된다. 포인터를 원소로 갖는 배열은 `dataType *variableName[]`로 선언한다. 그리고 바로 값을 할당(즉, 초기화)할 수 있는데 `{}`리터럴을 이용한다.

## 5.9. Pointers vs. Multi-dimensionalArrays
```c
int a[10][20];
int *b[10];
```
다차원 배열과 포인터를 원소로하는 배열은 차이가 있다.
`a`는 2차원 배열이므로 200개의 정수가 한곳에 모여 저장되어있다. 그래서 `a[row][col]`의 위치는 처음으로부터 `20*row + col`번째가 된다. `b`에서는 10개의 포인터가 선언되고 초기화는 이루어지지 않았다. 초기화를 하려면 초기화를 위한 문장을 써야한다. `b`의 각포인터가 20개 요소의 배열을 가리키고 있다면, 필요한 전체 메모리는 정수 200개와 10개의 포인터만큼이 된다. 즉 `b`의 경우가 더 많은 메모리가 소요된다. `b`의 장점은 각 행의 길이가 달라도 된다는 점이다. 다시 말하면 `b`의 포인터는 요소 20개인 배열을 가리킬 수도 있고, 20개가 아닌 배열도 가리킬 수 있다.

헷갈리지 않기 위해 이것만 기억하자.

**다차원 배열은 원소가 모두 실제 값이며, 포인터 배열은 원소가 각각 다른배열을 가리킬 수 있는 포인터이다.**

따라서 포인터 배열에서 원소가 가리키는 배열간에 주소의 연속성은 없으며, 포인터도 변수이기 때문에(값으로 주소를 가지고 있어야 하니까) 메모리를 더 먹는 것이다.

```c
char *name[] = {"Illegal month", "Jan", "Feb", "Mar"};
char aname[][15] = {"Illegal month", "Jan", "Feb", "Mar"};
```
### `name`의 경우
인덱스 | 해당 인덱스의 값 | 그 값이 가리키는 것
-|-|-
0|1023| 'I'
1|4012|'J'
2|5029|'F'
3|1204|'M'
각 인덱스의 값은 연속적이지 않은 메모리주소이며 그 것은 각기 다른 문자열을 가리키는 포인터이기 때문이다.

### `anmae`의 경우
인덱스 | 해당 인덱스의 값 | 그 값이 가리키는 것
-|-|-
0|0| 'I'
1|15|'J'
2|30|'F'
3|45|'M'
각 인덱스의 값은 15씩 차이가 나는 주소이고 이것은 다차원 배열이 모두 연속적 주소를 가지며 한공간에 모여있기 때문이다. 즉 `"Illegal month"`는 0~14까지의 주소를 사용하고 `"Jan"`은 15~30까지의 주소를 사용한다고 보면 된다.

## 5.10. Command-line Arguments
C를 지원하는 환경에서 어떤 프로그램을 실행할 때 Command-line argument를 프로그램에 넘겨주는 것이 가능하다. 우리가 함수 `main`을 실행할 때 두 개의 매개변수가 전달된다.
- `argc` : 그 프로그램을 실행하기 위한 매개변수의 개수
- `argv` : 매개변수들의 모임인 문자열을 가리키는 포인터

이런 문자열을 다룰 때 보통 몇중으로 되어 있는 포인터를 사용하게 된다.
`echo`라는 프로그램의 예시를 보자.
```bash
echo hello, world
```
출력은 다음과 같다.
```bash
hello, world
```
`argv[0]`은 프로그램 자신의 이름에 쓰인다. 따라서 `argc`는 최소 1개가 된다. `argc`가 1이라는 말은 커맨드 라인으로 부터온 매개변수가 없다는 뜻이다. 위의 `echo` 예는 `argc`가 3이며 `argv[0]`은 `"echo"`, `argv[1]`은 `"hello"`, `argv[2]`은 `"world"`이다. 첫번째 매개변수는 `argv[1]`이고 마지막 매개변수는 `argv[argc-1]`이다. 그리고 `argv[argc]`는 null 포인터가 된다.

`argv`로 들어온 매개변수를 출력하는 함수를 작성해보자
```c
#include <stdio.h>

int main(int argc, char *argv[]){
  while(--argc>0)
    // argc는 사이즈이므로 1을 빼고 시작해야 인덱스로 쓸 수 있다.
    // 하지만 여기서는 그냥 전체사이즈 보다 한번 덜 돌게 만들기위해 쓰였다.
    // 그냥 ++argv를 저 자리에 넣고 밑에 *argv를 해주는게 더 가독성이 좋을 것 같다.
    printf("%s%s", *++argv, (argc>1) ? " " : " ");
    // argv[0]은 호출된 함수의 이름(여기에선 main)이므로
    // 1을 더한 것부터 써주어야 인자만 출력할 수 있다.
  printf("\n");
  return 0;
}
```
이번엔 입력한 문자열내에 패턴을 찾는 프로그램을 만들어보자. 패턴은 커맨드라인 매개변수로 받는다.
```c
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline(char *line, int max); // 메인에서 쓰기 위해 선언만 해놓았다.
// 그전 챕터에 이 함수를 찾을 수 있다. 여튼 입력문자열을 받는 함수

main(int argc, char *argv[]){
  char line[MAXLINE];
  int found = 0;
  
  if(argc != 2)
    printf("Usage : find pattern\n");
    // 함수 이름과 함께 1개의 패턴을 받아야 하니까 argc가 2여야 한다.
    // 그게 아닐때 패턴 찾는거라고 알려주는 거다.
  else
    while(getline(line,MAXLINE)>0)
      // EOF가 아닐 때까지 문자열을 받는다.
      if(strstr(line,argv[1])!=NULL){
        // strstr은 line내 argv[1]이 일치하는 첫 번째 문자의 포인터를 리턴하는 함수다.
        // 못 찾으면 NULL을 리턴한다.
        printf("%s", line);
        // 그리고 일치하는 문자를 가진 문장을 출력한다.
        found++;
      }
  return found;
  // 여기서는 총 몇번 등장하는지가 리턴된다.
}
```
이번엔 `optional argument`를 붙여보자. command line에서 `-`를 붙여 나타내는 일종의 스위치같은 것이다. 다음 두개를 만들 것이다.
- `-x` : 패턴과 일치하지 않는 라인을 출력하는 옵션
- `-n` : 행의 번호를 함께 출력하는 옵션

이렇게 쓰면
```bash
find -x -n pattern
```
은 "패턴이 맞지 않는 행"을 "행번호와 함께 출력"할 것이다. 선택 매개변수는 순서를 바꾸어써도 괜찮아야 하고, 묶어서 써도 괜찮아야하며 프로그램의 내용은 선택매개변수의 수에 영향을 받지 않아야 한다.

```c
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline(char *line, int max);

main(int argc, char *argv[]){
  char line[MAXLINE]; // 한 행씩 저장할 변수
  long lineno = 0; // 행번호를 나타내는 정수변수
  int c, except = 0, number = 0, found = 0;
  // -x에 대한 스위치 역할을 하는 except 변수
  // -n에 대한 스위치 역할을 하는 number 변수
  // 총 찾은 카운트를 의미하는 found
  // 커맨드라인 매개변수로 들어온 녀석을 문자 1개 씩 저장할 c
  while(--argc > 0 && (*++argv)[0] == '-')
    // 먼저 받아들인 인자들 중 첫번째 문자가 '-'인 인자를 찾는다.
    while(c = *(++argv[0]))
      // 그럼 그 인자의 두번째 문자부터(++argv[0]이므로) 마지막까지를 루프로 돌려본다.
      switch(c){
        case 'x':
          except = 1;
          break;
          // 'x'옵션일경우 except를 1로 만들어 추후에 동작할 수 있게한다.
        case 'n':
          number = 1;
          break;
          // 'n'옵션일경우 number를 1로 만들어 추후에 동작할 수 있게한다.
        default:
          printf("find: illegal option %c\n", c);
          argc = 0;
          found = -1;
          // 그외에 '-'뒤에 붙은 문자들은 옵션이 아니므로 argc를 0으로만들어
          // 뒤이어 올 조건문에서 루프를 실행하지 않게 하며 
          // found를 -1로 리턴한다.
          break;
      }
  if(argc != 1)
    printf("Usage: find -x -n pattern\n");
    // 위에서 --argc > 0  루프를 돌아서 정상적인 경우 argc는 1이 되어야 한다.
  else
    while(getling(line,MAXLINE) > 0){
      // 역시 EOF까지 행을 읽으며
      lineno++;
      // 행번호를 하나씩 증가시킨다.
      if((strstr(line,*argv)!=NULL) != except){
        // (strstr(line,*argv)!=NULL)에서
        // 일치하는 문자열이 있다면 1이 리턴되고 
        // except기 0 이었다면 그것이 출력되지만
        // except가 1 인경우 괄호안의 expression이 0일 때 즉,
        // 일치하지 않는 경우가 출력되므로 의도에 맞다.
        if(number)
          // 행번호를 출력하는 옵션을 넣을 경우 number가 1이 되므로 아래가 실행된다.
          printf("%ld:",lineno);
        printf("%s",line);
        found++;
      }
    }
  return found;
}
```
## 5.11. Pointers to Functions
C에서 함수는 변수가 아니지만 함수의 포인터는 정의할 수 있다. 이 포인터는 매개변수로 사용될 수도 있고 배열의 원소로 사용될 수도 있는 등 여러가지 방법으로 조작이 가능하다.

5.6절에서 만들었던 프로그램을 고쳐 optional argument `-n`이 있으면 정렬이 사전식이 아니라 숫자 크기 순으로 하는 프로그램을 만들어보자.

정렬은 크게 세 부분으로 나뉜다.
1. 두 대상을 비교하는 부분
2. 두 대상체의 순서를 뒤집는 부분
3. 전체의 순서가 바로 될 때까지 비교와 교환을 계속하는 부분

우리가 작성하려고 하는 프로그램은 숫자정렬과 사전식 정렬의 두가지 동작이 필요하므로 비교하는 부분은 두가지가 있어야 한다.

두 행을 사전식으로 비교하는 것은 `strcmp`를 사용하면 되고 숫자 크기를 비교하는 것은 `numcmp`를 만들면 된다. 둘다 `int` 출력을 할 수 있기 때문에 함께 사용할 수 있다.

```C
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
int writelines(char *lineptr[], int nlines);

void qsort(void *lineptr[], int left, int right, int (*comp)(void *,void *));
int numcmp(char *, char *);

main (int argc, char *argv[]){
  int nlines;
  int numeric = 0; // 커맨드라인 '-n'옵션에 따라 1이 되고 숫자정렬이 된다.

  if(argc > 1 && strcmp(argv[1],"-n") == 0){
    // strcmp 값이 0이라는 것은 똑같은 문자열을 의미하므로 
    // -n 옵션이 있는지에 대한 조건문이다.
    numeric = 1;
  }

  if((nlines = readlines(lineptr,MAXLINES))>=0){
    qsort((void **) lineptr, 0, nlines-1, (int (*)(void*, void*)) (numeric ? numcmp : strcmp));
    writelines(lineptr,nlines);
    return 0;
  }else{
    printf("input too big to sort\n");
    return 1;
  }
}
```
`qsort`에서 파라미터로 아주 복잡한 유형이 눈에 띈다.
```c
int (*comp)(void *,void *)
```
대강 int를 리턴하는 포인터인데 좀 복잡해 보인다. (*comp)는 포인터가 가리키는 실제 값이랑 같다는 걸 떠올리자. 그럼 이런식으로 바꿔 볼 수 있다. `int something(void *, void *)` 어떻게 보이는가? 그렇다. 정확히 함수리터럴이다.

Javascript에서의 callback function처럼 함수를 포인터로 전달하기 위해 저런 문법을 쓴 거다. 저렇게 처리해줌으로써 compare함수로 어떤 함수든 받아들일 수 있게 된다. 다만 그 형식이 매개변수 두개를 받아서 정수형 리턴을 갖는 함수라는 제한만을 걸어뒀을 뿐.

qsort함수를 보자
```c
void qsort(void *v[], int left, int right, int (*comp)(void *, void *)){
  int i, last;
  void swap(void *v[], int, int);

  if(left >= right)
    return;
  swap(v, left, (left+right)/2);
  last = left;
  for(i=left+1; i<= right; i++)
    if((*comp)(v[i],v[left])<0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last-1, comp);
  qsort(v, last+1, right, comp);
}
```
`qsort`에 대한 알고리즘은 앞절에서 다루었다. 여기서는 콜백함수처럼 매개변수로 받은 함수의 포인터 `comp`를 `qsort`함수내에서 어떻게 사용하는지를 보자.
`if((*comp)(v[i],v[left])<0)`에서 `comp`는 함수의 포인터이므로 `*comp`가 함수가 되어 함수를 호출하는 것이다. 그리고 괄호는 꼭 있어야 한다.

```c
int *comp(void *, void*);
int (*comp)(void *, void*);
```
는 다르다. 첫번째는 comp가 함수인데 리턴 값이 정수의 포인터라는 뜻이다.
두번째는 우리가 아는 것처럼 함수의 포인터이다.

## 5.12. Complicated Declarations
포인터 개념을 여러번 중첩해서 쓸 수록 선언문은 아주 복잡해진다.
다음 두 선언문은 서로 다르다.
```c
int *f(); // 정수형 포인터를 리턴하는 "함수"
int (*pf)(); // 정수를 리턴하는 함수의 "포인터"
```
복잡하게 얽힌 선언문을 작성하는 좋은 방법 중 하나는 6.7절에서 다룰 `typedef`를 사용하는 것이다. 또 하나는 선언문을 말로 표현해주는 함수와 그 역동작을 하는 함수다.

우선 선언문을 설명으로 바꾸어주는 함수 `dcl`에 대해 설명한다. 실행 사례 몇가지를 보자.
```
char **argv
  argv : pointer to pointer to char
int (*daytab)[13]
  daytab : pointer to array[13] of int
int *daytab[13]
  daytab : array[13] of pointer to int
void *comp()
  comp : function returning pointer to void
void (*comp)()
  comp : pointer to function returning void
char (*(*x())[])()
  x: function returning pointer to array[] of pointer to function returning char
```
`dcl`은 C의 선언에 관한 문법을 그대로 적용한 프로그램이다.
구조는 다음과 같다.
```
dcl :         optional *'s direct-dcl
direct-dcl :  name
              (dcl)
              direct-dcl()
              direct-dcl[optional size]
```
하나의 `dcl`은 하나의 `direct-dcl`앞에 *가 붙어 포인터가 되는 것이고.
`direct-dcl`뒤에 ()나 []가 붙는 것도 `direct-dcl`이다.

여튼 중요한 것은 포인터가 들어가면서 복잡해지는 변수의 선언을 문법적으로 분석하여 해석해주는 것이 `dcl`프로그램이다. 그게 전부다.
