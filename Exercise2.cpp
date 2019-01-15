#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
vector<vector<string>> exp;

//function to calculate the number of digits in the number passed as argument
int numDigits(int a)
{
	int count = 0;
	if(a==0)
	{
		count = 1;
	}
	else
	{
		while(a>0)
		{
			count++;
			a/=10;
		}
	}
	return count;
}

//dynamic programming function to calculate the minimum length of expression
vector<vector<int>> dynamicProg(vector<vector<int>> X, vector <int> Z, int MAX)
{
	int rows = X.size();
	int columns = X[0].size();
	vector <int> Y(1);
	int operation[columns];
	int used[columns];
	for(int i=0; i<rows; i++)
	{
		cout<<(i+1)*100/rows<<"%"<<" done"<<endl;
		Y.resize(i+1);
		for(int s=0; s<=i; s++)
		{
			Y[s] = Z[s];
		}

		for(int j=0; j<columns; j++)
		{
			int temp = 0;	
			operation[j] = -1;
			used[j] = -1;
			
			//concatination
			temp = j;
			int countDigits = 0;
			int availableDigits = 0;
			do
			{
				int rem = temp%10;
				for(int k=0; k<=i; k++)
				{
					if(rem == Z[k])
					{
						availableDigits++;
					}
				}
				countDigits++;
				temp/=10;
			}
			while(temp>0);

			if(countDigits == availableDigits)
			{
				X[i][j] = countDigits;
				operation[j] = 0;
				used[j] = j;
				if(countDigits > 1)
				{
					Y.push_back(j);
				}
			}
						
			//multiplication
			int c = MAX;
			int d = X[i][j];
			for(int k=0; k<Y.size(); k++)
			{
				if(j>Y[k] && i>0 && Y[k]>1)
				{
					
					if(j%Y[k] == 0 && X[i][j/Y[k]] != MAX && operation[j/Y[k]]!=2)
					{
						
						c = X[i][j/Y[k]] + numDigits(Y[k]) + 1;	
					}
					if(c<d)
					{
						X[i][j] = c;
						d = c;
						operation[j] = 1;
						used[j] = Y[k];
					}
				}	
			}

			//addition
			int a = MAX;
			int b = X[i][j];
			for(int k=0; k<Y.size(); k++)
			{
				if(j>Y[k] && Y[k]!=0)
				{
						if(X[i][j-(Y[k])] != MAX)
						{
							a = X[i][j-Y[k]] + numDigits(Y[k]) + 1;	
						}
						if(a<b)
						{
							X[i][j] = a;
							b = a;
							operation[j] = 2;
							used[j] = Y[k];
						}
				}	
			}
		
		}

	}

	//printing the answer string
/*	int v = -1;
	int step = columns-1;
	cout<<endl;
	while (v!=0){
		v = operation[step];
		cout<<step<<"-->"<<operation[step]<<"---"<<used[step]<<endl;
		if (operation[step]==1){
			step = step / used[step];
		} else
		if (operation[step]==2){
			step = step - used[step];	
		}
	}
*/
	return X;
}

int main(int argc, char* argv[])
{
	ifstream fi(argv[1]);
	if (!fi)
	{
		cout << "cant open fi" << endl;
		return -1;
	}

	ofstream fo(argv[2]);
	if (!fo)
	{
		cout << "cant open fo" << endl;
		return -1;
	}

	int m, n, number, count;
	
	//reading the first value (i.e. the number of datasets) in the input set
	fi >> m;
	
	//check if the input file is empty
	if (m == 0)
	{
		cout << "the file has no dataset";
	}
	else
	{
		for (int j = 1; j <= m; j++)
		{
			//reading the number of elements in Set
			fi >> n;
			if (n == 0)
			{
				fo << "EMPTY" << endl;
			}
			else
			{
				cout<<"Processing Dataset->"<<j<<endl;
				vector<int> S(n);
				
				//reading the numbers
				for(int k=0; k<n; k++)
				{
						fi>>S[k];
				}
				
				//sort the numbers in the Set
				sort(begin(S), end(S));

				//reading the number to be made using Set of numbers
				fi>>number;
				
				//creating 2-D vector and initializing all cells to infinity
				int MAX_VALUE = 2*number+2;
				vector<vector<int>> T;
				T.resize(n, vector<int>(number+1, MAX_VALUE));
				
				//calling the function to calculate the length of expression using dynamic programming
				T = dynamicProg(T, S, MAX_VALUE);
					
				//writing the solution to the output file	
				if(T[n-1][number] != MAX_VALUE)
				{
					fo<<T[n-1][number];
					fo<<endl;
				}
				else
				{
					fo<<"N"<<endl;
				}
			}
		}
	}
return 1;
}