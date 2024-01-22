# Subject 번역

## General Instructions

- 이 프로젝트는 동료평가만 진행됩니다. 프로젝트의 파일 이름과 디렉토리 구조를 원하는대로 지정할 수 있지만, 아래의 규칙을 따라야만 합니다.
- 라이브러리의 이름은 반드시 `libft_malloc_$HOSTTYPE.so` 여야합니다.
- `Makefile`과 같은 도구를 통해 프로젝트를 컴파일해야 하며, 자주 사용되는 규칙이 포함되어 있어야 합니다. 반드시 필요할 때에만 리컴파일 & 리링크 되어야 합니다.
- `Makefile`은 반드시 `$HOSTTYPE` 환경 변수가 존재하는지 확인하고, 존재하지 않는다면 아래의 규칙을 통해 변수를 할당해야 합니다.
```Makefile
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
```
- `Makefile`은 반드시 `libft_malloc_$HOSTTYPE.so`를 가리키는 심볼릭 링크인 `libft_malloc.so`를 생성해야 합니다. 예를 들어, `libft_malloc.so -> libft_malloc_intel-mac.so` 와 같습니다.
- 영리한 사람이라면 `malloc`에 라이브러리를 사용할 것입니다. 리포지토리 루트에 자체 Makefile을 포함한 폴더 libft도 제출하세요. Makefile은 라이브러리를 컴파일한 다음 프로젝트를 컴파일해야 합니다.
- 할당을 관리하기 위한 전역 변수와 thread-safe를 위한 전역 변수가 허용됩니다.
- 프로젝트는 norm 없이도 클린코드여야 하며, 그렇지 않을경우 0점을 받게 됩니다.
- 에러를 신중하게 처리하세요. 당신의 함수가 UB나 SEGV로 이어져서는 안됩니다.
- 맨데토리 파트에서는 다음의 함수가 허용됩니다.
	- mmap(2)
	- munmap(2)
	- getpagesize(2 또는 3, OS에 따라 다름)
	- getrlimit(2)
	- libft에서 사용 가능한 모든 함수
	- pthread 라이브러리의 모든 함수
- 보너스 파트에서는 다른 함수 사용이 가능합니다. 그러나 디펜스 단계에서, 해당 함수의 사용이 정당함을 증명해야 합니다.

## Mandatory part

이 미니 프로젝트는 동적 메모리 관리 라이브러리를 작성하는 것입니다. 이미 사용 중인 일부 프로그램을 수정하거나 다시 컴파일하지 않고도 사용할 수 있도록 하기 위해, 다음 3개의 libc 함수를 재구현합니다.

함수 프로토타입은 반드시 시스템과 동일해야만 합니다.
```c
#include <stdlib.h>

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
```

- `malloc()`함수는 `size` 바이트 만큼 메모리를 할당하고, 그것에 대한 포인터를 반환합니다.
- `realloc()` 함수는 `ptr`이 가리키는 할당의 크기를 `size`로 변경하려고 시도하고 `ptr`을 반환합니다. `ptr`이 가리키는 메모리 할당을 확대할 공간이 충분하지 않으면, `realloc()`은 새 할당을 생성하고, `ptr`이 가리키는 이전 데이터를 새 할당에 맞는 만큼 복사한 다음, 이전 할당을 해제하고 할당된 메모리에 대한 포인터를 반환합니다.
- `free()`함수는 `ptr`이 가리키는 메모리를 해제합니다. 만약 `ptr`이 **NULL** 이라면, 아무런 연산이 수행되지 않습니다.
- 에러가 발생한다면, `malloc()`과 `realloc()` 함수는 **NULL** 포인터를 반환합니다.
- 메모리 영역을 시스템에 요구하고 반환받기 위해 `mmap()`과 `munmap()`을 사용해야 합니다.
- libc의 `malloc` 함수 없이, 프로젝트의 내부 기능을 위한 당신만의 메모리 할당을 관리해야 합니다.
- 성능적인 이유로, `mmap()`과 `munmap()` 의 호출 수를 제한해야 합니다. 반드시 메모리 영역을 _**사전 할당**_ 해야하며, _**작은**_ `malloc`과 _**중간**_ `malloc`을 보관해야 합니다.
- 각 영역은 최소 100개의 할당을 포함합니다.
	- 1부터 $n$ 바이트의 **`TINY`** `malloc` 들은 $N$ 바이트 크기의 영역에 보관됩니다.
	- $n + 1$부터 $m$ 바이트의 **`SMALL`** `malloc` 들은 $M$ 바이트 크기의 영역에 보관됩니다.
	- $m + 1$부터 그 이상 바이트의 **`LARGE`** `malloc` 들은 나머지 영역에 보관됩니다. 다시 말해, `mmap()`을 사용하는 그 자체의 영역에 보관됩니다.
- 속도(시스템 리콜 절약)와 메모리 절약 사이에서 적절한 절충점을 찾기 위해 $n$, $m$, $N$, $M$의 크기를 선택하는 것이 좋습니다.
- 또한 할당된 메모리 영역의 상태를 시각적으로 확인할 수 있는 함수를 작성해야 합니다. 프로토타입은 다음과 같습니다.:
	```c
	void show_alloc_mem();
	```
- 시각화는 다음과 같이 주소가 증가하는 방향으로 포맷팅 되어야 합니다.
```text
TINY: 0xA0000
OxA0020 - 0xA004A : 42 bytes
OxA006A - OxA00BE : 84 bytes
SMALL : OxAD000
OxAD020 - OxADEAD : 3725 bytes
LARGE : 0xB0000
OxB0020 - 0xBBEEF : 48847 bytes
Total : 52698 bytes
```

> 반드시 당신의 `malloc`으로 주어진 메모리를 정렬해야 합니다.

## Bonus part

- 멀티 쓰레드 프로그램에서 `malloc`의 사용을 관리합니다. (`pthread` 라이브러리를 사용하여 `thread-safe`하게 구현합니다.)
- 최대 점수를 얻으려면 다음과 같은 몇 가지 추가 기능(전체 목록은 아님)을 구현해야 합니다:
	- `malloc` 디버그 환경 변수를 관리합니다. `malloc` 시스템에서 이러한 기능을 모방하거나 직접 만들 수 있습니다. (주: MallocStackLogging 같은거 말하는듯?)
	- 할당 내역이나 할당된 영역의 헥사(hexa) 덤프와 같은 자세한 내용을 표시하는 `how _alloc_mem_ex()` 함수를 만듭니다.
	- 해제된 메모리를 조각 모음합니다. (`Defragment`)