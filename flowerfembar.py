def solveSystem(k, f, u, n):
    for k in range(1, n - 1 + 1, 1):
        for i in range(k + 1, n + 1, 1):
            factor = k[i - 1 * n + k - 1] / k[k - 1 * n + k - 1]
            for j in range(k, n + 1, 1):
                k[i - 1 * n + j - 1] = k[i - 1 * n + j - 1] - factor * k[k - 1 * n + j - 1]
            f[i - 1] = f[i - 1] - factor * f[k - 1]
    u[n - 1] = f[n - 1] / k[n - 1 * n + n - 1]
    for i in range(n - 1, 1 - 1, -1):
        sum = 0
        for j in range(i + 1, n + 1, 1):
            sum = sum + k[i - 1 * n + j - 1] * u[j - 1]
        u[i - 1] = f[i - 1] - sum / k[i - 1 * n + i - 1]

# Main
print("Number of Nodes:", end='', flush=True)
nNodes = int(input())
print("Number of Elements:", end='', flush=True)
nElems = int(input())
k = [0] * (nNodes * nNodes)
f = [0] * (nNodes)
u = [0] * (nNodes)
elem = [0] * (nElems * 2)

for i in range(1, nNodes * nNodes + 1, 1):
    k[i - 1] = 0
for i in range(1, nNodes + 1, 1):
    f[i - 1] = 0
for i in range(1, nElems + 1, 1):
    print("Element " + str(i) + " start-node:", end='', flush=True)
    elem[i - 1 * 2] = int(input())
    print("Element " + str(i) + " end-node:", end='', flush=True)
    elem[i - 1 * 2 + 1] = int(input())
    print("E, A, L for element " + str(i) + ":", end='', flush=True)
    e = float(input())
    a = float(input())
    l = float(input())
    ke = e * a / l
    n1 = elem[i - 1 * 2]
    n2 = elem[i - 1 * 2 + 1]
    idx = n1 - 1 * nNodes + n1 - 1
    k[idx] = k[idx] + ke
    idx = n1 - 1 * nNodes + n2 - 1
    k[idx] = k[idx] - ke
    idx = n2 - 1 * nNodes + n1 - 1
    k[idx] = k[idx] - ke
    idx = n2 - 1 * nNodes + n2 - 1
    k[idx] = k[idx] + ke
for i in range(1, nNodes + 1, 1):
    print("Load at node " + str(i) + ":", end='', flush=True)
    f[i - 1] = float(input())
for i in range(1, nNodes + 1, 1):
    k[i - 1 * nNodes + 0] = 0
    k[0 * nNodes + i - 1] = 0
k[0] = 1
f[0] = 0
solveSystem(k, f, u, nNodes)
print("Nodal Displacements:")
for i in range(1, nNodes + 1, 1):
    print("u[" + str(i) + "] = " + str(u[i - 1]))
