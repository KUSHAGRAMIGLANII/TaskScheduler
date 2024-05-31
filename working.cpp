#include <bits/stdc++.h>
using namespace std;

vector<int> Waiting_time;
vector<int> TurnAround_time;
vector<int> Finish_time;

const static bool cmp(const tuple<string, int, int> &t1, const tuple<string, int, int> &t2) {
    return get<1>(t1) < get<1>(t2);
}

void sortByArrivalTime(vector<tuple<string, int, int>> &input_tuple) {
    sort(input_tuple.begin(), input_tuple.end(), cmp);
}

int getArrivalTime(const tuple<string, int, int> &t1) {
    return get<1>(t1);
}

int getBurstTime(const tuple<string, int, int> &t1) {
    return get<2>(t1);
}

void getFCFS(vector<tuple<string, int, int>> &input_tuple, int process_count, int time_span) {
    Waiting_time.resize(process_count);
    TurnAround_time.resize(process_count);
    Finish_time.resize(process_count);
    
    sortByArrivalTime(input_tuple);

    int time = 0;
    for (int i = 0; i < process_count; i++) {
        int AT = getArrivalTime(input_tuple[i]);
        int BT = getBurstTime(input_tuple[i]);

        if (time < AT) {
            time = AT;  // If the CPU is idle, skip to the arrival time of the next process
        }

        time += BT;
        if(time>time_span){
            time=time_span;
        
        Finish_time[i] = time;
        TurnAround_time[i] = Finish_time[i] - AT;
        Waiting_time[i] = TurnAround_time[i] - BT;
        break;
        }
        Finish_time[i] = time;
        TurnAround_time[i] = Finish_time[i] - AT;
        Waiting_time[i] = TurnAround_time[i] - BT;
    }
}

void RoundRobin(vector<tuple<string, int, int>> &input_tuple, int process_count, int quantum, int time_span) {
    Waiting_time.resize(process_count);
    TurnAround_time.resize(process_count);
    Finish_time.resize(process_count);

    sortByArrivalTime(input_tuple);
    queue<pair<int, int>> q;
    int time = get<1>(input_tuple[0]);
    int CQ = quantum; // Current quantum
    q.push({0, get<2>(input_tuple[0])});

    for (int i = time; i < time_span; i++) {
        if (!q.empty()) {
            int Pid = q.front().first;
            q.front().second -= 1;
            // cout<<q.front().second<<" "<<Pid<<endl;
            // Add arriving processes to the queue
            for (int j = 1; j < process_count; j++) {
                if (getArrivalTime(input_tuple[j]) == i+1) {
                    q.push({j, get<2>(input_tuple[j])});
                }
            }

            int remaining_burst = q.front().second;
            int idx = q.front().first;
            int AT = getArrivalTime(input_tuple[idx]);
            int BT = getBurstTime(input_tuple[idx]);

            CQ--;

            if (remaining_burst == 0 || i==time_span-1) {
                Finish_time[idx] = i + 1; // Process completes at this time
                TurnAround_time[idx] = Finish_time[idx] - AT;
                Waiting_time[idx] = TurnAround_time[idx] - BT;
                q.pop();
                CQ = quantum;
            } else if (CQ == 0 ) {
                q.pop();
                // cout<<remaining_burst<<"$"<<endl;
                q.push({idx, remaining_burst});
                CQ = quantum;
            }
           
            continue;
            
        }

        // Add arriving processes to the queue (missed outside if-else)
        for (int j = 1; j < process_count; j++) {
            if (getArrivalTime(input_tuple[j]) == i+1) {
                q.push({j, get<2>(input_tuple[j])});
            }
        }
    }
}
void printans(const vector<tuple<string, int, int>>& input_tuple, int process_count) {
    // Print ID row
    cout << "ID             ";
    for (int i = 0; i < process_count; i++) {
        cout << " | " << get<0>(input_tuple[i]);
    }
    cout <<" |"<< endl;

    // Print Arrival Time row
    cout << "Arrival Time   ";
    for (int i = 0; i < process_count; i++) {
        cout << " | " << get<1>(input_tuple[i]);
    }
    cout <<" |"<< endl;

    // Print Burst Time row
    cout << "Burst Time     ";
    for (int i = 0; i < process_count; i++) {
        cout << " | " << get<2>(input_tuple[i]);
    }
    cout <<" |"<< endl;

    // Print Waiting Time row
    cout << "Waiting Time   ";
    for (int i = 0; i < process_count; i++) {
        cout << " | " << Waiting_time[i];
    }
   cout <<" |"<< endl;

    // Print Turnaround Time row
    cout << "Turnaround Time";
    for (int i = 0; i < process_count; i++) {
        cout << " | " << TurnAround_time[i];
    }
    cout <<" |"<< endl;

    // Print Finish Time row
    cout << "Finish Time    ";
    for (int i = 0; i < process_count; i++) {
        cout << " | " << Finish_time[i];
    }
   cout <<" |"<< endl;
}

int main() {
    int process_count;
    int time_span;

    cout << "Enter Time Span: ";
    cin >> time_span;

    cout << "Enter Number of Processes: ";
    cin >> process_count;

    unordered_map<string, int> process_types;
    process_types["fcfs"] = 1;

    string process_name;
    cout << "Enter the process name: ";
    cin >> process_name;

    vector<tuple<string, int, int>> input_tuple;

    for (int i = 0; i < process_count; i++) {
        string process_id;
        int AT, BT;
        cout << "Enter the Process ID, Arrival Time, Burst Time: ";
        cin >> process_id >> AT >> BT;
        input_tuple.emplace_back(process_id, AT, BT);
    }

    if (process_name == "fcfs" || process_name=="FCFS") {
        getFCFS(input_tuple, process_count, time_span);
        printans(input_tuple, process_count);
    } else if (process_name == "rr" || process_name=="RR") {
        int quantum;
        cout << "Enter Quantum: ";
        cin >> quantum;
        RoundRobin(input_tuple, process_count, quantum, time_span);
        printans(input_tuple, process_count);
    }

    return 0;
}
