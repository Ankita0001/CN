/* Simulate and implement go back n sliding window 
protocol. */
  
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int main()
{
	int nf,N;
	int no_tr=0;
	srand(time(NULL));
	cout<<"\n Enter the number of Frames: ";
	cin>>nf;
	cout<<"\n Enter the Window Size: ";
	cin>>N;
	cout<<endl;
	int i=1;
	while(i<=nf)
	{
		int x=0;
		for(int j=i;j<i+N && j<=nf;j++)
		{
			cout<<"\n Sent Frame "<<j<<endl;
			no_tr++;
		}
		for(int j=i;j<i+N && j<=nf;j++)
		{
			int flag = rand()%2;
			if(!flag)
			{
				cout<<"\n Acknowledgment for Frame "<<j<<endl;
				x++;
			}
			else
			{   
				cout<<"\n Frame "<<j<<" Not Received"<<endl;
                cout<<"\n Retransmitting Window !!"<<endl;
                break;
            }
		}
		cout<<endl;
		i+=x;
	}
	cout<<"\n Total number of Transmissions: "<<no_tr<<"\n\n";
	
	return 0;
}