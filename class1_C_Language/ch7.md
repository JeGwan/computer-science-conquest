# 7. Input and Output

## 7.1. Standard Input and Output
문자 스트림은 여러 개의 행으로 구성되는데, 각 행의 끝에는 줄바꿈 문자가 있다. 라이브러리의 함수는 줄바꿈 또는 리턴키 등에 적절히 대응하는 동작을 해야 한다.

가장 간단한 입력방법은 보통의 키보드로 표준 입력의 `getchar`를 이용하여 한 번에 한 문자씩 읽어 들이는 것이다. `getchar`는 그것이 호출될 때마다 다음의 입력 문자를 넘겨주고 파일의 끝을 만나면 EOF라는 값을 넘겨준다. 이 값은 상수고 보통 -1의 값을 가지지만 환경에 따라 다르다.

대부분의 환경에서는 `<`를 이용하여 키보드 대신에 파일을 이용할 수 있게 한다. 예를 들어 prog라는 프로그램 내에서 getchar가 사용되었다면 infile이라는 파일로부터 문자를 읽어 들이게 하기 위해 다음과 같이 한다.

### 파일을 입력으로 받기
```bash
prog <infile
```
`<infile`은 argv 안에 있는 명령 라인 매개변수에 포함되지 않는다. 입력 전환은 만약 입력이 다른 프로그램으로부터 온다 해도 밖에서는 보이지 않는다.
### 다른 프로그램의 출력을 입력으로 받기
```bash
otherprog|prog
```
위와 같은 CLI 명령어는 otherprog와 prog라는 두 프로그램을 실행시키고 otherprog의 standard output을 prog의 standard input으로 되게 한다.

### 출력을 파일로 저장하기
`putchar`는 문자를 표준 출력인 스크린에 보낸다. 에러 발생 시에는 EOF를 리턴한다. 출력은 다음과 같은 방식으로 파일로 전환이 가능하다.
```bash
prog >outfile
```

입출력 라이브러리 함수를 사용하는 프로그램의 시작 부분에는 반드시 다음 행이 필요하다.
```c
#include <stdio.h>
```
이때 이름은 <>를 사용하여 묶는데 이것은 표준 지정장소에 `stdio.h` 파일이 있다는 뜻이다.

막간 괄호 표현 정리
- () parentheses
- {} curly bracket or brace
- [] square bracket or just bracket(US)
- <> pointy bracket or less than greater than

## 7.2. Formatted Output-Printf
출력함수 printf는 내부의 수치 값을 문자로 바꾸어 준다.
```c
int printf(char *format, arg1, arg2, ...)
```
printf는 format이라는 문자열을 출력할 때 매개변수를 변환하고 형식화한 다음 출력시키고 출력된 문자의 개수를 리턴한다. 출력형식 제어 문자열은 두 종류가 있는데, 하나는 출력될 보통의 문자이고(그냥 문자) 또 하나는 출력형식을 정해주는 컨버전 문자(책에서는 conversion specification)이다. 즉 변수의 자리임을 나타내는 syntax이다.

컨버전 문자의 앞에는 %를 붙인다. %와 컨버전 문자 사이에는 다음과 같은 것들이 올 수 있다.
- 변환된 매개변수를 왼쪽에 맞추어 출력하게 하는 `-` 부호
- 최소 너비를 지정하는 숫자. 변환된 매개변수는 적어도 이 너비로 출력된다. 길이보다 짧게 입력하면 왼쪽 또는 오른쪽의 폭을 맞추기 위해 공백 또는 0으로 채워진다.
- 유효숫자를 타나내는 마침표 `.`
- 정밀도를 나타내는 숫자.
    - 문자열의 경우 : 최대 길이를 의미
    - 실수형의 경우 : 소수점 이하 숫자 길이를 의미
    - 정수형의 경우 : 최소 숫자 길이를 의미
