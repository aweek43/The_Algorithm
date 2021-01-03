#include "Hash_42576.cpp"
#include "StackQueue_42586.cpp"


void print(string answer);
void print(vector<int> answer);


int main()
{
	// write question function
	auto answer = StackQueue_42586();

	print(answer);
	return 0;
}

void print(string answer)
{
	cout << answer << endl;
}

void print(vector<int> answer)
{
	for (int ans : answer) cout << ans << endl;
}