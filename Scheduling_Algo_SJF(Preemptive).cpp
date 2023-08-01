
#include <iostream>
#include<iomanip>
#include<set>
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
    int shortestTask = 0;
    int min_burst = 9999;
    bool active =false;
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
	public: void arrangeArrival(){
        for (int i=0; i<n; i++) {
            remainingtime[i] = processes[i].Burst_time;
        }
		while(completed_tasks!=n){
            for(int j = 0;j<n;j++)
                    {
            if (processes[j].Arrival_time <= current_time && processes[j].Burst_time < min_burst && remainingtime[j]> 0)
            {
                shortestTask = j;
                min_burst = processes[j].Burst_time;
                active = true;
            }
        }

        if (active == false)
        {
            current_time++;
            continue;
        }

        min_burst = --remainingtime[shortestTask];
        if (min_burst == 0) 
        {
            min_burst = 99999;
        }

        if (remainingtime[shortestTask] == 0)
        {
            completed_tasks++;
            active = false;
            processes[shortestTask].Completion_time = current_time + 1;
            processes[shortestTask].Turn_Around_time = processes[shortestTask].Completion_time - processes[shortestTask].Arrival_time;
            processes[shortestTask].Waiting_time = processes[shortestTask].Turn_Around_time - processes[shortestTask].Burst_time;

            if (processes[shortestTask].Waiting_time < 0)
            {
                processes[shortestTask].Waiting_time = 0;
            }
        }
        current_time++;
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
    s.arrangeArrival();
	s.displayProcess();
	s.sequence();
	cout<<endl;
	cout<<"The Average Waiting time is : "<<s.cal_avg_wait()<<endl;
	cout<<"The Average Turn Around Time is : "<<s.cal_avg_tat()<<endl;
	return 0;
}
