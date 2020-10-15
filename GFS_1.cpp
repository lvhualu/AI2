#include<iostream>
#include<queue>
#define MAX 5000
using namespace std;

struct Node{
	int order;//�ڵ����
	int board[3][3];   //״̬
	int zeroX;      //0��x����
	int zeroY;      //0��y����
	struct Node *parent;    //�ӵ�����ָ��
};

//��ʼ״̬
Node s0 = {
	1,
	{{2,8,3},{1,0,4},{7,6,5}},
	1,
	1,
	NULL
};


//��ֹ״̬��ֻ�������ж��õĲ���Ҫ�и��ڵ�
/*Node sg = {
	0,
	{{8,1,3},{2,0,4},{7,6,5}},
	1,
	1,
	NULL
};*/

/*
Node sg = {
	0,
	{{2,8,3},{0,6,4},{1,7,5}},
	1,0,NULL
};
*/

Node sg = {
	0,
	{{8,1,3},{2,6,4},{7,5,0}},
	2,2,NULL
};

int order = s0.order;//�ڵ��ŴӸ��ڵ㿪ʼ

Node closed[MAX];	//closed��˳����ڵ����͵�˳���

//����ڵ��״̬�����ڵ���ţ��ڵ�״̬���ڵ�ĸ�ָ��
void showNode(Node a){
	cout<<"NO:"<<a.order<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<a.board[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"XY0:("<<a.zeroX+1<<","<<a.zeroY+1<<")"<<endl;
}

//�����ж������ڵ��״̬�Ƿ����
bool judgeBoard(Node x,Node y){
	bool flag = true;//���λ
	//��3*3��������һ���㲻һ���ͻ����ѭ�������Ұѱ����Ϊ false
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(x.board[i][j]!=y.board[i][j])
			{
				flag = false;
				break;
			}
		}
		if(false == flag) break;
	}
	//
	//showNode(x);
	//showNode(y);
	return  flag;
}

//��������һ��״̬�������ӵ�λ��
void swapChess(int x1,int y1,int x2,int y2,Node &temp){
	int t;
	t=temp.board[x1][y1];
	temp.board[x1][y1]=temp.board[x2][y2];
	temp.board[x2][y2]=t;
}


   //���� �ж��Ƿ��ǿ���չ�ڵ㣬Ҳ��������ڵ��Ƿ������ĳ�������������ң��ƶ�

//�����ж�������������һ���ǣ��ƶ�֮����������Ĵ���
//����һ�����ƶ�֮����������������ظ�����ԭ����·�����ֻ����ѭ����
bool isExtendNode(int x,int y,Node &t){//t=closed[temp.order] ,x,y���ƶ�֮���λ�ã�t�Ǹ��׽ڵ�
	//3��if�ṹ
	if(t.parent!=NULL)//���׽ڵ����
	{
		if((x>=0)&&(x<=2)&&(y>=0)&&(y<=2))//�ƶ�֮����������
        {
            if(!((x == t.parent->zeroX)&&(y == t.parent->zeroY)))//�ýڵ��0x,0y�͸��׽ڵ㲻һ��
                return true;
            else
                return false;//�����ƶ��Ĵ���
        }
        else
            return false;//�ƶ�֮����������
	}
	else if((x>=0)&&(x<=2)&&(y>=0)&&(y<=2))//���׽ڵ㲻���ڣ����ƶ�֮��Ľڵ���������
		return true;
//	else
//		return false;
}



//��
Node* extendNodeUP(Node &t){//t��close���е�����

	int x=t.zeroX-1;
	int y=t.zeroY;
	if(isExtendNode(x,y,t))//����չ�������ƶ�
	{
		Node *p=(Node *)malloc(sizeof(Node));//�����ӽڵ�

		//�������ϵ����ӽ����ƶ�
		*p=t;
		swapChess(x,y,t.zeroX,t.zeroY,*p);

		//���µĽڵ���г�ʼ��
		p->order=++order;
		p->zeroX=x;
		p->zeroY=y;
		p->parent=&t;//������ָ��ָ���׽ڵ�
		return p;
	}
	else//������չ
		return NULL;
}

