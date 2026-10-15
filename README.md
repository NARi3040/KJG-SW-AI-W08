# SW-AI-W07 · KAIST Pintos (x86-64) Project 1: Threads

크래프톤 정글 SW-AI Lab 13기 7주차 팀 프로젝트입니다. KAIST Pintos(x86-64)의 Project 1(Threads)을 구현했고, 다음 팀이 이어서 작업할 수 있도록 진행 상황과 구현 방식을 문서로 남깁니다.

> 이 저장소는 **KAIST Pintos(64비트)** 기준입니다. Stanford Pintos(32비트) 자료는 함수 이름, 구조체, 레지스터 이름이 다를 수 있으니 이 저장소의 코드와 먼저 대조해 주세요.
> 공식 문서: https://casys-kaist.github.io/pintos-kaist/

## 팀 구성

<table align="center">
  <tr>
    <td align="center" width="33%">
      <a href="https://github.com/NARi3040"><img src="https://github.com/NARi3040.png?size=200" width="150" alt="박준호"></a><br><br>
      <a href="https://github.com/NARi3040"><b>박준호</b></a>
    </td>
    <td align="center" width="33%">
      <a href="https://github.com/dohyunrho"><img src="https://github.com/dohyunrho.png?size=200" width="150" alt="노도현"></a><br><br>
      <a href="https://github.com/dohyunrho"><b>노도현</b></a>
    </td>
    <td align="center" width="33%">
      <a href="https://github.com/jye-1123"><img src="https://github.com/jye-1123.png?size=200" width="150" alt="지영은"></a><br><br>
      <a href="https://github.com/jye-1123"><b>지영은</b></a>
    </td>
  </tr>
</table>

### 학습 및 코드 관리 방식

- 스레드 스케줄링을 완성하는 것보다 **공부을 우선**으로 진행했습니다.
- 기능 단위로 구현했습니다.
- 코어타임에 모여 코드 리뷰를 한 뒤, 살아남은 코드만 `main`에 머지합니다.

## 현재 상태

**Priority Scheduling까지 완료**했고, Advanced Scheduler(MLFQS)는 미구현입니다.

| 영역 | 상태 |
| --- | --- |
| Alarm Clock | 완료 |
| Priority Scheduling (preemption, FIFO) | 완료 |
| Priority Donation (nested, multiple, chain) | 완료 |
| Advanced Scheduler (MLFQS) | **미구현** (스텁만 존재) |

`threads` 테스트는 20개 통과, 6개 실패이며 실패는 모두 MLFQS입니다(`mlfqs-load-1`, `mlfqs-load-60`, `mlfqs-load-avg`, `mlfqs-recent-1`, `mlfqs-nice-2`, `mlfqs-nice-10`).
## 문서

다음 팀은 위에서부터 순서대로 읽는 것을 추천합니다.

| 문서 | 내용 |
| --- | --- |
| [스레드 사용 가이드](docs/thread-guide.md) | 이 저장소의 스레드가 어떻게 동작하고 어떻게 쓰면 되는지, 지켜야 할 불변식 |
| [구현 방식](docs/implementation.md) | Alarm Clock, Priority Scheduling, Priority Donation 설계와 이유, 알려진 한계 |
| [개발 환경과 테스트](docs/dev-environment.md) | DevContainer, 빌드와 테스트 실행, pintos-util |
| [주석 규칙](docs/comment-style.md) | Doxygen 주석 형식과 HTML 문서 생성(Ubuntu, macOS, Windows) |

핵심 규칙 세 가지만 먼저 기억해 주세요.

- `ready_list`는 항상 priority 내림차순입니다. 그 안에 있는 스레드의 priority를 바꾸면 반드시 `thread_requeue()`를 호출해야 합니다.
- donation은 lock에만 적용됩니다. 세마포어는 priority를 전달하지 않습니다.
- 인터럽트는 끄기 전 상태로 복원합니다(`intr_set_level (old_level)`).

## 빠른 시작

VSCode에서 `Dev Containers: Reopen in Container`로 열고, 컨테이너 터미널에서 실행합니다.

```bash
cd pintos/threads
make check                 # 전체 테스트
```

한 테스트만 돌리거나 `pintos` 명령이 안 잡힐 때의 주의사항은 [개발 환경과 테스트](docs/dev-environment.md)에 있습니다.
