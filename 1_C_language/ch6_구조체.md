## 6. Structures
구조체란 하나의 이름으로 불릴 수 있는 서로 다른 타입의 변수들의 모임이다(PASCAL에서는 records). 구조체는 큰 프로그램에서 여러 변수들의 모임을 하나의 독립된 양으로 취급하게 해주므로 복잡한 자료를 다루는 것이 쉬워진다.

편히 생각하면 **객체**나 DB의 한 ROW라고 생각하면 되겠다.
### 6.1 Basics of Structures
**구조체 선언**
```c
struct point{
  int x;
  int y;
}
```
자바나 타입스크립트의 인터페이스 리터럴과 같다.

`struct`(type) : 명령어는 구조체의 시작을 나타낸다.  
`point`(name) : 구조체의 이름은 `struct` 뒤에 온다.  
`x,y`(member) :구조체에 속하는 변수들을 멤버라고 부르고 {}안에서 변수처럼 선언한다. 

멤버와 구조체의 이름은 엄밀히 구분되기 때문에 같은 이름이어도 상관없다. 또 구조체의 이름이 일종의 네임스페이스이기 때문에 동일한 멤버명을 다른 구조체에서 선언해도 문제없다.

**구조체 type의 선언과 구조체변수 선언**
```c
struct{...} x, y, z;
```
이렇게 하면 해당 구조(`{...}`)를 갖는 구조체를 3개(`x,y,z`) 선언한 것이다.

**구조체 type만 선언**
```c
struct{...};
```
이건 어따가 쓰는 걸까?

**선언된 구조체 type을 갖는 변수 선언**
```c
struct point pt
```
이렇게 되면 앞서 선언한 `point`의 구조와 같은 변수 `pt`가 만들어진다.


**선언된 구조체 type을 갖는 변수 선언과 할당**
```c
struct point pt = {320,200};
```

**구조체 멤버에 접근하는 법**
```c
pt.x; //320
pt.y; //200
```
`구조체이름.멤버이름`식으로 `.`이라는 멤버연산자를 이용해서 구조체의 이름과 멤버 이름을 연결시킨다.

**sqrt 무슨 문법이에요?**
```c
double dist, sqrt(double);
dist = sqrt((double)pt.x*pt.x+(double)pt.y*pt.y);
```

**구조체의 구조체도 있을 수 있다(객체안의 객체처럼)**
```c
struct rect{
  struct point pt1;
  struct point pt2;
}
```

**멤버로 구조체를 가지고 있는 구조체의 type을 갖는 변수와 접근**
```c
struct rect screen;
// screen의 pt1이라는 멤버의 x좌표는 다음과 같다.
screen.pt1.x;
```
### 6.2 Structures and Functions