- 만일 정수가 short로 출력되어야 하면 `h`, long으로 출력시키려면 `l`을 쓴다.
### printf의 컨버전 문자들
컨버전 문자 | 출력 형태
-:|-
d, i| int 10진수
o | int 8진수
x, X | int 16진수
u | int 부호 없는 10진수
c | int 단일 문자
s | char* 문자열로부터 '\0'이 있을 때까지 문자가 출력되거나<br> 정밀도에 의해 주어진 문자수만큼만 출력된다.
f | double [-]m, dddddd 여기서 d는 정밀도에 따라 다르다.(기본은 6자리)
e, E | double [-]m, ddddd e±xx 또는 [-]m, ddddddE±xx, <br>여기서도 d는 정밀도에 따라.(기본 6자리)
g,G | double 만일 지수가 주어진 정밀도 보다 크거나 -4보다 작으면<br> %e or %E를 사용하고 그렇지 않다면 %f를 사용한다.<br> 뒤에 붙는 0과 소수점은 출력되지 않는다.
p | void* 포인터, 어떤형태의 포인터든 집어넣으면 주소가 출력되는데 <br>이는 시스템에 따라 다름.
% | 변환되지 않는다. 그냥 %출력.
정밀도는 *로도 표현할 수 있는데, 그러면 출력형태는 출력될 매개변수의 최대 길이만큼을 리턴한다.

이를테면 다음을 보자.
```
%-15.10s
// 이는 15개의 자리를 갖는 문자열을 10자리 까지 표현하며 왼쪽정렬(-)하라는 의미다
// 다음을 리턴한다. |는 경계를 표시한 것이다.
|hello, wor      |
```

주의할 것은 컨버전 문자가 나타내는 데이터 타입과 해당 매개변수의 데이터타입이 일치해야한다는 점이다.

## 7.3. Variable-length Argument Lists
가변 길이(variable-length)를 가진 parameter 를 portable하게 처리할 수 있는 함수를 minprintf를 만들어보자.
```c
#include <starg.h>

void minprintf(char *fmt, ...){
  va_list ap; 
  // 매개변수를 차례로 가리키는 포인터 변수, argument pointer의 약자로 지었다.
  char *p, *sval;
  int ival;
  double dval;
  va_start(ap, fmt);
  // va_start는 va_list에 첫번째 매개변수를 할당해주는 역할이다
  for(p = fmt; *p; p++){
    // 이것은 포맷문자열의 처음부터 한 글자식 보는 루프이다.
    // pointer와 array를 기억하자
    if(*p != '%'){
      putchar(*p);
      continue;
      // 컨버전 문자가 아니면 그대로 출력하고 컨티뉴한다.
    }
    switch(*++p){
      // %일 경우 다음 글자에 따라 switch
      case 'd':
        // 정수형이므로
        ival = va_arg(ap,int);
        // var_arg는 함수로 들어온 매개변수 하나를 리턴하고
        // ap가 다음 매개변수를 가리키게 리턴한다.
        // stdarg.h는 매개변수를 어레이 형태로 처리하고
        // 그럼 각 매개변수의 주소가 붙어 있을 것이며 때문에
        // 배열에서 포인터가 다음 원소를 접근하는 것처럼
        // 기존 ap에 ap가 가리키는 데이터타입의 공간 다음에
        // 다음 순서의 매개변수의 주소가 있을 것이다.
        // 때문에 뒤에 데이터타입을 넣어준 것이다.
        printf("%d",ival);
        break;
      case 'f':
        dval = va_arg(ap,dobule);
        printf("%f",dval);
        break;
      case 's':
        for(sval=va_arg(ap, char*); *sval; sval++){
          putchar(*sval);
        }
        break;
      default:
        putchar(*p);
        break;
    }
  }
  va_end(ap);
  // ap에 있는 것을 지운다.
} 
```
그냥 단순히 %s, %f, %d를 너비나 유효자리수 따위를 정하지 않고 받은 변수 그대로를 출력해주는 미니 함수이다.

## 7.4. Formatted Input-Scanf
함수 scanf는 printf와 사용법이 유사한 함수인데, 출력함수가 아니고 입력함수이다.
scanf는 표준 입력으로부터 문자를 읽어 들여서 format의 변환형식에 따라 그들을 해석하고 매개변수에 결과를 저장한다.

즉, 포맷문자열을 매개변수로 주고나서 입력을 하면, 해당 포맷에 맞게 해석한다.
포맷 문자열을 주지 않을 땐 보통의 매개변수는 입력되는 문자가 위치해야 하는 곳을 가리키는 포인터이다. 즉, 문자가 저장되는 변수의 포인터변수이다.

여기서 포맷문자열(컨버전문자열)은 다음을 포함한다.
- 공백 또는 탭 즉 화이트스페이스는 무시된다.
- %를 제외한 보통 문자들
- %컨버전 문자, 변환이 없음을 알리는 *, 최대 자리수를 표시하는 숫자, short/long을 정해주는 h, l, L

