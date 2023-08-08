
#include <iostream>
#include<iomanip>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;


class Process{
	string process_name;
	int Arrival_time;
	int Burst_time;
	int Completion_time;
	int Turn_Around_time;
	int Waiting_time;
	friend class Scheduling;

	public: Process(){
		Arrival_time = 0;
		Burst_time =0;
		Completion_time = 0;
		Turn_Around_time = 0;
		Waiting_time = 0;
	}

	public: void getdata(){

		cout<<"Enter the Process Name : ";
		cin>>process_name;

		cout<<"Enter the Arrival Time for this Process : ";
		cin>>Arrival_time;

		cout<<"Enter the Burst Time for this Process : ";
		cin>>Burst_time;
	}
	public : void display(){

		cout<<"Process "<<process_name<<" : "<<Arrival_time<<cout.width(10)<<Burst_time<<cout.width(10)<<Completion_time<<cout.width(10)<<Turn_Around_time<<cout.width(10)<<Waiting_time<<endl;
	}

};

class Scheduling{
	int n;
	Process processes[10];
	float avg_wt = 0;
	float avg_tat = 0;
    int remainingtime[10];
    int current_time = 0;
    int completed_tasks = 0;
    int curr ;
    qukeue<int> readyQ;
	public : Scheduling(int len){
		n = len;
	}
	public : void getProcess(){
		for(int i =0;i<n;i++){
			cout<<"Enter the details of Process "<<i+1<<" : "<<endl;
			processes[i].getdata();
		}
	}
	public : void displayProcess(){
		cout<<"Process Name AT"<<cout.width(9)<<"BT"<<cout.width(9)<<"CT"<<cout.width(10)<<"TAT"<<cout.width(10)<<"WT"<<endl;
			for(int i =0;i<n;i++){
				processes[i].display();
			}
	}
	public: void arrangeArrival(int tq){
        for (int i=0; i<n; i++) {
            remainingtime[i] = processes[i].Burst_time;
        }
		   for (int j=0; j<n; j++)
    {
        if (processes[j].Arrival_time <= current_time)
        {
            readyQ.push(j);
        }
    }

      while (completed_tasks != n)
    {
        curr = readyQ.front(); // get the process index from the front of the Ready Queue
        readyQ.pop(); // remove the process from the front of the Ready Queue

        int counter = 0; // counter to keep track of time quantum spent on the current process

        // execute the process for a time quantum (ts) or its remaining burst time (whichever is smaller)
        while (counter!=tq && counter!=remainingtime[curr])
        {
            current_time++; // increment the current time
            counter++; // increment the counter for time spent on the current process

            // check if any new processes have arrived at the current time and add them to the Ready Queue
            for (int j=0; j<n; j++)
            {
                if (processes[j].Arrival_time == current_time)
                {
                    readyQ.push(j);
                }
            }
        }

        remainingtime[curr] -= counter;  // reduce the remaining burst time of the current process by the time quantum spent on it

        // if the remaining burst time of the current process becomes zero, the process is completed
        if (remainingtime[curr] == 0)
        {
            processes[curr].Completion_time = current_time;
            processes[curr].Turn_Around_time = processes[curr].Completion_time - processes[curr].Arrival_time;
            processes[curr].Waiting_time = processes[curr].Turn_Around_time - processes[curr].Burst_time;
            completed_tasks++;
        }
        else
        {
            readyQ.push(curr); // if the process is not completed, push it back to the Ready Queue to be scheduled later
        }
    }
    }
		
	public : float cal_avg_wait(){
		for(int i =0;i<n;i++){
			avg_wt += processes[i].Waiting_time;
		}
		return avg_wt/5;
	}
	public : float cal_avg_tat(){
			for(int i =0;i<n;i++){
				avg_tat += processes[i].Turn_Around_time;
			}
			return avg_tat/5;
		}
	public : void sequence(){
		for(int i =0;i<n;i++){
			cout<<processes[i].process_name<<" --> ";
		}
	}
};

int main() {
	int no_of_process;
	cout<<"Enter the number of Process arriving : ";
	cin>>no_of_process;
	Scheduling s(no_of_process);
	s.getProcess();
    s.arrangeArrival(4);
	s.displayProcess();
	s.sequence();
	cout<<endl;
	cout<<"The Average Waiting time is : "<<s.cal_avg_wait()<<endl;
	cout<<"The Average Turn Around Time is : "<<s.cal_avg_tat()<<endl;
	return 0;
}
