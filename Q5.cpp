/*Simulate and implement distance vector routing 
algorithm. */
  
#include<iostream>
using namespace std;

int main()
{
    int arr[50][50];
    int i,j,k,t;
    int node;

    cout<<"\n ENTER THE NUMBER OF NODES: ";
    cin>>node;

    // initialize the graph
    for (i=0;i<node;i++)
    {
        for(j=0;j<node;j++)
        {
            arr[i][j]=-1;
        }
    }
    char ch[8]={'A','B','C','D','E','F','G','H'};   //vertex name initialize
    // taking input
    for (i=0;i<node;i++)
    {
        for(j=0;j<node;j++)
        {
            if(i==j)        //for same vertex
            {
                arr[i][j]=0;
            }
            if(arr[i][j]==-1)
            {
                cout<<"\n ENTER THE DISTANCE BETWEEN "<<ch[i]<<" - "<<ch[j]<<": ";
                cin>>t;
                arr[i][j]=arr[j][i]=t;
            }
        }
    }
	cout<<endl<<endl <<" *_* *_* *_* *_* *_* *_* *_* *_* GRAPH REPRESENT BY ADJACENCEY MATRIX *_* *_* *_* *_* *_* *_* *_* *_* \n" <<endl;
    for (i=0;i<node;i++)
    {
        for(j=0;j<node;j++)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    /* Initializing via */
    int via[50][50];
    for (i=0;i<node;i++)
    {
        for(j=0;j<node;j++)
        {
            via[i][j]=-1;
        }
    }

    cout<<"\n\n *_* *_* *_* *_* *_* *_* *_* *_* AFTER UPDATE *_* *_* *_* *_* *_* *_* *_* *_* ";
    // Display table initialization
    for (i=0;i<node;i++)
    {
        cout<<"\n\n\t"<<ch[i]<<" TABLE ";
        cout<<"\nNode\tDist\tVia";
        for(j=0;j<node;j++)
        {
            cout<<"\n"<<ch[j]<<"\t"<<arr[i][j]<<"\t"<<via[i][j];
        }
    }

    //sharing table
     int sh[50][50][50];
    for(i=0;i<node;i++)
    {
        for(j=0;j<node;j++)
        {
            for (k=0;k<node;k++)
            {
                /* Check if edge is present or not*/
                if((arr[i][j]>-1)&&(arr[j][k]>-1))
                {
                    sh[i][j][k]=arr[j][k]+arr[i][j];
                }
                else
                {
                    sh[i][j][k]=-1;
                }
            }
        }
    }

    //displaying shared table
    for(i=0;i<node;i++)
    {   cout<<"\n\n *_* *_* *_* *_* *_* *_* *_* *_* \n";
        cout<<"\n\tFor "<<ch[i];
        cout<<endl;
        for (j=0;j<node;j++)
        {
            cout<<"\n\nFrom "<<ch[j];
            cout<<endl;
            for(k=0;k<node;k++)
            {
                cout<<"\n "<<ch[k]<<" "<<sh[i][j][k];
            }
        }
    }
  	int final[50][50];
    for(i=0;i<node;i++)
    {
        for(j=0;j<node;j++)
        {
            // Copy initial value from input graph
            final[i][j]=arr[i][j];
            via[i][j]=i;

            //update them
            // Check condition a - b - c
             for(k=0;k<node;k++)
            {

                 if((final[i][j]>sh[i][k][j]) || (final[i][j] == -1))
                {
                    if(sh[i][k][j]>-1)
                    {
                        final[i][j]=sh[i][k][j];
                        via[i][j]=k;
                    }
                }
            }

            if(final[i][j]==-1)
            {
                for(k=0;k<node;k++)
                {
                 if((final[i][k]!=-1)&&(final[k][j]!=-1))                       //there is no edge
                    {
                        if((final[i][j]==-1) || ((final[i][j]!=-1) &&(final[i][j]>final[i][k]+final[k][j])))
                        {
                            if(final[i][k]+final[k][j]>-1)
                            {
                                final[i][j]=final[i][k]+final[k][j];
                                via[i][j]=k;
                            }
                        }
                    }

                }
            }
        }
    }
	cout<<"\n\n *_* *_* *_* *_* *_* *_* *_* *_* AFTER UPDATE *_* *_* *_* *_* *_* *_* *_* *_* ";
    // Display table Updation
    for (i=0;i<node;i++)
    {
        cout<<"\n\n\t"<<ch[i]<<" Table";
        cout<<"\nNode\tDist\tVia";
        for(j=0;j<node;j++)
        {
            cout<<"\n"<<ch[j]<<"\t"<<final[i][j]<<"\t";
            if(i==via[i][j])
                cout<<"-";
            else
                cout<<ch[via[i][j]];
        }
    }
    cout<<"\n\n";
}