cf. 16진수는 영어로 hexadecimal이며 x는 이를 위한 약자이다.
### 기본 scanf 변환
컨버전문자 | 입력데이터 : 매개변수 타입
-:|-
d | 10진수 정수 : INT *
i | 정수 : INT *, 정수는 8진수(숫자앞에 O를 붙이면) 또는 <br>16진수(숫자앞에 Ox 또는 OX를 붙이면)가 될수도 있다.
o | 8진수 정수(앞에 O가 있거나 없는) : int *
u | 부호 없는 10진수 정수 : unsigned int *
x | 16진수 정수(앞에 Ox나 OX가 있거나 없는) : int *
c | 문자 : char *, white space의 뛰어넘기는 하지 않는다.<br> 다음의 non-white space 문자를 읽어 들이려면 %1s를 사용한다.
s | 문자열 : char *, 문자열을 위한 충분한 크기의 문자 배열을 가리킨다.<br> 문자열 끝에는 '\0'을 붙인다.
e, f, g | 부호, 10진포인터와 짓수를 선택적으로 가질 수 있는 부동소수점수 : float *
% | 문자 % : 매개변수로의 할당은 이어지지 않는다.

보통 결과는 대응되는 매개변수가 가리키는 변수에 저장되지만, 컨버전문자 *에 의해 입력되는 항목은 할당되지 않는다. 입력 필드는 non-white space문자의 문자열로 정의되고 다음의 white space문자까지 또는 필드 너비가 명시되었을 경우 필드 폭까지의 필드가 된다.

복잡하게 써있지만 다음의 예시를 그냥 보자.
```c
#include <stdio.h>

main(){
  double sum, v;
  sum = 0;
  while(scanf("%1f",&v) == 1)
    // 다음의 non-white space 문자 하나를 받고("%1s")
    // 그것을 call by value를 극복하기 위해 포인터 형태로 전달된(&v)
    // v에 저장한다. scanf의 리턴 값은 읽은 문자의 개수 이므로
    // EOF를 만나기 전까지 읽은 문자는 1글자씩 즉 위의 조건문을 만족하게되고
    // EOF를 만나면 EOF그대로를 리턴하기 때문에 while 문이 끝난다.
    printf("\t%.2f\n", sum+=v);
    // 읽어들인 숫자를 순서대로 합친 값을 출력했다.
  retun 0;
}
```

다음과 같은 형태의 날짜 데이터를 읽기 원한다면
```
25 Dec 1988
```
`scanf` 명령문은 다음과 같이 쓴다.
```c
int day, year;
char monthname[20];
scanf("%d %s %d", &day, monthname, &year);
```
여기서는 포맷문자열로 세가지 데이터타입을 지정했고, 화이트스페이스로 구분했으며 해당 입력데이터를 day, monthname, year로 할당하기 위해 포인터로 매개변수를 전달했다(monthname은 배열이기 때문에 이미 포인터기 때문에 &가 없다).

mm/dd/yy형태로 읽을 수도 있다.
```c
int day, month, year
scanf("%d/%d/%d", &month,&day,&year);
```

위의 두가지 입력중 어떤 형태도 받아들일 수 있게 하려면 입력된 라인을 해당 포맷문자열에 일치하는지를 조건문 삼으면 된다.
```c
while(getline(line,sizeof(line))>0){
  if(sscanf(line,"%d %s %d", &day, monthname, &year) == 3){
    printf("valid : %s\n", line);
  }else if(sscanf(line,"%d %s %d", &month, &day, &year) == 3){
    printf("valid : %s\n", line);
  }else{
    printf("invalid : %s\n", line);
  }
}
// 이 함수를 보면서 C에서 validation을 할 수 있는
// 심플한 예시 같다는 생각이 들었다.
```
sscanf는 CLI에서 입력을 받는 것이아니라 애초에 문자열을 매개변수로 받아서 읽는 함수이다.

### scanf : 터미널에서 입력을 받는다.
```c
int scanf(char *format, ...)
```
### sscanf : 문자열 매개변수를 통해 입력을 받는다.
```c
int sscanf(char *string, char *format, arg1, arg2, ...)
```

## 7.5. File Access
여기서는 파일을 액세스하는 프로그램을 작성한다. 이 작업을 필요로 하는 프로그램으로 cat이 있다. cat은 여러개 파일의 내용을 표준 출력으로 보낸다. 즉 몇개 파일의 내용을 모아서 화면에 표시해준다. 예를 들어
```bash
cat x.c y.c
```
는 터미널에 x.c 파일과 y.c의 내용을 출력한다.

