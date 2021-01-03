#include "Headers.h"

// https://programmers.co.kr/learn/courses/30/lessons/42576?language=cpp

// ���: ���� Ư���� 2�� for���� ���� �� list�� ���ص� ������,
// Hash��� ������ �����ϱ� ���� unordered_map�� ����� key�� value�� ���� Ǯ����.
string Hash_42576(vector<string> participant, vector<string> completion)
{
    string answer = "";
    unordered_map<string, int> completion_map; // int�� 0���� �ʱ�ȭ��
    for (auto comple : completion)
    {
        completion_map[comple]++; // �Ϸ��� ������ 1�� ����
    }

    for (auto parti : participant)
    {
        if (completion_map[parti] != 0)
        {
            completion_map[parti]--;
        }
        else // value�� 0�� ���� completion�� ���ų� �ٸ� �������ε��� �̹� ������ ȥ�ڸ� ���� ���
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