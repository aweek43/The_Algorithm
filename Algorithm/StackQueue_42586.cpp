#include "Headers.h"

// https://programmers.co.kr/learn/courses/30/lessons/42586


// 요약: 하루마다 progresses에 speeds를 더하며 첫번째 작업이 100%가 초과할 경우 그 뒤의
// 100% 초과하는 작업들을 한번에 배포하고 삭제하는 로직이다.
// 문제 주제에 맞게 Queue를 사용하고 싶었으나 하루마다 progresses에 speeds를 더하는 과정에서
// 계속 새로운 Queue에 넣는게 비효율적이라고 판단해 index 접근이 가능한 vector를 사용했다.
// 다만 최소한의 Queue의 성질을 이용하도록 pop()을 구현했다.
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