문제는 x.c나 y.c 같은 파일 이름을 프로그램 내에서 어떻게 처리하느냐 하는 것이다.
규칙은 간단하다. 읽거나 쓰기 전에 파일은 라이브러리 함수 fopen에 의해 열리면 된다.
fopen은 x.c 따위의 이름을 받아들여서 파일을 읽고 쓰기 위해 사용하는 포인터를 리턴한다.

이 포인터는 파일 포인터라고 불리며 파일에 관한 정보를 포함하는 구조체를 가리키는데, 이 구조체에는 버퍼의 위치와 버퍼 내에서의 문자의 위치, 파일이 읽기 위한 것인지 쓰기 위한 것인지, 에러나 EOF를 만나지 않았는지 등의 정보가 들어 있다.

사용자는 세부 사항을 알 필요가 없다. `<stdio.h>`에 있는 표준 입출력 정의에 FILE이라는 구조체의 정의가 있기 때문이다. 파일 포인터를 위해서는 단지 다음과 같은 선언만 하면 된다.

### 파일 포인터 선언
```c
FILE *fp; // 파일을 가리키는 포인터다
FILE *fopen(char *name, char *mode);
// 파일을 가리키는 포인터를 리턴한다.
```
FILE은 구조체의 이름이 아니라 데이터 타입의 이름이고 typedef(구조체 장에서 배웠던 커스텀 타입 디파인)에 의해 구현된다.

프로그램에서 fopen은
```c
fp = fopen(name,mode);
```
와 같이 쓴다.

fopen의 첫번째 매개변수는 문자열로 이루어진 파일의 이름이고, 두번째 매개변수는 문자열로 이루어진 mode인데 r(read), w(write), a(append) 가 있다.

만일 writing과 appending 위한 파일이 없다면 파일은 새로 만들어진다. writing으로 이미 존재하는 파일을 열면 기존의 내용은 지워진다. 

존재하지 않는 파일을 읽는 것은 에러이며 에러에는 허가되지 않는 파일을 읽을 경우 등 여러가지 원인이 있다. 만약 에러가 있을 때 fopen은 NULL을 리턴한다.

다음으로 필요한 것은 열린 파일을 읽거나 쓰는 방법이다. 이를 위한 방법에는 여러가지가 있는데 그중 getc와 putc가 가장 간단하다.
### getc
getc는 파일로 부터 차례대로 한문자씩 읽어 리턴한다. getc에서는 사용하는 파일의 포인터가 필요하다. 파일의 끝이거나 에러가 발생하면 EOF를 리턴한다.
```c
int getc(FILE *fp)
```

### putc
putc는 문자 c를 fp파일로 쓰고 쓰여진 문자를 리턴한다. 에러가 발생했다면 EOF를 쓰고 EOF를 리턴한다.
```c
int putc(int c, FILE *fp)
```

C프로그램이 처음 수행될 때 OS환경은 세개의 파일을 자동적으로 열고 세개 파일을 이ㅜ한 포인터를 배정한다. 이 파일들은 표준출력, 표준 입력과 표준 에러 출력이다.

이에 대응하는 파일 포인터는 stdin, stdout, stdeff로 불리고 `<stdio.h>`에서 선언되어 있다. 대개 stdin은 키보드로 받고 stdout, stderr은 터미널에 출력하지만 파일이나 파이프로 출력되는 위치를 바꿀 수 있다.

getchar와 putchar는 getc, putc, stdin, stdout으로 정의될 수도 있다.
```c
#define getchar() getc(stdin)
#define putchar(c) putc((c),stdout)
//getchar()라는 함수에 getc(stdin)을 할당한 거다.
//putchar(c)라는 함수에 putc((c),stdout)을 할당한 거다.
```

파일의 정형화된 입력과 출력을 수행하기 위해 fscanf, fprintf를 사용할 수 있다. 첫번째 매개변수가 파일의 포인터인 것을 제외하면 scanf, printf와 같다. 두번째 매개변수는 포맷문자열이다.
```c
int fscanf(FILE *fp, char *format, ...)
int fprintf(FILE *fp, char *format, ...)
```
이런 것을 바탕으로 우리는 이제 파일의 내용을 원하는 곳으로 출력하는 cat프로그램을 만들 수 있다. 만약 CLI에서 매개변수가 있다면 이들은 파일이름이나 기타 지시를 위한 것으로 해석되고 그렇지 않다면 우리가 직접입력하는 것을 처리한다.

