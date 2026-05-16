#include<iostream>
#include<vector>
using namespace std;

#define VMAX 20     //宏

template<class verType,class eType>
class graph {
private:
    int vnum;
    int ednum;
    int vmax;
    verType* verlist;
    eType** ematrix;
    eType noedge;
    bool isdirected;

public:
    graph(bool direct,eType e);
    ~graph();
    int numberOfVertex() const { return vnum; } // 返回图中的顶点数
    int numberOfEdge() const { return ednum; } // 返回图中的边数
    int getVertex(verType vertex) const; // 返回指定顶点在顶点列表中的下标
    bool existEdge(verType vertex1, verType vertex2) const; // 判断两个顶点之间是否存在边
    void insertVertex(verType vertex); // 插入一个顶点
    void insertEdge(verType vertex1, verType vertex2, eType edge); // 插入一条边
    void removeVertex(verType vertex); // 删除一个顶点
    void removeEdge(verType vertex1, verType vertex2); // 删除一条边
    int getFirstNeighbor(verType vertex) const; // 获取指定顶点的第一个邻接点
    int getNextNeighbor(verType vertex1, verType vertex2) const; // 获取指定顶点相对于另一个顶点的下一个邻接点
    void disp() const; // 显示邻接矩阵

};

template<class verType,class eType>
graph<verType,eType>::graph(bool direct,eType e){
    vnum = 0;
    ednum = 0;
    noedge = e;
    vmax = VMAX;
    isdirected = direct;    //初始化

    verlist = new verType[vmax];
    ematrix = new eType*[vmax];

    for(int i = 0;i < vmax;i++){
        ematrix[i] = new eType[vmax];
    }                                   //分配内存空间

    for(int i = 0;i < vmax;i++){
        for(int j = 0;j < vmax;j++){
            if(i == j){
                ematrix[i][j] = 0;
            }else{
                ematrix[i][j] = e;
            }
        }
    }
}

template<class verType,class eType>
graph<verType,eType>::~graph(){
    delete [] verlist;
    for(int i = 0;i < vmax;i++){
        delete [] ematrix[i];
    }
    delete [] ematrix;
}

template<class verType,class eType>
int graph<verType,eType>::getVertex(verType vertex) const{
    int i;
    for(i = 0;i < vnum;i++){
        if (verlist[i] == vertex) break;
    }

    if(i == vnum) return -1;

    return i;
}

template<class verType,class eType>
bool graph<verType,eType>::existEdge(verType vertex1, verType vertex2) const{
    int i,j;
    for(i = 0;i < vnum;i++){
        if(verlist[i] == vertex1) break;
    }

    for(j = 0;j < vnum;j++){
        if(verlist[j] == vertex2) break;
    }

    if(i == vnum || j == vnum || i == j) return false;

    if(ematrix[i][j] == noedge) return false;            //这两步判断分开写比较安全

    return true;
}

template<class verType,class eType>
void graph<verType,eType>::removeVertex(verType vertex){        //找到并删verlist的点，更改ednum，删邻接矩阵中的列/行,最后vnum--
    int i,j,k;
    for(i = 0;i < vnum;i++){
        if(verlist[i] == vertex) break;
    }

    if(i == vnum) return;    //避免后面越界

    for(j = i;j < vnum - 1;j++){
        verlist[j] = verlist[j + 1];
    }

    for(j = 0;j < vnum;j++){
        if(i != j && ematrix[i][j] != noedge) ednum--;         
    }

    if(isdirected){                                        //对于无向图，已删完。对于有向图，上一步只删了从该点出去的边，还需删指向该点的边
        for(k = 0;k < vnum;k++){
            if(k != i && ematrix[k][i] != noedge) ednum--;
        }
    }

    for(j = i;j < vnum - 1;j++){
        for(k = 0;k < vnum;k++){
            ematrix[k][j] == ematrix[k][j+1];          //删列
        }
    }

    for(j = i;j < vnum-1;j++){
        for(k = 0;k < vnum;k++){
            ematrix[j][k] == ematrix[j+1][k];
        }
    }

    vnum --;
}