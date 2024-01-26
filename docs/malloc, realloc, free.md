```c
#include <stdlib.h>

void * malloc(size_t size);

void * realloc(void * ptr, size_t size);

void free(void *ptr);
```  

# DESCRIPTION

`malloc()`, `realloc()` 함수는 메모리를 할당합니다.
할당된 메모리는 알티벡 및 SSE 관련 유형을 포함한 모든 데이터 유형에 사용할 수 있도록 정렬됩니다.
`free()` 함수는 앞의 할당 함수를 통해 생성된 할당을 해제합니다.

`malloc()` 함수는 크기 바이트의 메모리를 할당하고 할당된 메모리에 대한 포인터를 반환합니다.

`realloc()` 함수는 `ptr`이 가리키는 할당의 크기를 크기로 변경하려고 시도한 후 `ptr`을 반환합니다.
`ptr`이 가리키는 메모리가 할당을 확대할 공간이 충분하지 않으면, `realloc()`은 새 할당을 만들고, `ptr`이 가리키는 이전 데이터를 새 할당에 맞는 만큼 복사한 다음, 이전 할당을 해제하고, 할당된 메모리에 대한 포인터를 반환합니다.
`ptr`이 NULL이면, `realloc()`은 `size` 바이트에 대해 `malloc()`을 호출하는 것과 동일합니다.
크기가 0이고 `ptr`이 NULL이 아닌 경우, 최소 크기의 새 객체가 할당되고 원래 객체는 해제됩니다.
`calloc(3)`로 할당된 영역을 확장할 때, `realloc(3)`은 추가 메모리도 0으로 채워진다는 것을 보장하지 않습니다.

`free()` 함수는 `ptr`이 가리키는 메모리 할당을 해제합니다. `ptr`이 NULL 포인터이면 아무 작업도 수행되지 않습니다.

# RETURN VALUES

성공하면 `malloc()`, `realloc()` 함수는 할당된 메모리에 대한 포인터를 반환합니다.
에러가 발생하면 NULL 포인터를 반환하고 errno를 ENOMEM으로 설정합니다.

`realloc()`의 경우, 재할당이 실패해도 입력 포인터는 여전히 유효합니다.

`free()` 함수는 값을 반환하지 않습니다.

# DEBUGGING ALLOCATION ERRORS

애플리케이션의 할당 오류를 디버깅하는 데 도움이 되는 다양한 기능이 제공됩니다.
이러한 기능은 주로 환경 변수를 통해 제어됩니다.
인식되는 환경 변수와 그 의미는 아래에 설명되어 있습니다.

# ENVIRONMENT

다음 환경 변수는 할당 관련 함수의 동작을 변경합니다.

- **MallocDebugReport**
	설정하면 메시지가 기록되는 위치를 지정합니다. 표준 오류 스트림에 메시지를 쓰려면 "stderr", 모든 메시지를 삭제하려면 "none", 크래시를 일으키려는 조건에 대해서만 표준 오류에 메시지를 쓰려면 "crash"로 설정합니다.
	설정하지 않으면, 터미널로 보이는 경우(즉, isatty(STDERR_FILENO)가 0이 아닌 값을 반환하면 값을 반환하는 경우), 그렇지 않으면 버려집니다.

- **MallocGuardEdges** 
	설정한 경우 각 큰 블록의 앞뒤에 가드 페이지를 추가합니다.
	MallocDoNotProtectPrelude 설정한 경우, MallocGuardEdges를 무시하고 큰 블록의 앞에 가드 페이지를 추가하지 않습니다.

- **MallocDoNotProtectPostlude** 
	설정한 경우, MallocGuardEdges를 무시하고 큰 블록의 뒤에 가드 페이지를 추가하지 않습니다.

