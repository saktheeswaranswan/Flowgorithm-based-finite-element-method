import java.util.*;
import java.lang.Math;

public class Program {
    private static Scanner input = new Scanner(System.in);

    public static void main(String[] args) {
        int nNodes, nElems;

        System.out.print("Number of Nodes:");
        nNodes = input.nextInt();
        System.out.print("Number of Elements:");
        nElems = input.nextInt();
        double e, a, l;
        int i;
        double[] k = new double[nNodes * nNodes];
        double[] f = new double[nNodes], u = new double[nNodes];
        int[] elem = new int[nElems * 2];

        for (i = 1; i <= nNodes * nNodes; i++) {
            k[i - 1] = 0;
        }
        for (i = 1; i <= nNodes; i++) {
            f[i - 1] = 0;
        }
        for (i = 1; i <= nElems; i++) {
            System.out.print("Element " + i + " start-node:");
            elem[i - 1 * 2] = input.nextInt();
            System.out.print("Element " + i + " end-node:");
            elem[i - 1 * 2 + 1] = input.nextInt();
            System.out.print("E, A, L for element " + i + ":");
            e = input.nextDouble();
            a = input.nextDouble();
            l = input.nextDouble();
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
            System.out.print("Load at node " + i + ":");
            f[i - 1] = input.nextDouble();
        }
        for (i = 1; i <= nNodes; i++) {
            k[i - 1 * nNodes + 0] = 0;
            k[0 * nNodes + i - 1] = 0;
        }
        k[0] = 1;
        f[0] = 0;
        solveSystem(k, f, u, nNodes);
        System.out.println("Nodal Displacements:");
        for (i = 1; i <= nNodes; i++) {
            System.out.println("u[" + i + "] = " + u[i - 1]);
        }
    }
    
    public static void solveSystem(double[] k, double[] f, double[] u, int n) {
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
}
