#include<stdio.h>
struct Process{
	int process_id;
	int arrivaltime;
	int bursttime;
	int completion_time;
	int R_time;
}f[100], s[100], m[100];

int n, fc=0, sc=0, mc=0;
int timeslice;

void RoundRobin(){
	int time= m[0].arrivaltime, mark=0, cc=0, i, rc;
	while(time!=120 && cc!=mc){
		for(i=0; i<=mark; i++){
			if(m[i].R_time > timeslice){
				time += timeslice;
				m[i].R_time -= timeslice;
			}
			else if(m[i].R_time <=timeslice && m[i].R_time !=0){
				time += m[i].R_time;
				m[i].R_time =0;
				m[i].completion_time = time;
				cc++;
			}
			else;
		}
		int start = mark+1;
		for(rc= start; rc<mc; rc++){
			if(m[rc].arrivaltime <= time){
				mark++;
			}
		}
	}	
}

void MERGER_ONE(){
	int isc=0, ifc= 0, min, flag;
	if( fc!=0  && sc!=0){
		while(isc<sc && ifc<fc){
			if(f[ifc].arrivaltime == s[isc].arrivaltime){
				m[mc] = f[ifc];
				mc++;
				ifc++;
				m[mc]= s[isc];
				mc++;
				isc++;
			}
			else if(f[ifc].arrivaltime < s[isc].arrivaltime){
				m[mc]= f[ifc];
				mc++;
				ifc++;
			}
			else if(f[ifc].arrivaltime > s[isc].arrivaltime){
				m[mc]= s[isc];
				mc++;
				isc++;
			}
			else;
		}
		if(mc != (fc+sc)){
			if(fc!=ifc){
				while(ifc!=fc){
					m[mc]= f[ifc];
					mc++;
					ifc++;
				}
			}
			else if(sc!=isc){
				while(isc!=sc){
					m[mc]= s[isc];
					mc++;
					isc++;
				}
			}
		}
	}
	else if(fc==0){
		while(isc!=sc){
			m[mc]= s[isc];
			mc++;
			isc++;
		}
	}
	else if(sc==0){
		while(ifc!=fc){
			m[mc]= f[ifc];
			mc++;
			ifc++;
		}
	}
	else {
		printf("\n No valid Processs available\n");
	}
}

void print(){
	int i=0, total=0, sum=0; 
	double avg;
	printf("\nSummary for the Execution\n");
	printf("\nQuery ID\tArrival Time\tRessolving Time\tCompletion Time\tTurn Around Time\tWaiting Time");
	for(i; i<mc; i++){
		printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d",
		m[i].process_id, (m[i].arrivaltime+1000), m[i].bursttime, (m[i].completion_time+1000), (m[i].completion_time-m[i].arrivaltime), ((m[i].completion_time-m[i].arrivaltime)- m[i].bursttime));
		total= m[i].completion_time;
		sum+= (m[i].completion_time-m[i].arrivaltime);
	}
	avg = sum/mc;
	printf("\n\nTotal time Spent for all queries: %d", total);
	printf("\nAverage query time: %lf", avg);
	printf("\nProcess Execution Complete");
}

void input(){
	int map,  i, t;
	printf("Enter total no of queries: "); scanf("%d", &n);
	if(n==0) { printf("\n No queries\n"); }
	else{
		printf("\nEnter Timeslice for each Process: "); scanf("%d", &timeslice);
		printf("\nEnter 1 for faculty and 2 for student\n");
		for(i=0; i<n; i++){
			printf("\nProcess Type (1/2): "); scanf("%d", &map);
			if(map==1){
				printf("Query Id: "); scanf("%d", &f[fc].process_id);
				printf("Arrival Time: "); scanf("%d", &t);
				if(t<1000 || t>1200){
					printf("\nEnter Correct time");
					input();
				}
				else{f[fc].arrivaltime= t-1000;}
				printf("Resolving Time: "); scanf("%d", &f[fc].bursttime);	 f[fc].R_time= f[fc].bursttime; 
				fc++;
			} else{
				printf("Query Id: "); scanf("%d", &s[sc].process_id);
				printf("Arrival Time: "); scanf("%d", &t); 
				if(t<1000 || t>1200){
					printf("\nEnter Correct time\n");
					input();
				}
				else {s[sc].arrivaltime= t-1000; }
				printf("Resolving Time: "); scanf("%d", &s[sc].bursttime);	 s[sc].R_time= s[sc].bursttime;
				sc++;
			}
		}
	}
}

void inst(){
	printf("\nWelcome, please follow these instruction for the program"
			"\n********Enter time in 2400 hours format time (example for 10:30 am enter 1030)**********"
			"\n********Enter Query arrival times in ascending order, i.e., in real time arrival manner**********\n"
			"\nAll Time units are in minutes. \n\n"
			);
}

 main(){
 	inst();
	input();
	MERGER_ONE();
	RoundRobin();
	print();
}
