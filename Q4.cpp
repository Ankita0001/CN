/*Simulate and implement selective repeat sliding 
window protocol. */
 
#include<iostream>
#include <cstdlib>
#include<ctime>
#include <unistd.h>
#include <cmath>
using namespace std;

int main()
{
	int frms, n, size;
	int total_trans=0;
	cout<<"\n Enter the no. of Frames: ";
	cin>>frms;
	cout<<"\n Enter the Bit Sequence: ";
	cin>>n;
	size = pow(2,n)/2;
	int i=1;
	while(i<=frms)
	{
		int ctr=0;
		sleep(2);
		cout<<"\n\n *_* *_* *_* *_* *_* *_* *_* *_* SENDER SIDE *_* *_* *_* *_* *_* *_* *_* *_* ";
		for(int j=i;j<i+size && j<=frms;j++)
		{
			cout<<"\nFrame "<<j<<" is send by sender!!!!";
			total_trans++;
		}
		for(int k=i; k<i+size && k<=frms; k++)
		{
			sleep(2);
			cout<<"\n\n *_* *_* *_* *_* *_* *_* *_* *_* RECEIVER SIDE *_* *_* *_* *_* *_* *_* *_* *_* ";
			int event = rand()%2; // will generate either 0-error or 1-successfultransmission
			if(!event)
			{
				cout<<"\nFrame "<<k<<" received successfully!!!. Sending acknowledgment for frame "<<k<<" to sender.";
			}
			else
			{
				cout<<"\nReciever Waiting for frame "<<k;
				sleep(2);
				cout<<"\n\n *_* *_* *_* *_* *_* *_* *_* *_* SENDER SIDE *_* *_* *_* *_* *_* *_* *_* *_* ";
				cout<<"\nAcknowledgement for frame "<<k<<" not received ,waiting!!!!!!";
				cout<<"\nRetransmitting frame "<<k;
				sleep(2);
				cout<<"\n\n *_* *_* *_* *_* *_* *_* *_* *_* RECEIVER SIDE *_* *_* *_* *_* *_* *_* *_* *_* ";
				cout<<"\nFrame "<<k<<" received sucessfully!!!. Sending acknowledgment for frame "<<k<<" to sender.";
			}
			ctr++;
		}
		cout<<endl;
		i+=ctr;
	}
	cout<<"\nAll frames sent successfully!!!. \n";
	cout<<"\n Total number of Transmissions: "<<total_trans<<"\n\n";
	
	return 0;
}