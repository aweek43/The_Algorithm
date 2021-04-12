#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <numeric>
using namespace std;


void print(string answer);
void print(vector<int> answer);
void print(int answer);
string Hash_42576();
vector<int> StackQueue_42586();
int StackQueue_42583();
int Heap_42626();
int Heap_42627();
vector<int> Heap_42628();

int main()
{
	// write question function
	auto answer = Heap_42628();

	print(answer);
	return 0;
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42628?language=cpp
// ���: priority_queue�� ��� back�� ���� �� ������ �ȵǹǷ� 2���� priority_queue�� �������.
// max ���� ���� �ٷ� �����ϰ� min ���� ��� �ϳ��� queue���� ������ ��(�ּڰ�)�� ������ ���� �ٸ� queue�� 
// �ű����ν� �ּڰ� ���� ������ �����ߴ�.
*/
vector<int> Heap_42628(vector<string> operations) 
{
    vector<int> answer;
    priority_queue<int> max_heap1; // max heap
    priority_queue<int> max_heap2; // max heap
    for (auto o : operations)
    {
        if (o[0] == 'I') // insert
        {
            int value = stoi(o.substr(2)); // split
            if(max_heap1.size()) // ����ϴ� queue�� push
                max_heap1.push(value);
            else
                max_heap2.push(value);
        }
        else if (o[0] == 'D') // delete
        {
            if (o[2] == '-') // remove min element
            {
                if (max_heap1.size())
                {
                    int heap_size = max_heap1.size();
                    for (int i = 0; i < heap_size - 1; ++i)
                    {
                        int top = max_heap1.top();
                        max_heap2.push(top);
                        max_heap1.pop();
                    }
                    max_heap1.pop(); // �ּڰ� ����
                }
                else if (max_heap2.size())
                {
                    int heap_size = max_heap2.size();
                    for (int i = 0; i < heap_size - 1; ++i)
                    {
                        int top = max_heap2.top();
                        max_heap1.push(top);
                        max_heap2.pop();
                    }
                    max_heap2.pop(); // �ּڰ� ����
                }
            }
            else // remove max element
            {
                if (max_heap1.size()) // ����ϴ� queue���� pop
                {
                    max_heap1.pop();
                }
                else if (max_heap2.size())
                {
                    max_heap2.pop();
                }
            }
        }
    }
    int max_value = 0;
    int min_value = 0;
    if (max_heap1.size())
    {
        max_value = max_heap1.top();
        max_heap1.pop();
        int heap_size = max_heap1.size();
        for (int i = 0; i < heap_size - 1; ++i) // ������ ����(�ּڰ�) ���ϱ�
            max_heap1.pop();
        min_value = max_heap1.top();
    }
    else if (max_heap2.size())
    {
        max_value = max_heap2.top();
        max_heap2.pop();
        int heap_size = max_heap2.size();
        for (int i = 0; i < heap_size - 1; ++i) // ������ ����(�ּڰ�) ���ϱ�
            max_heap2.pop();
        min_value = max_heap2.top();
    }
    answer.push_back(max_value);
    answer.push_back(min_value);
    return answer;
}
vector<int> Heap_42628()
{
    return Heap_42628({ "I 7", "I 5", "I -5", "D -1" });
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42627?language=cpp
// ���: priority_queue�� �ҿ� �ð��� ���� Min Heap���� ����Ѵ�. job ��û�� ������ heap�� �ִ´�.
// ���� job�� ������ heap���� �ּ� �ҿ� �ð��� job�� �����Ѵ�.
// job�� �����ϴ� ���ȿ��� �ٸ� job�� �� �� �����Ƿ� �ٷ� �ش� job�� �ҿ�ð���ŭ �����Ų��.
*/
int Heap_42627(vector<vector<int>> jobs)
{
    vector<int> answers;
    int jobs_size = jobs.size();
    int time = 0;
    auto compare = [](vector<int> a, vector<int> b) {return a[1] > b[1]; }; // �ҿ�ð��� �������� ����
    priority_queue < vector<int>, vector<vector<int>>, decltype(compare) > jobs_heap(compare); // min heap

    while (jobs.size() || jobs_heap.size()) // ���� job, �������� job�� ���� ������
    {
        for (int idx = 0; idx < jobs.size(); ++idx)
        {
            if (jobs[idx][0] <= time) // ���� ������ ���� job �߰�
            {
                jobs_heap.push(jobs[idx]);
                jobs.erase(jobs.begin() + idx);
                idx--;
            }
        }

        if (jobs_heap.size())
        {
            vector<int> current_job = jobs_heap.top(); // ���� ª�� job pop
            jobs_heap.pop();

            time += current_job[1]; // �ҿ�ð���ŭ ����
            answers.push_back(time - current_job[0]); // �Ϸ�� ���� - ��û�� ����
        }
        else
        {
            time++;
        }
    }


    return (int)accumulate(answers.begin(), answers.end(), 0) / jobs_size;
}
int Heap_42627()
{
    return Heap_42627({ {0,3}, {1,9}, {2,6} });
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42626?language=cpp
// ���: priority_queue�� Min Heap���� ����Ѵ�. ���� ���� 2���� �̾� ���� �� �ٽ� �ִ´�.
// Heap�� root(���� ���� ��)�� K���� ���� ������ �ݺ��Ѵ�.
*/
int Heap_42626(vector<int> scoville, int K)
{
    int answer = 0;
    priority_queue< int, vector<int>, greater<int> > scoville_heap; // min heap
    for (auto s : scoville) // heap �ʱ�ȭ
        scoville_heap.push(s);

    int top1, top2, mixed;
    while (scoville_heap.top() < K)
    {
        if (scoville_heap.size() < 2) // �Ұ����� ���
            return -1;

        top1 = scoville_heap.top(); // 2���� pop
        scoville_heap.pop();
        top2 = scoville_heap.top();
        scoville_heap.pop();

        mixed = top1 + (top2 * 2); // ��� �ٽ� push
        scoville_heap.push(mixed);
        answer++;
    }

    return answer;
}
int Heap_42626()
{
    return Heap_42626({ 1,2,3,9,10,12 }, 7);
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

// print function overloading
void print(int answer) { cout << answer << endl; }
void print(string answer) { cout << answer << endl; }
void print(vector<int> answer) { for (int ans : answer) cout << ans << endl; }