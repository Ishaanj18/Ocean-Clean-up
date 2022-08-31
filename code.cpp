#include<bits/stdc++.h>
#define p_b push_back
#define lli long long int
using namespace std;
int main()
{
	vector<string> rid;
	unordered_map<int,string> mm;
	cout<<"Enter the number of deltas : ";
	int n;
	cin>>n;
	
	cout<<endl;
	int r1,r2,r3,cr1,cr2,cr3;
	cout<<"Enter the total number of Boyan Slat ocean clean up: ";
	cin>>r1;
	cout<<"Enter the amount of waste that cleaned by Boyan Slat at a time : ";
	cin>>cr1;
	cout<<endl;
	cout<<"Enter the total number of Floaters : ";
	cin>>r2;
	cout<<"Enter the amount of waste that cleaned by Floaters at a time : ";
	cin>>cr2;
	cout<<endl;
	cout<<"Enter the total number of Skimmers : ";
	cin>>r3;
	cout<<"Enter the amount of waste that cleaned by Skimmers at a time : ";
	cin>>cr3;
	cout<<endl;
	
	vector<double> metal;
	vector<double> plastic;
	vector<double> oil;
	vector<int> alloc_r1;
	vector<int> alloc_r2;
	vector<int> alloc_r3;
	vector<int> max_r1;
	vector<int> max_r2;
	vector<int> max_r3;
	vector<pair<double,double>> coord;
	vector<lli> population;
	vector<double> toxicity;
	int s1=0,s2=0,s3=0;
	
	//Taking data for each Delta
	for(int i=0;i<n;i++)
	{
		cout<<"Enter the delta Id of river "<<i+1<<" : ";
		string id;
		cin>>id;
		rid.push_back(id);
		
		cout<<"Enter the delta name : ";
		string name;
		cin>>name;
		mm[i]=name;
		
		cout<<"Enter the coordinates(x,y) of the delta : ";
		double x,y;
		cin>>x>>y;
		coord.p_b(make_pair(x,y));
		
		cout<<"Enter the population near the delta : ";
		lli pop;
		cin>>pop;
		population.p_b(pop);
		
		cout<<endl;
		double amt;
		cout<<"Enter the amount of metallic and heavy plastic waste in the delta "<<id<<" : ";
		cin>>amt;
		metal.p_b(amt);
		max_r1.p_b((int)(ceil(amt/cr1)));
		
		cout<<"Enter the amount of plastic waste in the delta "<<id<<" : ";
		cin>>amt;
		plastic.p_b(amt);
		max_r2.p_b((int)(ceil(amt/cr2)));
		
		cout<<"Enter the amount of oil and chemical waste in the delta "<<id<<" : ";
		cin>>amt;
		oil.p_b(amt);
		max_r3.p_b((int)(ceil(amt/cr3)));
		
		toxicity.p_b(metal[i]+plastic[i]+oil[i]);
		
		int nor1=0,nor2=0,nor3=0;
		cout<<"Enter the number of Boyan Slat allocated to delta "<<id<<" : ";
		cin>>nor1;
		alloc_r1.p_b(nor1);
		s1+=nor1;
		
		cout<<"Enter the number of Floater allocated to delta "<<id<<" : ";
		cin>>nor2;
		alloc_r2.p_b(nor2);
		s2+=nor2;
		
		cout<<"Enter the number of Skimmer allocated to river "<<id<<" : ";
		cin>>nor3;
		alloc_r3.p_b(nor3);
		s3+=nor3;
		cout<<endl;
	}
	
	//Calculating total toxicity
	double total_tox=0.0;
	for(int i=0;i<n;i++)
	{
		total_tox+=toxicity[i];
	}
	
	for(int i=0;i<n;i++)
	{
		toxicity[i]=toxicity[i]/total_tox;
	}
	
	//Calculating available resources
	vector<int> avail(3,0);
	avail[0]=r1-s1;
	avail[1]=r2-s2;
	avail[2]=r3-s3;
	
	//For Need Matrix
	vector<int> need_r1,need_r2,need_r3;
	for(int i=0;i<n;i++)
	{
		need_r1.p_b(max_r1[i]-alloc_r1[i]);
		need_r2.p_b(max_r2[i]-alloc_r2[i]);
		need_r3.p_b(max_r3[i]-alloc_r3[i]);
	}
	
	
	//Using Banker's Algorithm
	vector<bool> done(n,false);
	vector<int> safe(n);
	int count=0;
	double total_dist=0.0;
	bool flag=true;
	for(int i=0;i<n;i++)
	{
		double priority=0.0;
		int pos=-1;
		for(int j=0;j<n;j++)
		{
			if(need_r1[j]<=avail[0] && need_r2[j]<=avail[1] && need_r3[j]<=avail[2] && done[j]==false)
			{
				if(flag)
				{
					safe[count]=j;
					avail[0]=avail[0]+alloc_r1[j];
					avail[1]=avail[1]+alloc_r2[j];
					avail[2]=avail[2]+alloc_r3[j];
					flag=false;
					done[j]=true;
					count++;
					break;
				}
				else
				{
					//Calculating priority
					double p=(population[j]*toxicity[j]);
					int cc=safe[count-1];
					double xd=coord[j].first-coord[cc].first;
					double yd=coord[j].second-coord[cc].second;
					double dist=sqrt(pow(xd,2)+pow(yd,2));
					p=p/dist;
					
					if(priority<p)
					{
						priority=p;
						pos=j;
					}
				}
			}
		}
		if(pos!=-1)
		{
			done[pos]=true;
			int cc=safe[count-1];
			avail[0]=avail[0]+alloc_r1[pos];
			avail[1]=avail[1]+alloc_r2[pos];
			avail[2]=avail[2]+alloc_r3[pos];
			safe[count]=pos;
			double xd=coord[pos].first-coord[cc].first;
			double yd=coord[pos].second-coord[cc].second;
			double dist=sqrt(pow(xd,2)+pow(yd,2));
			total_dist+=dist;
			count++;
		}
	}
	
	//Displaying delta information
	cout<<"\nId\tName\tMetal\tPlastic\tOil\tA_r1\tA_r2\tA_r3\tM_r1\tM_r2\tM_r3\tNeed_r1\tNeed_r2\tNeed_r3\n";
	for(int i=0;i<n;i++)
	{
		cout<<rid[i]<<"\t"<<mm[i]<<"\t"<<metal[i]<<"\t"<<plastic[i]<<"\t"<<oil[i]<<"\t";
		cout<<alloc_r1[i]<<"\t"<<alloc_r2[i]<<"\t"<<alloc_r3[i]<<"\t";
		cout<<max_r1[i]<<"\t"<<max_r2[i]<<"\t"<<max_r3[i]<<"\t";
		cout<<need_r1[i]<<"\t"<<need_r2[i]<<"\t"<<need_r3[i]<<endl;
	}
	
	//Displaying the safe sequence
	cout<<"Safe sequence : ";
	for(int i=0;i<n;i++)
	{
		if(i==n-1)
		{
			cout<<rid[safe[i]];
		}
		else
		{
			cout<<rid[safe[i]]<<" --> ";
		}
	}
	cout<<endl;
	
	//Displaying the total distance tranversed
	cout<<"The total distance traversed : "<<total_dist<<endl;
	return 0;
}
