//============================================================================
// Name        : Scheduling.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

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
		for(int i =0;i<n;i++){
			for(int  j=0;j<n-i-1;j++){
				if(processes[j].Arrival_time > processes[j+1].Arrival_time){
					swap(processes[j],processes[j+1]);
				}
			}
		}
	}
	public: void calParam(){
		int sum = 0;
				processes[0].Completion_time = processes[0].Arrival_time+processes[0].Burst_time;
				processes[0].Turn_Around_time = processes[0].Completion_time - processes[0].Arrival_time;
				processes[0].Waiting_time  = processes[0].Turn_Around_time - processes[0].Burst_time;
		}
	
	public : void completiontime(){
		int temp,val;
		
		
		for(int i = 1;i<n;i++){
			temp = processes[i-1].Completion_time;
			int low = processes[i].Burst_time;
			for(int j = i;j<n;j++){
				if(temp>=processes[j].Arrival_time && low >= processes[j].Burst_time){
					low = processes[j].Burst_time;
					val = j;
				}
			}
				processes[val].Completion_time  = temp + processes[val].Burst_time;
				processes[val].Turn_Around_time = processes[val].Completion_time - processes[val].Arrival_time;
				processes[val].Waiting_time  = processes[val].Turn_Around_time - processes[val].Burst_time;
				swap(processes[val],processes[i]);
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
	s.calParam();
	s.completiontime();
	s.displayProcess();
	s.sequence();
	cout<<endl;
	cout<<"The Average Waiting time is : "<<s.cal_avg_wait()<<endl;
	cout<<"The Average Turn Around Time is : "<<s.cal_avg_tat()<<endl;
	return 0;
}
