#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;


void print(string answer);
void print(vector<int> answer);
void print(int answer);
string Hash_42576();
vector<int> StackQueue_42586();
int StackQueue_42583();


int main()
{
	// write question function
	auto answer = StackQueue_42583();

	print(answer);
	return 0;
}

/*
// https://programmers.co.kr/learn/courses/30/lessons/42583?language=cpp
// 요약: 다리를 Queue로 만들고 트럭 또는 공백(0)을 넣어 트럭의 위치까지 알 수 있게 했다.
// 트럭이 진입 가능할 경우 queue에 넣고 매 초마다 pop()을 하고 다음 트럭 또는 공백을 넣어
// 다리 위의 트럭을 한칸씩 진행시킨다.
*/
int StackQueue_42583(int bridge_length, int weight, vector<int> truck_weights)
{
    int answer = 0;
    int onBridge_weight = 0; // 현재 다리 위의 트럭 무게 합
    queue<int> onBridge; // 다리 위의 트럭과 위치
    for (int i = 0; i < bridge_length; ++i)
        onBridge.push(0);

    while (truck_weights.size() || onBridge.size()) // 대기 중, 다리 위 트럭이 없을 때 까지
    {
        onBridge_weight -= onBridge.front();
        onBridge.pop(); // 트럭 1칸 진행
        if (truck_weights.size() == 0) // 더이상 대기 중인 트럭이 없는 경우
        {
            answer += bridge_length; // 남은 다리 위 트럭을 한번에 진행시킴
            break;
        }
        if (onBridge_weight + truck_weights.front() <= weight) // 트럭 추가 가능
        {
            onBridge.push(truck_weights.front()); // 대기 중인 트럭을 다리 위에 추가
            onBridge_weight += truck_weights.front();
            truck_weights.erase(truck_weights.begin());
        }
        else
        {
            onBridge.push(0); // 다리 위에 공백 추가
        }
        answer++;
    }

    return answer;
}
int StackQueue_42583()
{
    return StackQueue_42583(2, 10, { 7,4,5,6 });
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42586
// 요약: 하루마다 progresses에 speeds를 더하며 첫번째 작업이 100%가 초과할 경우 그 뒤의
// 100% 초과하는 작업들을 한번에 배포하고 삭제하는 로직이다.
// 문제 주제에 맞게 Queue를 사용하고 싶었으나 하루마다 progresses에 speeds를 더하는 과정에서
// 계속 새로운 Queue에 넣는게 비효율적이라고 판단해 index 접근이 가능한 vector를 사용했다.
// 다만 Queue의 성질을 이용하도록 pop()을 구현했다.
*/
int queue_pop(vector<int>& queue)
{
    int pop = queue[0];
    queue.erase(queue.begin());
    return pop;
}
vector<int> StackQueue_42586(vector<int> progresses, vector<int> speeds)
{
    vector<int> answer;
    int release; // 한번에 배포되는 개수
    while (progresses.size())
    {
        release = 0;
        for (int i = 0; i < progresses.size(); ++i) // 하루가 지나 progress들에 진도 더함
        {
            progresses[i] += speeds[i];
        }

        while (progresses.size() && progresses[0] >= 100) // 배포 가능한 경우 차례대로 배포
        {
            queue_pop(progresses);
            queue_pop(speeds);
            release++;
        }

        if (release > 0) // 배포되었으면 배포된 개수 기록
            answer.push_back(release);
    }
    return answer;
}
vector<int> StackQueue_42586()
{
    return StackQueue_42586({ 93, 30, 55 }, { 1, 30, 5 });
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42576?language=cpp
// 요약: 문제 특성상 2중 for문을 돌며 두 list를 비교해도 되지만,
// Hash라는 주제에 부합하기 위해 unordered_map을 사용해 key로 value를 비교해 풀었다.
*/
string Hash_42576(vector<string> participant, vector<string> completion)
{
    string answer = "";
    unordered_map<string, int> completion_map; // int는 0으로 초기화됨
    for (auto comple : completion)
    {
        completion_map[comple]++; // 완료한 선수에 1을 더함
    }

    for (auto parti : participant)
    {
        if (completion_map[parti] != 0)
        {
            completion_map[parti]--;
        }
        else // value가 0인 경우는 completion에 없거나 다른 동명이인들이 이미 완주해 혼자만 남은 경우
        {
            answer = parti;
            break;
        }
    }

    return answer;
}
string Hash_42576()
{
    return Hash_42576({ "mislav", "stanko", "mislav", "ana" }, { "stanko", "ana", "mislav" });
}

void print(int answer) { cout << answer << endl; }
void print(string answer) { cout << answer << endl; }
void print(vector<int> answer) { for (int ans : answer) cout << ans << endl; }