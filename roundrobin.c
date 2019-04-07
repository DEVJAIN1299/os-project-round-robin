
#include<stdio.h>
#include<windows.h>

/*for some small graphics.... this function is used...*/

COORD coord = {0, 0};
void gotoxy(int x, int y)
{
	 COORD coord;
	 coord.X = x;
	 coord.Y = y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct process
{
	char name;
	int arrival_time,burst_time,waiting_time,turn_around_time,rt;
	int completed;
	float ntt;
}p[10];


int n;
int q[100];  				//queue
int front=-1,rear=-1;


void enqueue(int i)
{
	if(rear==100)
	printf("overflow");
	rear++;
	q[rear]=i;
	if(front==-1)
	front=0;
}


int dequeue()
{
	if(front==-1)
	printf("underflow");
	int temp=q[front];
	if(front==rear)
	front=rear=-1;
	else
	front++;
	return temp;
}


int isInQueue(int i)
{
	int k;
	for(k=front;k<=rear;k++)
	{
		if(q[k]==i)
		return 1;
	}
	return 0;
}


void sortByArrival()
{
	struct process temp;
	int i,j;
	for(i=0;i<n-1;i++)
		for(j=i+1;j<n;j++)
		{
			if(p[i].arrival_time>p[j].arrival_time)
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
		}	
}


int main()
{
	/* for the some basic graphics function......*/	
	
	system("color 0a");
	gotoxy(30,15);
	printf("loading.");
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".");
	system("color 79");
	system("cls");
	printf("\t\t\t   *** IMPLEMENTATION OF ROUND ROBIN ***");
	printf("\n\t\t\t\t***      DEV JAIN    ***");
	printf("\n\t\t\t\t***        K17KP    ***");	
	printf("\n\t\t\t\t***  REG NO : 11702174 **");
	printf("\t\t\t ");
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".");
    system("cls");


/*................................................................................................
								main code strart from here
................................................................................................*/


	int i,j,time=0,sum_bt=0,time_quantam;
	char c;
    float avgwt=0;
    gotoxy(3,5);
    
 	printf("Enter no of processes:");
 	scanf("%d",&n);
	
	for(i=0,c='A';i<n;i++,c++)
 	{	
		p[i].name=c;
 		printf("\nEnter the arrival time and burst time of process %c: ",p[i].name);
 		scanf("%d%d",&p[i].arrival_time,&p[i].burst_time);
 		p[i].rt=p[i].burst_time;
 		p[i].completed=0;
 		sum_bt+=p[i].burst_time;
 
	}
	
	printf("\n\n");
	
	printf("\nEnter the time quantum:");
	scanf("%d",&time_quantam);
	printf("\n\n");

	sortByArrival();
	enqueue(0);         				 // enqueue the first process
	
	printf("\n\n");
	
	printf("===================================\n");
	printf("\tProcess execution order: \n");
	printf("===================================\n\n");
	
	printf("Note :-According to the time quantam and process cpu burst  the process of order of exection will be print in the gannt chart.....\n\n");
	
	
	
	for(time=p[0].arrival_time;time<sum_bt;)       // run until the total burst time reached
	{  
		i=dequeue();
	
		if(p[i].rt<=time_quantam)
		{
			
		  /* for processes having remaining time with less than or  equal  to time quantum  */
                       
			time+=p[i].rt;
			
			p[i].rt=0;
			
			p[i].completed=1;          
    		
			printf(" %c ",p[i].name);
            
			p[i].waiting_time=time-p[i].arrival_time-p[i].burst_time;
            
			p[i].turn_around_time = time-p[i].arrival_time;       
            
			p[i].ntt=((float)p[i].turn_around_time/p[i].burst_time);
            
			for(j=0;j<n;j++)                	/*enqueue the processes which have come                                         while scheduling */
            {
            	if(p[j].arrival_time<=time && p[j].completed!=1&& isInQueue(j)!=1)
            	{
            		enqueue(j);
            
          		}
           	}
        }


    	else               				// more than time quantum
    	{	
    		Sleep(1000*time_quantam);            // acc. to time quantam this shows the gannt chart
    		time+=time_quantam;
    		p[i].rt-=time_quantam;
    		printf(" %c ",p[i].name);
    		for(j=0;j<n;j++)    		/*first enqueue the processes which have come while                                             scheduling */
            {
            	if(p[j].arrival_time<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1)
             	{
            		enqueue(j);
            
            	}
           	}
           	enqueue(i);  				 // then enqueue the uncompleted process
           
	
    	}

	}

	printf("\n\n\n");
	
	printf("\n***********************************************************************************************");
	printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time\t Normalized TT");	
	printf("\n***********************************************************************************************");
	

	for(i=0;i<n;i++)
	{
		avgwt+=p[i].waiting_time;
		printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f",p[i].name,p[i].arrival_time,p[i].burst_time,p[i].waiting_time,p[i].turn_around_time,p[i].ntt);
		
	}
	
	
	printf("\n\n");
	printf("\nAverage waiting time:%f\n",avgwt/n);

}