```c
#include <stdio.h>

main(int argc, char *argv[]){
  FILE *fp;
  void filecopy(FILE *, FILE *);

  if(argc==1)
    // 5장에서 배운것처럼 argv[0]은 자기 자신의 이름이다.
    // 따라서 argc 즉 매개변수의 갯수가 1이라면
    // 터미널에서 아무 매개변수도 들어오지 않은 것이다.
    filecopy(stdin,stdout);
    // 이 때는 입력과 출력을 터미널에서 한다.
  else
    while(--argc>0){
      if((fp = fopen(*++argv,"r")) == NULL){
        // 해당하는 파일이 없으면 없다고 출력해준다.
        printf("cat : can't open %s\n", *argv);
        return 1;
      }else{
        filecopy(fp,stdout);
        // 여기서는 표준출력(즉 터미널)에 파일의 내용을 카피,
        // 즉 출력해주었다.
        // 즉 stdout을 파일 취급했다.
        // 내부적으로 stdout은 받은 문자열을
        // 터미널로 출력해준다.
        fclose(fp);
      }
    }
  return 0;
}

void filecopy(FILE *ifp, FILE *ofp){
  // ifp : input file pointer
  // ofp : output file pointer
  int c;
  while((c=getc(ifp))!=EOF){
    putc(c,ofp);
  }
}
```
다음의 함수 fclose는
```c
int fclose(FILE *fp)
```
fopen의 역기능을 가진다. 이 함수는 fopen에 의해 설정된 external name과 파일 포인터 사이의 연결 상태를 해제하고 파일 포인터를 다른 파일에 재사용할 수 있게 한다. 또한 putc의 출력문자를 저장하는 버퍼를 없애 준다는 것이다.
fclose는 프로그램이 정상적으로 끝났을 때는 각자의 열린 파일에 대해 자동적으로 호출된다. 즉 자동으로 포인터를 해제한다.
## 7.6. Error Handllng-Stderr and Exit
cat함수의 에러 처리 방법은 그다지 좋지 않다. 만약 파일 중 하나가 어떤 이유로 접근할 수 없을 때, 에러메시지가 출력문의 끝에서 나타난다. 출력을 파이프라인을 통해 파일로 저장했다면 이런 에러가 파일에 들어가는 것은 곤란하다.

위의 문제를 해결하기 위해서 stderr로 불리는 또 하나의 stream을 stdin, stdout과 같은 방법으로 프로그램에서 할당하자. 출력을 터미널 또는 파일 어디로 지정하든 stderr의 에러문은 터미널에 나타난다.

```c
#include <stdio.h>

main(int argc, char *argv[]){
  FILE *fp;
  void filecopy(FILE *, FILE *);
  char *prog = argv[0];
  // prog는 에러 출력시 프로그램 이름을 나타내기 위해 할당했다.

  if(argc==1)
    filecopy(stdin,stdout);
  else
    while(--argc>0){
      if((fp = fopen(*++argv,"r")) == NULL){
        // 해당하는 파일이 없으면 없다고 출력해준다.
        fprintf(stderr,"%s : can't open %s\n",prog,*argv);
        // 에러가 발생하면 프로그램 이름과
        // 에러가 발생한 파일 이름을 출력한다.
        exit(1);  
      }else{
        filecopy(fp,stdout);
        fclose(fp);
      }
    }
  if(ferror(stdout)){
    fprintf(stderr, "%s: error writing stdout\n", prog);
    exit(2)
  }
  exit(0);
}
```
프로그램은 두가지 방식으로 에러를 알린다.

첫째, fprintf에 의해 만들어진 에러메시지를 stderr로 보내면 터미널에 나타나게된다. 프로그램 이름을 argv[0]으로 부터 포함했으므로 다른 프로그램과 함께 사용되더라도 에러의 근원지를 알 수 있다.

둘째, 표준 라이브러리 함수 exit을 사용한다. 이것이 호출되면 프로그램 수행이 끝나게 된다. exit의 리턴 값은 다른 프로그램에서도 사용할 수 있으므로 그 프로그램 수행의 성공여부를 검사할 수 있다. exit이 0을 리턴하게 되면 모든 게 잘되고 있는 것이고, 0이 아닌 값을 리턴하면 비정상적이라는 뜻이다. exit은 열린 파일에 대해 fclose를 호출하며 버퍼를 지우고 파일을 닫는다.

**throw의 전신 같다!**

main함수에 return _expr_ 으로 표현하거나 exit(_expr_)으로 표현하는 것은 같은 표현이다.
exit은 다른 함수로부터 호출할 수 있는 유리한 점을 가지고 있다. ferror는 fp에 에러가 발생한다면 0이 아닌 값을 리턴한다(그래서 위의 조건문식이 올바르게 작동하는 것이다).

