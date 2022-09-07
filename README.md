# 오목

<h3> 구현기능 </h3> <hr>

- 1:1 PVP(Player VS Player)모드 컴퓨터 한 대로 두 명의 플레이어가 한 번 씩 수를 두어 게임을 진행하는 방식
- AI 모드 한 명의 플레이어가 AI와 번갈아 가면서 수를 두어 게임을 진행하는 방식
- AI 모드는 각 경우마다 돌의 가중치를 정해 가중치가 높은 곳을 우선으로 돌을 놓는 방식으로 구현(MIN MAX 기법 참조)
- 스레드를 활용해 정해진 정해진 시간이 지난 후에 턴이 자동으로 넘어가도록 구현
- 메인화면에서 마우스 좌표값을 이용해 버튼 마우스오버 기능 구현
- 오목판 전체를 탐색하지 않고 수를 놓는 시점에 오목이 되는지 체크하여 시간 절약


<h3> 제작과정 </h3> <hr>
오목을 좋아해 많이 두던 시기에 AI 오목에게 크게 데인적이 있어 나도 한번 만들어보자는 식으로 오목 게임을 만들게 되었다. <br>
PVP를 구현하는 부분은 번갈아가며 돌의 색만 바꿔주고, 오목인지만 체크하면 되어 다소 쉬웠으나, <br>
오목 AI를 직접 만들어보니 신경써야되는 부분이 굉장히 많았다. <br>
가중치를 정해 돌을 계속 두어 반복하게 되면 최고의 결과값을 얻을 수 있겠지만, 시간이 매우 오려 걸린다는 단점이 있어<br>
탐색할 깊이 정해 탐색할 수 있도록 하였다. <br>
개발 초기에 타이머를 스레드로 구현하지 않았었는데, 시간이 가는 동안에 플레이어가 돌을 놓지 못하는 현상이 일어나
타이머는 스레드로 구현하게 되었다.

오목을 평소에 즐겨두지 않는 상대로는 괜찮은 승률을 보장했지만, 오목을 즐겨두거나 잘하는 상대는 하찮은 승률을 가져왔다.<br>
돌을 3개 혹은 4개를 연속으로 놓아 승리를 보장하는 3-3 혹은 3-4에 대한 특이 케이스에 대한 처리,<br>
오목판이 무한히 넓지 않고 크기가 정해져 있다는 점을 보안하지 못한 것 같다.<br> 

<h3> 실행과정 </h3><hr>

![image](https://user-images.githubusercontent.com/69779719/188831630-28f1c16a-ef2e-419f-984b-ea088709921d.png)

![image](https://user-images.githubusercontent.com/69779719/188831890-566ad137-e21c-4fd4-95b7-a4484a19c8d8.png)

<h3> 사용기술 </h3> <hr>
Windows APi, C/C++
<h3> ETC </h3> <hr>



