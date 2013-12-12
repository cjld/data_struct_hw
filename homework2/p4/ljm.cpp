#include <cstdio>

#define SET_DFN(seq, index) cross[seq]->getHead()->getV()->setDfn(index)
#define SET_LOW(seq, index) cross[seq]->getHead()->getV()->setLow(index)

#define DFN(seq) cross[seq]->getHead()->getV()->getDfn()
#define LOW(seq) cross[seq]->getHead()->getV()->getLow()

#define MAX(a, b) ((a) > (b)) ? (a) : (b);

using namespace std;

int N, M;

int convert(char c) {
    switch(c) {
        case 'm':return 1;
        case 'M':return 0;
    }
}

class Vertex {
    public:
        Vertex(int seq_ = 0) : seq(seq_), value(0), visit(false), instack(false), inqueue(false), dist(-1), low(-1), dfn(-1) {}
        int getValue() {
            return value;
        }
        int getSeq() {
            return seq;
        }
        int getDfn() {
            return dfn;
        }
        int getLow() {
            return low;
        }
        int getDist() {
            return dist;
        }
        bool visited() {
            return visit;
        }
        bool inStack() {
            return instack;
        }
        bool inQueue() {
            return inqueue;
        }
        void setDist(int dist_) {
            dist = dist_;
        }
        void setVisit(bool visit_) {
            visit = visit_;
        }
        void setStack(bool instack_) {
            instack = instack_;
        }
        void setQueue(bool inqueue_) {
            inqueue = inqueue_;
        }
        void setValue(int value_) {
            value = value_;
        }
        void setData(char data_) {
            data = data_; 
            value = convert(data_);
        }
        void setDfn(int dfn_) {
            dfn = dfn_;
        }
        void setLow(int low_) {
            low = low_;
        }
        void setSeq(int seq_) {
            seq = seq_;
        }
    private:
        char data;
        bool visit, instack, inqueue;
        int seq, value, dfn, low, dist;
}; 

class Node {
    public:
        Node(Vertex * v_ = NULL, Node * next_ = NULL) : v(v_), next(next_) {}
        Node(int seq_): next(NULL) {
            v = new Vertex(seq_);
        }
        Vertex * getV() {
            return v;
        }
        Node * getNext() {
            return next;
        }
        void setNext(Node * next_) {
            next = next_;
        }
    private:
        Vertex * v;
        Node * next;
};

class List {
    public:
        List(int seq_) : degree(0) {
            head = new Node(seq_);
        }
        Node * getHead() {
            return head;
        }
        void addSucc(Vertex * succ_) {
            degree ++;
            Node * next = new Node(succ_);
            next->setNext(head->getNext());
            head->setNext(next);
        }
        void show() {
            Node * u = head;
            printf("list:");
            while (u != NULL) {
                printf("%d ", u->getV()->getSeq());
                u = u->getNext();
            }
            printf("value %d\n", head->getV()->getValue());
            //printf("\n");
        }

    private:
        int degree;
        Node * head;
};

class Graph {
    public:
        Graph(int size_) : size(size_), sccNum(0), sccList(NULL) {
            cross = new List*[size];
            for (int i = 0; i < size; i ++) {
                cross[i] = new List(i);
            }
        }
        List ** getCross() {
            return cross;
        }
        void setBE(int begin_, int end_) {
            begin = begin_;
            end = end_;
        }
        void setNode(int i, char c) {
            cross[i]->getHead()->getV()->setData(c);
        }
        void show() {
            for (int i = 0; i < size; i ++) {
                cross[i]->show();
            }
            if (sccList != NULL) {
                for (int i = 0; i < size; i ++) {
                    printf("node %d scc %d\n", i, sccList[i]);
                }
            }
        }
        Graph * reconstruct() {
            Graph * nGraph = new Graph(sccNum);
            for (int i = 0; i < size; i ++) {
                nGraph->getCross()[sccList[i]]->getHead()->getV()->setValue(nGraph->getCross()[sccList[i]]->getHead()->getV()->getValue() + cross[i]->getHead()->getV()->getValue());
                Node * u = cross[i]->getHead()->getNext();
                while (u != NULL) {
                    nGraph->getCross()[sccList[i]]->addSucc(nGraph->getCross()[sccList[u->getV()->getSeq()]]->getHead()->getV());
                    u = u->getNext();
                }
            }
            nGraph->setBE(sccList[0], sccList[size - 1]);
            return nGraph;
        }
/********************************************************************************************
 * Functions to find path;
 ********************************************************************************************/
        void spfa() {
            int * queue = new int[N * 50], head = 0, tail = -1;
            cross[0]->getHead()->getV()->setDist(1 - cross[0]->getHead()->getV()->getValue());
            queue[++tail] = 0;
            cross[0]->getHead()->getV()->setQueue(true);
            
            while (head <= tail) {
                int seq = queue[head ++];
                cross[seq]->getHead()->getV()->setQueue(false);
                Node * v = cross[seq]->getHead()->getNext();
                while (v != NULL) {
                    if ((v->getV()->getDist() == -1) || (v->getV()->getDist() > (cross[seq]->getHead()->getV()->getDist() - v->getV()->getValue() + 1))) {
                        v->getV()->setDist(cross[seq]->getHead()->getV()->getDist() - v->getV()->getValue() + 1);
                        if (!v->getV()->inQueue()) {
                            queue[++tail] = v->getV()->getSeq();
                            v->getV()->setQueue(true);
                        }
                    }
                    v = v->getNext();
                }
            }
            printf("%d\n", cross[size - 1]->getHead()->getV()->getDist());
        }
        void dijkstra() { 
        }
        void SCC() {
            int * s = new int[N + 1], index = -1, top = -1;
            sccList = new int[N + 1];
            for (int i = 0; i < N; i ++) {
                sccList[i] = N;
            }
            for (int i = 0; i < N; i ++)
                if (sccList[i] == N)
                    tarjan(i, s, top, index);
            //printf("%d %d\n", index, top);
        }
        
