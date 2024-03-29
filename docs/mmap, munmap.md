```c
#include <sys/mmap.h>

void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);

int munmap(void *addr, size_t len);
```

# mmap()

`mmap()` 시스템 콜은 addr에서 시작하여 최대 len 바이트까지 계속되는 페이지가 바이트 오프셋에서 시작하여 fd로 기술되는 객체에서 매핑되도록 합니다.
오프셋 또는 len이 페이지 크기의 배수가 아닌 경우 매핑된 영역이 지정된 범위를 넘어 확장될 수 있습니다. 매핑된 객체의 끝을 벗어나는 모든 확장은 0으로 채워집니다.

플래그에 MAP_FIXED가 지정되면 시스템은 지정된 주소에 매핑을 배치하려고 시도하며, 해당 위치에 이미 존재하는 매핑을 제거할 수도 있습니다.
MAP_FIXED가 지정되지 않은 경우, 시스템은 malloc(3) 및 기타 할당자를 통해 할당된 메모리를 포함하여 기존 매핑과 겹치지 않는 경우 addr에서 시작하는 주소 범위를 사용하려고 시도합니다.
그렇지 않으면 시스템은 기존 매핑과 겹치지 않는 매핑의 대체 주소를 선택합니다(구현 종속 알고리즘 사용).
다시 말해, 지정된 주소 범위가 이미 다른 것에 의해 매핑된 경우 MAP_FIXED가 없으면 시스템은 주소 공간에서 빈 위치를 찾으려고 시도합니다.
addr이 0이고 MAP_FIXED가 지정되지 않은 경우, 주소 공간의 기존 매핑과 겹치지 않도록 시스템에서 주소를 선택합니다.
모든 경우에 해당 지역의 실제 시작 주소가 반환됩니다.
MAP_FIXED를 지정한 경우 mmap이 성공하면 할당된 주소 범위의 이전 매핑이 모두 삭제됩니다.
MAP_FIXED가 지정되지 않은 경우 이전 매핑은 삭제되지 않습니다.

  
보호 기능(지역 접근성)은 다음 값을 비트-OR하여 prot 인수에 지정합니다:

- **PROT_NONE** 
	페이지에 액세스할 수 없습니다.
- **PROT_READ** 
	페이지를 읽을 수 있습니다.
- **PROT_WRITE** 
	페이지를 쓸 수 있습니다.
- **PROT_EXEC** 
	페이지를 실행할 수 있습니다.

하드웨어 제한으로 인해 일부 플랫폼에서는 PROT_WRITE가 PROT_READ를 의미할 수 있고, PROT_READ가 PROT_EXEC를 의미할 수 있습니다.
이식 가능한 프로그램은 이러한 플래그를 별도로 강제할 수 있는지에 의존해서는 안 됩니다.

`flags` 인자는 매핑된 객체의 유형, 매핑 옵션, 매핑된 페이지 사본에 대한 수정이 프로세스에 비공개(복사 후 쓰기)인지 아니면 다른 참조와 공유할 것인지 여부를 지정합니다.
공유, 매핑 유형 및 옵션은 플래그 인수에 다음 값을 비트-OR하여 지정합니다:

- **MAP_ANONYMOUS**
	MAP_ANON의 동의어.

- **MAP_ANON** 
	특정 파일과 연결되지 않은 익명 메모리를 매핑합니다. 오프셋 인자는 무시됩니다.
	Mac OS X 전용: MAP_ANON 영역을 만드는 데 사용되는 파일 설명자는 일부 Mach VM 플래그를 전달하는 데 사용할 수 있으며, 해당 영역과 연결된 플래그가 없는 경우 -1로 지정할 수 있습니다. Mach VM 플래그는 `<mach/vm_statistics.h>`에 정의되어 있으며 현재 mmap에 적용되는 플래그는 다음과 같습니다:
	- VM_FLAGS_PURGABLE - Mach 제거 가능(즉, 휘발성) 메모리를 생성합니다.
	- VM_MAKE_TAG(tag) - 8비트 태그를 영역에 연결하기 위함. `<mach/vm_statistics.h>`는 일부 사전 설정 태그(VM_MEMORY_ 접두사 포함)를 정의합니다. 사용자는 240~255 사이의 태그를 사용하는 것이 좋습니다. 태그는 도구에서 특정 메모리 영역을 식별하는 데 사용됩니다.

- **MAP_FILE** 
	일반 파일에서 매핑합니다. (기본 매핑 유형이므로 지정할 필요가 없습니다.)

- **MAP_FIXED** 
	시스템에서 지정된 주소와 다른 주소를 선택하도록 허용하지 않습니다. 지정된 주소를 사용할 수 없으면 `mmap()`이 실패합니다. MAP_FIXED가 지정된 경우 `addr`은 페이지 크기의 배수여야 합니다.

- **MAP_FIXED**
	요청이 성공하면 `mmap()`에 의해 설정된 매핑이 프로세스의 페이지에 대한 이전 매핑을 `addr`에서 `addr + len` 범위로 대체합니다.
	이 옵션의 사용은 권장하지 않습니다.

- **MAP_HASSEMAPHORE** 
	영역에 세마포어가 포함될 수 있으며 특별한 처리가 필요할 수 있음을 커널에 알립니다.

- **MAP_PRIVATE** 
	수정 사항을 비공개로 유지합니다(쓰기 시 복사 - Copy on Write).

