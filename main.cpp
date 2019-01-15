#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int expPuzzle(int input[], int number, int length);
int expPuzzle(int input[], int number, int length) 
{

		bool T[length][number + 1];
		int Mat[length][number + 1];
		int op[length][number + 1];
		
		int output = 0;
       	for(int q=0; q< length; q++){
			for(int w=0; w<= number; w++){
				//cout<<Mat[q][w]<<" ";
				T[q][w] = false;
				Mat[q][w] = 2 * number + 2;
				op[q][w] = -1;
			}	
			//cout<<endl;
		}
        for (int i = 0; i < length; i++)
        {

            for (int j = 0; j <= number; j++) 
            {

            	int temp = j;
            	string str = to_string(j);
            	if(i==0)
            	{
            		if(j<input[i]){
            			T[i][j] = false;
            		}
            		else if(j==input[i]){
            			T[i][j] = true;
            			Mat[i][j] = str.length();
            			op[i][j] = 0;
            		}
            		else{
            			//concatination
            			//for(int i=0; i<length; i++)
            			//{
	            			if(input[i]!=0 && j%10 == input[i]){
	            				temp/=10;
	            				T[i][j] = true;
	            				Mat[i][j] = Mat[i][temp]+1;
	            				op[i][j] = 0;
	            				//break;
	            			}
            			//}
            			//multiplication
            			if(input[i]!=0 && j%input[i] == 0 && T[i][j/input[i]] == true){
            				//cout<<"INSIDE"<<endl;
            				if(T[i][j]==true){
            					int temp2 = Mat[i][j];
            					Mat[i][j] = min(Mat[i][j], Mat[i][j/input[i]]+2);
            					if(temp2 != Mat[i][j])
            					op[i][j] = 1;
            				}
            				else{
            					//cout<<"INSIDE INSIDE ELSE"<<endl;
	            				T[i][j] = true;
	            				Mat[i][j] = Mat[i][j/input[i]]+2;
	            				op[i][j] = 1;
	            			}
            			}
            			//addition
            			if(T[i][j-input[i]] == true){
            				if(T[i][j]==true){
            					int temp2 = Mat[i][j];
            					Mat[i][j] = min(Mat[i][j], Mat[i][j-input[i]]+2);
            					if(temp2 != Mat[i][j])
            					op[i][j] = 2;
            				}
            				else{
	            				T[i][j] = true;
	            				Mat[i][j] = Mat[i][j-input[i]]+2;
	            				op[i][j] = 2;
            				}

            			}

            		}
            	}
            	else
            	{
            		T[i][j] = T[i-1][j];
           			Mat[i][j] = Mat[i-1][j];
           			op[i][j] = op[i-1][j];

					if(j==input[i])
					{
						T[i][j] = true;
	            		op[i][j] = 0;
	            		Mat[i][j] = str.length();
					}
					else if(j>input[i])
					{
						//concatination
						for(int f=0; f<length; f++)
            			{
						if(j%10 == input[f]){
            				temp/=10;
            				if(T[i][temp] == true && op[i][temp] == 0){
            				T[i][j] = true;
            				Mat[i][j] = Mat[i][temp]+1;
            				op[i][j] = 0;
            				}	
            			}
            			}
            			//multiplication
            			if(input[i]!=0 && j%input[i] == 0 && T[i][j/input[i]] == true && op[i][j/input[i]] != 2){
            				int temp2 = Mat[i][j];
            				T[i][j] = true;
            				Mat[i][j] = min(Mat[i][j], Mat[i][j/input[i]]+2);
            				if(temp2 != Mat[i][j])
            				op[i][j] = 1;
            			}
            			//addition
            			if(T[i][j-input[i]] == true){
            				int temp3 = Mat[i][j];
            				T[i][j] = true;
            				Mat[i][j] = min(Mat[i][j], Mat[i][j-input[i]]+2);
            				if(temp3 != Mat[i][j])
            				op[i][j] = 2;
            			}
					}
				}	
			}
		}		


	int k = length-1;
	int l = number;
	

	output = Mat[k][l];
	
	return output;
 }

int main(int argc, char* argv[]){
    
    
    
    ifstream in(argv[1]);
    
    if(!in){
        cout<<"Cannot open  input file;"<<endl;
        return -1;
    }
    
    ofstream out(argv[2]);
    
    if(!out){
        cout<<"Cannot open  output file;"<<endl;
        return -1;
    }
int datasets; 
in>>datasets;

     
    
for(int i=0;i<datasets;i++)
{
    int N;
	in>>N;

    //out<<"------"<<N<<"-----"<<endl;
    
	int input1[N];
	for(int j=0;j<N;j++)
	{
		in>>input1[j];
	}

	sort(input1, input1 + N);

	int number;
	in>>number;
	//out<<"------"<<number<<"-----"<<endl;
        int output = expPuzzle(input1, number, N);
        if(output == 2*number+2)
        	out<<"N";
        else{
	        //out<<"------"<<output<<"-----"<<endl;
	        out<<output;
        }
        out<<endl;
}
    
    return 0;
}

   
  

    

    
  
    
    