        void topology() {
            //printf("begin end: %d %d\n", begin, end);
            printf("%d\n", dfs(begin));
        }
        int dfs(int seq) {
            Node * u = cross[seq]->getHead()->getNext();
            int maxDist = -1;
            /*if (seq == end) {
                cross[seq]->getHead()->getV()->setVisit(true);
                cross[seq]->getHead()->getV()->setDist(cross[seq]->getHead()->getV()->getValue());
                return cross[seq]->getHead()->getV()->getDist();
            }*/
            /*if (u == NULL && (seq != end)) {
                cross[seq]->getHead()->getV()->setDist(-1);
                cross[seq]->getHead()->getV()->setVisit(true);
                return -1;
            }*/
            while (u != NULL) {
                int vSeq = u->getV()->getSeq();
                if (vSeq != seq && !u->getV()->visited()) {
                    if (vSeq == end) {
                        maxDist = u->getV()->getValue();
                        u->getV()->setDist(maxDist);
                        u->getV()->setVisit(true);
                        break;
                    }
                    int tmp = dfs(vSeq);
                    if (tmp != -1) {
                        maxDist = MAX(maxDist, tmp);
                        //printf("mdist : %d %d\n", maxDist, vSeq);
                    }
                }
                else if (vSeq != seq) {
                    if (vSeq == end) {
                        maxDist = u->getV()->getDist();
                        break;
                    }
                    if (u->getV()->getDist() != -1)
                        maxDist = MAX(maxDist, u->getV()->getDist());
                    //printf("mdist : %d %d\n", maxDist, vSeq);
                }
                u->getV()->setVisit(true);
                u = u->getNext();
            }
            if (maxDist == -1) {
                cross[seq]->getHead()->getV()->setDist(-1);
                cross[seq]->getHead()->getV()->setVisit(true);
                return -1;
            }
            cross[seq]->getHead()->getV()->setDist(maxDist + cross[seq]->getHead()->getV()->getValue());
            return cross[seq]->getHead()->getV()->getDist();
        }

    protected:
        void tarjan(int seq, int *s, int& top, int& index) { 
            index ++;
            SET_DFN(seq, index);
            SET_LOW(seq, index);
            s[++top] = seq;
            cross[seq]->getHead()->getV()->setStack(true);
            cross[seq]->getHead()->getV()->setVisit(true);

            Node * v = cross[seq]->getHead()->getNext();
            while (v != NULL) {
                if (!v->getV()->visited()) {
                    //printf("low v, low u, dfn v, dfn u : %d %d %d %d\n", v->getV()->getLow(), LOW(seq), v->getV()->getDfn(), DFN(seq));
                    tarjan(v->getV()->getSeq(), s, top, index);
                    if (v->getV()->getLow() < LOW(seq)) {
                        SET_LOW(seq, v->getV()->getLow());
                    }
                }
                else if (v->getV()->inStack()) {
                    if (DFN(v->getV()->getSeq()) < LOW(seq)) {
                        SET_LOW(seq, DFN(v->getV()->getSeq()));
                    }
                }
                v = v->getNext();
            }
            if (DFN(seq) == LOW(seq)) {
                int w;
                //printf("SCC: %d %d\n", DFN(seq), LOW(seq));
                do {
                    w = s[top];
                    top --;
                    cross[w]->getHead()->getV()->setStack(false);
                    sccList[w] = sccNum;
                    //printf("%d ", w);
                
                } while (seq != w);
                sccNum ++;
                //printf("\n");
            }
        }
        
    private:
        int size, *sccList, sccNum, begin, end;
        List ** cross;
};

int main() {
    //freopen("input.txt","r", stdin);
    //freopen("out.txt", "w", stdout);
    scanf("%d%d", &N, &M);
    //printf("n m : %d %d\n", N, M);

    getchar();
    Graph * graph = new Graph(N);
    for (int i = 0; i < N; i ++) {
        //char tmp = getchar();
        graph->setNode(i, getchar());
        //printf("tmp : %c\n", tmp);
    }
    getchar();
    while (M --) {
        int in, out;
        scanf("%d%d", &in, &out);
        //printf("in, out : %d %d\n", in, out);
        graph->getCross()[in]->addSucc(graph->getCross()[out]->getHead()->getV());
    }

    //problem 1;
    graph->spfa();
    //graph->show();

    //problem 2;
    graph->SCC();
    //graph->show();

    Graph * newGraph = graph->reconstruct();
    //newGraph->show();

    newGraph->topology();

    return 0;
}
