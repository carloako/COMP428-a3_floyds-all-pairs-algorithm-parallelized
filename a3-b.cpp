#include <cstdlib>
#include <climits>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <mpi.h>

using namespace std;

// Replace INF with a big number, be careful of overflows in case you use INT_MAX (addition of 2 INT_MAX will cause overflows)
// Instead, maybe use INF = (INT_MAX - 2)/2 or INT_MAX/10 etc etc;

static const int INF = 100;

int n = 36;

int arr[36][36] = {
    {0, 1, INF, INF, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, 0, 2, INF, 3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, 0, 3, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, 0, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, 0, 5, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 20, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {6, INF, INF, INF, INF, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, 0, 1, INF, INF, INF, INF, 6, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, 0, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, 0, 3, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, 6, INF, 3, INF, INF, 0, 1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 2, INF, 3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 5, INF, INF, INF, INF, INF, 10, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 6, INF, INF, INF, INF, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF, 2, INF, INF, 6, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 5, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, 0, INF, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 3, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 14},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, 1, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {25, INF, INF, 10, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 1, 2, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 3, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, 3, INF, INF, 0, INF, INF, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF, INF, INF, INF, 6, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, 5, 0, INF, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, 0, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, 3, 0, INF, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, 0, INF, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 3, INF, 1, 0, INF},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1, 0}};