- **MAP_SHARED** 
	수정 사항이 공유됩니다.

- **MAP_NOCACHE** 
	이 매핑의 페이지는 커널의 메모리 캐시에 유지되지 않습니다. 시스템의 메모리가 부족하면 MAP_NOCACHE 매핑의 페이지가 가장 먼저 회수됩니다.
	이 플래그는 지역성(locality)이 거의 없는 매핑을 위한 것으로, 커널에 이 매핑의 페이지가 가까운 시일 내에 다시 필요하지 않을 것 같다는 힌트를 제공합니다. 

이에 부합하는 애플리케이션은 MAP_PRIVATE 또는 MAP_SHARED를 지정해야 합니다.
close(2) 시스템 호출은 페이지 매핑을 해제하지 않습니다. 자세한 내용은 `munmap(2)`를 참조하세요.
현재 설계에서는 프로세스가 스왑 공간의 위치를 지정하는 것이 허용되지 않습니다.
향후에는 파일 설명자 인자가 스왑을 수행할 파일 또는 장치를 지정하는 추가 매핑 유형인 MAP_SWAP을 정의할 수 있습니다.

성공적으로 완료되면 `mmap()`은 매핑된 영역에 대한 포인터를 반환합니다. 그렇지 않으면 **MAP_FAILED** 값이 반환되고 오류를 나타내는 errno가 설정됩니다.

다음과 같은 경우 `mmap()` 시스템 호출이 실패합니다:

[EACCES] 플래그 PROT_READ가 prot 인자의 일부로 지정되었고 fd가 읽기를 위해 열려 있지 않습니다. 플래그 MAP_SHARED 및 PROT_WRITE가 플래그 및 prot 인수의 일부로 지정되었고 fd가 쓰기용으로 열려 있지 않습니다.
[EBADF] fd 인수가 유효한 열린 파일 설명자가 아닙니다.
[EINVAL] MAP_FIXED가 지정되었고 addr 인수가 페이지 정렬되지 않았거나 원하는 주소 공간의 일부가 사용자 프로세스의 유효한 주소 공간을 벗어난 곳에 있습니다.
[EINVAL] 플래그에 MAP_PRIVATE 또는 MAP_SHARED가 포함되지 않았습니다.
[EINVAL] len 인수가 음수이거나 0입니다. 이전에는 인수가 0인 경우 시스템 호출에서 오류를 반환하지 않았습니다. 아래의 호환성 섹션에서 다른 잠재적인 추가 제한 사항을 참조하십시오.
[EINVAL] offset 인수가 getpagesize(3)에서 반환된 페이지 크기에 따라 페이지 정렬되지 않았습니다.
[ENODEV] MAP_ANON이 지정되지 않았고 fd가 참조하는 파일이 매핑을 지원하지 않습니다.
[ENOMEM] MAP_FIXED가 지정되었고 addr 인수를 사용할 수 없습니다. MAP_FIXED가 지정되었고 지정한 주소 범위가 프로세스의 주소 공간 제한을 초과합니다. MAP_ANON이 지정되었고 사용 가능한 메모리가 부족합니다.
[ENXIO] 지정한 범위의 주소가 fd에 유효하지 않습니다.
[EOVERFLOW] 지정한 범위의 주소가 fd에 설정된 최대 오프셋을 초과합니다.

# munmap()

`munmap()` 시스템 호출은 지정된 주소 범위에 대한 매핑을 삭제하여 범위 내의 주소에 대한 추가 참조가 잘못된 메모리 참조를 생성합니다.

`munmap()`이 더티 페이지를 처리하는 방법은 매핑 해제되는 메모리 유형에 따라 다릅니다:

[Anonymous] 메모리가 익명 메모리이고 마지막 참조가 사라지는 경우 익명 메모리의 정의에 따라 내용이 삭제됩니다.
[System V Shared] 메모리 매핑이 시스템 V 공유 메모리를 사용하여 생성된 경우, 시스템 V 메모리 영역이 삭제되거나 시스템이 재부팅될 때까지 내용이 유지됩니다.
[File Mapping] 매핑이 파일의 데이터를 매핑하는 경우(맵_공유), 메모리가 더럽혀지면 결국 디스크에 다시 기록됩니다. 이 작업은 향후 어느 시점에 자동으로 수행됩니다(구현에 따라 다름). 참고: 메모리를 디스크에 강제로 다시 쓰게 하려면 msync(2)를 사용하세요.

`munmap()`이 완료된 후에도 메모리에 대한 다른 참조가 남아 있으면 메모리 자체에 아무 것도 기록되지 않으며 필요한 경우 메모리를 교체할 수 있습니다.
메모리는 마지막 참조가 사라질 때까지 계속 유지됩니다(System V Shared 메모리의 경우 위 참조).
성공적으로 완료되면 `munmap`은 0을 반환합니다. 그렇지 않으면 -1 값이 반환되고 오류를 나타내는 errno가 설정됩니다.

`munmap()`은 다음과 같은 경우 실패합니다:

[EINVAL] addr 매개 변수가 페이지 정렬되지 않았습니다(즉, 페이지 크기의 배수).
[EINVAL] len 매개 변수가 음수이거나 0입니다.
[EINVAL] 매핑 해제 중인 영역의 일부가 현재 유효한 주소 공간의 일부가 아닙니다.
