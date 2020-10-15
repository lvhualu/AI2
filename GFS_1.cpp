#include<iostream>
#include<queue>
#define MAX 5000
using namespace std;

struct Node{
	int order;//节点序号
	int board[3][3];   //状态
	int zeroX;      //0的x坐标
	int zeroY;      //0的y坐标
	struct Node *parent;    //子到父的指针
};

//起始状态
Node s0 = {
	1,
	{{2,8,3},{1,0,4},{7,6,5}},
	1,
	1,
	NULL
};


//终止状态，只是用来判断用的不需要有父节点
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

int order = s0.order;//节点标号从根节点开始

Node closed[MAX];	//closed表，顺序表，节点类型的顺序表

//输出节点的状态包括节点序号，节点状态，节点的父指针
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

//用来判断两个节点的状态是否相等
bool judgeBoard(Node x,Node y){
	bool flag = true;//标记位
	//在3*3的阵中有一个点不一样就会结束循环，并且把标记置为 false
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

//用来交换一下状态盘上棋子的位置
void swapChess(int x1,int y1,int x2,int y2,Node &temp){
	int t;
	t=temp.board[x1][y1];
	temp.board[x1][y1]=temp.board[x2][y2];
	temp.board[x2][y2]=t;
}


   //用来 判断是否是可扩展节点，也就是这个节点是否可以向某个方向（上下左右）移动

//所以判断条件有两个，一个是：移动之后不在棋盘里的错误。
//另外一个是移动之后在棋盘里，但是他重复走了原来的路，这种会出现循环。
bool isExtendNode(int x,int y,Node &t){//t=closed[temp.order] ,x,y是移动之后的位置，t是父亲节点
	//3层if结构
	if(t.parent!=NULL)//父亲节点存在
	{
		if((x>=0)&&(x<=2)&&(y>=0)&&(y<=2))//移动之后在棋盘中
        {
            if(!((x == t.parent->zeroX)&&(y == t.parent->zeroY)))//该节点的0x,0y和父亲节点不一样
                return true;
            else
                return false;//来回移动的错误
        }
        else
            return false;//移动之后不再棋盘里
	}
	else if((x>=0)&&(x<=2)&&(y>=0)&&(y<=2))//父亲节点不存在，且移动之后的节点在棋盘中
		return true;
//	else
//		return false;
}



//上
Node* extendNodeUP(Node &t){//t是close表中的内容

	int x=t.zeroX-1;
	int y=t.zeroY;
	if(isExtendNode(x,y,t))//可扩展，可以移动
	{
		Node *p=(Node *)malloc(sizeof(Node));//创建子节点

		//对棋盘上的棋子进行移动
		*p=t;
		swapChess(x,y,t.zeroX,t.zeroY,*p);

		//对新的节点进行初始化
		p->order=++order;
		p->zeroX=x;
		p->zeroY=y;
		p->parent=&t;//让他的指针指向父亲节点
		return p;
	}
	else//不可扩展
		return NULL;
}

//下
Node* extendNodeDown(Node &t){//t=closed[temp.order] 即close表中的信息
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


//右
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

//左
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


//广度优先搜索
int GFS(Node &begin,Node &end,queue<Node> &open){//参数有 初始节点  终止节点  还有open队列
	if(!open.empty()){                           //它只调用一次
		cout<<"初始队非空"<<endl;
		return 0;
	}
	//初始节点入队
	open.push(begin);

	Node temp;//节点
	Node *eNode;//节点指针

	//初始队列不为空，这里有循环，进行广度搜索
	while(!open.empty())
	{
		temp = open.front();//取队头

		open.pop(); //把队头弹出

		closed[temp.order]=temp;//把队头放入那个close表中、

       //是否到目标状态了
		if(judgeBoard(temp,sg)) return temp.order;  

       //进行移动
		if((eNode=extendNodeLeft(closed[temp.order]))!=NULL){//enode指向新的节点,extend时候会进行order++操作
			open.push((*eNode));//把节点放入队列中           //还会进行指针的连接，就是移动之后所有新节点的信息都会
			                                                  //进行变化
			//展示一下节点
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


//寻找路径，从下向上
void findPath(Node *closed,int endOrder){
	Node *p = &closed[endOrder];
	while(p!=NULL)
	{
		showNode(*p);
		cout<<"---------------------------"<<endl;
		p=p->parent;
	}
}


//主函数
int main(){
	queue<Node> open;	//open表，队列
	//cout<<"初始状态:";
	showNode(s0);
	//cout<<"目标状态:";
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
