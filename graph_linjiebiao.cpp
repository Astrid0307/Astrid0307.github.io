#include<iostream>
using namespace std;

#define VMAX 20

template<class verType,class eType>
struct eNode{
    int dest;
    verType weight;
    eNode* link;
};

template<class verType,class eType>
struct verNode{
    verType data;
    eNode<verType,eType>* adj;
};

template<class verType,class eType>
class graph{
private:
    int vnum,ednum;
    int vmax;
    bool isdirected;
    eNode<verType,eType>* verlist;
public:
    graph(bool direct);// 构造函数：初始化图结构，direct为是否有向图标志
    ~graph(); // 析构函数：释放图结构占用的内存
    int numberOfVertex() const { return verts; } // 返回图中的顶点数
    int numberOfEdge() const { return edges; } // 返回图中的边数

    int getVertex(verType vertex) const; // 根据顶点值返回其在顶点数组中的下标
    bool existEdge(verType vertex1, verType vertex2) const; // 判断两个顶点之间是否存在边
    int getFirstNeighbor(verType vertex) const; // 获取顶点的第一个邻接点，如果没有返回-1
    int getNextNeighbor(verType vertex1, verType vertex2) const; // 获取顶点vertex1相对于顶点vertex2的下一个邻接点，如果没有返回-1
    void disp() const; // 显示图的邻接矩阵
    void insertVertex(verType vertex); // 插入一个顶点
    void insertEdge(verType vertex1, verType vertex2, eType edge); // 插入一条边，连接vertex1和vertex2
    void removeVertex(verType vertex); // 删除一个顶点
    void removeEdge(verType vertex1, verType vertex2); // 删除一条边，连接vertex1和vertex2

};

template<class verType,class eType>
graph<verType,eType>::graph(bool direct){
    isdirected = direct;
    vnum = 0;
    ednum = 0;
    vmax = VMAX;
    verlist = new verNode<verType,eType> [vmax];
}

template<class verType,class eType>
graph<verType,eType>::~graph(){
    eNode<verType,eType>* p;
    for(int i = 0;i < vnum;i++){
        while(verlist[i].adj){
            p = verlist[i].adj;
            verlist[i].adj = p->link;
            delete p;
        }
    }

    delete[]verlist;
}

template<class verType,class eType>
void graph<verType,eType>:: insertEdge(verType vertex1, verType vertex2, eType edge){
    int i,j;
    for(i = 0;i < vnum;i++){
        if(verlist[i] == vertex1) break;
    }
    for(j = 0;j < vnum;j++){
        if(verlist[j] == vertex2) break;
    }
    if(i == vnum || j == vnum || i == j) return;

    eNode<verType,eType>*tmp = new eNode<verType,eType>;
    tmp->dest = j;
    tmp->link = verlist[i].adj;
    tmp->weight = edge;
    verlist[i].adj = tmp;

    if(! isdirected){
        tmp = new eNode<verType,eType>;
        tmp->dest = i;
        tmp->link = verlist[j].adj;
        tmp->weight = edge;
        verlist[j].adj = tmp;
    }

    ednum++;

}

template<class verType,class eType>
void graph<verType,eType>::removeVertex(verType vertex){
    int i;
    for(i = 0;i < vnum;i++){
        if(verlist[i] == vertex) break;
    }
    if(i == vnum) return;

    //删与该点相连的边
    int j;
    for(j = 0;j < vnum;j++){
        if(j != i){
            eNode<verType,eType>*p = verlist[j].adj
            while(p){
                if(p.adj->dest == i){
                    eNode<verType,eType>*tmp = p.adj;
                    p.adj = tmp->link;
                    delete tmp;
                }
                verlist[j].adj = 
            }
        }
    }
}