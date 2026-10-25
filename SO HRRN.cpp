#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    bool completed;
};

int main() {
    int n = 10;
    Process p[10] = {
        {1, 2, 10, 0, 0, 0, false},
        {2, 5, 3, 0, 0, 0, false},
        {3, 1, 10, 0, 0, 0, false},
        {4, 7, 1, 0, 0, 0, false},
        {5, 0, 5, 0, 0, 0, false},
        {6, 5, 10, 0, 0, 0, false},
        {7, 1, 7, 0, 0, 0, false},
        {8, 0, 1, 0, 0, 0, false},
        {9, 3, 5, 0, 0, 0, false},
        {10, 0, 2, 0, 0, 0, false}
    };

    int completedCount = 0;
    int currentTime = 0;

    cout << "========================================================" << endl;
    cout << "   SIMULASI PENJADWALAN CPU - HRRN (NON-PREEMPTIVE)     " << endl;
    cout << "   NPM: 2517051030                                     " << endl;
    cout << "========================================================" << endl << endl;

    int minAt = p[0].at;
    for(int i = 1; i < n; i++) {
        if(p[i].at < minAt) minAt = p[i].at;
    }
    if(currentTime < minAt) currentTime = minAt;

    while (completedCount < n) {
        int idx = -1;
        float maxRR = -1.0;

        cout << "--------------------------------------------------------" << endl;
        cout << "Waktu Saat Ini (Current Time) = " << currentTime << endl;
        cout << setw(6) << "PID" << setw(8) << "AT" << setw(8) << "BT" << setw(8) << "WT" << setw(16) << "Response Ratio" << endl;
        cout << "--------------------------------------------------------" << endl;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= currentTime) {
                int wt = currentTime - p[i].at;
                float rr = (float)(wt + p[i].bt) / p[i].bt;
                
                cout << setw(5) << "P" << p[i].id
                     << setw(8) << p[i].at 
                     << setw(8) << p[i].bt 
                     << setw(8) << wt 
                     << setw(16) << fixed << setprecision(2) << rr << endl;

                if (rr > maxRR) {
                    maxRR = rr;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            int nextAt = -1;
            for (int i = 0; i < n; i++) {
                if (!p[i].completed) {
                    if (nextAt == -1 || p[i].at < nextAt) {
                        nextAt = p[i].at;
                    }
                }
            }
            currentTime = nextAt;
            cout << "[Info] CPU Idle, melompat ke waktu: " << currentTime << endl;
            continue;
        }

        cout << "--------------------------------------------------------" << endl;
        cout << "=> Proses Terpilih: P" << p[idx].id << " (Response Ratio Tertinggi: " << fixed << setprecision(2) << maxRR << ")\n\n";

        currentTime += p[idx].bt;
        p[idx].ct = currentTime;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].completed = true;
        completedCount++;
    }

    cout << "\n========================================================" << endl;
    cout << "             TABEL HASIL AKHIR ALGORITMA HRRN           " << endl;
    cout << "========================================================" << endl;
    cout << setw(6) << "PID" << setw(8) << "AT" << setw(8) << "BT" << setw(8) << "CT" << setw(8) << "TAT" << setw(8) << "WT" << endl;
    cout << "--------------------------------------------------------" << endl;

    float totalTat = 0, totalWt = 0;
    for (int i = 0; i < n; i++) {
        totalTat += p[i].tat;
        totalWt += p[i].wt;
        cout << setw(5) << "P" << p[i].id
             << setw(8) << p[i].at
             << setw(8) << p[i].bt
             << setw(8) << p[i].ct
             << setw(8) << p[i].tat
             << setw(8) << p[i].wt << endl;
    }
    cout << "--------------------------------------------------------" << endl;
    cout << fixed << setprecision(2);
    cout << "Rata-rata Turnaround Time (TAT) : " << (totalTat / n) << endl;
    cout << "Rata-rata Waiting Time (WT)     : " << (totalWt / n) << endl;
    cout << "========================================================" << endl;

    return 0;
}
