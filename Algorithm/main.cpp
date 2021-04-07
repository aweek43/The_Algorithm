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
// ���: �ٸ��� Queue�� ����� Ʈ�� �Ǵ� ����(0)�� �־� Ʈ���� ��ġ���� �� �� �ְ� �ߴ�.
// Ʈ���� ���� ������ ��� queue�� �ְ� �� �ʸ��� pop()�� �ϰ� ���� Ʈ�� �Ǵ� ������ �־�
// �ٸ� ���� Ʈ���� ��ĭ�� �����Ų��.
*/
int StackQueue_42583(int bridge_length, int weight, vector<int> truck_weights)
{
    int answer = 0;
    int onBridge_weight = 0; // ���� �ٸ� ���� Ʈ�� ���� ��
    queue<int> onBridge; // �ٸ� ���� Ʈ���� ��ġ
    for (int i = 0; i < bridge_length; ++i)
        onBridge.push(0);

    while (truck_weights.size() || onBridge.size()) // ��� ��, �ٸ� �� Ʈ���� ���� �� ����
    {
        onBridge_weight -= onBridge.front();
        onBridge.pop(); // Ʈ�� 1ĭ ����
        if (truck_weights.size() == 0) // ���̻� ��� ���� Ʈ���� ���� ���
        {
            answer += bridge_length; // ���� �ٸ� �� Ʈ���� �ѹ��� �����Ŵ
            break;
        }
        if (onBridge_weight + truck_weights.front() <= weight) // Ʈ�� �߰� ����
        {
            onBridge.push(truck_weights.front()); // ��� ���� Ʈ���� �ٸ� ���� �߰�
            onBridge_weight += truck_weights.front();
            truck_weights.erase(truck_weights.begin());
        }
        else
        {
            onBridge.push(0); // �ٸ� ���� ���� �߰�
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
// ���: �Ϸ縶�� progresses�� speeds�� ���ϸ� ù��° �۾��� 100%�� �ʰ��� ��� �� ����
// 100% �ʰ��ϴ� �۾����� �ѹ��� �����ϰ� �����ϴ� �����̴�.
// ���� ������ �°� Queue�� ����ϰ� �;����� �Ϸ縶�� progresses�� speeds�� ���ϴ� ��������
// ��� ���ο� Queue�� �ִ°� ��ȿ�����̶�� �Ǵ��� index ������ ������ vector�� ����ߴ�.
// �ٸ� Queue�� ������ �̿��ϵ��� pop()�� �����ߴ�.
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
    int release; // �ѹ��� �����Ǵ� ����
    while (progresses.size())
    {
        release = 0;
        for (int i = 0; i < progresses.size(); ++i) // �Ϸ簡 ���� progress�鿡 ���� ����
        {
            progresses[i] += speeds[i];
        }

        while (progresses.size() && progresses[0] >= 100) // ���� ������ ��� ���ʴ�� ����
        {
            queue_pop(progresses);
            queue_pop(speeds);
            release++;
        }

        if (release > 0) // �����Ǿ����� ������ ���� ���
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
// ���: ���� Ư���� 2�� for���� ���� �� list�� ���ص� ������,
// Hash��� ������ �����ϱ� ���� unordered_map�� ����� key�� value�� ���� Ǯ����.
*/
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

void print(int answer) { cout << answer << endl; }
void print(string answer) { cout << answer << endl; }
void print(vector<int> answer) { for (int ans : answer) cout << ans << endl; }