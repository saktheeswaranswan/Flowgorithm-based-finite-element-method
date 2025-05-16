#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

// Headers
string toString (double);
int toInt (string);
double toDouble (string);
void solveSystem(double k[], double f[], double u[], int n);

int main() {
    int nNodes, nElems;

    cout << "Number of Nodes:";
    cin >> nNodes;
    cout << "Number of Elements:";
    cin >> nElems;
    double e, a, l;
    int i;
    double k[nNodes * nNodes];
    double f[nNodes], u[nNodes];
    int elem[nElems * 2];

    for (i = 1; i <= nNodes * nNodes; i++) {
        k[i - 1] = 0;
    }
    for (i = 1; i <= nNodes; i++) {
        f[i - 1] = 0;
    }
    for (i = 1; i <= nElems; i++) {
        cout << "Element " << i << " start-node:";
        cin >> elem[i - 1 * 2];
        cout << "Element " << i << " end-node:";
        cin >> elem[i - 1 * 2 + 1];
        cout << "E, A, L for element " << i << ":";
        cin >> e;
        cin >> a;
        cin >> l;
        double ke;

        ke = e * a / l;
        int n1, n2, idx;

        n1 = elem[i - 1 * 2];
        n2 = elem[i - 1 * 2 + 1];
        idx = n1 - 1 * nNodes + n1 - 1;
        k[idx] = k[idx] + ke;
        idx = n1 - 1 * nNodes + n2 - 1;
        k[idx] = k[idx] - ke;
        idx = n2 - 1 * nNodes + n1 - 1;
        k[idx] = k[idx] - ke;
        idx = n2 - 1 * nNodes + n2 - 1;
        k[idx] = k[idx] + ke;
    }
    for (i = 1; i <= nNodes; i++) {
        cout << "Load at node " << i << ":";
        cin >> f[i - 1];
    }
    for (i = 1; i <= nNodes; i++) {
        k[i - 1 * nNodes + 0] = 0;
        k[0 * nNodes + i - 1] = 0;
    }
    k[0] = 1;
    f[0] = 0;
    solveSystem(k, f, u, nNodes);
    cout << "Nodal Displacements:" << endl;
    for (i = 1; i <= nNodes; i++) {
        cout << "u[" << i << "] = " << u[i - 1] << endl;
    }
    return 0;
}

void solveSystem(double k[], double f[], double u[], int n) {
    int i, j, k;
    double factor;

    for (k = 1; k <= n - 1; k++) {
        for (i = k + 1; i <= n; i++) {
            factor = k[i - 1 * n + k - 1] / k[k - 1 * n + k - 1];
            for (j = k; j <= n; j++) {
                k[i - 1 * n + j - 1] = k[i - 1 * n + j - 1] - factor * k[k - 1 * n + j - 1];
            }
            f[i - 1] = f[i - 1] - factor * f[k - 1];
        }
    }
    u[n - 1] = f[n - 1] / k[n - 1 * n + n - 1];
    for (i = n - 1; i >= 1; i--) {
        double sum;

        sum = 0;
        for (j = i + 1; j <= n; j++) {
            sum = sum + k[i - 1 * n + j - 1] * u[j - 1];
        }
        u[i - 1] = f[i - 1] - sum / k[i - 1 * n + i - 1];
    }
}

// The following implements type conversion functions.
string toString (double value) { //int also
    stringstream temp;
    temp << value;
    return temp.str();
}

int toInt (string text) {
    return atoi(text.c_str());
}

double toDouble (string text) {
    return atof(text.c_str());
}
