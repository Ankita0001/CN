/* Simulate and implement stop and wait protocol for 
noisy channel. */

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
//#include<conio.h>
//#include<dos.h>
using namespace std;
#define time 5
#define max_seq 1
#define tot_pack 5

int randn(int n)
{
    return rand()%n + 1;
}

typedef struct
{
    int data;
}packet;

typedef struct
{
    int kind;
    int seq;
    int ack;
    packet info;
}frame;

typedef enum{ frame_arrival,error,time_out}event_type;
frame data1;
//creating prototype
void from_network_layer(packet *);
void to_physical_layer(frame *);
void to_network_layer(packet *);
void from_physical_layer(frame*);
void sender();
void receiver();
void wait_for_event_sender(event_type *);
void wait_for_event_receiver(event_type *);
//end


#define inc(k) if(k<max_seq)k++;else k=0;


int i=1;
char turn;
int disc=0;

int main()
{
   while(!disc)
   {  
   		sender();
     	// delay(400);
      	receiver();
   	}
    getchar();
    return 0;
}

void sender()
{
    static int frame_to_send=0;
    static frame s;
    packet buffer;
    event_type event;
    static int flag=0;       //first place
    if (flag==0)
    {
    	from_network_layer(&buffer);
    	s.info=buffer;
    	s.seq=frame_to_send;
		cout<<"\nSender Information: "<<s.info.data<<"\n";
		cout<<"\nSequence No.: "<<s.seq;
		turn='r';
		to_physical_layer(&s);
		flag=1;
    }
	wait_for_event_sender(&event);
	if(turn=='s')
	{
		if(event==frame_arrival)
		{
			from_network_layer(&buffer);
			inc(frame_to_send);
			s.info=buffer;
			s.seq=frame_to_send;
			cout<<"\n\nSender Information: "<<s.info.data<<"\n";
			cout<<"\nSequence No.: "<<s.seq;
			//getch();
			turn='r';
			to_physical_layer(&s);
		}
 	}
}                   //end of sender function

void from_network_layer(packet *buffer)
{
	(*buffer).data=i;
	i++;
}                            //end of from network layer function

void to_physical_layer(frame *s)
{
	data1=*s;
}             //end of to physical layer function

void wait_for_event_sender(event_type *e)
{
	static int timer=0;
	if(turn=='s')
    {   
		timer++;
    	//timer=0;
    	return ;
  	}
	else                          //event is frame arrival
    {
       timer=0;
       *e=frame_arrival;
    }
}              //end of wait for event function

void receiver()
{
    static int frame_expected=0;
    frame s,r;
    event_type event;
    wait_for_event_receiver(&event);
    if(turn=='r')
    { 
		if(event==frame_arrival)
    	{
          	from_physical_layer(&r);
          	if(r.seq==frame_expected)
    		{
       			to_network_layer(&r.info);
       			inc (frame_expected);
    		}
    		else
    		cout<<"\nReceiver: Acknowledgement Resent \n";
    		//getch();
    		turn='s';
    		to_physical_layer(&s);
      	}
	}
}                     //end of receiver function

void wait_for_event_receiver(event_type *e)
{
    if(turn=='r')
    {
   		*e=frame_arrival;
     }
}

void from_physical_layer(frame *buffer)
{
    *buffer=data1;
}

void to_network_layer(packet *buffer)
{
    cout<<"\nReceiver: Packet Received: "<< i-1;
    cout<<"\nAcknowledgement Sent ";
    //getch();
    if(i>tot_pack)
    {
 		disc=1;
		cout<<"\nDiscontinue\n";
	}
}       //end of network layer function