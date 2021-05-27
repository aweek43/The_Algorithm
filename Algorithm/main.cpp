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
int Greedy_42862();
string Greedy_42883();
int Greedy_42885();
int Greedy_42861();
int Greedy_42884();

int main()
{
	// write question function
    auto answer = Greedy_42884();

	print(answer);
	return 0;
}


/*
// https://programmers.co.kr/learn/courses/30/lessons/42862?language=cpp
// 요약: 도난당한 학생 본인에게 여벌이 있는 경우와 앞, 뒤 학생에게 여벌이 있는 경우를 계산해 vector에서 제거한다.
// 모두 제거했을 때 lost vector에 남은 학생이 수업을 못 듣는 학생임으로 전체에서 그만큼 뺀다.
// ** 전체 학생만큼의 배열을 미리 정의하고 그 안에 lost와 reserve 학생의 index에 값을 넣으면 1중 for문만으로 계산할 수 있다 **
*/
int Greedy_42862(int n, vector<int> lost, vector<int> reserve)
{
    int answer = 0;
    bool found;
    // 도난당한 학생 중 여벌이 있는 경우
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

    // 도난당한 학생의 앞, 뒤 번호 학생에게 여벌이 있는 경우
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
// 요약: 앞자리부터 가능한 범위 내에서 max인 값으로 결정한다.
// max값 index의 앞부분은 결과에 포함되면 안되므로 삭제한다.
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
// 요약: 몸무게를 sorting하고 가장 가벼운 사람과 가장 무거운 사람은 매칭한다.
// 이 두명의 몸무게가 limit 이하면 둘이 구명보트를 태우고 아닌 경우 무거운 사람만 태운다.
// 남은 사람 중에 다시 같은 방식으로 매칭하며 진행한다.
*/
int Greedy_42885(vector<int> people, int limit)
{
    int answer = 0;
    sort(people.begin(), people.end());
    int size = people.size();
    int front = 0; // 가장 가벼운 사람
    int back = size - 1; // 가장 무거운 사람
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
// 요약: 크루스칼 알고리즘으로 푸려고 했으나 문제 카테고리가 greedy이기 때문에 프림 알고리즘을 선택했다.
// 처음 임의의 한 섬을 선택한 후, 선택된 섬과 선택되지 않은 섬을 잇는 다리를 모두 고른다.
// 고른 다리 중 비용이 최소인 다리와 그 다리가 연결된 섬을 선택한다.
// 모든 섬이 선택될 때까지 반복한다.
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
    while (selected_node.size() < n) // 모든 섬을 연결할 때까지 반복
    {
        vector<vector<int>> dist;
        for (auto c : costs)
        {
            if ((isInclude(selected_node, c[0]) && !isInclude(selected_node, c[1])) || // 이미 선택된 것과 선택되지 않은 노드인 경우
                (isInclude(selected_node, c[1]) && !isInclude(selected_node, c[0])))
            {
                dist.push_back(c);
            }
        }
        auto min_node = min_element(dist.begin(), dist.end(), [](vector<int> a, vector<int> b) { return a[2] < b[2]; });
        selected_path.push_back(*min_node);
        if(!isInclude(selected_node, (*min_node)[1])) // 선택되지 않은 노드를 선택
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
// 요약: 차량의 진출 지점을 기준으로 정렬한다. 카메라에 찍혔는지 체크할 벡터를 만든다.
// 차량이 진출했을 때 카메라에 찍히지 않은 차량이면 그 위치에 카메라를 설치하고 해당 위치에 있는 차량들을
// 카메라에 찍혔다고 셋팅한다.
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
// 요약: priority_queue의 경우 back에 접근 및 삭제가 안되므로 2개의 priority_queue를 만들었다.
// max 값의 경우는 바로 삭제하고 min 값의 경우 하나의 queue에서 마지막 값(최솟값)을 제외한 값을 다른 queue로 
// 옮김으로써 최솟값 삭제 로직을 구현했다.
// ** top과 bottom에 접근 및 삭제가 가능한 multiset을 쓰면 더 좋을 듯 하다 **
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
            if(max_heap1.size()) // 사용하는 queue에 push
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
                    max_heap1.pop(); // 최솟값 버림
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
                    max_heap2.pop(); // 최솟값 버림
                }
            }
            else // remove max element
            {
                if (max_heap1.size()) // 사용하는 queue에서 pop
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
        for (int i = 0; i < heap_size - 1; ++i) // 마지막 원소(최솟값) 구하기
            max_heap1.pop();
        min_value = max_heap1.top();
    }
    else if (max_heap2.size())
    {
        max_value = max_heap2.top();
        max_heap2.pop();
        int heap_size = max_heap2.size();
        for (int i = 0; i < heap_size - 1; ++i) // 마지막 원소(최솟값) 구하기
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
// 요약: priority_queue를 소요 시간에 대한 Min Heap으로 사용한다. job 요청이 들어오면 heap에 넣는다.
// 이전 job이 끝나면 heap에서 최소 소요 시간인 job을 수행한다.
// job을 수행하는 동안에는 다른 job을 할 수 없으므로 바로 해당 job의 소요시간만큼 진행시킨다.
*/
int Heap_42627(vector<vector<int>> jobs)
{
    vector<int> answers;
    int jobs_size = jobs.size();
    int time = 0;
    auto compare = [](vector<int> a, vector<int> b) {return a[1] > b[1]; }; // 소요시간을 기준으로 비교함
    priority_queue < vector<int>, vector<vector<int>>, decltype(compare) > jobs_heap(compare); // min heap

    while (jobs.size() || jobs_heap.size()) // 남은 job, 진행중인 job이 없을 때까지
    {
        for (int idx = 0; idx < jobs.size(); ++idx)
        {
            if (jobs[idx][0] <= time) // 현재 시점에 들어온 job 추가
            {
                jobs_heap.push(jobs[idx]);
                jobs.erase(jobs.begin() + idx);
                idx--;
            }
        }

        if (jobs_heap.size())
        {
            vector<int> current_job = jobs_heap.top(); // 가장 짧은 job pop
            jobs_heap.pop();

            time += current_job[1]; // 소요시간만큼 진행
            answers.push_back(time - current_job[0]); // 완료된 시점 - 요청된 시점
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
// 요약: priority_queue를 Min Heap으로 사용한다. 가장 작은 2개를 뽑아 섞은 뒤 다시 넣는다.
// Heap의 root(가장 작은 값)가 K보다 작을 때까지 반복한다.
*/
int Heap_42626(vector<int> scoville, int K)
{
    int answer = 0;
    priority_queue< int, vector<int>, greater<int> > scoville_heap; // min heap
    for (auto s : scoville) // heap 초기화
        scoville_heap.push(s);

    int top1, top2, mixed;
    while (scoville_heap.top() < K)
    {
        if (scoville_heap.size() < 2) // 불가능한 경우
            return -1;

        top1 = scoville_heap.top(); // 2개를 pop
        scoville_heap.pop();
        top2 = scoville_heap.top();
        scoville_heap.pop();

        mixed = top1 + (top2 * 2); // 섞어서 다시 push
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
// ** 하루씩 진행시키도 않아도 처음 시점에 각 progress들의 끝나는 날을 계산할 수 있으므로 
// 이를 미리 계산해 놓으면 바로 배포시점으로 갈 수 있다 **
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

// print function overloading
void print(int answer) { cout << answer << endl; }
void print(string answer) { cout << answer << endl; }
void print(vector<int> answer) { for (int ans : answer) cout << ans << endl; }