int main(int argc, char *argv[])
{

    int id;

    int numProcesses;

    MPI_Init(&argc, &argv);

    float initialTime = MPI_Wtime();

    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    int grpsize = sqrt(numProcesses);

    int colorRow = id / grpsize;
    int colorColumn = id % grpsize;

    MPI_Comm rowComm;
    MPI_Comm colComm;

    MPI_Comm_split(MPI_COMM_WORLD, colorRow, id, &rowComm);
    MPI_Comm_split(MPI_COMM_WORLD, colorColumn, id, &colComm);

    int rowId;
    int rowSize;

    int colId;
    int colSize;

    MPI_Comm_size(rowComm, &rowSize);
    MPI_Comm_rank(rowComm, &rowId);
    MPI_Comm_size(colComm, &colSize);
    MPI_Comm_rank(colComm, &colId);

    int arrayRowSize = sqrt(pow(n, 2) / numProcesses);
    int array[arrayRowSize][arrayRowSize];

    if (id == 0)
    {
        // fill up p0 array
        for (int i = 0; i < arrayRowSize; i++)
        {
            for (int j = 0; j < arrayRowSize; j++)
            {
                array[i][j] = arr[i][j];
            }
        }

        // send partitions to other arrays
        for (int i = 1; i < numProcesses; i++)
        {
            for (int j = 0; j < arrayRowSize; j++)
            {
                int sendArr[arrayRowSize];
                for (int k = 0; k < arrayRowSize; k++)
                {
                    sendArr[k] = arr[j + i / grpsize * arrayRowSize][k + i % grpsize * arrayRowSize];
                }
                MPI_Send(sendArr, arrayRowSize, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
    }
    else
    {
        // receive partitions from p0
        for (int i = 0; i < arrayRowSize; i++)
        {
            MPI_Recv(array[i], arrayRowSize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    // pipeline attempt
    for (int k = 1; k <= n; k++)
    {
        int prevk = k - 1;
        // send column
        int colSender = 0;
        int colArr[arrayRowSize];
        for (int row = 0; row < rowSize; row++)
        {
            if (prevk >= (row * arrayRowSize) && prevk < ((row + 1) * arrayRowSize))
            {
                colSender = row;
                break;
            }
        }
        int destLeft = rowId - 1;
        int destRight = rowId + 1;
        if (prevk >= (rowId * arrayRowSize) && prevk < ((rowId + 1) * arrayRowSize))
        {
            for (int i = 0; i < arrayRowSize; i++)
            {
                colArr[i] = array[i][prevk % arrayRowSize];
            }
            // send right
            if (rowId < rowSize - 1)
                MPI_Send(colArr, arrayRowSize, MPI_INT, destRight, 0, rowComm);
            // send left
            if (rowId > 0)
                MPI_Send(colArr, arrayRowSize, MPI_INT, destLeft, 0, rowComm);
        }
        else
        {
            MPI_Status status;
            MPI_Recv(colArr, arrayRowSize, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, rowComm, &status);
            if (rowId < status.MPI_SOURCE && rowId > 0)
                MPI_Send(colArr, arrayRowSize, MPI_INT, destLeft, 0, rowComm);
            else if (rowId > status.MPI_SOURCE && rowId < rowSize - 1)
                MPI_Send(colArr, arrayRowSize, MPI_INT, destRight, 0, rowComm);
            // else
            // cout << "Error row sending in id " << id << "\n";
        }

        // send row
        int rowSender = 0;
        int rowArr[arrayRowSize];
        for (int col = 0; col < colSize; col++)
        {
            if (prevk >= (col * arrayRowSize) && prevk < ((col + 1) * arrayRowSize))
            {
                rowSender = col;
                break;
            }
        }
        destLeft = colId - 1;
        destRight = colId + 1;
        if (prevk >= (colId * arrayRowSize) && prevk < ((colId + 1) * arrayRowSize))
        {
            for (int i = 0; i < arrayRowSize; i++)
            {
                rowArr[i] = array[prevk % arrayRowSize][i];
            }
            // send right
            if (colId < colSize - 1)
                MPI_Send(rowArr, arrayRowSize, MPI_INT, destRight, 0, colComm);
            // send left
            if (colId > 0)
                MPI_Send(rowArr, arrayRowSize, MPI_INT, destLeft, 0, colComm);
        }
        else
        {
            MPI_Status status;
            MPI_Recv(rowArr, arrayRowSize, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, colComm, &status);
            if (colId < status.MPI_SOURCE && colId > 0)
                MPI_Send(rowArr, arrayRowSize, MPI_INT, destLeft, 0, colComm);
            else if (colId > status.MPI_SOURCE && colId < colSize - 1)
                MPI_Send(rowArr, arrayRowSize, MPI_INT, destRight, 0, colComm);
        }

        // compute matrix of process
        for (int i = 0; i < arrayRowSize; i++)
        {
            for (int j = 0; j < arrayRowSize; j++)
            {
                array[i][j] = min(array[i][j], rowArr[j] + colArr[i]);
            }
        }
    }

    int finalMatrix[n][n];
    int counts[numProcesses];
    for (int i = 0; i < numProcesses; i++)
    {
        counts[i] = arrayRowSize;
    }
    int displacements[numProcesses];
    for (int i = 0; i < numProcesses; i++)
    {
        displacements[i] = i * arrayRowSize;
    }
    // gather matrix
    if (id == 0)
    {
        MPI_Status status;
        for (int i = 0; i < arrayRowSize; i++)
        {
            int tempArr[arrayRowSize * numProcesses];
            MPI_Gatherv(array[i], arrayRowSize, MPI_INT, tempArr, counts, displacements, MPI_INT, 0, MPI_COMM_WORLD);
            for (int proc = 0; proc < numProcesses; proc++)
            {
                int rowIndex = proc / rowSize;
                int colIndex = proc % colSize;
                for (int j = 0; j < arrayRowSize; j++)
                {
                    finalMatrix[i + (rowIndex * arrayRowSize)][j + (colIndex * arrayRowSize)] = tempArr[j + proc * arrayRowSize];
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < arrayRowSize; i++)
        {
            MPI_Gatherv(array[i], arrayRowSize, MPI_INT, NULL, NULL, NULL, MPI_INT, 0, MPI_COMM_WORLD);
        }
    }

    ios init(NULL);
    init.copyfmt(cout);

    // print matrix
    if (id == 0)
    {
        for (int i = 0; i < n; i++)
        {
            cout << "{";
            for (int j = 0; j < n; j++)
            {
                cout << setw(2) << finalMatrix[i][j] << " ";
            }
            cout.copyfmt(init);
            cout << "}\n";
        }
    }
    cout << "\n";

    MPI_Comm_free(&rowComm);
    MPI_Comm_free(&colComm);

    if (id == 0)
    {
        float finalTime = MPI_Wtime();
        float duration = (finalTime - initialTime) * 1000;
        cout << "Floyd's algorithm using pipelining with " << numProcesses << " process/es took ";
        printf("%.3fms\n", duration);
    }

    MPI_Finalize();

    return 0;
}
