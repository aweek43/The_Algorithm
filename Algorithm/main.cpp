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
void print(long long answer);

string Hash_42576();
vector<int> StackQueue_42586();
int StackQueue_42583();
int Heap_42626();
int Heap_42627();
vector<int> Heap_42628();
int Greedy_42862();
string Greedy_42883();
int Greedy_42885();
int Greedy_42861();
int Greedy_42884();
int DynamicProgramming_42895();
int DynamicProgramming_43105();
int DynamicProgramming_42898();
int DynamicProgramming_42897();
long long BinarySearch_43238();
int BinarySearch_43236();

int main()
{
	// write question function
    auto answer = BinarySearch_43236();

	print(answer);
	return 0;
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42862?language=cpp
// ���: �������� �л� ���ο��� ������ �ִ� ���� ��, �� �л����� ������ �ִ� ��츦 ����� vector���� �����Ѵ�.
// ��� �������� �� lost vector�� ���� �л��� ������ �� ��� �л������� ��ü���� �׸�ŭ ����.
// ** ��ü �л���ŭ�� �迭�� �̸� �����ϰ� �� �ȿ� lost�� reserve �л��� index�� ���� ������ 1�� for�������� ����� �� �ִ� **
*/
int Greedy_42862(int n, vector<int> lost, vector<int> reserve)
{
    int answer = 0;
    bool found;
    // �������� �л� �� ������ �ִ� ���
    for (auto i=lost.begin(); i != lost.end();)
    {
        found = false;
        for (auto r=reserve.begin(); r != reserve.end();)
        {
            if ((*i) == (*r)) 
            {
                i = lost.erase(i);
                r = reserve.erase(r);
                found = true;
                break;
            }
            else
            {
                r++;
            }
        }
        if(!found)
            i++;
    }

    // �������� �л��� ��, �� ��ȣ �л����� ������ �ִ� ���
    for (auto i = lost.begin(); i != lost.end();)
    {
        found = false;
        for (auto r = reserve.begin(); r != reserve.end();)
        {
            if (abs((*i) - (*r)) == 1)
            {
                i = lost.erase(i);
                r = reserve.erase(r);
                found = true;
                break;
            }
            else
            {
                r++;
            }
        }
        if(!found)
            i++;
    }

    answer = n - lost.size();

    return answer;
}
int Greedy_42862()
{
    return Greedy_42862(5, { 2,4 }, { 1,3,5 });
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42883?language=cpp
// ���: ���ڸ����� ������ ���� ������ max�� ������ �����Ѵ�.
// max�� index�� �պκ��� ����� ���ԵǸ� �ȵǹǷ� �����Ѵ�.
*/
string Greedy_42883(string number, int k)
{
    string answer = "";
    int insert = number.length() - k;

    for (;insert > 0; --insert)
    {
        char local_max = '0';
        int max_idx = -1;
        for (int i = 0; i <= number.length() - insert; ++i)
        {
            if ((number[i] - '0') > (local_max - '0')) // char to int
            {
                local_max = number[i];
                max_idx = i;
            }
        }
        answer += local_max;
        number.replace(0, ++max_idx, "");
    }

    return answer;
}
string Greedy_42883()
{
    return Greedy_42883("4177252841", 4);
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42885?language=cpp
// ���: �����Ը� sorting�ϰ� ���� ������ ����� ���� ���ſ� ����� ��Ī�Ѵ�.
// �� �θ��� �����԰� limit ���ϸ� ���� ����Ʈ�� �¿�� �ƴ� ��� ���ſ� ����� �¿��.
// ���� ��� �߿� �ٽ� ���� ������� ��Ī�ϸ� �����Ѵ�.
*/
int Greedy_42885(vector<int> people, int limit)
{
    int answer = 0;
    sort(people.begin(), people.end());
    int size = people.size();
    int front = 0; // ���� ������ ���
    int back = size - 1; // ���� ���ſ� ���
    while (front < back)
    {
        if (people[front] + people[back] <= limit)
        {
            front++; back--;
        }
        else
        {
            back--;
        }
        answer++;
    }
    if (front == back)
        answer++;

    return answer;
}
int Greedy_42885()
{
    return Greedy_42885({ 70,80,50 }, 100);
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42861?language=cpp
// ���: ũ�罺Į �˰������� Ǫ���� ������ ���� ī�װ��� greedy�̱� ������ ���� �˰����� �����ߴ�.
// ó�� ������ �� ���� ������ ��, ���õ� ���� ���õ��� ���� ���� �մ� �ٸ��� ��� ����.
// �� �ٸ� �� ����� �ּ��� �ٸ��� �� �ٸ��� ����� ���� �����Ѵ�.
// ��� ���� ���õ� ������ �ݺ��Ѵ�.
*/
bool isInclude(vector<int> arr, int value)
{
    for (auto a : arr)
    {
        if (a == value)
            return true;
    }
    return false;
}
int Greedy_42861(int n, vector<vector<int>> costs)
{
    int answer = 0;
    vector<vector<int>> selected_path;
    vector<int> selected_node;

    selected_node.push_back(0);
    while (selected_node.size() < n) // ��� ���� ������ ������ �ݺ�
    {
        vector<vector<int>> dist;
        for (auto c : costs)
        {
            if ((isInclude(selected_node, c[0]) && !isInclude(selected_node, c[1])) || // �̹� ���õ� �Ͱ� ���õ��� ���� ����� ���
                (isInclude(selected_node, c[1]) && !isInclude(selected_node, c[0])))
            {
                dist.push_back(c);
            }
        }
        auto min_node = min_element(dist.begin(), dist.end(), [](vector<int> a, vector<int> b) { return a[2] < b[2]; });
        selected_path.push_back(*min_node);
        if(!isInclude(selected_node, (*min_node)[1])) // ���õ��� ���� ��带 ����
            selected_node.push_back((*min_node)[1]);
        else
            selected_node.push_back((*min_node)[0]);
    }

    for (auto s : selected_path)
        answer += s[2];
    return answer;
}
int Greedy_42861()
{
    return Greedy_42861(4, { {0, 1, 5},{1, 2, 3},{2, 3, 3},{1, 3, 2},{0, 3, 4} });
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42884?language=cpp
// ���: ������ ���� ������ �������� �����Ѵ�. ī�޶� �������� üũ�� ���͸� �����.
// ������ �������� �� ī�޶� ������ ���� �����̸� �� ��ġ�� ī�޶� ��ġ�ϰ� �ش� ��ġ�� �ִ� ��������
// ī�޶� �����ٰ� �����Ѵ�.
*/
int Greedy_42884(vector<vector<int>> routes)
{
    int answer = 0;
    vector<bool> meetCamera(routes.size(), false);
    sort(routes.begin(), routes.end(), [](vector<int> a, vector<int> b) { return a[1] < b[1]; });
    for (int i = 0; i < routes.size(); ++i)
    {
        if (meetCamera[i] == false)
        {
            answer++;
            for (int ii = 0; ii < routes.size(); ++ii)
            {
                if (routes[ii][0] <= routes[i][1] && routes[ii][1] >= routes[i][1])
                    meetCamera[ii] = true;
            }
        }
    }
    return answer;
}
int Greedy_42884()
{
    return Greedy_42884({ {-20, 15},{-14, -5},{-18, -13},{-5, -3} });
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42628?language=cpp
// ���: priority_queue�� ��� back�� ���� �� ������ �ȵǹǷ� 2���� priority_queue�� �������.
// max ���� ���� �ٷ� �����ϰ� min ���� ��� �ϳ��� queue���� ������ ��(�ּڰ�)�� ������ ���� �ٸ� queue�� 
// �ű����ν� �ּڰ� ���� ������ �����ߴ�.
// ** top�� bottom�� ���� �� ������ ������ multiset�� ���� �� ���� �� �ϴ� **
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
// ** �Ϸ羿 �����Ű�� �ʾƵ� ó�� ������ �� progress���� ������ ���� ����� �� �����Ƿ� 
// �̸� �̸� ����� ������ �ٷ� ������������ �� �� �ִ� **
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


/*
// https://programmers.co.kr/learn/courses/30/lessons/42895?language=cpp
// ���: N�� i�� ����� ���� �� �ִ� ���� a�� ����� ���� �� ���հ� b�� ����� ���� �� ���ճ����� ������̴�. (�̶� i = a + b)
// ���� i�� ����� ���� ������ �����ϰ� i+1��° ����� ���� ���� ����� �� ����Ѵ�.
// �� �� 8�� ����� ���� ������ ����ϸ� �ʹ� ���� �ɸ��Ƿ� �� i���� ���� ���Դ��� üũ�Ѵ�.
// �߰���, vector<set<int>>�� �� ��� ���� ���� �ߺ����� �ʾ� ���� ȿ������ ������ ���ȴ�.
*/
int DynamicProgramming_42895(int N, int number)
{
    int answer = -1;
    vector<vector<int>> cases(9);

    for (int i = 1; i <= 8; ++i)
    {
        int num = N;
        for (int _ = 1; _ < i; ++_) // ���� ���̱�
            num = 10 * num + N;
        cases[i].push_back(num);

        for (int one = 1; one < i; ++one) // 1 ~ i-1 ��°������ ���ճ����� ��Ģ���� ��� ����
        {
            int other = i - one;
            for (int m = 0; m < cases[one].size(); ++m)
            {
                for (int n = 0; n < cases[other].size(); ++n)
                {
                    cases[i].push_back(cases[one][m] + cases[other][n]);
                    cases[i].push_back(cases[one][m] - cases[other][n]);
                    cases[i].push_back(cases[one][m] * cases[other][n]);
                    if(cases[other][n] != 0) // divide by zero ó��
                        cases[i].push_back(cases[one][m] / cases[other][n]);
                }
            }
        }

        for (auto c : cases[i]) // ���� �ִ��� Ȯ��
        {
            if (c == number)
            {
                return i;
            }
        }
    }
    
    return answer;
}
int DynamicProgramming_42895()
{
    return DynamicProgramming_42895(5, 12);
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/43105?language=cpp
// ���: Ʈ���� ���� �Ʒ����� 2�� ����� �ִ��� �� �θ��忡 ���Ѵ�.
// �̷��� ��� �ö󰡸� �ᱹ root��尡 ���İ� ������ �ִ��� �ȴ�.
*/
int DynamicProgramming_43105(vector<vector<int>> triangle)
{
    int answer = 0;
    int curDepth = triangle.size() - 1; // ���� �Ʒ����� ��
    for (int i = curDepth - 1; i >= 0; --i)
    {
        for (int j = 0; j <= i; ++j)
        {
            triangle[i][j] += max(triangle[i + 1][j], triangle[i + 1][j+1]);
        }
    }

    answer = triangle[0][0]; // ���� ����� �ִ밪�� ����
    return answer;
}
int DynamicProgramming_43105()
{
    return DynamicProgramming_43105({ {7},{3, 8},{8, 1, 0},{2, 7, 4, 4},{4, 5, 2, 6, 5} });
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42898?language=cpp
// ���: �׻� ������ �Ǵ� �Ʒ��θ� �����̹Ƿ� �ִܰ���� ���̴� ��ֹ��� ���� ���� �����ϴ�.
// �ʱ⿡ �� �������� �ִܰ���� ���� 1�� �����ϰ� ��, ���� ������ ���� ���ذ��� �ش� �������� �ִܰ���� ���� ����Ѵ�.
// ��ֹ��� �ִ� ������ 0���� �����ϰ� �̾ ����Ѵ�.
*/
int DynamicProgramming_42898(int m, int n, vector<vector<int>> puddles)
{
    int answer = 0;
    vector<vector<int>> path(m, vector<int>(n, 1));

    for (auto p : puddles) // puddle�� 0���� �ʱ�ȭ
    {
        if (!p.size())
            break;

        if (p[0] == 1) // 1�� or 1�࿡ puddle�� ������ ���� ��or�� 0���� �ʱ�ȭ
        {
            for (int i = p[1] - 1; i < n; ++i)
            {
                path[0][i] = 0;
            }
        }
        else if (p[1] == 1)
        {
            for (int i = p[0] - 1; i < m; ++i)
            {
                path[i][0] = 0;
            }
        }
        else
        {
            path[p[0] - 1][p[1] - 1] = 0;
        }
    }

    for (int i = 1; i < m; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            if(path[i][j] != 0) // puddle�� �ƴ� ���
            {
                path[i][j] = (path[i-1][j] + path[i][j-1]) % 1000000007;
            }
        }
    }

    answer = path[m - 1][n - 1];
    return answer;
}
int DynamicProgramming_42898()
{
    return DynamicProgramming_42898(3, 3, { {1, 3},{3, 1},{2, 3} });
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42897?language=cpp
// ���: ������ �ּҴ����� �ɰ��� (�ι�° ���� �� + ���� ��)�� �ʹ� ���� (ù��° ���� ��)�� �ʹ� ���� ����������.
// �� �� ��� �� ���� ū���� �����Ѵ�. �� ���� ��궧 ������ ��� ����� ����� ����Ѵ�.
// ������ ���� �迭�� �����̱� ������ ������ ���� ���� ���ο� ���� ���� ������ �޶����� �ȴ�.
// ������ ���� ���� ���θ� ó���� �� �� �����Ƿ� ���� ������ case�� ������.
// �ִ� ����° ������ �ʹ� ����� ���� �����Ƿ� ù��°, �ι�°, ����° ������ �ʹ� case�� ������.
// ������ ù��° ������ �ʹ� ���� �ι�° ������ �ʹ� ��쿡�� ����Ǳ� ������ ���� ������� �ʾƵ� �ȴ�.
*/
int DynamicProgramming_42897(vector<int> money)
{
    vector<int> answers;
    int moneySize = money.size();

    // �ι�° ������ �ʹ� ���
    vector<int> dp(moneySize, 0);
    dp[0] = money[0];
    for (int i = 1; i < moneySize - 1; ++i)
    {
        int p_prev = i - 2;
        int prev = i - 1;
        if (i == 1) // ���� ���
        {
            p_prev = moneySize - 1;
        }

        dp[i] = max((dp[p_prev] + money[i]), dp[prev]);
    }
    answers.push_back(dp[moneySize - 2]);

    // ����° ������ �ʹ� ���
    dp = vector<int>(moneySize, 0);
    dp[1] = money[1];
    for (int i = 2; i < moneySize; ++i)
    {
        int p_prev = i - 2;
        int prev = i - 1;
        dp[i] = max((dp[p_prev] + money[i]), dp[prev]);
    }
    answers.push_back(dp[moneySize - 1]);

    return *max_element(answers.begin(), answers.end());
}
int DynamicProgramming_42897()
{
    return DynamicProgramming_42897({1,2,3,1});
}

/*
// https://programmers.co.kr/learn/courses/30/lessons/43238?language=cpp
// ���: ��Ȯ�� ��� �������� ¥�� �ִ� �ð��� �������� ���ϴ°� �ƴ� �ð��� �ּ�, �ִ񰪸� ���ϰ�
// �̺�Ž������ ������ �ִ� �ð��� ã�� �����̴�. Ư�� �ð����� �ɻ� �ð��� ���� ���� �ش� �ɻ���� �� �ð��� �ɻ��� �� �ִ� ��� ���̴�.
// �ٸ� Ÿ���� overflow �̽��� ��� ������ long long���� ����ȯ�ؼ� ����ؾ� �Ѵ�.
*/
long long BinarySearch_43238(int n, vector<int> times)
{
    long long min_ele = (*min_element(times.begin(), times.end()));

    long long answer = (long long)n * min_ele;
    long long left = min_ele;
    long long right = (long long)n * min_ele; // BS ���� left�� �������� overflow ����

    while (left <= right)
    {
        long long people = 0;
        long long mid = (left + right) / 2;

        for (long long t : times)
        {
            // mid �ð� ���� ��� �ɻ���� �ɻ����� �� ��� ��
            people += (mid / t);

            // ���� people�� long long type�� ���� �� �־� �� iterator���� üũ�ؾ� ��
            if (people >= n) // n���� ũ�� �� ���� �ð����� �ɻ� ����
            {
                answer = mid;
                right = mid - 1;
                break;
            }
        }

        if (people < n) // n���� ������ �� ���� �ð��� �ʿ���
        {
            left = mid + 1;
        }
    }

    return answer;
}
long long BinarySearch_43238()
{
    return BinarySearch_43238(2, {1, 2});
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/43236?language=cpp
// ���: �ּ�, �ִ��� ���ϰ� �̺�Ž������ �� ������ �Ÿ��� �ִ� �߰����� ���� �ʵ��� ���� �����Ѵ�.
// ���ŵ� ���� ������ n���� Ŭ ��� �߰��� �̻����δ� �ּҰ��� ���� �� �����Ƿ� �߰��� ���Ϻ��� �ٽ� Ž���Ѵ�.
// ���ŵ� ���� ������ n���� ���� ��� n��ŭ �����ص� �ش� ���� �ּҰ����� ���� �� �����Ƿ� ������ �� �� �ִ�.
*/
int BinarySearch_43236(int distance, vector<int> rocks, int n)
{
    int answer = 0;
    sort(rocks.begin(), rocks.end());
    rocks.push_back(distance); // ���� ���� �߰�
    int left = 0;
    int right = distance;

    while (left <= right)
    {
        int prev = 0; // ���� ����
        int count = 0;
        int mid = (left + right) / 2;
        for (auto r : rocks)
        {
            if (r - prev <= mid)
            {
                count++;
            }
            else
            {
                prev = r;
            }
        }

        if (count > n)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
            answer = mid + 1;
        }
    }

    return answer;
}
int BinarySearch_43236()
{
    return BinarySearch_43236(25, { 2,14,11,21,17 }, 2);
}


// print function overloading
void print(int answer) { cout << answer << endl; }
void print(long long answer) { cout << answer << endl; }
void print(string answer) { cout << answer << endl; }
void print(vector<int> answer) { for (int ans : answer) cout << ans << endl; }