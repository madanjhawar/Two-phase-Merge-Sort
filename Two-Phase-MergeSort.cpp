#include<bits/stdc++.h>

#define mod 1000000007
#define f(i,a,b) for(i=a;i<b;i++)
#define ff(i,a) for(i=0;i<a;i++)
#define sc scanf
#define pr printf
#define clr(a) memset(a,0,sizeof(a))
#define ll long long
#define vi vector<int>
#define pin(n) printf("%d\n",n)
#define pll(n) printf("%lld\n",n)
#define sin(n) scanf("%d",&n)
#define sll(n) scanf("%lld",&n)
#define pins(n) printf("%d ",n)
#define plls(n) printf("%lld ",n)
#define ss(n) scanf("%s",n)
#define nl pr("\n")
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define sl(a) strlen(a)

using namespace std;

int line_size;
int ncols,total_rows;
string order;

string str_remove_spaces(string a)
{
	int i,j,k,l;
	l=a.size();
	i=0;
	while(i<l && a[i]==' ')
		i++;
	j=l-1;
	while(j>=0 && a[j]==' ')
		j--;

	char temp[1000];
	k=0;

	while(i<=j)
		temp[k++]=a[i++];
	temp[k]='\0';

	string truncated_string(temp);
	return truncated_string;
}

vector<string> str_split(string a,string delim)
{
	string s = a;
	string delimiter = delim;

	vector<string> peices;

	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != -1) 
	{
		token = s.substr(0, pos);
		peices.pb(token);
		s.erase(0, pos + delimiter.length());
	}
	peices.pb(s);
	return peices;
}

struct comp
{
	bool operator() (const string &line1, const string &line2)
	{
		string line3=line1,line4=line2;
		vector<string> words=str_split(line3,",");
		int i;
		line3="";
		ff(i,ncols)
			line3+=","+words[i];
		line3.erase(line3.begin());

		words=str_split(line4,",");
		line4="";
		ff(i,ncols)
			line4+=","+words[i];
		line4.erase(line4.begin());
		if(order=="asc")
			return line3<line4;
		else
			return line3>=line4;
	}
};  


map<string,int> handle_metadata()
{
	ifstream file("metadata.txt");
	string line;
	vector<string> col;
	map<string,int> mymap;

	if(file.is_open())
	{
		while(getline(file,line))
		{

			col=str_split(line,",");
			mymap[col[0]]=atoi(col[1].c_str());
		}
		return mymap;
	} 
	else
	{
		printf("Couldn't open metadata.txt\n");
		exit(0);
	}
}

void page_sort(int num_rows,string input,vector<int> tosort_index)              // first step, read page by page, sort and write in a file
{
	int rows=0,i,j;
	string line,outline;

	vector<string> words;
	string instance="";
	int actual[120];

	ff(i,tosort_index.size())
	{
		actual[tosort_index[i]]=i;
	}


	vector<string> page;
	ifstream file(input.c_str());
	if(file.is_open())
	{
		ofstream out("temp_output1.txt");
		ofstream fout("first_phase.txt");

		while(getline(file,line))
		{
			instance="";
			words=str_split(line," ");

			ff(i,tosort_index.size())
			{
				instance=instance + "," + words[tosort_index[i]];
			}
			instance.erase(instance.begin());


			page.pb(instance);
			rows++;
			if(rows==num_rows)
			{

				sort(page.begin(),page.end(),comp());
				ff(i,page.size())
				{
					outline="";
					words=str_split(page[i],",");
					ff(j,tosort_index.size())
					{
						outline+=" "+words[actual[j]];
					}
					outline.erase(outline.begin());
					out << outline << endl;
					fout << outline << endl;
					words.clear();
					total_rows++;
				}
				page.clear();
				rows=0;
			}
		}
		if(page.size()>0)
		{
			sort(page.begin(),page.end(),comp());
			ff(i,page.size())
			{
				outline="";
				words=str_split(page[i],",");
				ff(j,tosort_index.size())
				{
					outline+=" "+words[actual[j]];
				}
				outline.erase(outline.begin());
				out << outline << endl;
				fout << outline << endl;
				total_rows++;
			}
			page.clear();
		} 
		out.close();
		fout.close();
		file.close();
	}
	else
	{
		cout << "Couldn't open input file." << endl;
		exit(0);
	}
}


int main(int argc,char *argv[])
{
	int i,j,k,l,m,n;
	int main_memory;
	string input,output;
	vector<string> tosort_columns;
	map<string,int> column_names;
	map<string,int> :: iterator it;
	string c,line;

	if(argc<5)
	{
		cout << "Not sufficient arguments given." << endl;
		exit(0);
	}
	input=argv[1];
	output=argv[2];
	main_memory=atoi(argv[3]);
	order=argv[4];

	f(i,5,argc)
	{
		tosort_columns.pb(argv[i]);                      // column names in sort order
	}
	ncols=tosort_columns.size();
	column_names=handle_metadata();                      // column names with their size




	vector<int> tosort_index;                           // stores index of the input columns

	ff(i,tosort_columns.size())
	{
		c=tosort_columns[i];
		j=0;
		for(it=column_names.begin();it!=column_names.end();it++)
		{
			if(c==it->first)
			{
				tosort_index.pb(j);
				break;
			}
			j++;
		}
	}

	int flag;

	ff(i,column_names.size())
	{
		flag=0;
		ff(j,tosort_index.size())
		{
			if(tosort_index[j]==i)
			{
				flag=1;
				break;
			}
		}
		if(!flag)
			tosort_index.pb(i);
	}


	int row_size=0;
	for(it=column_names.begin();it!=column_names.end();it++)
	{
		row_size+=it->second;
	}
	row_size+=(column_names.size()-1)*sizeof(' ');


	int num_rows=(main_memory*1024*716)/row_size;
	if(num_rows==0)
	{
		cout << "Insufficient Memory" << endl;
		exit(0);
	}

	page_sort(num_rows,input,tosort_index);

	return 0;
}