//��
Node* extendNodeDown(Node &t){//t=closed[temp.order] ��close���е���Ϣ
	int x=t.zeroX+1;
	int y=t.zeroY;
	if(isExtendNode(x,y,t))
	{
		Node *p=(Node *)malloc(sizeof(Node));
		*p=t;
		swapChess(x,y,t.zeroX,t.zeroY,*p);
		p->order=++order;
		p->zeroX=x;
		p->zeroY=y;
		p->parent=&t;
		return p;
	}
	else
		return NULL;
}


//��
Node* extendNodeRight(Node &t){
	int x=t.zeroX;
	int y=t.zeroY+1;
	if(isExtendNode(x,y,t))
	{
		Node *p=(Node *)malloc(sizeof(Node));
		*p=t;
		swapChess(x,y,t.zeroX,t.zeroY,*p);
		p->order=++order;
		p->zeroX=x;
		p->zeroY=y;
		p->parent=&t;
		return p;
	}
	else
		return NULL;
}

//��
Node* extendNodeLeft(Node &t){
	int x=t.zeroX;
	int y=t.zeroY-1;
	if(isExtendNode(x,y,t))
	{
		Node *p=(Node *)malloc(sizeof(Node));
		*p=t;
		swapChess(x,y,t.zeroX,t.zeroY,*p);
		p->order=++order;
		p->zeroX=x;
		p->zeroY=y;
		p->parent=&t;
		return p;
	}
	else
		return NULL;
}


//�����������
int GFS(Node &begin,Node &end,queue<Node> &open){//������ ��ʼ�ڵ�  ��ֹ�ڵ�  ����open����
	if(!open.empty()){                           //��ֻ����һ��
		cout<<"��ʼ�ӷǿ�"<<endl;
		return 0;
	}
	//��ʼ�ڵ����
	open.push(begin);

	Node temp;//�ڵ�
	Node *eNode;//�ڵ�ָ��

	//��ʼ���в�Ϊ�գ�������ѭ�������й������
	while(!open.empty())
	{
		temp = open.front();//ȡ��ͷ

		open.pop(); //�Ѷ�ͷ����

		closed[temp.order]=temp;//�Ѷ�ͷ�����Ǹ�close���С�

       //�Ƿ�Ŀ��״̬��
		if(judgeBoard(temp,sg)) return temp.order;  

       //�����ƶ�
		if((eNode=extendNodeLeft(closed[temp.order]))!=NULL){//enodeָ���µĽڵ�,extendʱ������order++����
			open.push((*eNode));//�ѽڵ���������           //�������ָ������ӣ������ƶ�֮�������½ڵ����Ϣ����
			                                                  //���б仯
			//չʾһ�½ڵ�
			//showNode(*(eNode->parent));
			//showNode(*eNode);
		}
		if((eNode=extendNodeUP(closed[temp.order]))!=NULL){
			open.push((*eNode));
			//showNode(*(eNode->parent));
			//showNode(*eNode);
		}
		if((eNode=extendNodeRight(closed[temp.order]))!=NULL){
			open.push((*eNode));
			//showNode(*(eNode->parent));
			//showNode(*eNode);
		}
		if((eNode=extendNodeDown(closed[temp.order]))!=NULL){
			open.push((*eNode));
			//showNode(*(eNode->parent));
			//showNode(*eNode);
		}
	}
	return 0;
}


//Ѱ��·������������
void findPath(Node *closed,int endOrder){
	Node *p = &closed[endOrder];
	while(p!=NULL)
	{
		showNode(*p);
		cout<<"---------------------------"<<endl;
		p=p->parent;
	}
}


//������
int main(){
	queue<Node> open;	//open������
	//cout<<"��ʼ״̬:";
	showNode(s0);
	//cout<<"Ŀ��״̬:";
	showNode(sg);
	cout<<"---------------------------"<<endl;


	int endOrder = GFS(s0,sg,open);
	//cout<<"---------------------------"<<endl;
	/*
	for(int i=1;i<=endOrder;i++)
		showNode(closed[i]);
	*/
	findPath(closed,endOrder);
	return 0;
}
