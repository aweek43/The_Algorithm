#include "Headers.h"

// https://programmers.co.kr/learn/courses/30/lessons/42576?language=cpp

// 요약: 문제 특성상 2중 for문을 돌며 두 list를 비교해도 되지만,
// Hash라는 주제에 부합하기 위해 unordered_map을 사용해 key로 value를 비교해 풀었다.
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