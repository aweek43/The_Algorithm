#include "Headers.h"

// https://programmers.co.kr/learn/courses/30/lessons/42586


// ���: �Ϸ縶�� progresses�� speeds�� ���ϸ� ù��° �۾��� 100%�� �ʰ��� ��� �� ����
// 100% �ʰ��ϴ� �۾����� �ѹ��� �����ϰ� �����ϴ� �����̴�.
// ���� ������ �°� Queue�� ����ϰ� �;����� �Ϸ縶�� progresses�� speeds�� ���ϴ� ��������
// ��� ���ο� Queue�� �ִ°� ��ȿ�����̶�� �Ǵ��� index ������ ������ vector�� ����ߴ�.
// �ٸ� �ּ����� Queue�� ������ �̿��ϵ��� pop()�� �����ߴ�.
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