#include <bits/stdc++.h>
using namespace std;
//first come first serverd
class Job
{
    string id ;
    string name ;
    int arival_t;
    int burst_t;
    int complete_t;
    int turb_at ;
    int waiting_t;
    int prio;
    int arrivandburst;

public:
    Job()
    {
        id = "";
        name = "";
        arival_t = 0;
        burst_t = 0;
        complete_t  = 0;
        turb_at  = 0;
        waiting_t  = 0;
        prio = 0;
        arrivandburst = 0;
    }

    Job(string i , string n ,int at ,int bs)
    {
        id = i;
        name = n;
        arival_t = at;
        burst_t = bs;
        complete_t  = 0;
        turb_at  = 0;
        waiting_t  = 0;
        prio = 0;
        arrivandburst = 0;
    }
    friend class Schedule ;
};

class Schedule
{
    int n;
    Job *ptr;
    float averageTAT ;
    float average_wating_t ;

public:
    Schedule(int num)
    {
        n = num;
        ptr = new Job[n];
        averageTAT = 0;
        average_wating_t = 0;
    }

    bool comp(Job const a ,Job const b)
    {
        return a.arival_t <= b.arival_t;
    }

    void set_data(int i ,string id ,string name ,int at ,int bt);
    void input();
    void bubble_sort_arrival_time()
    {
        for(int i =  0 ; i < n ;i++)
        {
            for(int j = 0 ; j < n ;j++)
            {
                if(ptr[i].arival_t < ptr[j].arival_t)
                {
                    swap(ptr[i] ,ptr[j]);
                }
            }
        }
    }
    void insertion_sort_burst_time()
    {
        for(int i = 1 ; i < n ;i++)
        {
            bool f = 0;
            for(int j = i ; j > 0 ; j-- )
            {
                if(ptr[j-1].burst_t > ptr[j].burst_t){
                    swap(ptr[j-1] ,ptr[j]);
                    f = 1;
                }
                if(f == 0){
                    break;
                }
            }
        }
    }
    void insertion_sort_priority_based()
        {
            for(int i = 1 ; i < n ;i++)
            {
                bool f = 0;
                for(int j = i ; j > 0 ; j-- )
                {
                    if(ptr[j-1].prio < ptr[j].prio){
                        swap(ptr[j-1] ,ptr[j]);
                        f = 1;
                    }
                    if(f == 0){
                        break;
                    }
                }
            }
        }
    void calculate_completetime();
    void calculate_turnAroundTime();
    void calculate_waitingtime();
    void calculate_average_TAT();
    void calculate_average_wT();
    void take_priority();
    void addarriveandbust();
    void display();

};



void Schedule::set_data(int i ,string id ,string name ,int at ,int bt)
{
    ptr[i].id = id;
    ptr[i].name = name;
    ptr[i].arival_t = at;
    ptr[i].burst_t = bt;
}
void Schedule ::input()
{
    string id ,name ;
    int at ,bt ;

    cout<<"\nEnter Name, ID, Arrival Time, Burst Time:"<<endl;

    for(int i = 0 ; i < n ;i++)
    {
        cout<<"\nJob "<<i+1<<":"<<endl;
        cin>>id>>name>>at>>bt;
        set_data(i ,id ,name ,at ,bt);
    }
}

void Schedule::calculate_completetime()
{
    ptr[0].complete_t = ptr[0].burst_t;
    for(int i = 1; i < n ;i++)
    {
        ptr[i].complete_t = ptr[i-1].complete_t + ptr[i].burst_t;
    }
}

void Schedule::calculate_turnAroundTime()
{
    for(int i = 0; i < n ;i++)
    {
        ptr[i].turb_at = ptr[i].complete_t - ptr[i].arival_t;
    }
}
void Schedule::calculate_waitingtime()
{
    for(int i = 0; i < n ;i++)
    {
        ptr[i].waiting_t = ptr[i].turb_at - ptr[i].burst_t;
    }
}
void Schedule::calculate_average_wT()
{
    float sum = 0;
    for(int i = 0; i < n ;i++)
    {
        sum += ptr[i].waiting_t;
    }

    double avg = (sum)/n;
    cout<<"Average wating time = "<< avg <<endl;
}

void Schedule::calculate_average_TAT()
{
    float sum = 0;
    for(int i = 0; i < n ;i++)
    {
        sum += ptr[i].turb_at;
    }

    double avg = (sum)/n;
    cout<<"\nAverage turn around time = "<< avg <<endl;
}

void Schedule::take_priority()
{
    int p;
    cout<<"Enter priorities according to job name: "<<endl;
    for(int i = 0 ; i < n ;i++)
    {
        cout<<"Priority of job "<<ptr[i].name<<":"<<endl;
        cin>>p;
        ptr[i].prio = p;
    }
}
void Schedule::display()
{
    cout<<"\nID\t"<<"Name\t"<<"AT\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"Waiting Time"<<endl;
    for(int i = 0; i < n ;i++)
    {
        cout<<ptr[i].id<<"\t"<<ptr[i].name<<"\t"<<ptr[i].arival_t<<"\t"<<ptr[i].burst_t<<"\t"<<ptr[i].complete_t<<"\t"<<ptr[i].turb_at<<"\t"<<ptr[i].waiting_t<<endl;
    }
}
void Schedule::addarriveandbust()
{
    for(int i = 0 ; i < n ;i++)
    {

    }
}
int main() {
    int n;
    cout<<"Enter number of jobs:"<<endl;
    cin>>n;
    Schedule obj(n);
    obj.input();

    bool f = 1;

    while(f)
    {
        int choice;
		cout<<"\n--------------- MENU ---------------";
		cout<<"\n1. FCFS  \n2. SJF \n3. Priority-Based Scheduling \n4. Exit"<<endl;
		cout<<"------------------------------------"<<endl;
		cout<<"\nEnter choice: "<<endl;
		cin>>choice;

		switch(choice)
		{
			case 1 :
				obj.bubble_sort_arrival_time();
				obj.calculate_completetime();
				obj.calculate_turnAroundTime();
				obj.calculate_waitingtime();
				obj.calculate_average_TAT();
				obj.calculate_average_wT();
				obj.display();
				break;

			case 2:
				obj.insertion_sort_burst_time();
				obj.calculate_completetime();
				obj.calculate_turnAroundTime();
				obj.calculate_waitingtime();
				obj.calculate_average_TAT();
				obj.calculate_average_wT();
				obj.display();
				break;

			case 3:
				obj.take_priority();
				obj.insertion_sort_priority_based();
				obj.calculate_completetime();
				obj.calculate_turnAroundTime();
				obj.calculate_waitingtime();
				obj.calculate_average_TAT();
				obj.calculate_average_wT();
				obj.display();
				break;



			default:
				cout<<"Thank you! Exiting Program..."<<endl;;
				f = 0;
        }

    }
    cout<<"Exit Successful..."<<endl;


    return 0;
}