출력 에러는 매우 드물긴 하지만 저장공간(HDD)이 꽉차있을 경우 발생할 여지가 있다. 그렇기 때문에 프로그램에서 이 점을 잘 검사해야 한다. feof(FILE *)는 ferror의 유사형이다. 이 함수는 파일의 끝을 발견하면 0이 아닌 값을 리턴한다(EOF!).

## 7.7. Line Input and Output
표준 라이브러리는 이전 장들에서 사용한 getline 함수와 유사한 fgets 입력함수를 가지고 있다.
```c
char *fgets(char *line, int maxline, FILE *fp)
```
fgets는 다음 라인(`\n`를 포함한)을 파일 fp로부터 문자열인 line에 읽어 들이는데, 최대 maxline-1 의 문자를 읽을 수 있다. 입력 완료된 라인은 '\0'에 의해 종료된다. 보통 fgets는 line을 리턴하는데, 파일의 ㄲ끝이거나 에러를 만났을 시에는 NULL을 리턴한다. 

출력함수 fputs는 '\0'을 포함하지 않는 문자열을 파일에 출력시킨다.
```c
int fputs(char *line, FILE *fp)
```
에러가 발생하면 EOF를 리턴하고, 나머지 경우에는 0을 리턴한다.

gets와 puts는 stdin과 stdout과 stdout에 작용된다는 점이 fgets, fputs와 다른점이다(fgets, fputs의 f가 상징하듯 이 함수들은 파일에 적용된다).
gets는 마지막의 '\n'을 제거하지만 puts는 그것을 추가한다.

```c
char *fgets(char *s, int n, FILE *iop){
  // iop라는 파일로부터 라인 s를 최대 길이 n까지 읽고, 읽은 라인을 반환하는 함수다.
  register int c;
  register char *cs;
  cs = s;
  while(--n > 0 && (c=getc(iop)) != EOF)
    // n 은 maxline이므로 maxline개 까지만 받는다.
    // c 는 문자 하나를 받는다.
    if((*cs++ = c) == '\n')
      // cs라는 문자열의 인덱스에 c를 저장하고 1증가 시킨다.
      // 그런데 동시에 이게 '\n'이 었다면 라인의 끝이므로 종료한다.
      break;
    *cs = '\0';
    // 마지막에는 \0을 할당한다.
    return (c == EOF && cs == s) ? NULL : s;
    // 끝이 났따면 null을 리턴, 아니라면 라인을 리턴한다.
}

char *fputs(char *s, FILE *iop){
  int c;

  while(c = *s++){
    putc(c,iop);
    // 라인 s에서 '\0'이 나오기 전까지 한글자씩읽어 iop에 집어넣는다.
  }
  return ferror(iop) ? EOF : 0;
}
```
fgets를 사용해서 getline을 작성하는 것은 어렵지 않다.
```c
int getline(char *line, int max){
  if(fgets(line,max,stdin) == NULL){
    return 0;
  }else{
    return strlen(line);
  }
}
```

## 7.8. Miscellaneous Functions
표준 라이브러리는 상당히 다양한 함수를 제공한다. 이 절에서는 그중 자주 쓰이는 것에 대해 설명했다.

### 문자열 조작
`<string.h>`에 있는 함수들은 다음과 같다.
매개변수의 이름에서 s,t 는 char * 이고, c와 n은 int이다.
|함수|기능|
|-|-|
|strcat(s,t)|t를 s의 끝에 연결시킨다.|
|strncat(s,t,n)|t중 n개의 문자를 s의 끝에 연결시킨다.|
|strcmp(s,t)|s-t를 리턴한다.|
|strncmp(s,t,n)|strcmp와 같지만 처음 n개의 문자만이 대상이다.|
|strcpy(s,t)|s에 t를 복사한다.|
|strncpy(s,t,n)|t의 n개 문자를 s에 복사한다.|
|strlen(s)|s의 길이를 리턴한다.|
|strchr(s,c)|s에서 처음 발견된 문자 c의 포인터를 리턴하거나 존재하지 않으면 <br> NULL을 리턴한다.|
|strrchr(s,c)|s에서 마지막에 발견된 문자 c의 포인터를 리턴하거나 존재하지 않으면 <br>NULL을 리턴한다.|

### 문자분류와 변환
`<ctype.h>`의 함수는 다음과 같다. c는 unsigned char로 나타낼 수 있는 int거나 EOF이다.
`