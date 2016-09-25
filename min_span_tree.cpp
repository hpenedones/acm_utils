#include <stdio.h>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
#define LIM 100

typedef struct _edge{
    int start;
    int end;
    float weight;
} Edge;


struct compare {

    bool operator()(const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    }
};

float pts[LIM][2];
bool visited[LIM];
int nvisited;


float dist(int i, int j) {

    return sqrt(    (pts[i][0]-pts[j][0])*(pts[i][0]-pts[j][0]) + 
                    (pts[i][1]-pts[j][1])*(pts[i][1]-pts[j][1]) );


}

int main(int argc, const char *argv[])
{
    int a, cases;
    scanf("%d\n",&cases);
    for(a=0; a<cases; a++) {
        int n;
        scanf("%d\n",&n);   
        int i;
        for (i = 0; i < n; i++) {
            scanf("%f %f\n",&pts[i][0], &pts[i][1]);
            visited[i] = false;
        }
        nvisited = 0;

        priority_queue<Edge, vector<Edge>, compare > pqueue;
        Edge fake;
        fake.start=-1;
        fake.end=0;
        fake.weight=0.0;
        pqueue.push(fake); /* fake initial edge */

        float min_span_tree = 0.0;
        Edge current;
        do {
            int j;
            do {
                current = pqueue.top();
                pqueue.pop();
            } while (visited[current.end]);
            visited[current.end]=true;
            nvisited++;
            min_span_tree += current.weight;
            for(j=0; j<n; j++)
                if (!visited[j])
                {
                    Edge e;
                    e.start = current.end;
                    e.end = j;
                    e.weight = dist(e.start, e.end);
                    pqueue.push(e);
                }
        }
        while(nvisited != n);          

        if (a>0) putchar('\n');
        printf("%.2f\n", min_span_tree);


    }
    return 0;
}