- **MallocStackLogging** 
	이 옵션을 설정하면 기본 동작은 모든 할당 및 할당 해제 이벤트를 스택과 함께 디스크 로그에 기록하는 것입니다.
	`leaks(1)` 및 `malloc_history(1)`와 같은 도구를 사용할 수 있습니다.
	시스템 콜 및 mach 트랩(예: mmap(1))에 의해 할당된 가상 메모리 영역의 할당만 기록하려면 "vm"으로 설정합니다.
	가상 메모리 영역이 아닌 malloc(3) 및 관련 인터페이스를 통한 할당만 기록하려면 "malloc"으로 설정합니다.
	기록이 아닌 현재 할당만 기록하려면 "lite"로 설정합니다. 이러한 기록은 디스크 로그가 아닌 인메모리 데이터 구조에 의해 기록됩니다.

- **MallocStackLoggingNoCompact** 
	이 옵션을 설정하면 모든 스택을 malloc_history 프로그램과 호환되는 방식으로 기록합니다.

- **MallocStackLoggingDirectory** 
	이 옵션을 설정하면 스택 로그를 기본 위치(/tmp)에 저장하는 대신 지정된 디렉터리에 기록합니다.

- **MallocScribble** 
	설정하면 할당된 메모리를 0xAA 바이트로 채웁니다. 이렇게 하면 새로 할당된 메모리의 내용을 가정하는 프로그램이 실패할 가능성이 높아집니다. 또한 이 옵션을 설정하면 할당 해제된 메모리를 0x55 바이트로 채웁니다.
	이렇게 하면 더 이상 할당되지 않은 메모리에 액세스하여 프로그램이 실패할 가능성이 높아집니다.
	해제된 메모리가 내부적으로 관리되는 방식에 따라 0x55 패턴이 할당 해제된 메모리 블록의 일부에 나타나지 않을 수도 있습니다.

- **MallocCheckHeapStart `<s>`** 
	설정된 경우, MallocCheckHeapEach에 지정된 대로 매 `<n>`마다 주기적 힙 검사를 시작하기 전에 대기할 할당 횟수 `<s>`를 지정합니다.
	MallocCheapStart가 설정되어 있지만 MallocCheapEach가 지정되지 않은 경우 기본 검사 반복 횟수는 1000 입니다.

- **MallocCheckHeapEach `<n>`**
	설정하면 매 `<n>` 연산마다 힙에 대한 일관성 검사를 실행합니다.
	MallocCheckHeapEach는 MallocCheckHeapStart가 설정된 경우에만 의미가 있습니다.

- **MallocCheckHeapSleep `<t>`**
	MallocCheckHeapStart가 설정되어 있고 힙 손상이 감지된 경우 절전 모드(디버거가 연결될 때까지 대기)로 전환할 시간(초)을 설정합니다.
	기본값은 100초입니다. 이 값을 0으로 설정하면 전혀 절전 모드로 전환되지 않습니다. 이 값을 음수로 설정하면 힙 손상이 처음 감지될 때만 (양수 초 동안) 절전 모드로 전환됩니다.

- **MallocCheckHeapAbort `<b>`** 
	MallocCheckHeapStart가 설정되어 있고 이 값이 0이 아닌 값으로 설정되어 있으면 힙 손상이 감지되면 잠자기 대신 abort(3)가 호출되도록 합니다.

- **MallocErrorAbort** 
	설정하면 이전에 해제된 포인터에서 free(3)를 호출하는 등 malloc(3) 또는 free(3)에서 오류가 발생한 경우 abort(3)가 호출됩니다.

- **MallocCorruptionAbort** 
	MallocErrorAbort와 유사하지만 메모리 부족 상태에서는 중단하지 않으므로 메모리 손상을 유발하는 오류만 포착하는 데 더 유용합니다.
	MallocCorruptionAbort는 항상 64비트 프로세스에 설정됩니다.

- **MallocHelp** 
	이 옵션을 설정하면 할당 관련 함수가 주의하는 환경 변수 목록을 간단한 설명과 함께 인쇄합니다. 목록은 이 문서와 일치해야 합니다.

