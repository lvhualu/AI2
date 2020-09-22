//�������-8�������� 
 
#include <iostream>
#include <cstring>
using namespace std;
 
const int Max = 8;
const int All = 363000;	//�ܵĸ�����9��= 362880����ȡ363000
int Fac[Max] = {1};		//����չ����Ҫ�õ��Ĺ��� 
char a[All][9];		
bool visit[All];
char goal[9];
int dis[All];
int dir[4][2]={{-1,0},{1,0},{0,1},{0,-1}};	//����ʱ�õ����ĸ����� 
 
void Init();	//���룬�Լ���ʼ��Fac 
int getValue(char* s);		//����չ����Hash�����棡����
bool check(int head);	//check�Ƿ��Ѿ�����Ŀ��״̬ 
int bfs();			//�������������̣� 
 
int main()
{
	Init();
	int ans = bfs();
	if(ans == -1) cout << "No answers!" << endl;
	else cout << ans << endl;
	return 0;	
}
 
void Init()
{
	for(int i=0; i<9; ++i)
		cin >> a[0][i];
	for(int i=0; i<9; ++i)
		cin >> goal[i];
	for(int i=1; i<Max; ++i)
		Fac[i] = Fac[i-1] * i;
}
int getValue(char* s)
{
	int sum = 0, cnt, key = 1;
	for(int i=0; i<9; ++i)
	{
		cnt = 0;
		for(int j=i+1; j<9; ++j)
			if(s[j] < s[i]) ++cnt;
		sum += cnt * Fac[Max-i];
	}
	return sum;
}
inline bool check(int head)
{
	for(int i=0; i<9; ++i){
		if(a[head][i] != goal[i])
			return false;
	}
	return true;
}
int bfs(){
	int head = 0, tail = 1;
	int x, y, z, nx, ny, nz;
	while(head < tail){
		if(check(head)) return dis[head];
 
		for(int i=0; i<9; ++i){
			if(a[head][i] == '0'){
				x = i / 3;
				y = i % 3;
				z = i;
				break;
			}
		}
		
		for(int i=0; i<4; ++i){
			nx = x + dir[i][0];
			ny = y + dir[i][1];
			nz = 3*nx + ny;
 
			if(nx<0 || ny<0 || nx>2 || ny>2)
				continue;
 
			for(int i=0; i<9; ++i)
				a[tail][i] = a[head][i];
			a[tail][z] = a[tail][nz];
			a[tail][nz] = '0';			
 
			int t = getValue(a[tail]);
			if(!visit[t]){
				visit[t] = true;
				dis[tail] = dis[head] + 1;
				++tail;
			}
		}
		++head;
	}	
}